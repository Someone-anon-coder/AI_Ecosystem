import json

small_steps_prompt = ""

with open("json_files/helper_KB_files/get_small-steps.json", 'r', encoding='utf8') as small_steps_file:
    small_steps = json.load(small_steps_file)

small_steps_prompt = f"""{small_steps[0]['system_message']}

How to answer to user: {small_steps[0]['answer_format']}
If user ask anything unrelated to the knowledge base or something you cannot handle with given classes answer with: {small_steps[0]['cant_answer_format']}


Classes Available to you are:\n\n"""

for i in range(1, len(small_steps)):
    small_steps_prompt += f"""\tClass Name: {small_steps[i]['Class_Name']}
\tClass System Message: {small_steps[i]['Class_System_Message']}
\tClass Examples are: \n"""

    for example_query, example_answer in small_steps[i]['Class_Examples'].items():
        small_steps_prompt += f"""\t\tExample User Query: {example_query}
\t\tExample Answer: {example_answer}\n\n"""

    small_steps_prompt += "\n\n"

small_steps_prompt += "Examples:\n"
for user_query, answer in small_steps[0]['examples'].items():
    small_steps_prompt += f"\tUser Query: {user_query}\n\tAnswer: {answer}\n\n"

small_steps_prompt += small_steps[0]['Note']

with open("text_files/KB_files/get_small-steps_prompt.txt", 'w', encoding='utf8') as small_steps_file:
    small_steps_file.write(small_steps_prompt)