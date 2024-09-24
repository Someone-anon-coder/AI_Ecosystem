import re
import os
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
        "geminimodel": GeminiModel,
        "googlesearch": GoogleSearch,
        "googlenews": GoogleNews,
        "file": File,
        "folder": Folder
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

    kb_name = re.findall("kb ```kb_name (.*?)```", responce, re.DOTALL)[0]
    return kb_name

gemini = load_class("geminimodel")
kb_name = get_kb_name("Create file \"hello.txt\" and write \"hello\" in it then hide the file", gemini, "gemini-1.5-flash")
print(kb_name)

