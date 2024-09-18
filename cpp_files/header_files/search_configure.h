#ifndef SEARCH_CONFIGURE_H
#define SEARCH_CONFIGURE_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <curl/curl.h>
#include <map>
#include <nlohmann/json.hpp>

/// @brief Class for searching Google
class GoogleSearch{
    private:
        // Class Private Variables
        std::string __api_key; // Google custom search json API key
        std::string __cx_key; // Google custom search json Search Engine ID

        const int __filter[2] = {0, 1}; // Controls turning on or off the duplicate content filter.
        const int __c2coff[2] = {0, 1}; // Enables or disables Simplified and Traditional Chinese Search.

        const char __site_search_filter[2] = {'i', 'e'}; // Whether to include or exclude a particular site
        const char __date_restrict[4] = {'d', 'w', 'm', 'y'}; // Whether to restrict search based on day, week, month or year

        const std::string __available_languages[36] = {"lang_ar", "lang_bg", "lang_ca", "lang_cs", "lang_da", "lang_de", "lang_el", "lang_en", "lang_es", "lang_et", "lang_fi", "lang_fr", "lang_hr", "lang_hu", "lang_id", "lang_is", "lang_it", "lang_iw", "lang_ja", "lang_ko", "lang_lt", "lang_lv", "lang_nl", "lang_no", "lang_pl", "lang_pt", "lang_ro", "lang_ru", "lang_sk", "lang_sl", "lang_sr", "lang_sv", "lang_tr", "lang_zh-CN", "lang_zh-TW"}; // Availalble languages for documents to search in
        const std::string __available_interface_languages[83] = {"af", "sq", "sm", "ar", "az", "eu", "be", "bn", "bh", "bs", "bg", "ca", "zh-CN", "zh-TW", "hr", "cs", "da", "nl", "en", "eo", "et", "fo", "fi", "fr", "fy", "gl", "ka", "de", "el", "gu", "iw", "hi", "hu", "is", "id", "ia", "ga", "it", "ja", "jw", "kn", "ko", "la", "lv", "lt", "mk", "ms", "ml", "mt", "mr", "ne", "no", "nn", "oc", "fa", "pl", "pt-BR", "pt-PT", "pa", "ro", "ru", "gd", "sr", "si", "sk", "sl", "es", "su", "sw", "sv", "tl", "ta", "te", "th", "ti", "tr", "uk", "ur", "uz", "vi", "cy", "xh", "zu"}; // Language to display results in
        const std::string __available_user_countries[249] = {"af", "al", "dz", "as", "ad", "ao", "ai", "aq", "ag", "ar", "am", "aw", "au", "at", "az", "bs", "bh", "bd", "bb", "by", "be", "bz", "bj", "bm", "bt", "bo", "ba", "bw", "bv", "br", "io", "bn", "bg", "bf", "bi", "kh", "cm", "ca", "cv", "ky", "cf", "td", "cl", "cn", "cx", "cc", "co", "km", "cg", "cd", "ck", "cr", "ci", "hr", "cu", "cy", "cz", "dk", "dj", "dm", "do", "ec", "eg", "sv", "gq", "er", "ee", "et", "fk", "fo", "fj", "fi", "fr", "gf", "pf", "tf", "ga", "gm", "ge", "de", "gh", "gi", "gr", "gl", "gd", "gp", "gu", "gt", "gn", "gw", "gy", "ht", "hm", "va", "hn", "hk", "hu", "is", "in", "id", "ir", "iq", "ie", "il", "it", "jm", "jp", "jo", "kz", "ke", "ki", "kp", "kr", "kw", "kg", "la", "lv", "lb", "ls", "lr", "ly", "li", "lt", "lu", "mo", "mk", "mg", "mw", "my", "mv", "ml", "mt", "mh", "mq", "mr", "mu", "yt", "mx", "fm", "md", "mc", "mn", "ms", "ma", "mz", "mm", "na", "nr", "np", "nl", "an", "nc", "nz", "ni", "ne", "ng", "nu", "nf", "mp", "no", "om", "pk", "pw", "ps", "pa", "pg", "py", "pe", "ph", "pn", "pl", "pt", "pr", "qa", "re", "ro", "ru", "rw", "sh", "kn", "lc", "pm", "vc", "ws", "sm", "st", "sa", "sn", "cs", "sc", "sl", "sg", "sk", "si", "sb", "so", "za", "gs", "es", "lk", "sd", "sr", "sj", "sz", "se", "ch", "sy", "tw", "tj", "tz", "th", "tl", "tg", "tk", "to", "tt", "tn", "tr", "tm", "tc", "tv", "ug", "ua", "ae", "uk", "us", "um", "uy", "uz", "vu", "ve", "vn", "vg", "vi", "wf", "eh", "ye", "zm", "zw"}; // Available contries for users to search from
        const std::string __available_result_countries[249] = {"countryAF", "countryAL", "countryDZ", "countryAS", "countryAD", "countryAO", "countryAI", "countryAQ", "countryAG", "countryAR", "countryAM", "countryAW", "countryAU", "countryAT", "countryAZ", "countryBS", "countryBH", "countryBD", "countryBB", "countryBY", "countryBE", "countryBZ", "countryBJ", "countryBM", "countryBT", "countryBO", "countryBA", "countryBW", "countryBV", "countryBR", "countryIO", "countryBN", "countryBG", "countryBF", "countryBI", "countryKH", "countryCM", "countryCA", "countryCV", "countryKY", "countryCF", "countryTD", "countryCL", "countryCN", "countryCX", "countryCC", "countryCO", "countryKM", "countryCG", "countryCD", "countryCK", "countryCR", "countryCI", "countryHR", "countryCU", "countryCY", "countryCZ", "countryDK", "countryDJ", "countryDM", "countryDO", "countryTP", "countryEC", "countryEG", "countrySV", "countryGQ", "countryER", "countryEE", "countryET", "countryEU", "countryFK", "countryFO", "countryFJ", "countryFI", "countryFR", "countryFX", "countryGF", "countryPF", "countryTF", "countryGA", "countryGM", "countryGE", "countryDE", "countryGH", "countryGI", "countryGR", "countryGL", "countryGD", "countryGP", "countryGU", "countryGT", "countryGN", "countryGW", "countryGY", "countryHT", "countryHM", "countryVA", "countryHN", "countryHK", "countryHU", "countryIS", "countryIN", "countryID", "countryIR", "countryIQ", "countryIE", "countryIL", "countryIT", "countryJM", "countryJP", "countryJO", "countryKZ", "countryKE", "countryKI", "countryKP", "countryKR", "countryKW", "countryKG", "countryLA", "countryLV", "countryLB", "countryLS", "countryLR", "countryLY", "countryLI", "countryLT", "countryLU", "countryMO", "countryMK", "countryMG", "countryMW", "countryMY", "countryMV", "countryML", "countryMT", "countryMH", "countryMQ", "countryMR", "countryMU", "countryYT", "countryMX", "countryFM", "countryMD", "countryMC", "countryMN", "countryMS", "countryMA", "countryMZ", "countryMM", "countryNA", "countryNR", "countryNP", "countryNL", "countryAN", "countryNC", "countryNZ", "countryNI", "countryNE", "countryNG", "countryNU", "countryNF", "countryMP", "countryNO", "countryOM", "countryPK", "countryPW", "countryPS", "countryPA", "countryPG", "countryPY", "countryPE", "countryPH", "countryPN", "countryPL", "countryPT", "countryPR", "countryQA", "countryRE", "countryRO", "countryRU", "countryRW", "countrySH", "countryKN", "countryLC", "countryPM", "countryVC", "countryWS", "countrySM", "countryST", "countrySA", "countrySN", "countryCS", "countrySC", "countrySL", "countrySG", "countrySK", "countrySI", "countrySB", "countrySO", "countryZA", "countryGS", "countryES", "countryLK", "countrySD", "countrySR", "countrySJ", "countrySZ", "countrySE", "countryCH", "countrySY", "countryTW", "countryTJ", "countryTZ", "countryTH", "countryTG", "countryTK", "countryTO", "countryTT", "countryTN", "countryTR", "countryTM", "countryTC", "countryTV", "countryUG", "countryUA", "countryAE", "countryUK", "countryUS", "countryUM", "countryUY", "countryUZ", "countryVU", "countryVE", "countryVN", "countryVG", "countryVI", "countryWF", "countryEH", "countryYE", "countryYU", "countryZM", "countryZW"}; // Available countries to get results from
        const std::string __available_filetypes[64] = {".pdf", ".ps", ".csv", ".epub", ".kmz", ".gpx", ".hwp", ".htm", ".html", ".xls", ".xlsx", ".ppt", ".pptx", ".doc", ".docx", ".odp", ".ods", ".odt", ".rtf", ".svg", ".tex", ".txt", ".text", ".bas", ".c", ".cc", ".cpp", ".cxx", ".h", ".hpp", ".cs", ".java", ".pl", ".py", ".wml", ".wap", ".xml", "BMP", "GIF", "JPEG", "PNG", "WebP", "SVG", "3GP", "3G2", "ASF", "AVI", "DivX", "M2V", "M3U", "M3U8", "M4V", "MKV", "MOV", "MP4", "MPEG", "OGV", "QVT", "RAM", "RM", "VOB", "WebM", "WMV", "XAP"}; // Available filetypes extension for documents
        const std::string __safe[2] = {"active", "off"}; // Safe search
        const std::string __sort[2] = {"date-sdate:a", "date-sdate:d"}; // ascending or descending order sort by date
        const std::string __search_type[1] = {"image"}; // Whether to search for images
        const std::string __rights[5] = {"cc_publicdomain", "cc_attribute", "cc_sharealike", "cc_noncommercial", "cc_nonderived"}; // Available rights on the documents
        const std::string __image_sizes[7] = {"huge", "icon", "large", "medium", "small", "xlarge", "xxlarge"}; // Available sizes for image search
        const std::string __image_types[6] = {"clipart", "face", "lineart", "stock", "photo", "animated"}; // Available style of images
        const std::string __image_color_types[4] = {"color", "gray", "mono", "trans"}; // Available color types to search images
        const std::string __image_dominant_color_types[12] = {"black", "blue", "brown", "gray", "green", "orange", "pink", "purple", "red", "teal", "white", "yellow"}; // Available dominant colors to search for images

