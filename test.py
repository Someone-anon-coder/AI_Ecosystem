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

def create_db(db_name = "vectors.db") -> None:
    """Create the database

    Args:
        db_name: The name of the database
    """

    conn = sqlite3.connect(db_name)
    cursor = conn.cursor()

    cursor.execute("""CREATE TABLE IF NOT EXISTS Vectors(
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        text TEXT NOT NULL,
        vector BLOB NOT NULL
    )""")

    conn.commit()
    conn.close()

def store_vectors(vectors: list, texts: list, db_name = "vectors.db") -> None:
    """Store the vectors in the database

    Args:
        vectors: The vectors to store
        texts: The texts to store
        db_name: The name of the database
    """

    conn = sqlite3.connect(db_name)
    cursor = conn.cursor()

    for vector, text in zip(vectors, texts):
        cursor.execute("INSERT INTO Vectors (text, vector) VALUES (?, ?)", (text, vector))

    conn.commit()
    conn.close()

def remove_data(db_name = "vectors.db") -> None:
    """Remove the data from the database

    Args:
        db_name: The name of the database
    """

    conn = sqlite3.connect(db_name)
    cursor = conn.cursor()

    cursor.execute("DELETE FROM Vectors")

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

def query_similar_results(query, model, db_name = "vectors.db", top_k = 3):
    query_vector = model.encode([query])[0]

    conn = sqlite3.connect(db_name)
    cursor = conn.cursor()

    cursor.execute("SELECT text, vector FROM Vectors")

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

model = SentenceTransformer('sentence-transformers/all-MiniLM-L6-v2')
create_db()

texts = """
"Artificial Intelligence | CISA"
"CISA's whole-of-agency plan to: promote the beneficial uses of AI to enhance cybersecurity capabilities, ensure AI systems are protected from cyber-based ..."
"https://www.cisa.gov/ai"

"What Is AI in Cybersecurity?"
"AI-powered cybersecurity tools and systems have the ability to support providing even better data protection against threats by quickly recognizing behavior ..."
"https://www.sophos.com/en-us/cybersecurity-explained/ai-in-cybersecurity"

"AI and Cybersecurity: A New Era | Morgan Stanley"
"AI allows cybercriminals to automate many of the processes used in social-engineering attacks, as well as create more personalized, sophisticated and effective ..."
"https://www.morganstanley.com/articles/ai-cybersecurity-new-era"

"What Is AI for Cybersecurity? | Microsoft Security"
"AI for cybersecurity defined. AI for cybersecurity uses AI to analyze and correlate event and cyberthreat data across multiple sources, turning it into clear ..."
"https://www.microsoft.com/en-us/security/business/security-101/what-is-ai-for-cybersecurity"

"4 use cases for AI in cyber security"
"Apr 19, 2024 ... It's being used to analyze logs, predict threats, read source code, identify vulnerabilities and even to create or exploit vulnerabilities."
"https://www.redhat.com/en/blog/4-use-cases-ai-cyber-security"

"Artificial Intelligence (AI) Cybersecurity | IBM"
"IBM Security® provides transformative, AI-powered solutions that optimize analysts' time—by accelerating ai threat detection and mitigation, expediting ..."
"https://www.ibm.com/ai-cybersecurity"

"Ideas for AI in cybersecurity : r/cybersecurity"
"Jan 26, 2024 ... - User Behavior Analysis: use Ai to monitor and analyze user behavior patterns within a computer system, detecting anomalous activities that may ..."
"https://www.reddit.com/r/cybersecurity/comments/1abgm6g/ideas_for_ai_in_cybersecurity/"

"Artificial Intelligence in Cybersecurity | Balbix"
"AI enhances threat intelligence by analyzing large datasets in real time and providing predictive insights. This capability allows cybersecurity teams to ..."
"https://www.balbix.com/insights/artificial-intelligence-in-cybersecurity/"

"The intersection of cybersecurity and artificial intelligence | Security ..."
"Jan 15, 2024 ... AI has proven to be a valuable asset in the cybersecurity arsenal, but it is not a silver bullet. The cybersecurity landscape is dynamic, with ..."
"https://www.securitymagazine.com/articles/100312-the-intersection-of-cybersecurity-and-artificial-intelligence"

"A Primer On Artificial Intelligence And Cybersecurity"
"Sep 26, 2023 ... Artificial intelligence acts as a powerful catalyst and enabler for cybersecurity in our connected ecosystem."
"https://www.forbes.com/sites/chuckbrooks/2023/09/26/a-primer-on-artificial-intelligence-and-cybersecurity/"
""".split("\n\n")

vectorized_data = vectorize_text(texts, model)
store_vectors(vectorized_data, texts)

query = "Why is AI important in cybersecurity?"
results = query_similar_results(query, model, top_k=3)

for result in results:
    print(result, "\n\n")

remove_data()