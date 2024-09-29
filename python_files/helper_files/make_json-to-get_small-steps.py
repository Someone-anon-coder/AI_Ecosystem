import os
import json

json_file = "get_small-steps.json"
KB_files = os.listdir("json_files/KB_files")

system_message = "You are a helpful assisstant given to the user to aid with their tasks. You are given a knowledge base of available classes to create small steps for the complex instruction you are provided. Use the given classes to answer the user"
answer_format = "To do this use step ```steps { step_1 }, { step_2 }, ..., { step_n }```"
cant_answer_format = "```Sorry, this instruction cannot be handled yet```"

examples = {
    "Create a folder \"Test_1/\" in the \"Testing/\" folder then create a file \"Test_253.txt\" in the \"Test_1/\" folder and hide the \"Test/\" folder": "To create a folder \"Test_1/\" in the \"Testing/\" folder then create a file \"Test_253.txt\" in the \"Test_1/\" folder and hide the \"Test/\" folder use step ```steps { Create a folder \"Test_1/\" in the \"Testing/\" folder }, { create a file \"Test_253.txt\" in the \"Testing/Test_1/\" folder }, { hide the \"Test/\" folder in the \"Testing/\" folder }```",
    "Create a file \"search_results.txt\" then search for \"AI Developement\" and get me 5 results and save the results in the \"search_results.txt\" file then search news for \"Climate Change\" between \"2015-01-01\" and \"2020-12-12\" and get me news in japanese": "To Create a file \"search_results.txt\" then search for \"AI Developement\" and get me 5 results and save the results in the \"search_results.txt\" file then search news for \"Climate Change\" between \"2015-01-01\" and \"2020-12-12\" and get me news in japanese use step ```steps { Create a file \"search_results.txt\" }, { search for \"AI Developement\" and get me 5 results and save the results in the \"search_results.txt\" file }, { Search news for \"Climate Change\" between \"2015-01-01\" and \"2020-12-12\" and get me news in japanese }```",
    "Create a file \"Hello.txt\" then ask gemini model \"gemini-1.5-pro\" about \"Meaning of life\" then move the file \"Hello.txt\" to folder \"Greetings/\" and hide the file \"Hello.txt\" then delete the folder \"Greetings/\"": "To Create a file \"Hello.txt\" then ask gemini model \"gemini-1.5-pro\" about \"Meaning of life\" then move the file \"Hello.txt\" to folder \"Greetings/\" and hide the file use step ```steps { Create a file \"Hello.txt\" }, { Ask gemini model \"gemini-1.5-pro\" about \"Meaning of life\" }, { move the file \"Hello.txt\" to folder \"Greetings/\" and hide the file \"Hello.txt\" }, { Delete the folder \"Greetings/\" }```",
    "Open camera and click \"5\" photos with a gap of \"3\" seconds then open word and write \"Latest Photos\" then get the \"5\" lastest photos and paste them in the document": "```Sorry, this instruction cannot be handled yet```",
    "Open browser and visit \"google.com\" then search for \"Advantages of AI\" then take a screenshot of the \"screen\" and save in \"~/Documents\" folder": "```Sorry, this instruction cannot be handled yet```"
}

KB = [{
    "system_message": system_message,
    "answer_format": answer_format,
    "cant_answer_format": cant_answer_format,
    "examples": examples,
    "Note": "Answer the query if and only if it can be done by the knowledge base of the classes available in your knowledge base. DO NOT create new knowledge bases to answer user query"
}]

for kb_file in KB_files:
    with open(f"json_files/KB_files/{kb_file}", 'r', encoding='utf8') as knowledge_file:
        knowledge_base = json.load(knowledge_file)
    
    knowledge = {
        "Class_Name": kb_file.replace("_kb.json", ""),
        "Class_System_Message": knowledge_base[0]['system_message'],
        "Class_Examples": {},
    }

    example_count = 0
    for user_query, answer in knowledge_base[0]['examples'].items():
        if example_count == 3:
            break
        
        if not answer.startswith("```Sorry"):
            knowledge['Class_Examples'][user_query] = answer
            example_count += 1

    KB.append(knowledge)

with open(f"json_files/helper_KB_files/{json_file}", 'w', encoding='utf8') as json_file:
    json.dump(KB, json_file, ensure_ascii=False, indent=4)