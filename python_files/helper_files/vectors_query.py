import numpy
import sqlite3
from sentence_transformers import SentenceTransformer

def vectorize_text(texts: list, model: SentenceTransformer) -> list:
    """Vectorize the given text

    Args:
        text: The text to vectorize
        model: The model to use for vectorization

    Returns:
        The vectorized text
    """

    return model.encode(texts, show_progress_bar=True)

def create_db(table_name: str, db_name:str = "database_files/vectors.db") -> None:
    """Create the database

    Args:
        table_name: The name of the table to create
        db_name: The name of the database
    """

    conn = sqlite3.connect(db_name)
    cursor = conn.cursor()

    cursor.execute(f"""CREATE TABLE IF NOT EXISTS {table_name}(
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        text TEXT NOT NULL,
        vector BLOB NOT NULL
    )""")

    conn.commit()
    conn.close()

def store_vectors(vectors: list, texts: list, table_name: str, db_name: str = "database_files/vectors.db") -> None:
    """Store the vectors in the database

    Args:
        vectors: The vectors to store
        texts: The texts to store
        table_name: The name of the table to store the vectors in
        db_name: The name of the database
    """

    conn = sqlite3.connect(db_name)
    cursor = conn.cursor()

    for vector, text in zip(vectors, texts):
        cursor.execute(f"INSERT INTO {table_name} (text, vector) VALUES (?, ?)", (text, vector))

    conn.commit()
    conn.close()

def remove_data(table_name: str, db_name: str = "database_files/vectors.db") -> None:
    """Remove the data from the database

    Args:
        table_name: The name of the table to remove the data from
        db_name: The name of the database
    """

    conn = sqlite3.connect(db_name)
    cursor = conn.cursor()

    cursor.execute(f"DELETE FROM {table_name}")

    conn.commit()
    conn.close()

def cosine_similarity(vector1: list, vector2: list) -> float:
    """Calculate the cosine similarity between two vectors

    Args:
        vector1: The first vector
        vector2: The second vector

    Returns:
        The cosine similarity between the two vectors
    """

    return numpy.dot(vector1, vector2) / (numpy.linalg.norm(vector1) * numpy.linalg.norm(vector2))

def query_similar_results(query: str, model: SentenceTransformer, table_name: str, db_name: str = "database_files/vectors.db", top_k = 3) -> list:
    """Query the database table for similar results

    Args:
        query: The query to search for
        model: The model to use for vectorization
        table_name: The name of the table to search in
        db_name: The name of the database

    Returns:
        The similar results
    """

    query_vector = model.encode([query])[0]

    conn = sqlite3.connect(db_name)
    cursor = conn.cursor()

    cursor.execute(f"SELECT text, vector FROM {table_name}")

    all_results = []
    similarities = []

    for row in cursor.fetchall():
        text = row[0]
        vector_blob = row[1]
        
        vector = numpy.frombuffer(vector_blob, dtype=numpy.float32)

        similarity = cosine_similarity(query_vector, vector)
        all_results.append(text)
        similarities.append(similarity)
    
    conn.close()

    top_indices = numpy.argsort(similarities)[-top_k:][::-1]
    top_results = [all_results[i] for i in top_indices]

    return top_results