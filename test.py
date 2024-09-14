from modules.angel_configure import GoogleSearch

google = GoogleSearch()

google._search_google("Cat")
google._get_result(title = True, snippet = True)

print()
google._get_result(2, title = True, snippet = True)

print()
google._get_result(title = True, snippet = True, result_index = 3)