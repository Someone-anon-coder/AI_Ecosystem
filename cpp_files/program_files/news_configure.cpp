#include "../header_files/news_configure.h"
#include <iostream>
#include <string>

GoogleNews::GoogleNews(
    const std::string language = "en", // Languge you want to get the news in
    const std::string country = "US", // Country you want to get the news from
    const std::string period = "anytime", // Time period to get news from
    const std::string start_date = "", // Starting date for when to get news from
    const std::string end_date = "", // Ending date for when to get the news till. End date should be atleast 1 day after start date
    const int max_results = 10, // Max number of results to be returned for the news
    const std::vector<std::string> exclude_websites = {} // Websites to exclude when searching for the news
){
    this->_language = language;
    this->_country = country;
    this->_period = period;
    this->_start_date = start_date;
    this->_end_date = end_date;
    this->_max_results = max_results;
    this->_exclude_websites = exclude_websites;
}

GoogleNews::~GoogleNews(){
    this->_language = "";
    this->_country = "";
    this->_period = "";
    this->_start_date = "";
    this->_end_date = "";
    this->_max_results = 10;
    this->_exclude_websites = {};
}

std::map<std::string, std::map<std::string, std::string>> GoogleNews::__class_info__(){
    std::map<std::string, std::string> __name_discription__ = { // Name and description of the class
        {"GoogleNews", "Class for searching news on Google News"}
    };

    std::map<std::string, std::string> __constuctor_paramters__ = { // Constructor paramter names and descriptions
        {"language", "Languge you want to get the news in"},
        {"country", "Country you want to get the news from"},
        {"period", "Time period to get news from"},
        {"start_date", "Starting date for when to get news from"},
        {"end_date", "Ending date for when to get the news till. End date should be atleast 1 day after start date"},
        {"max_results", "Max number of results to be returned for the news"},
        {"exclude_websites", "Websites to exclude when searching for the news"}
    };

    std::map<std::string, std::string> __function_info__ = { // Function names and descriptions
        {"_get_language", "Function to get the language"},
        {"_get_country", "Function to get the country"},
        {"_get_period", "Function to get the period"},
        {"_get_start_date", "Function to get the start date"},
        {"_get_end_date", "Function to get the end date"},
        {"_get_max_results", "Function to get the max results"},
        {"_get_exclude_websites", "Function to get the excluded websites"},
        {"_get_news", "Function to get the news"},
        {"_get_latest_topics", "Function to get the news on latest topics"},
        {"_get_news_by_topic", "Function to get the news on the given topic"},
        {"_get_news_by_country", "Function to get the news on the given country"},
        {"_get_news_by_site", "Function to get the news from the given site"},
        {"_set_language", "Function to set the language"},
        {"_set_country", "Function to set the country"},
        {"_set_period", "Function to set the time period"},
        {"_set_start_date", "Function to set the start date"},
        {"_set_end_date", "Function to set the end date"},
        {"_set_max_results", "Function to set the max results"},
        {"_set_excluded_websites", "Function to set the excluded websites"}
    };

    std::map<std::string, std::string> __function_parameters__ = { // Function names and parameters
        {"_get_language", "Not used"},
        {"_get_country", "Not used"},
        {"_get_period", "Not used"},
        {"_get_start_date", "Not used"},
        {"_get_end_date", "Not used"},
        {"_get_max_results", "Not used"},
        {"_get_exclude_websites", "Not used"},
        {"_get_news", "keyword (str) <Required>\nfilename (str)"},
        {"_get_latest_topics", "filename (str)"},
        {"_get_news_by_topic", "topic (str) <Required>\nfilename (str)"},
        {"_get_news_by_country", "country (str) <Required>\nfilename (str)"},
        {"_get_news_by_site", "site (str) <Required>\nfilename (str)"},
        {"_set_language", "language (str) <Required>"},
        {"_set_country", "country (str) <Required>"},
        {"_set_period", "period (str) <Required>"},
        {"_set_start_date", "start_date (str) <Required>"},
        {"_set_end_date", "end_date (str) <Required>"},
        {"_set_max_results", "max_results (int) <Required>"},
        {"_set_excluded_websites", "excluded_websites (list) <Required>"}
    };

    std::map<std::string, std::string> __function_parameters_description__ = { // Function names, parameters and descriptions
        {"_get_language", "Not used"},
        {"_get_country", "Not used"},
        {"_get_period", "Not used"},
        {"_get_start_date", "Not used"},
        {"_get_end_date", "Not used"},
        {"_get_max_results", "Not used"},
        {"_get_exclude_websites", "Not used"},
        {"_get_news", "keyword: Keyword used to search news\nfilename: File to save articles in"},
        {"_get_latest_topics", "filename: File to save articles in"},
        {"_get_news_by_topic", "topic: Search the news on this topic\nfilename: File to save articles in"},
        {"_get_news_by_country", "country: Search the news on this country\nfilename: File to save articles in"},
        {"_get_news_by_site", "site: Search the news from this site\nfilename: File to save articles in"},
        {"_set_language", "language: Languge you want to get the news in"},
        {"_set_country", "country: Country you want to get the news from"},
        {"_set_period", "period: Time period to get news from"},
        {"_set_start_date", "start_date: Starting date for when to get news from"},
        {"_set_end_date", "end_date: Ending date till when news is presented"},
        {"_set_max_results", "max_results: Max number of results for the news"},
        {"_set_excluded_websites", "excluded_websites: Websites to exclude from the results"}
    };

    std::map<std::string, std::string> __function_return_types__ = { // Function names and return types
        {"_get_language", "String of the language"},
        {"_get_country", "String of the country"},
        {"_get_period", "String of the period"},
        {"_get_start_date", "String of the date"},
        {"_get_end_date", "String of the date"},
        {"_get_max_results", "Number of max results"},
        {"_get_exclude_websites", "Vector of excluded websites"},
        {"_get_news", "None"},
        {"_get_latest_topics", "None"},
        {"_get_news_by_topic", "None"},
        {"_get_news_by_country", "None"},
        {"_get_news_by_site", "None"},
        {"_set_language", "None"},
        {"_set_country", "None"},
        {"_set_period", "None"},
        {"_set_start_date", "True if start date and end date are different"},
        {"_set_end_date", "True if start date and end date are different"},
        {"_set_max_results", "None"},
        {"_set_excluded_websites", "None"}
    };

    return { // Vector of maps containing the class information
        {"Name_Description", __name_discription__},
        {"Constructor_Parameters", __constuctor_paramters__},
        {"Function_Info", __function_info__},
        {"Function_Parameters", __function_parameters__},
        {"Parameter_Description", __function_parameters_description__},
        {"Function_Return", __function_return_types__}
    };
}

