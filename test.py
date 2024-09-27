from python_files.helper_files.create_steps import load_class, get_kb_name, get_kb_prompt, get_blocks, parse_blocks, execute_functions

while True:
    query = input("Enter your query: ")
    if query == "exit":
        break

    gemini = load_class("GeminiModel")
    kb_name = get_kb_name(query, gemini, "gemini-1.5-flash")

    if kb_name == "":
        print("Sorry this knowledge base is not available yet")
        continue

    gemini = load_class("GeminiModel")
    kb = get_kb_prompt(kb_name)
    gemini._set_model("gemini-1.5-flash", kb)

    response = gemini._query_model(query)

    print(response, end="\n")
    parse_blocks(*get_blocks(response))

    class_object = load_class(kb_name)
    execute_functions(class_object)