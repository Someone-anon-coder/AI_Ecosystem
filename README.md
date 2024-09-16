## AI Ecosystem: A Framework for NLP-driven Task Completion

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

**Note:** AI Ecosystem is currently in its early stages of development, and the installation process is not yet finalized. This README will be updated with instructions once the project is more mature.

## Usage

The project has been updated to provide individual classes for specific tasks. You can now use these classes to perform their intended operations, such as file manipulation or performing Google searches. Below is a brief overview of the available classes and their usage:

### File Class
- Use the `File` class for file manipulation tasks like creating or reading files.
  
### GoogleSearch Class
- The `GoogleSearch` class allows you to perform searches on Google and store the results in a file.

### Example Usage

Here’s an example of how to use the `File` and `GoogleSearch` classes together:

```python
from modules.angel_configure import GoogleSearch, File

file = File()
google = GoogleSearch()

json_directory = "json_files/"
json_file = "search_result.json"

# Create a file to store the search result
file.create_file(json_file, json_directory)

# Perform a Google search and save the result in the created file
google._search_google("Something", json_directory + json_file)
```

In this example:
- A file is created in the specified directory using the `File` class.
- The `GoogleSearch` class is used to perform a Google search and store the search results in the created file.

**Note:** Further updates and instructions will be provided as the project evolves.

## Knowledge Base Structure

The core of AI Ecosystem's understanding and task execution lies in its knowledge bases. These are JSON files containing information about available functions and their parameters. Each function represents an action that can be performed, while parameters define the inputs required for that action.

Here's a snippet of a knowledge base (`file_kb.json`) for file manipulation:

```json
[
    {
        "system_message": "You are a helpful assisstant given to the user to aid with their tasks. Gemini. Use the given knowledge base to answer the user.",
        "function_format": "use function ```function_name [function_name]```",
        "parameter_format": "with parameters ```parameters { parameter_1 = value_1 }, { parameter_2 = value_2 }, ..., { parameter_n = value_n }```",
        "answer_format": "To do this use function ```function_name [function_name]``` with parameters ```parameters { parameter_1 = value_1 }, { parameter_2 = value_2 }, ..., { parameter_n = value_n }```",
        "cant_answer_format": "```Sorry, this query cannot be handled by me```",
        "examples": {},
        "Note": "Answer the query if and only if it can be done by the functions available in your knowledge base. DO NOT create new functions or parameters to answer user query"
    },
    {
        "name": "_check_file",
        "description": "Function to check if it is a file",
        "parameters": {
            "filename (str)": "Specify this parameter to Name of the file",
            "file_path (str)": "Specify this parameter to Path of the file"
        },
        "returns": "None"
    },
    {
        "name": "_copy_file",
        "description": "Function to copy a file",
        "parameters": {
            "filename (str)": "Specify this parameter to Name of the file",
            "new_path (str)": "Specify this parameter to New path of the file",
            "file_path (str)": "Specify this parameter to Path of the file"
        },
        "returns": "None"
    },
    {
        "name": "_create_file",
        "description": "Function to create a file",
        "parameters": {
            "filename (str)": "Specify this parameter to Name of the file",
            "file_path (str)": "Specify this parameter to Path of the file"
        },
        "returns": "None"
    },
    ...,
    {
        "name": "_write_file",
        "description": "Function to write to a file",
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

## Contributing

Contributions are welcome! If you're interested in contributing to the development of AI Ecosystem, please feel free to reach out to the project maintainers or submit a pull request.

## Disclaimer

This project is still under active development. Features and functionality may be subject to change. Right now Gemini API key is used for nlp to task convergence, but will change in the future to operate smaller local models to ensure privacy and latency free task completions

## Future Plans

- **Expansion of Model Capabilities**:  The project will continuously expand the capabilities of its models to handle a broader range of tasks and scenarios.
- **Integration with External APIs**:  Integration with external APIs will enhance the project's ability to interact with real-world data and systems.
- **User-Friendly Interface**:  The project will strive to provide a user-friendly interface for interacting with the system and specifying tasks.

We believe AI Ecosystem has the potential to revolutionize how humans interact with computers, enabling seamless automation of complex tasks through natural language. 