        // Class Private Functions

        /// @brief Function to trim whitespace from a string
        /// @param str The string to be trimmed
        /// @return The trimmed string
        std::string __trim(
            const std::string& str // String to be trimmed
        );

        /// @brief Function to load the .env file
        /// @param filePath The path to the .env file
        /// @return A map of key-value pairs
        std::unordered_map<std::string, std::string> __load_env_file(
            const std::string& filePath // Path of the env file
        );

        /// @brief Function to get a specific value for a key from the map
        /// @param envMap The Unordered map to read
        /// @param key The key to find
        /// @return Value of the key in env file
        std::string __get_env_value(
            const std::unordered_map<std::string, std::string>& envMap, // The Unordered map to read
            const std::string& key // The key to find in the map
        );

        /// @brief Function to load API and CX keys from a file
        /// @param env_filename Name of the file that contains API and CX keys
        void __get_api_cx(
            std::string env_filename // Name of the file that contains API and CX keys
        );

        /// @brief Get the total size of the downloaded data
        /// @param contents pointer to buffer containing the downloaded data
        /// @param size size of the downloaded data
        /// @param nmemb number of elements in the downloaded data
        /// @param output Pointer to user defined data
        /// @return Total size of the downloaded data
        static size_t __WriteCallBack(
            void* contents, // pointer to buffer containing the downloaded data
            size_t size, // size of the downloaded data
            size_t nmemb, // number of elements in the downloaded data
            std::string* output // Pointer to user defined data
        );