void GoogleNews::__log__(
    const std::string content // Content to write to log file
){
    std::ifstream previous_log_file; // File object to read from the previous log file
    previous_log_file.open(this->_log_filename);

    std::string previous_content((std::istreambuf_iterator<char>(previous_log_file)), std::istreambuf_iterator<char>()); // Content from the previous log file
    previous_log_file.close();

    std::ofstream new_log_file; // File object to write the new log file
    new_log_file.open(this->_log_filename);

    previous_content += content + "\n";
    new_log_file << previous_content;

    new_log_file.close();
}

size_t GoogleNews::__WriteCallback(
    void* contents, // pointer to buffer containing the downloaded data
    size_t size, // size of the downloaded data
    size_t nmemb, // number of elements in the downloaded data
    void* userp // pointer to the user-defined data
) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

bool GoogleNews::__contains(
    const std::vector<std::string>& vec, // Vector to search for the given value
    std::string value // Value to search for in the vector
) {
    std::unordered_set<std::string> set(vec.begin(), vec.end()); // Unordered set to remove duplicates
    return set.find(value) != set.end();
}

bool GoogleNews::__is_date_different(
    const int start_year, // Start year for news search
    const int start_month, // Start month for news search
    const int start_day, // Start day for news search
    const int end_year, // End year for news search 
    const int end_month, // End month for news search 
    const int end_day // End day for news search
) {
    std::tm start_date = {0, 0, 0, start_day, start_month - 1, start_year - 1900}; // Start date format
    std::tm end_date = {0, 0, 0, end_day, end_month - 1, end_year - 1900}; // End date format
    
    std::time_t start_time = std::mktime(&start_date); // Start time
    std::time_t end_time = std::mktime(&end_date); // End time
    
    return difftime(end_time, start_time) >= 86400;
}

std::string GoogleNews::__url_parameters(){
    std::string time_query = ""; // Stores period if start date and end date are not given, else them
    
    if (this->_start_date != "" || this->_end_date != ""){
        if (this->_start_date != ""){
            time_query += " after:" + this->_start_date + "";
        }
        if (this->_end_date != ""){
            time_query += " before:" + this->_end_date + "";
        }
    } else if (this->_period != "anytime"){
        time_query += " when:" + this->_period;
    }
    
    std::string language = this->_language == "en" ? this->_language + "-US": this->_language; // Languages to used for news search
    
    return time_query + 
        "&hl=" + language + 
        "&gl=" + this->_country +
        "&ceid=" + this->_country + ":" + this->_language;
}

