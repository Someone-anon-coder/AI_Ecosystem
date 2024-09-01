#include "../header_files/news_configure.h"

// Class Constructor
GoogleNews::GoogleNews(
    const std::string language, // Languge you want to get the news in
    const std::string country, // Country you want to get the news from
    const std::string period, // Time period to get news from
    const std::string start_date, // Starting date for when to get news from
    const std::string end_date, // Ending date for when to get the news till. End date should be atleast 1 day after start date
    const int max_results, // Max number of results to be returned for the news
    const std::vector<std::string> exclude_websites // Websites to exclude when searching for the news
){ // Initializes the GoogleNews class and sets the class variables
    this->_language = language;
    this->_country = country;
    this->_period = period;
    this->_start_date = start_date;
    this->_end_date = end_date;
    this->_max_results = max_results;
    this->_exclude_websites = exclude_websites;
}

// Class Destructor
GoogleNews::~GoogleNews(){}

// Class Functions
size_t GoogleNews::__WriteCallback(
    void* contents, // pointer to buffer containing the downloaded data
    size_t size, // size of the downloaded data
    size_t nmemb, // number of elements in the downloaded data
    void* userp // pointer to the user-defined data
) { // Callback function to handle the data received
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

bool GoogleNews::__contains(
    const std::vector<std::string>& vec, // Vector to search for the given value
    std::string value // Value to search for in the vector
) { // Checks if the given value is present in the vector
    std::unordered_set<std::string> set(vec.begin(), vec.end());
    return set.find(value) != set.end();
}

bool GoogleNews::__is_date_different(
    const int start_year, // Start year for news search
    const int start_month, // Start month for news search
    const int start_day, // Start day for news search
    const int end_year, // End year for news search 
    const int end_month, // End month for news search 
    const int end_day // End day for news search
) { // Checks if the start and end dates are different
    std::tm start_date = {0, 0, 0, start_day, start_month - 1, start_year - 1900};
    std::tm end_date = {0, 0, 0, end_day, end_month - 1, end_year - 1900};
    std::time_t start_time = std::mktime(&start_date);
    std::time_t end_time = std::mktime(&end_date);
    return difftime(end_time, start_time) >= 86400;
}

std::string GoogleNews::__url_parameters(){ // Crafts parameters to be included in the url for news search
    std::string time_query = "";
    if (this->_start_date != "" || this->_end_date != ""){
        if (this->_start_date != ""){
            time_query += "%20after%3A" + this->_start_date;
        }
        if (this->_end_date != ""){
            time_query += "%20before%3A" + this->_end_date;
        }
    } else if (this->_period != "anytime"){
        time_query += "%20when%3A" + this->_period;
    }
    std::string language = this->_language == "en" ? this->_language + "-US": this->_language;
    return time_query + 
        "&hl=" + language + 
        "&gl=" + this->_country +
        "&ceid=" + this->_country + ":" + this->_language;
}

std::string GoogleNews::__full_url(
    std::string keyword // Keyword used for searching the news
){ // Crafts the full url for news search
    std::string parameters = this->__url_parameters();
    
    return this->__news_url + "/search?q=" + keyword + parameters;
}

std::string GoogleNews::__get_rss_content(
    const std::string& url // URL for news search
) { // Function to request the URL and get the content
    CURL* curl;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, __WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return readBuffer;
}

std::vector<std::unordered_map<std::string, std::string>> GoogleNews::__parse_rss_content(
    const std::string& xmlContent // XML content to be parsed
) { // Function to parse the XML content
    int result = 1;
    
    using namespace tinyxml2;
    XMLDocument doc;
    doc.Parse(xmlContent.c_str());
    std::vector<std::unordered_map<std::string, std::string>> items;
    XMLElement* channel = doc.FirstChildElement("rss")->FirstChildElement("channel");
    for(XMLElement* item = channel->FirstChildElement("item"); item != nullptr; item = item->NextSiblingElement("item")) {
        if (result > this->_max_results) break;
        
        std::unordered_map<std::string, std::string> itemMap;
        XMLElement* titleElem = item->FirstChildElement("title");
        if(titleElem) itemMap["title"] = titleElem->GetText();
        XMLElement* linkElem = item->FirstChildElement("link");
        if(linkElem) itemMap["link"] = linkElem->GetText();
        XMLElement* pubDateElem = item->FirstChildElement("pubDate");
        if(pubDateElem) itemMap["pubDate"] = pubDateElem->GetText();
        XMLElement* descriptionElem = item->FirstChildElement("description");
        if(descriptionElem) itemMap["description"] = descriptionElem->GetText();
        XMLElement* sourceElem = item->FirstChildElement("source");
        if(sourceElem) {
            itemMap["source"] = sourceElem->GetText();
            const char* sourceUrl = sourceElem->Attribute("url");
            if (sourceUrl) itemMap["source_url"] = sourceUrl;
        }
        items.push_back(itemMap);
        result++;
    }
    return items;
}

void GoogleNews::__get_news(
    const std::string keyword, // query used to get news
    const std::string article_file // file to save articles in
){ // Function to get the news
    std::string query = this->__news_url + keyword + this->__url_parameters();
    std::cout << query << std::endl;
    std::string content = this->__get_rss_content(query);
    std::ofstream articles_file;
    auto items = this->__parse_rss_content(content);
    
    articles_file.open(article_file.c_str());
    
    for (const auto& item : items) {
        articles_file << "------------------------>>-->>" << std::endl;
        articles_file << "Title: " << item.at("title") << std::endl;
        articles_file << "Link: " << item.at("link") << std::endl;
        articles_file << "PubDate: " << item.at("pubDate") << std::endl;
        articles_file << "Description: " << item.at("description") << std::endl;
        articles_file << "Source: " << item.at("source") << std::endl;
        articles_file << "Source URL: " << item.at("source_url") << std::endl;
        articles_file << "<<--<<------------------------" << std::endl;
        articles_file << std::endl;
    }
    articles_file.close();
}

// Class Functions
// Getters

std::string GoogleNews::get_language(){ // Returns the languge in which news is presented
    return this->_language;
}

std::string GoogleNews::get_country(){ // Returns the country from which news is presented
    return this->_country;
}

std::string GoogleNews::get_period(){ // Returns the time period for when news is presented
    return this->_period;
}

std::string GoogleNews::get_start_date(){ // Returns the starting date for when news is presented
    return this->_start_date;
}

std::string GoogleNews::get_end_date(){ // Returns the ending date till when news is presented
    return this->_end_date;
}

int GoogleNews::get_max_results(){ // Returns the max number of results for the news
    return this->_max_results;
}

std::vector<std::string> GoogleNews::get_exclude_websites(){ // Returns the websites which are excluded when searching for the news
    return this->_exclude_websites;
}

void GoogleNews::get_news(
    const std::string keyword, // Keyword used to search news
    const std::string filename // File to save articles in
){ // Gets the news
    std::string query = "/search?q=" + keyword;
    this->__get_news(query, filename);
}

void GoogleNews::get_latest_topics(
    const std::string filename // File to save articles in
){ // Get news on latest topics
    this->__get_news("?", filename);
}

void GoogleNews::get_news_by_topic(
    const std::string topic, // Search the news on this topic
    const std::string filename // File to save articles in
){ // Gets the news on the given topic
    if (this->__contains(this->__available_topics, topic)){
        std::string query = "headlines/section/topic/" + topic + "?";
        this->__get_news(query, filename);
    }
}

void GoogleNews::get_news_by_country(
    const std::string country, // Search the news on this country
    const std::string filename // File to save articles in
){ // Gets the news on the given country
    if (this->__contains(this->__available_countries, country)){
        std::string query = "headlines/section/geo/" + country + "?";
        this->__get_news(query, filename);
    }
}

void GoogleNews::get_news_by_site(
    const std::string site, // Search the news on this site
    const std::string filename // File to save articles in
){ // Gets the news on the given site
    this->__get_news("site:" + site, filename);
}

// Setters
void GoogleNews::set_language(
    const std::string language // Languge you want to get the news in
){ // Sets the languge in which news is presented
    this->_language = language;
}

void GoogleNews::set_country(
    const std::string country // Country you want to get the news from
){ // Sets the country from which news is presented
    this->_country = country;
}

void GoogleNews::set_period(
    const std::string period // Time period to get news from
){ // Sets the time period for when news is presented
    this->_period = period;
}

bool GoogleNews::set_start_date(
    const std::string start_date // Starting date for when to get news from
){ // Sets the starting date for when news is presented. Format: YYYY-MM-DD
    this->_start_date = start_date;
    this->__start_year = std::stoi(start_date.substr(0, 4));
    this->__start_month = std::stoi(start_date.substr(5, 2));
    this->__start_day = std::stoi(start_date.substr(8, 2));
    return this->__is_date_different(
        this->__start_year,
        this->__start_month,
        this->__start_day,
        this->__end_year,
        this->__end_month,
        this->__end_day
    );
}

bool GoogleNews::set_end_date(
    const std::string end_date // Ending date till when news is presented
){ // Sets the ending date till when news is presented. Format: YYYY-MM-DD
    this->_end_date = end_date;
    this->__end_year = std::stoi(end_date.substr(0, 4));
    this->__end_month = std::stoi(end_date.substr(5, 2));
    this->__end_day = std::stoi(end_date.substr(8, 2));
    return this->__is_date_different(
        this->__start_year,
        this->__start_month,
        this->__start_day,
        this->__end_year,
        this->__end_month,
        this->__end_day
    );
}

void GoogleNews::set_max_results(
    const int max_results // Max number of results for the news
){ // Sets the max number of results for the news
    this->_max_results = max_results;
}

void GoogleNews::set_excluded_websites(
    std::vector<std::string> excluded_websites // Websites to exclude from the results
){ // Sets the websites to exclude from the results
    this->_exclude_websites = excluded_websites;
}