        /// @brief Get json data from the given google custom search url
        /// @param url Url to get data from
        /// @return String of json data
        std::string __fetch_json_data(
            const std::string& url // Url to fetch data from
        );

        /// @brief Save the result json data to a json file
        /// @param json_data Json data to save
        /// @param filename Name of the file to save json data in
        void __save_json_data(
            const std::string json_data, // Json data to save
            const std::string filename // Name of the file to save json data in
        );

        /// @brief Encode Url
        /// @param url url to encode
        /// @return String of Encoded url
        std::string __encode_url(
            const std::string& url // Url to encode
        );

        /// @brief Create search url used to search on google, Omiting and Adding appropriate parameters only
        void __construct_search_url();

    public:
        // Class Public Variables

        int _num_results; // Number of results to return for the search
        int _start_index; // Position to start from when getting search results
        int _filter; // turn on or off duplicate content
        int _c2coff; // turn on or off Simplified and Traditional Chinese Search
        int _date_restrict; // Whether to restrict search based on dates. "1" for yes and "0" for no
        
        std::string _extra_query; // Extra queries to include in the search terms
        std::string _exact_terms; // A phrase that all documents in the search results must contain
        std::string _exclude_terms; // A word or phrase that should not appear in any documents in the search results
        std::string _site_search; // A given site which should always be included or excluded from results. Based on *_site_search_filter*
        std::string _site_search_filter; // Whether to Include or exclude the sites specified in *_site_search*
        std::string _link_site; // Specifies that all search results should contain a link to a particular URL
        std::string _or_terms; // Provides additional search terms to check for in a document, where each document in the search results must contain at least one of the additional search terms
        std::string _date_restrict_type; // Restricts results to URLs based on date. In format dateType[number]. Example: m3 restricts to past 3 months
        std::string _low_range; // query terms to append before the search query
        std::string _high_range; // query terms to append after the search query
        std::string _search_type; // Specifies the search type: image. If unspecified, results are limited to webpages
        std::string _filetype; // Restricts results to files of a specified extension
        std::string _rights; // Filters based on licensing
        std::string _img_size; // Returns images of a specified size
        std::string _img_type; // Returns images of a type
        std::string _img_color_type; // Returns black and white, grayscale, transparent, or color images
        std::string _img_dominant_color; // Returns images of a specific dominant color
        std::string _language; // Language to search google in
        std::string _interface_language; // Sets the user interface language
        std::string _user_country; // Country to search from in google
        std::string _result_country; // Country to search for in google
        std::string _safe; // Whether to show explicit results.
        std::string _sort; // Return results in specific order

