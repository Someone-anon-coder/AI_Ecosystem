import os
import json
import google.generativeai as genai

from typing import Any, Iterable, Mapping
from google.generativeai.types import HarmCategory, HarmBlockThreshold

class GeminiModel():
    """Class for querying gemini model
    """
    
    def __class_info__(self) -> dict:
        __name_discription__ = {"GeminiModel": "Class for querying gemini model"} # Name and description of the class
        __constuctor_paramters__ = {"Not used": "Not used"} # Constructor parameters of the class
        
        __function_info__ = { # Function names and their description
            "_query_model": "Query the model with the given query",
            "_get_available_models": "Get a list of available models",
            "_modify_safety_settings": "Change the safety settings of the model",
            "_get_current_configuration": "Get the current configuration of the model",
            "_set_configuration": "Set the configuration of the model",
            "_get_model": "Get the model object",
            "_set_model": "Set the model to use",
            "_load_history": "Load the history from the given file",
            "_clear_history": "Clear the history and save it to the given file"
        }
        
        __function_parameters__ = { # Function names and their parameter
            "_query_model": "query (str) <Required>\nverbose (bool)",
            "_get_available_models": "Not used",
            "_modify_safety_settings": "safety (HarmCategory.name) <Required>\nsetting (HarmBlockThreshold.name)",
            "_get_current_configuration": "Not used",
            "_set_configuration": "candidate_count (int | None)\nstop_sequences (Iterable[str] | None)\nmax_output_tokens (int | None)\ntemperature (float | None)\ntop_p (float | None)\ntop_k (int | None)\nresponse_mime_type (str | None)\nresponse_schema (Mapping[str, Any] | None)",
            "_get_model": "Not used",
            "_set_model": "model_name (str) <Required>\nsystem_message (str | None)\nsafety_settings (Mapping[HarmCategory: HarmBlockThreshold] | None)",
            "_load_history": "filename (str)",
            "_clear_history": "filename (str)"
        }
        
        __function_parameters_description__ = { # Function Parameter names and their description
            "_query_model": "query: Query to ask the model\nverbose: Include extra information with result",
            "_get_available_models": "Not used",
            "_modify_safety_settings": "safety: Harm category to change the safety settings of\nsetting: Block threshold to change the safety settings to",
            "_get_current_configuration": "Not used",
            "_set_configuration": "candidate_count: Number of candidates to return\nstop_sequences: Words to stop the generation\nmax_output_tokens: Maximum number of tokens to generate\ntemperature: Temperature of the generation\ntop_p: Top p of the generation\ntop_k: Top k of the generation\nresponse_mime_type: Mime type of the response\nresponse_schema: Schema of the response",
            "_get_model": "Not used",
            "_set_model": "model_name: Name of the model to use\nsystem_message: System message to use\nsafety_settings: Safety settings to use",
            "_load_history": "filename: Name of the file to load the history from",
            "_clear_history": "filename: Name of the file to save the history to"
        }
        
        __function_return_types__ = { # Function names and their return types
            "_query_model": "Query the model with the given query",
            "_get_available_models": "Get a list of available models",
            "_modify_safety_settings": "Change the safety settings of the model",
            "_get_current_configuration": "Get the current configuration of the model",
            "_set_configuration": "Set the configuration of the model",
            "_get_model": "Get the model object",
            "_set_model": "Set the model to use",
            "_load_history": "Load the history from the given file",
            "_clear_history": "Clear the history and save it to the given file"
        }
        
        return {
            "Name_Description": __name_discription__,
            "Constructor_Parameters": __constuctor_paramters__,
            "Function_Info": __function_info__,
            "Function_Parameters": __function_parameters__,
            "Parameter_Description": __function_parameters_description__,
            "Function_Return": __function_return_types__,
        }
        
    def __init__(self) -> None:
        """Initialize GeminiModel and configure model to use
        """
        
        self._model_name = "gemini-1.5-pro"
        self._context = "you are a helpful assistant"
        
        self._history = [{
            "Role": "SYSTEM:",
            "Content": self._context
        }]
        
        self._safety_settings = { # Default settings for gemini model
            HarmCategory.HARM_CATEGORY_DANGEROUS_CONTENT: HarmBlockThreshold.HARM_BLOCK_THRESHOLD_UNSPECIFIED,
            HarmCategory.HARM_CATEGORY_HARASSMENT: HarmBlockThreshold.HARM_BLOCK_THRESHOLD_UNSPECIFIED,
            HarmCategory.HARM_CATEGORY_HATE_SPEECH: HarmBlockThreshold.BLOCK_LOW_AND_ABOVE,
            HarmCategory.HARM_CATEGORY_SEXUALLY_EXPLICIT: HarmBlockThreshold.BLOCK_LOW_AND_ABOVE,
        }
        
        self.__configure_model()
        
        self._configuration = genai.GenerationConfig()
        self._model = genai.GenerativeModel(self._model_name, generation_config=self._configuration, system_instruction=self._context, safety_settings=self._safety_settings)
    
    def __get_previous_messages(self) -> str:
        """Get the previous messages in the history

        Returns:
            str: Previous messages in the history
        """
        
        history = ""
        
        self._history[0]['Content'] = self._context
        
        for message in self._history:
            history += f"{message['Role']}: {message['Content']}\n"
        
        return history

    def __save_history(self, filename: str="json_files/gemini_history.json") -> None:
        """Save the history to the given file

        Args:
            filename (str, optional): Name of the file to save the history to. Defaults to "json_files/gemini_history.json".
        """
        
        with open(filename, 'w', encoding='utf-8') as file:
            json.dump(self._history, file, ensure_ascii=False, indent=4)

    def __configure_model(self) -> None:
        """Load the API key from the .env file and configure the model
        """
        
        from dotenv import load_dotenv
        load_dotenv("secret_files/.env")
        
        genai.configure(api_key=os.getenv("GEMINI_API_KEY"))
    
    def _query_model(self, query: str, verbose: bool = False) -> str:
        """Query the model with the given query
        
        Args:
            query (str): Query to ask the model
            verbose (bool, optional): Include extra information with result. Defaults to False.

        Returns:
            str: Result of the query
        """
        
        history = self.__get_previous_messages()
        responce = self._model.generate_content(history + "\n\nUser:" + query)
        
        self._history.append({
            "Role": "USER:",
            "Content": query
        })
        self._history.append({
            "Role": "ASSISTANT:",
            "Content": responce.text
        })
        self.__save_history()
        
        return responce._result if verbose else responce.text
    
    def _get_available_models(self) -> list:
        """Get a list of available models

        Returns:
            list: List of available models
        """
        
        return [model.name for model in genai.list_models()]
    
    def _modify_safety_settings(self, safety: HarmCategory, setting: HarmBlockThreshold = HarmBlockThreshold.BLOCK_LOW_AND_ABOVE) -> None:
        """Change the safety settings of the model

        Args:
            safety (HarmCategory.name): Harm category to change the safety settings of
            setting (HarmBlockThreshold.name, optional): Block threshold to change the safety settings to. Defaults to HarmBlockThreshold.BLOCK_LOW_AND_ABOVE.
        """
        
        self._safety_settings[safety] = setting
        self._model._safety_settings = self._safety_settings
    
    def _get_current_configuration(self) -> object:
        """Get the current configuration of the model

        Returns:
            object: Current configuration of the model
        """
        
        return self._configuration
    
    def _set_configuration(
        self,
        candidate_count: int | None = None,
        stop_sequences: Iterable[str] | None = None,
        max_output_tokens: int | None = None,
        temperature: float | None = None,
        top_p: float | None = None,
        top_k: int | None = None,
        response_mime_type: str | None = None,
        response_schema: Mapping[str, Any] | None = None
    ) -> None:
        """Set the configuration of the model

        Args:
            candidate_count (int | None, optional): Number of candidates to return. Defaults to None.
            stop_sequences (Iterable[str] | None, optional): Words to stop the generation. Defaults to None.
            max_output_tokens (int | None, optional): Maximum number of tokens to generate. Defaults to None.
            temperature (float | None, optional): Temperature of the generation. Defaults to None.
            top_p (float | None, optional): Top p of the generation. Defaults to None.
            top_k (int | None, optional): Top k of the generation. Defaults to None.
            response_mime_type (str | None, optional): Mime type of the response. Defaults to None.
            response_schema (Mapping[str, Any] | None, optional): Schema of the response. Defaults to None.
        """
        
        self._configuration.candidate_count = candidate_count
        self._configuration.stop_sequences = stop_sequences
        self._configuration.max_output_tokens = max_output_tokens
        self._configuration.temperature = temperature
        self._configuration.top_p = top_p
        self._configuration.top_k = top_k
        self._configuration.response_mime_type = response_mime_type
        self._configuration.response_schema = response_schema
        
        self._model._generation_config = self._configuration
    
    def _get_model(self) -> genai.GenerativeModel:
        """Get the model object

        Returns:
            genai.GenerativeModel: Model object
        """
        
        return self._model

    def _set_model(self, model_name: str, system_message: str | None = None, safety_settings: dict | None = None) -> None:
        """Set the model to use

        Args:
            model_name (str): Name of the model to use
            system_message (str | None, optional): System message to use. Defaults to None.
            safety_settings (_type_, optional): Safety settings to use. Defaults to None.
        """
        
        self._model_name = model_name
        self._context = system_message if system_message is not None else self._context
        self._safety_settings = safety_settings if safety_settings is not None else self._safety_settings
        
        self._model = genai.GenerativeModel(model_name=self._model_name, safety_settings=self._safety_settings, system_instruction=self._context, generation_config=self._configuration)
    
    def _load_history(self, filename: str= "json_files/gemini_history.json") -> list:
        """Load the history from the given file

        Args:
            filename (str, optional): Name of the file to load the history from. Defaults to "json_files/gemini_history.json".

        Returns:
            list: History loaded from the file
        """
        
        with open(filename, 'r', encoding='utf-8') as file:
            history = json.load(file)
        
        return history
    
    def _clear_history(self, filename: str="json_files/gemini_history.json") -> None:
        """Clear the history and save it to the given file

        Args:
            filename (str, optional): Name of the file to save the history to. Defaults to "json_files/gemini_history.json".
        """
        
        with open(filename, 'w', encoding='utf-8') as file:
            json.dump([{"Role": "SYSTEM:", "Content": self._context}], file, ensure_ascii=False, indent=4)
        
        self._history = [{"Role": "SYSTEM:", "Content": self._context}]
        
if __name__ == "__main__":
    gemini = GeminiModel()
    
    gemini._set_model(model_name="gemini-1.5-flash", system_message="You are a helpful assistant")
    
    print(gemini._query_model("What is the meaning of life?"))