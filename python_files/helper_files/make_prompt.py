import json

kb = "Folder"
knowledge_base = []

with open(f"json_files/KB_files/{kb}_kb.json", 'r', encoding='utf8') as kb_file:
    knowledge_base = json.load(kb_file)

system_message = f"""{knowledge_base[0]['system_message']}

How to specify functions: {knowledge_base[0]['function_format']}
How to specify paramters: {knowledge_base[0]['parameter_format']}

How to answer to user: {knowledge_base[0]['answer_format']}
If user ask anything unrelated to the knowledge base or something you cannot handle with given knowledge base answer with: {knowledge_base[0]['cant_answer_format']}
"""

system_message += "\n\nYou have been given the knowledge base below:\n"

function_para = ""
for i in range(1, len(knowledge_base)):
    function_para += f"""\t{i}: Function Name: {knowledge_base[i]['name']}
\tFunction Description: {knowledge_base[i]['description']}
\tFunction Parameters: """

    if knowledge_base[i]['parameters'] != {}:
        for para_name, para_description in knowledge_base[i]['parameters'].items():
            function_para += f"\n\t\t{para_name}: {para_description}"
    else:
        function_para += "No parameters for this function"
    
    function_para += f"\n\tFunction Returns: {knowledge_base[i]['returns']}\n\n"

system_message += function_para

examples = "\nExamples:\n"
for user_query, answer in knowledge_base[0]['examples'].items():
    examples += f"\tUser Query: {user_query}\n\tAnswer: {answer}\n\n"

system_message += examples + "\n"
system_message += knowledge_base[0]['Note']
system_message += f"\nIf you cannot answer a user based on the knowledge base then always respond with: {knowledge_base[0]['cant_answer_format']}"

with open(f"text_files/KB_files/{kb}_kb.txt", 'w', encoding='utf8') as kb_file:
    kb_file.write(system_message)