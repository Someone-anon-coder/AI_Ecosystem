import sys
import os
import json

sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '../../', '')))
from modules.angel_configure import GoogleNews

def create_system_message(model_type: str = "[to specify]", ex: dict = {}) -> dict:
    """Create system message for the model

    Args:
        model_type (str): Model type to use for the system message. Defaults to "[to specify]".
        ex (dict): Examples of user questions and their answers by the model. Defaults to {}.

    Returns:
        dict: System message for the model
    """
    
    system_message: str = f"You are a helpful assisstant given to the user to aid with their tasks. {model_type}. Use the given knowledge base to answer the user." # System Message for the model
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

def create_function(function_name: str, function_description: str, parameters: dict | None = None, returns: str = "None") -> dict:
    """Create function for the model

    Args:
        function_name (str): Name of the function
        function_description (str): Description of the function
        parameters (dict | None, optional): Parameters of the function. Defaults to None.
        returns (str, optional): Returns of the function. Defaults to "None".

    Returns:
        dict: Function for the model
    """
    
    return {
        "name": function_name,
        "description": function_description,
        "parameters": parameters if parameters is not None else {},
        "returns": returns
    }

def create_parameter(paramters_disc: str, parameter_type: str) -> dict:
    """Create parameter for the model

    Args:
        paramters_disc (str): Parameter discription in a function
        parameter_type (str): Parameter type in a function

    Returns:
        dict: Parameter for the model
    """
    
    parameters = {}
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
        
        _, para_type = para_in_type.split(':')
        
        parameters[para_in_disc.strip()] = "Specify this parameter to " + para_type.strip()
    
    return parameters
    
if __name__ == "__main__":
    google = GoogleNews()
    
    knowledge_base = []
    knowledge_base.append(create_system_message())
    
    functions = google.__class_info__()['Function_Info']
    return_types = google.__class_info__()['Function_Return']
    
    for function_name, function_description in functions.items():
    
        parameter_disc = google.__class_info__()['Function_Parameters'][function_name]
        parameter_type = google.__class_info__()['Parameter_Description'][function_name]
        return_type = return_types[function_name]
        
        knowledge_base.append(create_function(function_name=function_name, function_description=function_description, parameters=create_parameter(paramters_disc=parameter_disc, parameter_type=parameter_type), returns=return_type))
    
    with open('json_files/KB_files/news_kb.json', 'w', encoding='utf8') as kb_file:
        json.dump(knowledge_base, kb_file, ensure_ascii=False, indent=4)
