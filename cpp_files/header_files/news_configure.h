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

/// @brief Class to Search News on Google News
class GoogleNews{
    private:
        // Class Private Variables

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

        // Class Private Functions

        /// @brief Callback function to handle the data received
        /// @param contents pointer to buffer containing the downloaded data
        /// @param size size of the downloaded data
        /// @param nmemb number of elements in the downloaded data
        /// @param userp pointer to the user-defined data
        /// @return size * nmemb
        static size_t __WriteCallback(
            void* contents, // pointer to buffer containing the downloaded data
            size_t size, // size of the downloaded data
            size_t nmemb, // number of elements in the downloaded data
            void* userp // pointer to the user-defined data
        );

        /// @brief Checks if the given value is present in the vector
        /// @param vec Vector to search for the given value
        /// @param value Value to search for in the vector
        /// @return true if the value is present in the vector, false otherwise
        bool __contains(
            const std::vector<std::string>& vec, // Vector to search for the given value
            std::string value // Value to search for in the vector
        );

        /// @brief Checks if the start and end dates are different
        /// @param start_year Start year for news search
        /// @param start_month Start month for news search
        /// @param start_day Start day for news search
        /// @param end_year End year for news search 
        /// @param end_month End month for news search 
        /// @param end_day End day for news search
        /// @return true if the start and end dates are different, false otherwise
        bool __is_date_different( // Checks if the start and end dates are different
            const int start_year, // Start year for news search
            const int start_month, // Start month for news search
            const int start_day, // Start day for news search
            const int end_year, // End year for news search 
            const int end_month, // End month for news search 
            const int end_day // End day for news search
        );

        /// @brief Crafts parameters to be included in the url for news search
        /// @return String of constructed url parameters
        std::string __url_parameters();

        /// @brief Crafts the full url for news search
        /// @param keyword Keyword used for searching the news
        /// @return String of constructed url
        std::string __full_url(
            std::string keyword // Keyword used for searching the news
        );

        /// @brief Function to request the URL and get the content
        /// @param url URL for news search
        /// @return String of the content
        std::string __get_rss_content(
            const std::string& url // URL for news search
        );

        /// @brief Function to parse the XML content
        /// @param xmlContent XML content to be parsed
        /// @return Vector of unordered maps containing the parsed content
        std::vector<std::unordered_map<std::string, std::string>> __parse_rss_content(
            const std::string& xmlContent // XML content to be parsed
        );

        /// @brief Function to get the news
        /// @param keyword Keyword used to search news
        /// @param article_file File to save articles in
        void __get_news(
            const std::string keyword, // query used to get news
            const std::string article_file // file to save articles in
        );

    public:
        // Class Public Variables
        
        int _max_results; // Max results to return for news search
        std::string _language; // Language to use to search news
        std::string _country; // Country to use to search news
        std::string _period; // Period to use to search news
        std::string _start_date; // Start date to use to search news from 
        std::string _end_date; // End date to use to search news till
        std::vector<std::string> _exclude_websites; // Websites to exclude when searching for the news

        /// @brief Initialize google news constructor with default parameters
        /// @param language Languge you want to get the news in
        /// @param country Country you want to get the news from
        /// @param period Time period to get news from
        /// @param start_date Starting date for when to get news from
        /// @param end_date Ending date for when to get the news till. End date should be atleast 1 day after start date
        /// @param max_results Max number of results to be returned for the news
        /// @param exclude_websites Websites to exclude when searching for the news
        GoogleNews(
            const std::string language, // Languge you want to get the news in
            const std::string country, // Country you want to get the news from
            const std::string period, // Time period to get news from
            const std::string start_date, // Starting date for when to get news from
            const std::string end_date, // Ending date for when to get the news till. End date should be atleast 1 day after start date
            const int max_results, // Max number of results to be returned for the news
            const std::vector<std::string> exclude_websites // Websites to exclude when searching for the news
        );

        /// @brief Class Destructor
        ~GoogleNews();

        // Class Public Functions

        /// @brief Function to get the class information
        /// @return Vector of maps containing the class information
        std::map<std::string, std::map<std::string, std::string>> __class_info__();

        // Getters

        /// @brief Function to get the language
        /// @return String of the language
        std::string _get_language();

        /// @brief Function to get the country
        /// @return String of the country
        std::string _get_country();

        /// @brief Function to get the period
        /// @return String of the period
        std::string _get_period();

        /// @brief Function to get the start date
        /// @return String of the date
        std::string _get_start_date();

        /// @brief Function to get the end date
        /// @return String of the date
        std::string _get_end_date();

        /// @brief Function to get the max results
        /// @return Number of max results
        int _get_max_results();

        /// @brief Function to get the excluded websites
        /// @return Vector of excluded websites
        std::vector<std::string> _get_exclude_websites();

        /// @brief Function to get the news
        /// @param keyword Keyword used to search news
        /// @param filename File to save articles in
        void _get_news(
            const std::string keyword, // Keyword used to search news
            const std::string filename // File to save articles in
        );

        /// @brief Function to get the news on latest topics
        /// @param filename File to save articles in
        void _get_latest_topics(
            const std::string filename // File to save articles in
        );

        /// @brief Function to get the news on the given topic
        /// @param topic Search the news on this topic
        /// @param filename File to save articles in
        void _get_news_by_topic(
            const std::string topic, // Search the news on this topic
            const std::string filename // File to save articles in
        );

        /// @brief Function to get the news on the given country
        /// @param country Search the news on this country
        /// @param filename File to save articles in
        void _get_news_by_country(
            const std::string country, // Search the news on this country
            const std::string filename // File to save articles in
        );

        /// @brief Function to get the news from the given site
        /// @param site Search the news from this site
        /// @param filename File to save articles in
        void _get_news_by_site(
            const std::string site, // Search the news on this site
            const std::string filename // File to save articles in
        );

        // Setters

        /// @brief Function to set the language
        /// @param language Languge you want to get the news in
        void _set_language(
            const std::string language // Languge you want to get the news in
        );

        /// @brief Function to set the country
        /// @param country Country you want to get the news from
        void _set_country(
            const std::string country
        );

        /// @brief Function to set the time period
        /// @param period Time period to get news from
        void _set_period(
            const std::string period // Time period to get news from
        );

        /// @brief Function to set the start date
        /// @param start_date Starting date for when to get news from
        /// @return True if start date and end date are different
        bool _set_start_date(
            const std::string start_date // Starting date for when to get news from
        );

        /// @brief Function to set the end date
        /// @param end_date Ending date till when news is presented
        /// @return True if start date and end date are different
        bool _set_end_date(
            const std::string end_date // Ending date till when news is presented
        );

        /// @brief Function to set the max results
        /// @param max_results Max number of results for the news
        void _set_max_results(
            const int max_results // Max number of results for the news
        );

        /// @brief Function to set the excluded websites
        /// @param excluded_websites Websites to exclude from the results
        void _set_excluded_websites(
            std::vector<std::string> excluded_websites // Websites to exclude from the results
        );
};

#endif