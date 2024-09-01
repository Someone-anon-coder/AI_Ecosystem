#ifndef NEWS_CONFIGURE_H
#define NEWS_CONFIGURE_H

#include <ctime>
#include <map>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include <fstream>
#include <iostream>

#include <curl/curl.h>
#include "tinyxml2.h"

class GoogleNews{
    private:
        // Class Variables
        std::string __news_url="https://news.google.com/rss"; // Url for google news search

        int __start_year; // Year at which the news search should start
        int __start_month; // Month at which the news search should start
        int __start_day; // Day at which the news search should start
        
        int __end_year; // Year at which the news search should end
        int __end_month; // Month at which the news search should end
        int __end_day; // Day at which the news search should end

        std::vector<std::string> __available_countries = {"AU", "BW", "CA", "ET", "GH", "IN", "ID", "IE", "IL", "KE", "LV", "MY", "NA", "NZ", "NG", "PK", "PH", "SG", "ZA", "TZ", "UG", "GB", "US", "ZW", "CZ", "DE", "AT", "CH", "AR", "CL", "CO", "CU", "MX", "PE", "VE", "BE", "FR", "MA", "SN", "IT", "LT", "HU", "NL", "NO", "PL", "BR", "PT", "RO", "SK", "SI", "SE", "VN", "TR", "GR", "BG", "RU", "UA", "RS", "AE", "SA", "LB", "EG", "BD", "TH", "CN", "TW", "HK", "JP", "KR"}; // Availble countries to search news for
        std::vector<std::string> __available_languages = {"en", "id", "cs", "de", "es-419", "fr", "it", "lv", "lt", "hu", "nl", "no", "pl", "pt-419", "pt-150", "ro", "sk", "sl", "sv", "vi", "tr", "el", "bg", "ru", "sr", "uk", "he", "ar", "mr", "hi", "bn", "ta", "te", "ml", "th", "zh-Hans", "zh-Hant", "ja", "ko"}; // Availble languages to search news for
        std::vector<std::string> __available_topics = {"WORLD", "NATION", "BUSINESS", "TECHNOLOGY", "ENTERTAINMENT", "SPORTS", "SCIENCE", "HEALTH"}; // Availble topics to search news for
        std::vector<std::string> __available_periods = {"hour", "day", "week", "month", "year", "any_time"}; // Availble periods to search news for

        // Class Functions
        static size_t __WriteCallback( // Callback function to handle the data received
            void* contents, // pointer to buffer containing the downloaded data
            size_t size, // size of the downloaded data
            size_t nmemb, // number of elements in the downloaded data
            void* userp // pointer to the user-defined data
        );

        bool __contains( // Checks if the given value is present in the vector
            const std::vector<std::string>& vec, // Vector to search for the given value
            std::string value // Value to search for in the vector
        );

        bool __is_date_different( // Checks if the start and end dates are different
            const int start_year, // Start year for news search
            const int start_month, // Start month for news search
            const int start_day, // Start day for news search
            const int end_year, // End year for news search 
            const int end_month, // End month for news search 
            const int end_day // End day for news search
        );

        std::string __url_parameters();

        std::string __full_url( // Crafts parameters to be included in the url for news search
            std::string keyword="" // Keyword used for searching the news
        );

        std::string __get_rss_content( // Function to request the URL and get the content
            const std::string& url // URL for news search
        );

        std::vector<std::unordered_map<std::string, std::string>> __parse_rss_content( // Function to parse the XML content
            const std::string& xmlContent // XML content to be parsed
        );

        void __get_news( // Function to get the news
            const std::string keyword, // query used to get news
            const std::string article_file="text_files/news_articles.txt" // file to save articles in
        );

    public:
        // Class Variables
        int _max_results; // Max results to return for news search
        std::string _language; // Language to use to search news
        std::string _country; // Country to use to search news
        std::string _period; // Period to use to search news
        std::string _start_date; // Start date to use to search news from 
        std::string _end_date; // End date to use to search news till
        std::vector<std::string> _exclude_websites; // Websites to exclude when searching for the news

        // Class Constructor
        GoogleNews( // Initialize google news constructor with default parameters
            const std::string language = "en", // Languge you want to get the news in
            const std::string country = "US", // Country you want to get the news from
            const std::string period = "anytime", // Time period to get news from
            const std::string start_date = "", // Starting date for when to get news from
            const std::string end_date = "", // Ending date for when to get the news till. End date should be atleast 1 day after start date
            const int max_results = 10, // Max number of results to be returned for the news
            const std::vector<std::string> exclude_websites = {} // Websites to exclude when searching for the news
        );

        // Class Destructor
        ~GoogleNews(); // Nothing implemented here

        // Class Functions
        // Getters
        std::string get_language(); // Returns the languge in which news is presented

        std::string get_country(); // Returns the country from which news is presented

        std::string get_period(); // Returns the time period for when news is presented

        std::string get_start_date(); // Returns the starting date for when news is presented

        std::string get_end_date(); // Returns the ending date till when news is presented

        int get_max_results(); // Returns the max number of results for the news

        std::vector<std::string> get_exclude_websites(); // Returns the websites which are excluded when searching for the news

        void get_news( // Gets the news
            const std::string keyword, // Keyword used to search news
            const std::string filename="text_files/news_articles.txt" // File to save articles in
        );

        void get_latest_topics( // Get news on latest topics
            const std::string filename="text_files/news_articles.txt" // File to save articles in
        );

        void get_news_by_topic( // Search the news on this topic
            const std::string topic, // Search the news on this topic
            const std::string filename="text_files/news_articles.txt" // File to save articles in
        );

        void get_news_by_country( // Search the news on this country
            const std::string country, // Search the news on this country
            const std::string filename="text_files/news_articles.txt" // File to save articles in
        );

        void get_news_by_site( // Search the news from this site
            const std::string site, // Search the news on this site
            const std::string filename="text_files/news_articles.txt" // File to save articles in
        );

        // Setters
        void set_language( // Sets the languge in which news is presented
            const std::string language // Languge you want to get the news in
        );

        void set_country( // Sets the country from which news is presented
            const std::string country // Country you want to get the news from
        );

        void set_period( // Sets the time period for when news is presented
            const std::string period // Time period to get news from
        );

        bool set_start_date( // Sets the starting date for when news is presented
            const std::string start_date // Starting date for when to get news from
        );

        bool set_end_date( // Sets the ending date till when news is presented
            const std::string end_date // Ending date till when news is presented
        );

        void set_max_results( // Sets the max number of results for the news
            const int max_results // Max number of results for the news
        );

        void set_excluded_websites( // Sets the websites to exclude from the results
            std::vector<std::string> excluded_websites // Websites to exclude from the results
        );
};

#endif