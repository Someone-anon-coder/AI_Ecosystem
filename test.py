from modules.angel_configure import GoogleSearch, File

file = File()
google = GoogleSearch()

json_directory = "json_files/"
json_file = "search_result.json"

file.create_file(json_file, json_directory)

google._search_google("Something", json_directory + json_file)