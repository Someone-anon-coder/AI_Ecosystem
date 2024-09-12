from modules.angel_configure import GoogleSearch

google = GoogleSearch()

json_file = "json_files/search_result.json"
google._search_google("Something", json_file)