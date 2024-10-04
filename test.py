from sentence_transformers import SentenceTransformer
from python_files.helper_files import create_steps, vectors_query

query_to_search = "AI as a tool in Cybersecurity"

query = f"search google for \"{query_to_search}\" and get me \"10\" results and get me title and snippet of all the results then create a file \"Hello.txt\""
small_steps = create_steps.get_small_steps(query)

for step in small_steps:
    create_steps.small_step(step)

model = SentenceTransformer('sentence-transformers/all-MiniLM-L6-v2')

try:
    with open("text_files/search_results.txt", 'r', encoding='utf8') as search_file:
        search_results = search_file.read().split("\n\n")

    search_vectors = vectors_query.vectorize_text(search_results, model)
    
    vectors_query.create_db("SearchResults")
    vectors_query.store_vectors(search_vectors, search_results, "SearchResults")
    
    results = vectors_query.query_similar_results(query_to_search, model, "SearchResults", top_k=5)
    vectors_query.remove_data("SearchResults")

    query_results = "\n\n".join(results)

    from python_files.configuration_files.gemini_configure import GeminiModel

    model = GeminiModel()
    model._set_model("gemini-1.5-flash", f"The google search found this: {query_results}")

    response = model._query_model(query_to_search)
    print(response)

except Exception as e:
    print(e)