        std::string _search_terms; // Query to search for on google
        std::string _search_url; // Google Custom Search url
        std::string _json_file; // Name of the file to save response data
        std::string _env_file; // Name of the file that contains Google Search API and CX keys

        // Class Public Functions

        /// @brief Class Constructor. Initializes class variables and constructs the search url
        /// @param search_terms Query to search for on google
        /// @param num_results Number of Results to return
        /// @param start_index Position to start from when getting search results
        /// @param filter turn on or off duplicate content
        /// @param c2coff turn on or off Simplified and Traditional Chinese in search
        /// @param date_restrict Whether to restrict search based on dates
        /// @param extra_query Extra queries to include in the search
        /// @param exact_terms A phrase to include in documents of the search
        /// @param exclude_terms A word or phrase to exclude from the search
        /// @param site_search A given site which should always be included or excluded from results. Based on *site_search_filter*
        /// @param site_search_filter Whether to Include or exclude the sites specified in *site_search*
        /// @param link_site Specifies a link that should be in all search results
        /// @param or_terms Additional search terms to include in documents in search
        /// @param date_restrict_type Restrict results based on date
        /// @param low_range Query terms to append before a query
        /// @param high_range QUery terms to append after a query
        /// @param search_type Specifies the search type. Eg: "image"
        /// @param filetype Restricts results to files of a specified extension
        /// @param rights Filters based on licensing
        /// @param img_size Returns images of specified size
        /// @param img_type Returns image of a type
        /// @param img_color_type Returns black and white, grayscale, transparent, or color images
        /// @param img_dominant_color Returns images of a specific dominant color
        /// @param language Language to search google in. Defualt is 'English'
        /// @param interface_language Sets the user interface language
        /// @param user_country Country to search from in google
        /// @param result_country Country to search for in google
        /// @param safe Whether to show explicit results.
        /// @param sort Return results in specific order
        /// @param json_file Name of the json file to store search result
        /// @param env_file Name of the env file that contains Google Search API and CX Keys
        GoogleSearch(
            const std::string search_terms, // Query to search for on google

            const int num_results, // Results to return for the search
            const int start_index, // Position to start from when getting search results
            const int filter, // turn on or off duplicate content
            const int c2coff, // turn on or off Simplified and Traditional Chinese Search
            const int date_restrict, // Whether to restrict search based on dates. "1" for yes and "0" for no
            
            const std::string extra_query, // Extra queries to include in the search terms
            const std::string exact_terms, // A phrase that all documents in the search results must contain
            const std::string exclude_terms, // A word or phrase that should not appear in any documents in the search results
            const std::string site_search, // A given site which should always be included or excluded from results. Based on *_site_search_filter*
            const std::string site_search_filter, // Whether to Include or exclude the sites specified in *_site_search*
            const std::string link_site, // Specifies that all search results should contain a link to a particular URL
            const std::string or_terms, // Provides additional search terms to check for in a document, where each document in the search results must contain at least one of the additional search terms
            const std::string date_restrict_type, // Restricts results to URLs based on date. In format dateType[number]. Example: m3 restricts to past 3 months
            const std::string low_range, // query terms to append before the search query
            const std::string high_range, // query terms to append after the search query
            const std::string search_type, // Specifies the search type: image. If unspecified, results are limited to webpages
            const std::string filetype, // Restricts results to files of a specified extension
            const std::string rights, // Filters based on licensing
            const std::string img_size, // Returns images of a specified size
            const std::string img_type, // Returns images of a type
            const std::string img_color_type, // Returns black and white, grayscale, transparent, or color images
            const std::string img_dominant_color, // Returns images of a specific dominant color
            const std::string language, // Language to search google in. Defualt is 'English'
            const std::string interface_language, // Sets the user interface language
            const std::string user_country, // Country to search from in google
            const std::string result_country, // Country to search for in google
            const std::string safe, // Whether to show explicit results.
            const std::string sort, // Return results in specific order

            const std::string json_file, // Name of the json file to store search result
            const std::string env_file // Name of the env that contains Google Search API and CX Keys
        );

