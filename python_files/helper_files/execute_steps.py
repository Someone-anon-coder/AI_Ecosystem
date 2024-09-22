import os
import sys

sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '../../', '')))

def load_class(class_name: str) -> object:
    
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

if __name__ == "__main__":
    gemini = load_class("geminimodel")
    query = input("Enter your query:")
    
    
