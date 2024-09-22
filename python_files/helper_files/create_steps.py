def get_blocks(string_to_parse: str):
    function_with_parameters = re.findall(r'use function ```(.*?)``` with parameters ```(.*?)```', string_to_parse, re.DOTALL)
    
    for function_with_parameter in function_with_parameters:
        string_to_parse = string_to_parse.replace(f'use function ```{function_with_parameter[0]}``` with parameters ```{function_with_parameter[1]}```', '')
    
    only_functions = re.findall(r'use function ```(.*?)```', string_to_parse, re.DOTALL)
    
    return function_with_parameters, only_functions

def parse_blocks(function_with_parameters, only_functions):
    function_parameter = []
    
    if (function_with_parameters != []):
        for function_with_parameter in function_with_parameters:
            function_name, parameters = function_with_parameter[0], function_with_parameter[1].replace("parameters ", "")
            
            parameters = re.findall(r'\{ (.*?) \}', parameters)
            parameter_dict = {}
            for parameter in parameters:
                parameter_name, parameter_value = parameter.split(' = ')
                
                parameter_dict[parameter_name] = parameter_value
                
            f_p = {
                "function_name": function_name,
                "parameters": parameter_dict
            }
            
            function_parameter.append(f_p)
        
    if (only_functions != []):
        for only_function in only_functions:
            f_p = {
                "function_name": only_function,
                "parameters": {}
            }
            
            function_parameter.append(f_p)
        
    with open("json_files/query_steps.json", 'w', encoding='utf8') as query_steps:
        json.dump(function_parameter, query_steps, ensure_ascii=False, indent=4)

if __name__ == "__main__":
    import re
    import os
    import sys
    import json
    
    sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '../../', '')))
    from python_files.configuration_files.gemini_configure import GeminiModel

    with open("text_files/KB_files/file_kb.txt", 'r', encoding= 'utf8') as kb_file:
        kb = kb_file.read()

    gemini = GeminiModel()
    gemini._set_model("gemini-1.5-flash", kb)

    query = "Create a file \"Hello.txt\" write \"Hello\" in it then create a file \"bye.txt\" write \"Bye\" in it and then delete both files."
    response = gemini._query_model(query)

    print(response)
    parse_blocks(*get_blocks(response))