        /// @brief Class Destructor. Deinitializes the class variables
        ~GoogleSearch();

        /// @brief Function to get the class information
        /// @return Vector of maps containing the class information
        std::map<std::string, std::map<std::string, std::string>> __class_info__();

        // Getters

        /// @brief Number of results to be returned by google search
        /// @return Integer of number of results
        int _get_num_results();

        /// @brief Index at which search result starts
        /// @return Integer of start index
        int _get_start_index();

        /// @brief Check whether duplicate is turned On or Off
        /// @return Integer specifying if duplicate content is on or off
        int _get_filter();

        /// @brief Check whether Simplified and Traditional Chinese Search is turned On or Off
        /// @return Integer specifying if Simplified and Traditional Chinese Search is on or off
        int _get_c2coff();

        /// @brief Check whether search is restricted by date
        /// @return Integer specifying if search is restricted by date
        int _get_date_restrict();

        /// @brief Get the query used to search on google
        /// @return String of search query 
        std::string _get_query();

        /// @brief Get the constructed url used to query google
        /// @return String of constructed url
        std::string _get_search_url();

        /// @brief Get the extra queries in the search
        /// @return String of extra queries in the search
        std::string _get_extra_query();

        /// @brief Get the exact terms each document will include when searching
        /// @return String of extra terms
        std::string _get_exact_terms();

        /// @brief Get the word which is excluded from appearing in documents from search result
        /// @return String of excluded terms
        std::string _get_exclude_terms();

        /// @brief Get the site to always include or exclude when searching a query
        /// @return String of site which is always included or excluded
        std::string _get_site_search();

        /// @brief Get the value specifying if site should always be included or excluded when searching
        /// @return String of filter specifying whether site is included or excluded
        std::string _get_site_search_filter();

