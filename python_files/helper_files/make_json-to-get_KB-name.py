import os
import json

main_knowledge_base_file = "get_knowledge-base.json"
kb_directory = "json_files/KB_files"
kb_files = os.listdir(kb_directory)

main_kb = [{
    "system_message": "You are a helpful assisstant given to the user to aid with their tasks. You are provided to user as their PC asisstant for selecting a proper Knowledge Base according to user queries. Use the given classes to answer the user",
    "answer_format": "To do this use kb ```kb_name [kb_name]```",
    "cant_answer_format": "```Sorry, this knowledge base is not available yet```",
    "examples": {
        "Unhide a file \".test.txt\" in directory \"hidden_files\\test_files/\" and then move it to \"test_files/\"": "To unhide a file \".test.txt\" in directory \"hidden_files\\test_files/\" and then move it to \"test_files/\" use kb ```kb_name File```",
        "Turn off \"simplified chinese\" and search for \"Great wall of China\" but restrict results to past 2 years": "To turn off \"simplified chinese\" and search for \"Great wall of China\" but restrict results to past 2 years use kb ```kb_name GoogleSearch",
        "Change the response candidates to \"10\" and the temperature of the model to \"0.2\" and then say to \"gemini-pro-1.0\" \"Hello!\"": "To change the response candidates to \"10\" and the temperature of the model to \"0.2\" and then say to \"gemini-pro-1.0\" \"Hello!\" use kb ```kb_name GeminiModel",
        "Open camera and click \"5\" photos with a gap of \"3\" seconds each then open the photo": "```Sorry, this knowledge base is not available yet```",
        "Open word and create a \"blank\" document then write \"hello\" and close it without saving": "```Sorry, this knowledge base is not available yet```"
    },
    "Note": "Answer the query if and only if it can be done by the knowledge base of the classes available in your knowledge base. DO NOT create new knowledge bases to answer user query"
}]

for kb_file in kb_files:
    
    with open(f"{kb_directory}/{kb_file}", 'r', encoding='utf8') as knowledge_file:
        knowledge_base = json.load(knowledge_file)
    
    knowledge = {
        "Class_Name": kb_file.replace("_kb.json", ""),
        "Class_System_Message": knowledge_base[0]['system_message'],
        "Class_Examples": {},
        "Class_Functions": []
    }
    
    example_count = 0
    for example_user_query, example_answer in knowledge_base[0]['examples'].items():
        if example_count == 3:
            break
        
        knowledge['Class_Examples'][example_user_query] = example_answer
        example_count += 1
    
    for function in knowledge_base[1:]:
        parameters = []
        for parameter_name, _ in function['parameters'].items():
            parameters.append(parameter_name)
        
        knowledge['Class_Functions'].append({
            "Function_Name": function['name'],
            "Function_Description": function['description'],
            "Function_Parameters": parameters,
        })
        
    main_kb.append(knowledge)

with open(f"json_files/helper_KB_files/{main_knowledge_base_file}", 'w', encoding='utf8') as main_kb_file:
    json.dump(main_kb, main_kb_file, ensure_ascii=False, indent=4)