std::string GoogleNews::__full_url(
    std::string keyword = "" // Keyword used for searching the news
){
    std::string parameters = this->__url_parameters(); // Constructed parameters for news search
    return this->__news_url + "/search?q=" + keyword + parameters;
}

std::string GoogleNews::__get_rss_content(
    const std::string& url // URL for news search
) {
    CURL* curl; // Curl object to get the result data
    std::string readBuffer; // Buffer to store the result data

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
) {
    using namespace tinyxml2;
    
    int result = 1; // Starting index to start XML parsing 
    XMLDocument doc; // XML document to parse XML content
    
    doc.Parse(xmlContent.c_str());
    
    std::vector<std::unordered_map<std::string, std::string>> items; // All items in the XML content
    
    XMLElement* channel = doc.FirstChildElement("rss")->FirstChildElement("channel"); // Channel element in the xml content
    for(XMLElement* item = channel->FirstChildElement("item"); item != nullptr; item = item->NextSiblingElement("item")) {
        if (result > this->_max_results) break;
        
        std::unordered_map<std::string, std::string> itemMap; // Unordered map of items of XML content
        
        XMLElement* titleElem = item->FirstChildElement("title"); // Title element in the XML content
        if(titleElem) itemMap["title"] = titleElem->GetText();
        
        XMLElement* linkElem = item->FirstChildElement("link"); // Link element in the XML content
        if(linkElem) itemMap["link"] = linkElem->GetText();
        
        XMLElement* pubDateElem = item->FirstChildElement("pubDate"); // PubDate element in the XML content
        if(pubDateElem) itemMap["pubDate"] = pubDateElem->GetText();
        
        XMLElement* descriptionElem = item->FirstChildElement("description"); // Description element in the XML content
        if(descriptionElem) itemMap["description"] = descriptionElem->GetText();
        
        XMLElement* sourceElem = item->FirstChildElement("source"); // Source element in the XML content
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

std::string GoogleNews::__encode_url(
    const std::string& url // Url to encode
) {
    std::ostringstream encoded;
    for (char c : url) {
        if (isalnum(static_cast<unsigned char>(c)) || 
        c == '-' || c == '_' || c == '.' || c == '~' || 
        c == '&' || c == '$' || c == '+' || c == ',' || 
        c == '/' || c == ':' || c == ';' || c == '=' || 
        c == '?' || c == '@' || c == '#' || c == '!' ||
        c == '*') {
            encoded << c;
        } else {
            encoded << '%' << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << (int)static_cast<unsigned char>(c);
        }
    }
    return encoded.str();
}

void GoogleNews::__get_news(
    const std::string keyword, // query used to get news
    const std::string article_file = "text_files/news_articles.txt" // file to save articles in
){
    std::string encoded_url = this->__encode_url(this->__full_url(keyword)); // Encoded url query to get news

    std::cout << "Encoded Url: " + encoded_url << std::endl;
    
    std::string content = this->__get_rss_content(encoded_url); // XML Content from the news query
    std::ofstream articles_file; // File object to save articles
    
    auto items = this->__parse_rss_content(content); // Items in the XML content
    
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

std::string GoogleNews::_get_language(){
    std::string log_content = "The language used to get the news is: " + this->_language;
    this->__log__(log_content);

    return this->_language;
}

std::string GoogleNews::_get_country(){
    std::string log_content = "The country used to get the news is: " + this->_country;
    this->__log__(log_content);

    return this->_country;
}

std::string GoogleNews::_get_period(){
    std::string log_content = "The period used to get the news is: " + this->_period;
    this->__log__(log_content);

    return this->_period;
}

std::string GoogleNews::_get_start_date(){
    std::string log_content = "The start date used to get the news is: " + this->_start_date;
    this->__log__(log_content);

    return this->_start_date;
}

std::string GoogleNews::_get_end_date(){
    std::string log_content = "The end date used to get the news is: " + this->_end_date;
    this->__log__(log_content);

    return this->_end_date;
}

int GoogleNews::_get_max_results(){
    std::string log_content = "The max results used to get the news is: " + std::to_string(this->_max_results);
    this->__log__(log_content);

    return this->_max_results;
}

std::vector<std::string> GoogleNews::_get_exclude_websites(){
    std::string log_content = "The excluded websites used to get the news are: " + std::to_string(this->_exclude_websites.size());
    this->__log__(log_content);

    return this->_exclude_websites;
}

void GoogleNews::_get_news(
    const std::string keyword, // Keyword used to search news
    const std::string filename = "text_files/news_articles.txt" // File to save articles in
){

    std::string query = "/search?q=" + keyword; // News Query to search news
    this->__get_news(query, filename);

    std::string log_content = "Searched for news for the keyword: " + keyword + ", and saved the results in the file: " + filename + ".";
    this->__log__(log_content);
}

void GoogleNews::_get_latest_topics(
    const std::string filename = "text_files/news_articles.txt" // File to save articles in
){
    this->__get_news("?", filename);

    std::string log_content = "Searched for latest topics and saved the results in the file: " + filename + ".";
    this->__log__(log_content);
}

void GoogleNews::_get_news_by_topic(
    const std::string topic, // Search the news on this topic
    const std::string filename = "text_files/news_articles.txt" // File to save articles in
){
    bool correct_topic = this->__contains(this->__available_topics, topic);

    if (correct_topic){
        std::string query = "headlines/section/topic/" + topic + "?";
        this->__get_news(query, filename);
    }

    std::string log_content = "Searched for news on the topic: " + topic;
    if (correct_topic)
        log_content += " and saved the results in the file: " + filename + ".";
    else
        log_content += ", but it is not in the list of available topics, so could not get the results.";

    this->__log__(log_content);
}

void GoogleNews::_get_news_by_country(
    const std::string country, // Search the news on this country
    const std::string filename = "text_files/news_articles.txt" // File to save articles in
){
    bool correct_country = this->__contains(this->__available_countries, country);

    if (correct_country){
        std::string query = "headlines/section/geo/" + country + "?"; // Query with country
        this->__get_news(query, filename);
    }

    std::string log_content = "Searched for news on the country: " + country;
    if (correct_country)
        log_content += " and saved the results in the file: " + filename + ".";
    else
        log_content += ", but it is not in the list of available countries, so could not get the results.";

    this->__log__(log_content);
}

void GoogleNews::_get_news_by_site(
    const std::string site, // Search the news on this site
    const std::string filename = "text_files/news_articles.txt" // File to save articles in
){
    this->__get_news("site:" + site, filename);

    std::string log_content = "Search for news based on site " + site + " and saved results in the file " + filename + ".";
    this->__log__(log_content);
}

void GoogleNews::_set_language(
    const std::string language // Languge you want to get the news in
){
    this->_language = language;

    std::string log_content = "Language set to " + language + " to search the news.";
    this->__log__(log_content);
}

void GoogleNews::_set_country(
    const std::string country // Country you want to get the news from
){
    this->_country = country;

    std::string log_content = "Country set to " + country + " to search the news.";
    this->__log__(log_content);
}

void GoogleNews::_set_period(
    const std::string period // Time period to get news from
){
    this->_period = period;

    std::string log_content = "Period set to " + period + " to search the news.";
    this->__log__(log_content);
}

void GoogleNews::_set_start_date(
    const std::string start_date // Starting date for when to get news from
){
    this->_start_date = start_date;
    this->__start_year = std::stoi(start_date.substr(0, 4));
    this->__start_month = std::stoi(start_date.substr(5, 2));
    this->__start_day = std::stoi(start_date.substr(8, 2));

    std::string log_content = "Start date set to " + start_date + " to search the news.";
    this->__log__(log_content);
}

void GoogleNews::_set_end_date(
    const std::string end_date // Ending date till when news is presented
){
    this->_end_date = end_date;
    this->__end_year = std::stoi(end_date.substr(0, 4));
    this->__end_month = std::stoi(end_date.substr(5, 2));
    this->__end_day = std::stoi(end_date.substr(8, 2));

    bool date_different = this->__is_date_different(this->__start_year, this->__start_month, this->__start_day, this->__end_year, this->__end_month, this->__end_day);
    
    std::string log_content;
    if (date_different)
        log_content += "End date set to " + end_date + " to search the news.";
    else
        log_content += "End date could not be set as the start date and end date difference is less than a day. Please set again";
    this->__log__(log_content);
}

void GoogleNews::_set_max_results(
    const int max_results // Max number of results for the news
){
    this->_max_results = max_results;

    std::string log_content = "Max results set to " + std::to_string(max_results) + " to search the news.";
    this->__log__(log_content);
}

void GoogleNews::_set_excluded_websites(
    std::vector<std::string> excluded_websites // Websites to exclude from the results
){
    this->_exclude_websites = excluded_websites;

    std::string log_content = "Excluded websites are: ";
    for (auto excluded_website: excluded_websites)
        log_content += excluded_website + ", ";

    this->__log__(log_content);
}