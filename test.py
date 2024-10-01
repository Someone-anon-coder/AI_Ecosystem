import nltk
from nltk.corpus import stopwords
from nltk.tokenize import word_tokenize
from nltk.stem import WordNetLemmatizer
from sklearn.feature_extraction.text import TfidfVectorizer
import sqlite3

def get_content(file: str) -> str:
    """Get the content of the given file

    Args:
        file (str): Path to the file

    Returns:
        str: Content of the file
    """


    with open(file, 'r', encoding='utf-8') as f:
        content = f.read()
    
    return content

def preprocess_text(text) -> list:
    """Preprocess the given text

    Args:
        text (str): Text to preprocess

    Returns:
        list: Preprocessed text
    """

    tokens = word_tokenize(text.lower())

    stop_words = set(stopwords.words('english'))
    filtered_tokens = [token for token in tokens if token.isalnum() and token not in stop_words]

    lemmatizer = WordNetLemmatizer()
    lemmatized_tokens = [lemmatizer.lemmatize(token) for token in filtered_tokens]

    return lemmatized_tokens

def vectorize_text(processed_text: list) -> tuple:
    """Vectorize the given texts

    Args:
        texts (list): Texts to vectorize

    Returns:
        tuple: Vectorized texts and the vectorizer used
    """

    vectorizer = TfidfVectorizer()
    vectors = vectorizer.fit_transform([' '.join(processed_text)])

    return vectors, vectorizer

def connect_upload_vectors(database_name: str, vectorizer: TfidfVectorizer, vectors: list):
    conn = sqlite3.connect(database_name)
    cursor = conn.cursor()

    cursor.execute("""
    CREATE TABLE IF NOT EXISTS vectors(
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        word TEXT,
        vector BLOB
    )
    """)

    words = vectorizer.get_feature_names_out()
    for word, vector in zip(words, vectors.toarray()[0]):
        cursor.execute("INSERT INTO vectors (word, vector) VALUES (?, ?)", (word, vector))

    conn.commit()
    conn.close()