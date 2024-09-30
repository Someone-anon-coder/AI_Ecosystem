from python_files.helper_files.create_steps import get_small_steps, small_step

while True:
    query = input("Enter your query: ")
    if query == "exit":
        break

    small_steps = get_small_steps(query)
    for step in small_steps:
        small_step(step)
    
    print()