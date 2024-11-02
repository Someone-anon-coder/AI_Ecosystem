def create_system_message(model_type: str = "[to specify]", ex: dict = {}) -> dict:
    """Create system message for the model

    Args:
        model_type (str): Model type to use for the system message. Defaults to "[to specify]".
        ex (dict): Examples of user questions and their answers by the model. Defaults to {}.

    Returns:
        dict: System message for the model
    """
    
    system_message: str = f"You are a helpful assisstant given to the user to aid with their tasks. You are provided to user as their PC asisstant {model_type} according to user queries. Use the given knowledge base to answer the user." # System Message for the model
    function_format: str = "use function ```function_name [function_name]```" # Function creation format
    parameter_format: str = "with parameters ```parameters { parameter_1 = value_1 }, { parameter_2 = value_2 }, ..., { parameter_n = value_n }```" # Parameter assignment format
    answer_format: str = "To do this use function ```function_name [function_name]``` with parameters ```parameters { parameter_1 = value_1 }, { parameter_2 = value_2 }, ..., { parameter_n = value_n }```" # Answer format by the model
    cant_answer_format: str = "```Sorry, this query cannot be handled by me```" # Cant answer format by the model
    Note: str = "Answer the query if and only if it can be done by the functions available in your knowledge base. DO NOT create new functions or parameters to answer user query" # Extra instructions for the model
    
    examples = ex # Dictionary of example user questions and their answers by the model
    
    return { # System message for the model
        "system_message": system_message,
        "function_format": function_format,
        "parameter_format": parameter_format,
        "answer_format": answer_format,
        "cant_answer_format": cant_answer_format,
        "examples": examples,
        "Note": Note
    }

def create_function(function_name: str, function_description: str, parameters: tuple[dict, list] | None = None, returns: str = "None") -> dict:
    """Create function for the model

    Args:
        function_name (str): Name of the function
        function_description (str): Description of the function
        parameters (dict | None, optional): Parameters of the function. Defaults to None.
        returns (str, optional): Returns of the function. Defaults to "None".

    Returns:
        dict: Function for the model
    """
    
    if parameters[1] != []:
        function_description += ". The Parameters ["
        
        for para in parameters[1]:
            function_description += para.split(' ')[0] + ", " if para != parameters[1][-1] else para.split(' ')[0]
        
        function_description += "] are required"
        
    return {
        "name": function_name,
        "description": function_description,
        "parameters": parameters[0] if parameters[0] is not None else {},
        "returns": returns
    }

def create_parameter(paramters_disc: str, parameter_type: str) -> tuple[dict, list]:
    """Create parameter for the model

    Args:
        paramters_disc (str): Parameter discription in a function
        parameter_type (str): Parameter type in a function

    Returns:
        dict: Parameter for the model
        list: Required parameters for the model
    """
    
    parameters = {}
    required_parameters = []
    
    try: 
        parameters_in_disc = paramters_disc.split('\n')
    except ValueError:
        parameters_in_disc = parameter_disc
    
    try:
        parameters_in_type = parameter_type.split('\n')
    except ValueError:
        parameters_in_type = parameter_type
    
    for para_in_disc, para_in_type in zip(parameters_in_disc, parameters_in_type):
        if para_in_disc == "Not used":
            continue
        
        if " <Required>" in para_in_disc:
            required_parameters.append(para_in_disc.replace(" <Required>", "").strip())
        
        _, para_type = para_in_type.split(':')
        
        parameters[para_in_disc.replace(" <Required>", "").strip()] = "Specify this parameter to " + para_type.strip()
    
    return parameters, required_parameters
    
if __name__ == "__main__":
    import sys
    import os
    import json

    sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '../../', '')))

    from python_files.configuration_files.gemini_configure import GeminiModel
    # from modules.angel_configure import GoogleNews
    
    class_object = GeminiModel()
    
    knowledge_base = []
    class_info = class_object.__class_info__()
    
    class_name = list(class_info['Name_Description'].keys())[0]
    class_description = [description for _,description in class_info['Name_Description'].items()][0].replace("Class ", "")
    
    functions = class_info['Function_Info']
    return_types = class_info['Function_Return']
    examples = class_info['Class_Examples']
    
    knowledge_base.append(create_system_message(model_type=class_description, ex=examples))
    for function_name, function_description in functions.items():
    
        parameter_disc = class_info['Function_Parameters'][function_name]
        parameter_type = class_info['Parameter_Description'][function_name]
        return_type = return_types[function_name]
        
        knowledge_base.append(create_function(function_name=function_name, function_description=function_description, parameters=create_parameter(paramters_disc=parameter_disc, parameter_type=parameter_type), returns=return_type))
    
    with open(f'json_files/KB_files/{class_name}_kb.json', 'w', encoding='utf8') as kb_file:
        json.dump(knowledge_base, kb_file, ensure_ascii=False, indent=4)
