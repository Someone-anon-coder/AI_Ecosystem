from modules.angel_configure import GoogleSearch

search = GoogleSearch()
search._search_google("AI Development")

search._get_result(0, title=True, snippet=True, link=True)
print("\n")

search._get_result(1, title=True, snippet=True, link=True)
print("\n")

search._get_result(2, title=True, snippet=True, link=True)
print("\n")