        /// @brief Get the link included in each result
        /// @return String of link
        std::string _get_link_site();

        /// @brief Get the extra terms included in documents in search result
        /// @return String of extra terms
        std::string _get_or_terms();

        /// @brief Get the date restricting the search results
        /// @return String of date restricting the search results
        std::string _get_date_restrict_type();

        /// @brief Get the query appended to before the search query
        /// @return String of query appended to before the search query
        std::string _get_low_range();

        /// @brief Get the query appended to after the search query
        /// @return String of query appended to after the search query
        std::string _get_high_range();

        /// @brief Get the search type of the query
        /// @return String of search type
        std::string _get_search_type();

        /// @brief Get the filetype of the query
        /// @return String of filetype
        std::string _get_filetype();

        /// @brief Get the licensing of the query
        /// @return String of licensing
        std::string _get_rights();

        /// @brief Get the size of the image
        /// @return String of image size
        std::string _get_img_size();

        /// @brief Get the type of the image
        /// @return String of image type
        std::string _get_img_type();

        /// @brief Get the color type of the image
        /// @return String of image color type
        std::string _get_img_color_type();

        /// @brief Get the dominant color of the image
        /// @return String of image dominant color
        std::string _get_img_dominant_color();

        /// @brief Get the language to search google
        /// @return String of language
        std::string _get_language();

        /// @brief Get the user interface language
        /// @return String of user interface language
        std::string _get_interface_language();

        /// @brief Get the country to search from in google
        /// @return String of country
        std::string _get_user_country();

        /// @brief Get the country to search for in google
        /// @return String of country
        std::string _get_result_country();

        /// @brief Get the safe search
        /// @return String of safe search
        std::string _get_safe();

        /// @brief Get the sort order
        /// @return String of sort order
        std::string _get_sort();

        /// @brief Get the name of the json file that stores search result
        /// @return String of json file name
        std::string _get_json_file();

        /// @brief Get the name of the file that contains Google Search API and CX Keys
        /// @return String of env file name
        std::string _get_env_file();

        // Setters

        /// @brief Set the number of results to be returned by google search
        /// @param num_results Integer of number of results
        void _set_num_results(
            const int num_results // number of results to return 
        );

        /// @brief Set the index at which search result starts
        /// @param start_index Integer of start index
        void _set_start_index(
            const int start_index // index at which search result starts
        );

        /// @brief Set to check whether duplicate is turned On or Off
        /// @param filter Integer specifying if duplicate content is on or off
        void _set_filter(
            const int filter // check whether duplicate is turned On or Off
        );

        /// @brief Turn on or off Simplified and Traditional Chinese
        /// @param c2coff Integer Specifying to turn on or off Simplified and Traditional Chinese
        void _set_c2coff(
            const int c2coff // Turn on or off Simplified and Traditional Chinese
        );

        /// @brief Set whether to restrict search based on date
        /// @param date_restrict Whether to restrict search based on date
        void _set_date_restrict(
            const int date_restrict // check whether search is restricted by date
        );

        /// @brief Set extra queries to search for with the search query
        /// @param extra_query String of extra queries to search for with the search query
        void _set_extra_query(
            const std::string extra_query // extra queries to search for with the search query
        );

        /// @brief Set the phrase to include in document in search results
        /// @param exact_terms String of phrase to include in document in search results
        void _set_exact_terms(
            const std::string exact_terms // phrase to include in document in search results
        );

        /// @brief Set the terms to exclude from documents in search result
        /// @param exclude_terms String of terms to exclude from documents in search result
        void _set_exclude_terms(
            const std::string exclude_terms // terms to exclude from documents in search result
        );

        /// @brief Set the site to always include or exclude from search results
        /// @param site_search String of site to always include or exclude from search results
        void _set_site_search(
            const std::string site_search // site to always include or exclude from search results
        );

        /// @brief Set the value to always include or exclude site from search results
        /// @param site_search_filter Char of value specifying to include or exclude a site
        void _set_site_search_filter(
            const char site_search_filter // value specifying to include or exclude a site
        );

