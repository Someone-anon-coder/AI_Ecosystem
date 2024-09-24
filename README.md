# AI Ecosystem: A Framework for NLP-driven Task Completion

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

## Description

AI Ecosystem is an evolving project that aims to build a hierarchical model structure capable of efficiently completing human-like tasks on a computer using natural language processing (NLP). It tackles the challenge of bridging the gap between complex human instructions and automated task execution by developing a system that understands, interprets, and translates natural language commands into actionable steps.

## Features

- **Hierarchical Model Structure**:  The project is structured as a hierarchy of models, allowing for increasingly complex tasks to be broken down into smaller, more manageable subtasks.
- **Natural Language Understanding**:  Models are trained to understand natural language instructions, including nuances, context, and implicit information.
- **Task Decomposition**:  Complex tasks are automatically decomposed into a series of smaller, executable steps.
- **Multi-Modal Capabilities**:  The system will eventually support interaction with various data sources and interfaces, including files, websites, and APIs.
- **Modular Design**: The project is designed to be modular, allowing for easy addition and customization of new models and task functionalities.

## Installation

### First Instruction For Installation

- **Set up the Environment**
  - Clone this repository using: ```bash git clone https://github.com/Someone-anon-coder/AI_Ecosystem.git```
  - Create virtual environment using: ```python3 -m venv [virtual_env_name]``` eg: `AI_Ecosystem`
  - Activate the virtual environment using: ```bash source [virutal_env_name/bin/activate]``` eg: `source AI_Ecosystem/bin/activate`
  - Download the necessary python libraries using: ```pip install -r support_files/requirements.txt```
  - Download the necessary cpp libraries using: ```bash sudo apt update && sudo xargs -a support_files/requirements_c.txt apt install -y``` Note: you need to be Administrater

- **Get `GEMINI_API_KEY`**
  - Log in to google ai studio
  - Get a new api key
  - Create a new folder `secret_files`
  - Create a new file `.env` in the `secret_files` folder
  - Write `GEMINI_API_KEY=` in the `.env` file and paste your API key

- Update the `test.py` file to execute the appropriate commands

**Note:** AI Ecosystem is currently in its early stages of development, and the installation process is not yet finalized. This README will be updated with instructions once the project is more mature.

## Usage

The project has been updated to provide individual classes for specific tasks. You can now use these classes to perform their intended operations, such as file manipulation or performing Google searches. Below is a brief overview of the available classes and their usage:

### First Usage Example

```python

from create_steps import load_class, get_kb_name, get_kb_prompt, get_blocks, parse_blocks, execute_functions

query = "Create a folder \"Something\\\""

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

```

This example creates a folder Something in your current directory. If you want to do something else using other classes, just change the query.

**Note:** Further updates and instructions will be provided as the project evolves.

## Knowledge Base Structure

The core of AI Ecosystem's understanding and task execution lies in its knowledge bases. These are JSON files containing information about available functions and their parameters. Each function represents an action that can be performed, while parameters define the inputs required for that action.

Here's a snippet of a knowledge base (`file_kb.json`) for file manipulation:

