import re
import os
import json
import sys

sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '../../', '')))

def load_class(class_name: str) -> object:
    """Load the class with the given name

    Args:
        class_name (str): Name of the class to load

    Returns:
        object: Class object
    """
    
    from python_files.configuration_files.gemini_configure import GeminiModel
    from modules.angel_configure import GoogleSearch
    from modules.angel_configure import GoogleNews
    from modules.angel_configure import File
    from modules.angel_configure import Folder
    
    classes = {
        "GeminiModel": GeminiModel,
        "GoogleSearch": GoogleSearch,
        "GoogleNews": GoogleNews,
        "File": File,
        "Folder": Folder
    }
    
    instance = classes[class_name].__new__(classes[class_name])
    instance.__init__()
    
    return instance

def get_kb_name(prompt: str, gemini_model: object, model_name: str, kb_file: str = 'text_files/KB_files/1_kb.txt') -> str:
    """Get knowledge base name from the prompt response

    Args:
        prompt (str): Prompt to ask gemini
        gemini_model (object): Gemini model object
        model_name (str): Name of the model to use
        kb_file (str, optional): File to load knowledge base from. Defaults to 'text_files/KB_files/1_kb.txt'.

    Returns:
        str: Knowledge base name
    """

    with open(kb_file, 'r', encoding='utf-8') as kb:
        system_instruction = kb.read()

    gemini_model._set_model(model_name, system_instruction)
    responce = gemini_model._query_model(prompt)

    if (responce.startswith("```Sorry")):
        return ""

    kb_name = re.findall("kb ```kb_name (.*?)```", responce, re.DOTALL)[0]
    return kb_name

def get_kb_prompt(kb_name: str, kb_folder: str = "text_files/KB_files/") -> str:
    """Get knowledge base prompt from the knowledge base name

    Args:
        kb_name (str): Knowledge base name
        kb_folder (str, optional): Folder to load knowledge base from. Defaults to "text_files/KB_files/".

    Returns:
        str: Knowledge base prompt
    """
    
    with open(kb_folder + kb_name + "_kb.txt", 'r', encoding='utf8') as kb_file:
        kb = kb_file.read()
    
    return kb

def get_blocks(string_to_parse: str) -> tuple[list, list]:
    """Get Function and Parameter blocks

    Args:
        string_to_parse (str): String to parse

    Returns:
        tuple: Function and Parameter blocks
    """

    function_with_parameters = re.findall(r'use function ```(.*?)``` with parameters ```(.*?)```', string_to_parse, re.DOTALL)
    
    for function_with_parameter in function_with_parameters:
        string_to_parse = string_to_parse.replace(f'use function ```{function_with_parameter[0]}``` with parameters ```{function_with_parameter[1]}```', '')
    
    only_functions = re.findall(r'use function ```(.*?)```', string_to_parse, re.DOTALL)
    
    return function_with_parameters, only_functions

def parse_blocks(function_with_parameters: list, only_functions: list) -> None:
    """Parse Function and Parameter blocks and create a json file of steps

    Args:
        function_with_parameters (list): List of functions and parameters
        only_functions (list): List of functions
    """

    function_parameter = []
    
    if (function_with_parameters != []):
        for function_with_parameter in function_with_parameters:
            function_name, parameters = function_with_parameter[0], function_with_parameter[1].replace("parameters ", "")
            
            parameters = re.findall(r'\{ (.*?) \}', parameters)
            parameter_dict = {}
            for parameter in parameters:
                parameter_name, parameter_value = parameter.split(' = ')
                
                try:
                    parameter_dict[parameter_name] = int(parameter_value)
                except:
                    parameter_dict[parameter_name] = parameter_value
                
            f_p = {
                "function_name": function_name.replace("function_name ", ""),
                "parameters": parameter_dict
            }
            
            function_parameter.append(f_p)
        
    if (only_functions != []):
        for only_function in only_functions:
            f_p = {
                "function_name": only_function.replace("function_name ", ""),
                "parameters": {}
            }
            
            function_parameter.append(f_p)
        
    with open("json_files/query_steps.json", 'w', encoding='utf8') as query_steps:
        json.dump(function_parameter, query_steps, ensure_ascii=False, indent=4)

def sanitize_value(value: str) -> str:
    """Sanitize value

    Args:
        value (str): Value to sanitize

    Returns:
        str: Sanitized value
    """

    if isinstance(value, str) and value.startswith('"') and value.endswith('"'):
        return value[1:-1]
    
    return value

def execute_function(class_object: object, function_name: str, parameters: dict) -> None:
    """Execute function

    Args:
        class_object (object): object of class that contains the function
        function_name (str): Name of the function
        parameters (dict): Parameters of the function
    """
    
    sanitized_parameters = {param_name: sanitize_value(param_value) for param_name, param_value in parameters.items()}

    print(f"Function Name: {function_name}")
    print(f"Parameters: {sanitized_parameters}\n")

    if sanitized_parameters == {}:
        getattr(class_object, function_name)()
    else:
        args = list(sanitized_parameters.values())
        getattr(class_object, function_name)(*args)

def execute_functions(class_object: object, function_file: str = "json_files/query_steps.json") -> None:
    """Execute functions from the json file

    Args:
        class_object (object): object of class that contains the functions
        function_file (str, optional): File to load functions from. Defaults to "json_files/query_steps.json".
    """

    with open(function_file, 'r', encoding='utf8') as steps_file:
        steps = json.load(steps_file)
    
    for step in steps:
        function_name = step['function_name']
        parameters = step['parameters']

        execute_function(class_object, function_name, parameters)

if __name__ == "__main__":
    query = "Create file \"Hello.txt\" in \"text_files/\" and write \"hello\" in it"

    gemini = load_class("GeminiModel")
    kb_name = get_kb_name(query, gemini, "gemini-1.5-flash")

    gemini = load_class("GeminiModel")
    kb = get_kb_prompt(kb_name)
    gemini._set_model("gemini-1.5-flash", kb)

    response = gemini._query_model(query)

    print(response)
    parse_blocks(*get_blocks(response))

    class_object = load_class(kb_name)
    execute_functions(class_object)