        /// @brief Set the link to include in each search result
        /// @param link_site String of link to include in each search result
        void _set_link_site(
            const std::string link_site // link to include in each search result
        );

        /// @brief Set the additional terms to include in the document in search result
        /// @param or_terms String of additional terms to include in documents
        void _set_or_terms(
            const std::string or_terms // additional terms to include in the document
        );

        /// @brief Set the date restrict type to restrict search results
        /// @param date_restrict_type String of date restrict type to restrict search results
        void _set_date_restrict_type(
            const std::string date_restrict_type // date restrict type to restrict search results
        );

        /// @brief Set the query appended to before the search query
        /// @param low_range String of query appended to before the search query
        void _set_low_range(
            const std::string low_range // query appended to before the search query
        );

        /// @brief Set the query appended to after the search query
        /// @param high_range String of query appended to after the search query
        void _set_high_range(
            const std::string high_range // query appended to after the search query
        );

        /// @brief Set the search type of the query
        /// @param search_type String of search type of the query
        void _set_search_type(
            const std::string search_type // search type of the query
        );

        /// @brief Set the filetype of the query
        /// @param filetype String of filetype of the query
        void _set_filetype(
            const std::string filetype // filetype of the query;
        );

        /// @brief Set the licensing of the query
        /// @param rights String of licensing of the query
        void _set_rights(
            const std::string right // licensing of the query
        );

        /// @brief Set the size of the image
        /// @param img_size String of size of the image
        void _set_img_size(
            const std::string img_size // size of the image
        );

        /// @brief Set the type of the image
        /// @param img_type String of type of the image
        void _set_img_type(
            const std::string img_type // type of the image
        );

        /// @brief Set the color type of the image
        /// @param img_color_type String of color type of the image
        void _set_img_color_type(
            const std::string img_color_type // color type of the image
        );

        /// @brief Set the dominant color of the image
        /// @param img_dominant_color String of dominant color of the image
        void _set_img_dominant_color(
            const std::string img_dominant_color // dominant color of the image
        );

        /// @brief Set the language to search google
        /// @param language String of language to search google
        void _set_language(
            const std::string language // language to search google
        );

        /// @brief Set the user interface language
        /// @param interface_language String of user interface language
        void _set_interface_language(
            const std::string interface_language // user interface language
        );

        /// @brief Set the country to search from in google
        /// @param user_country String of country to search from in google
        void _set_user_country(
            const std::string user_country // country to search from in google
        );

        /// @brief Set the country to search for in google
        /// @param result_country String of country to search for in google
        void _set_result_country(
            const std::string result_country // country to search for in google
        );

        /// @brief Set the safe search
        /// @param safe String of safe search
        void _set_safe(
            const std::string safe // safe search
        );

        /// @brief Set the sort order
        /// @param sort String of sort order
        void _set_sort(
            const std::string sort // sort order
        );

        /// @brief Set the json file to save search result
        /// @param json_file Name of the file to save response data
        void _set_response_file(
            const std::string json_file // Name of the file to save response data
        );

        /// @brief Set the name of env file that contains secret keys
        /// @param env_file Name of the file that contains Google Search API and CX Keys
        void _set_env_file(
            const std::string env_file // Name of the file that contains Google Search API and CX Keys
        );

        /// @brief Search the google based on given query
        /// @param query Query to search on google
        /// @param json_file Name of the file to save response data
        void _search_google(
            const std::string query, // Query to search Google
            const std::string json_file // Name of the file to save response data
        );

        /// @brief Parse Json file and retrive relevant information of specified index
        /// @param result_index Index of individual result to parse
        /// @param title Get Title
        /// @param snippet Get Snippet
        /// @param link Get Link
        /// @param image Get Image
        /// @param filename Name of the file to retrive response data from
        void _get_result(
            const int result_index, // Index of individual result to parse
            
            const bool title, // Get Title
            const bool snippet, // Get Snippet
            const bool link, // Get Link
            const bool image, // Get Image
            
            const std::string filename // Name of the file to retrive response data from
        );
};

#endif