import json

main_knowledge_base_file = "json_files/KB_files/1_kb.json"
with open(main_knowledge_base_file, 'r', encoding='utf8') as main_kb_file:
    main_knowledge_base = json.load(main_kb_file)

main_prompt = f"""{main_knowledge_base[0]['system_message']}

How to answer to user: {main_knowledge_base[0]['answer_format']}
If user ask anything unrelated to the knowledge base or something you cannot handle with given classes answer with: {main_knowledge_base[0]['cant_answer_format']}


You have been given the Knowledge Base of Classes below:\n"""

for class_info in main_knowledge_base[1:]:
    main_prompt += f"""\tClass Name: {class_info['Class_Name']}
\tClass System Message: {class_info['Class_System_Message']}\n\n"""

    main_prompt += "\tClass Functions: \n"
    for function_info in class_info['Class_Functions']:
        main_prompt += f"""\t\t{function_info['Function_Name']}: {function_info['Function_Description']}\n"""

    main_prompt += "\n\tClass Examples: \n"
    for example_query, example_answer in class_info['Class_Examples'].items():
        main_prompt += f"""\t\tExample User Query: {example_query}
\t\tExample Answer: {example_answer}\n\n"""

    main_prompt += "\n\n"

main_prompt += "Examples:\n"
for user_query, answer in main_knowledge_base[0]['examples'].items():
    main_prompt += f"\tUser Query: {user_query}\n\tAnswer: {answer}\n\n"

main_prompt += main_knowledge_base[0]['Note']

with open("text_files/KB_files/1_kb.txt", 'w', encoding='utf8') as main_kb_file:
    main_kb_file.write(main_prompt)