```json
[
    {
        "system_message": "You are a helpful assisstant given to the user to aid with their tasks. You are provided to user as their PC asisstant for file manipulation according to user queries. Use the given knowledge base to answer the user.",
        "function_format": "use function ```function_name [function_name]```",
        "parameter_format": "with parameters ```parameters { parameter_1 = value_1 }, { parameter_2 = value_2 }, ..., { parameter_n = value_n }```",
        "answer_format": "To do this use function ```function_name [function_name]``` with parameters ```parameters { parameter_1 = value_1 }, { parameter_2 = value_2 }, ..., { parameter_n = value_n }```",
        "cant_answer_format": "```Sorry, this query cannot be handled by me```",
        "examples": {
            "Create file \"hello.txt\" and write \"hello\" in it then hide the file": "To create a file \"hello.txt\" and write \"hello\" in it then hide a file use function ```function_name _create_file``` with parameters ```parameters { filename = \"hello.txt\" }``` then use function ```function_name _write_file``` with parameters ```parameters { filename = \"hello.txt\" }, { content = \"hello\" }``` then use function ```function_name _hide_file``` with parameters ```parameters { filename = \"hello.txt\" }",
            "Unhide a file \".test.txt\" in directory \"hidden_files\\test_files\\\" and then move it to \"test_files\\\"": "To unhide a file \".test.txt\" in directory \"hidden_files\\test_files\\\" and then move it to \"test_files\\\" use function ```function_name _unhide_file``` with parameters ```parameters { filename = \".test.txt\" }, { file_path = \"hidden_files\\test_files\\\" }``` then use function ```function_name _move_file``` with parameters ```parameters { filename = \"test.txt\" }, { new_path = \"test_files\\\" }, { file_path = \"hidden_files\\test_files\\\" }, { new_path = \"test_files\\\" }```",
            "Create a file \"pass.csv\" then write \"user, pass\\nabc, test\" in it and then move it to \"secret_files\\\" then hide it": "to create a file \"pass.csv\" then write \"user, pass\\nabc, test\" in it and then move it to \"secret_files\\\" then hide it use function ```function_name _create_file``` with parameters ```parameters { filename = \"pass.csv\" }``` then use function ```function_name _write_file``` with parameters ```parameters { filename = \"pass.csv\" }, { content = \"user, pass\\nabc, test\" }``` then use ```function_name _move_file``` with parameters ```parameters { filename = \"pass.csv\" }, { new_path = \"secret_files\\\" }``` then use function ```function_name _hide_file``` with parameters ```parameters { filename = \"pass.csv\" }, { file_path = \"secret_files\\\" }```",
            "Set model to \"gemini-1.5-pro\" and set system instruction to \"You are a great philosopher\" and then query it \"Meaning of life\" and then clear the conversation history": "```Sorry, this query cannot be handled by me```",
            "list folder \"Passwords\" and then copy it to \"Nothing\\\" then delete it": "```Sorry, this query cannot be handled by me```"
        },
        "Note": "Answer the query if and only if it can be done by the functions available in your knowledge base. DO NOT create new functions or parameters to answer user query"
    },
    {
        "name": "_check_file",
        "description": "Function to check if it is a file. The Parameters [filename] are required",
        "parameters": {
            "filename (str)": "Specify this parameter to Name of the file",
            "file_path (str)": "Specify this parameter to Path of the file"
        },
        "returns": "None"
    },
    {
        "name": "_copy_file",
        "description": "Function to copy a file. The Parameters [filename, new_path] are required",
        "parameters": {
            "filename (str)": "Specify this parameter to Name of the file",
            "new_path (str)": "Specify this parameter to New path of the file",
            "file_path (str)": "Specify this parameter to Path of the file"
        },
        "returns": "None"
    },
    ...,
    {
        "name": "_write_file",
        "description": "Function to write to a file. The Parameters [filename] are required",
        "parameters": {
            "filename (str)": "Specify this parameter to Name of the file",
            "content (str)": "Specify this parameter to Content of the file",
            "file_path (str)": "Specify this parameter to Path of the file"
        },
        "returns": "None"
    }
]
```

This structure provides a clear and organized way for the system to understand and execute commands related to file operations.

## Main Prompt System Message

```json
    {
        "system_message": "You are a helpful assisstant given to the user to aid with their tasks. You are provided to user as their PC asisstant for selecting a proper Knowledge Base according to user queries. Use the given classes to answer the user",
        "answer_format": "To do this use kb ```kb_name [kb_name]```",
        "cant_answer_format": "```Sorry, this knowledge base is not available yet```",
        "examples": {
            "Unhide a file \".test.txt\" in directory \"hidden_files\\test_files\\\" and then move it to \"test_files\\\"": "To unhide a file \".test.txt\" in directory \"hidden_files\\test_files\\\" and then move it to \"test_files\\\" use kb ```kb_name File```",
            "Turn off \"simplified chinese\" and search for \"Great wall of China\" but restrict results to past 2 years": "To turn off \"simplified chinese\" and search for \"Great wall of China\" but restrict results to past 2 years use kb ```kb_name GoogleSearch",
            "Change the response candidates to \"10\" and the temperature of the model to \"0.2\" and then say to \"gemini-pro-1.0\" \"Hello!\"": "To change the response candidates to \"10\" and the temperature of the model to \"0.2\" and then say to \"gemini-pro-1.0\" \"Hello!\" use kb ```kb_name GeminiModel",
            "Open camera and click \"5\" photos with a gap of \"3\" seconds each then open the photo": "```Sorry, this knowledge base is not available yet```",
            "Open word and create a \"blank\" document then write \"hello\" and close it without saving": "Sorry, this knowledge base is not available yet```"
        },
        "Note": "Answer the query if and only if it can be done by the knowledge base of the classes available in your knowledge base. DO NOT create new knowledge bases to answer user query"
    },
```

This json object describes the prompt to be given to AI for it to decide which knowledge base to use according to user query.

## Contributing

Contributions are welcome! If you're interested in contributing to the development of AI Ecosystem, please feel free to reach out to the project maintainers or submit a pull request.

## Disclaimer

This project is still under active development. Features and functionality may be subject to change. Right now Gemini API key is used for nlp to task convergence, but will change in the future to operate smaller local models to ensure privacy and latency free task completions

## Future Plans

- **Expansion of Model Capabilities**:  The project will continuously expand the capabilities of its models to handle a broader range of tasks and scenarios.
- **Integration with External APIs**:  Integration with external APIs will enhance the project's ability to interact with real-world data and systems.
- **User-Friendly Interface**:  The project will strive to provide a user-friendly interface for interacting with the system and specifying tasks.

We believe AI Ecosystem has the potential to revolutionize how humans interact with computers, enabling seamless automation of complex tasks through natural language.
