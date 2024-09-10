#include <vector>
#include "cpp_files/program_files/read_dotenv.cpp"

/// @brief Class to implement Google Custom JSON Search
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

        /// @brief Function to load API and CX keys from a file
        /// @param filename Name of the file that contains API and CX keys
        void __get_api_cx(
            std::string filename = "secret_files/.env" // Name of the file that contains API and CX keys
        ){
            std::unordered_map<std::string, std::string> environment_variables = load_env_file(filename);

            this->__api_key = get_env_value(environment_variables, "SEARCH_API_KEY");
            this->__cx_key = get_env_value(environment_variables, "SEARCH_CSE_KEY");
        }

        /// @brief Create search url used to search on google,
        /// @brief Omiting and Adding appropriate parameters only
        void __construct_search_url(){
            std::string cx_key = this->__cx_key; // local variable to access cx key
            std::string api_key = this->__api_key; // local variable to access api key

            std::string search_url = "https://www.googleapis.com/customsearch/v1?q=" + this->_search_terms + "&key=" + api_key + "&cx=" + cx_key; // Search url constructed for searching on google

            search_url += this->_num_results > 0 ? "&num=" + std::to_string(this->_num_results) : "";
            search_url += this->_start_index > -1 ? "&start=" + std::to_string(this->_start_index) : "";
            search_url += this->_language != "" ? "&lr=" + this->_language : "";
            search_url += this->_safe != "" ? "&safe=" + this->_safe : "";
            search_url += this->_sort != "" ? "&sort=" + this->_sort : "";
            
            search_url += "&filter=" + std::to_string(this->_filter);
            
            search_url += this->_user_country != "" ? "&userLocation=" + this->_user_country : "";
            search_url += this->_interface_language != "" ? "&gl=" + this->_interface_language : "";
            search_url += this->_user_country != "" ? "&location=" + this->_user_country : "";
            search_url += this->_result_country != "" ? "&cr=" + this->_result_country : "";
            
            search_url += "&c2coff=" + std::to_string(this->_c2coff);

            search_url += this->_extra_query != "" ? "&hq=" + this->_extra_query : "";
            search_url += this->_interface_language != "" ? "&hl=" + this->_interface_language : "";
            search_url += this->_site_search != "" ? "&siteSearch=" + this->_site_search : "";
            search_url += this->_site_search_filter != "" ? "&siteSearchFilter=" + this->_site_search_filter : "";
            search_url += this->_exact_terms != "" ? "&exactTerms=" + this->_exact_terms : "";
            search_url += this->_exclude_terms != "" ? "&excludeTerms=" + this->_exclude_terms : "";
            search_url += this->_link_site != "" ? "&linkSite=" + this->_link_site : "";
            search_url += this->_or_terms != "" ? "&orTerms=" + this->_or_terms : "";
            search_url += this->_date_restrict_type != "" ? "&dateRestrict=" + this->_date_restrict_type : "";
            search_url += this->_low_range != "" ? "&lowRange=" + this->_low_range : "";
            search_url += this->_high_range != "" ? "&highRange=" + this->_high_range : "";
            search_url += this->_search_type != "" ? "&searchType=" + this->_search_type : "";
            search_url += this->_filetype != "" ? "&fileType=" + this->_filetype : "";
            search_url += this->_rights != "" ? "&rights=" + this->_rights : "";
            search_url += this->_img_size != "" ? "&imgSize=" + this->_img_size : "";
            search_url += this->_img_type != "" ? "&imgType=" + this->_img_type : "";
            search_url += this->_img_color_type != "" ? "&imgColorType=" + this->_img_color_type : "";
            search_url += this->_img_dominant_color != "" ? "&imgDominantColor=" + this->_img_dominant_color : "";

            this->_search_url = search_url;
        }
        
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
        GoogleSearch(
            const std::string search_terms = "", // Query to search for on google

            const int num_results = 0, // Results to return for the search
            const int start_index = -1, // Position to start from when getting search results
            const int filter = 0, // turn on or off duplicate content
            const int c2coff = 0, // turn on or off Simplified and Traditional Chinese Search
            const int date_restrict = 0, // Whether to restrict search based on dates. "1" for yes and "0" for no
            
            const std::string extra_query = "", // Extra queries to include in the search terms
            const std::string exact_terms = "", // A phrase that all documents in the search results must contain
            const std::string exclude_terms = "", // A word or phrase that should not appear in any documents in the search results
            const std::string site_search = "", // A given site which should always be included or excluded from results. Based on *_site_search_filter*
            const std::string site_search_filter = "", // Whether to Include or exclude the sites specified in *_site_search*
            const std::string link_site = "", // Specifies that all search results should contain a link to a particular URL
            const std::string or_terms = "", // Provides additional search terms to check for in a document, where each document in the search results must contain at least one of the additional search terms
            const std::string date_restrict_type = "", // Restricts results to URLs based on date. In format dateType[number]. Example: m3 restricts to past 3 months
            const std::string low_range = "", // query terms to append before the search query
            const std::string high_range = "", // query terms to append after the search query
            const std::string search_type = "", // Specifies the search type: image. If unspecified, results are limited to webpages
            const std::string filetype = "", // Restricts results to files of a specified extension
            const std::string rights = "", // Filters based on licensing
            const std::string img_size = "", // Returns images of a specified size
            const std::string img_type = "", // Returns images of a type
            const std::string img_color_type = "", // Returns black and white, grayscale, transparent, or color images
            const std::string img_dominant_color = "", // Returns images of a specific dominant color
            const std::string language = "", // Language to search google in. Defualt is 'English'
            const std::string interface_language = "", // Sets the user interface language
            const std::string user_country = "", // Country to search from in google
            const std::string result_country = "", // Country to search for in google
            const std::string safe = "", // Whether to show explicit results.
            const std::string sort = "" // Return results in specific order
        ){
            this->_search_terms = search_terms;

            this->_num_results = num_results;
            this->_start_index = start_index;
            this->_filter = filter;
            this->_c2coff = c2coff;
            this->_date_restrict = date_restrict;

            this->_extra_query = extra_query;
            this->_exact_terms = exact_terms;
            this->_exclude_terms = exclude_terms;
            this->_site_search = site_search;
            this->_site_search_filter = site_search_filter;
            this->_link_site = link_site;
            this->_or_terms = or_terms;
            this->_date_restrict_type = date_restrict_type;
            this->_low_range = low_range;
            this->_high_range = high_range;
            this->_search_type = search_type;
            this->_filetype = filetype;
            this->_rights = rights;
            this->_img_size = img_size;
            this->_img_type = img_type;
            this->_img_color_type = img_color_type;
            this->_img_dominant_color = img_dominant_color;

            this->_language = language;
            this->_interface_language = interface_language;
            this->_user_country = user_country;
            this->_result_country = result_country;
            this->_safe = safe;
            this->_sort = sort;

            this->__get_api_cx();

            if (search_terms != "")
                this->__construct_search_url();
        }

        /// @brief Class Destructor. Deinitializes the class variables
        ~GoogleSearch(){
            this->__api_key = "";
            this->__cx_key = "";

            this->_num_results = 10;
            this->_start_index = 0;
            this->_filter = 0;
            this->_c2coff = 0;
            this->_date_restrict = 0;

            this->_extra_query = "";
            this->_exact_terms = "";
            this->_exclude_terms = "";
            this->_site_search = "";
            this->_site_search_filter = "";
            this->_link_site = "";
            this->_or_terms = "";
            this->_date_restrict_type = "";
            this->_low_range = "";
            this->_high_range = "";
            this->_search_type = "";
            this->_filetype = "";
            this->_rights = "";
            this->_img_size = "";
            this->_img_type = "";
            this->_img_color_type = "";
            this->_img_dominant_color = "";
            this->_language = "";
            this->_interface_language = "";
            this->_user_country = "";
            this->_result_country = "";
            this->_safe = "";
            this->_sort = "";
        }

        // Getters

        /// @brief Number of results to be returned by google search
        /// @return Integer of number of results
        int _get_num_results(){
            return this->_num_results;
        }

        /// @brief Index at which search result starts
        /// @return Integer of start index
        int _get_start_index(){
            return this->_start_index;
        }

        /// @brief Check whether duplicate is turned On or Off
        /// @return Integer specifying if duplicate content is on or off
        int _get_filter(){
            return this->_filter;
        }

        /// @brief Check whether Simplified and Traditional Chinese Search is turned On or Off
        /// @return Integer specifying if Simplified and Traditional Chinese Search is on or off
        int _get_c2coff(){
            return this->_c2coff;
        }

        /// @brief Check whether search is restricted by date
        /// @return Integer specifying if search is restricted by date
        int _get_date_restrict(){
            return this->_date_restrict;
        }

        /// @brief Get the query used to search on google
        /// @return String of search query 
        std::string _get_query(){
            return this->_search_terms;
        }

        /// @brief Get the constructed url used to query google
        /// @return String of constructed url
        std::string _get_search_url(){
            return this->_search_url;
        }

        /// @brief Get the extra queries in the search
        /// @return String of extra queries in the search
        std::string _get_extra_query(){
            return this->_extra_query;
        }

        /// @brief Get the extra terms each document will include when searching
        /// @return String of extra terms
        std::string _get_exact_terms(){
            return this->_exact_terms;
        }

        /// @brief Get the word which is excluded from appearing in documents from search result
        /// @return String of excluded terms
        std::string _get_exclude_terms(){
            return this->_exclude_terms;
        }

        /// @brief Get the site to always include or exclude when searching a query
        /// @return String of site which is always included or excluded
        std::string _get_site_search(){
            return this->_site_search;
        }

        /// @brief Get the value specifying is site should always be included or excluded when searching
        /// @return String of filter specifying whether site is included or excluded
        std::string _get_site_search_filter(){
            return this->_site_search_filter;
        }

        /// @brief Get the link included in each result
        /// @return String of link
        std::string _get_link_site(){
            return this->_link_site;
        }

        /// @brief Get the extra terms included in documents in search result
        /// @return String of extra terms
        std::string _get_or_terms(){
            return this->_or_terms;
        }

        /// @brief Get the date restricting the search results
        /// @return String of date restricting the search results
        std::string _get_date_restrict_type(){
            return this->_date_restrict_type;
        }

        /// @brief Get the query appended to before the search query
        /// @return String of query appended to before the search query
        std::string _get_low_range(){
            return this->_low_range;
        }

        /// @brief Get the query appended to after the search query
        /// @return String of query appended to after the search query
        std::string _get_high_range(){
            return this->_high_range;
        }

        /// @brief Get the search type of the query
        /// @return String of search type
        std::string _get_search_type(){
            return this->_search_type;
        }

        /// @brief Get the filetype of the query
        /// @return String of filetype
        std::string _get_filetype(){
            return this->_filetype;
        }

        /// @brief Get the licensing of the query
        /// @return String of licensing
        std::string _get_rights(){
            return this->_rights;
        }

        /// @brief Get the size of the image
        /// @return String of image size
        std::string _get_img_size(){
            return this->_img_size;
        }

        /// @brief Get the type of the image
        /// @return String of image type
        std::string _get_img_type(){
            return this->_img_type;
        }

        /// @brief Get the color type of the image
        /// @return String of image color type
        std::string _get_img_color_type(){
            return this->_img_color_type;
        }

        /// @brief Get the dominant color of the image
        /// @return String of image dominant color
        std::string _get_img_dominant_color(){
            return this->_img_dominant_color;
        }

        /// @brief Get the language to search google
        /// @return String of language
        std::string _get_language(){
            return this->_language;
        }

        /// @brief Get the user interface language
        /// @return String of user interface language
        std::string _get_interface_language(){
            return this->_interface_language;
        }

        /// @brief Get the country to search from in google
        /// @return String of country
        std::string _get_user_country(){
            return this->_user_country;
        }

        /// @brief Get the country to search for in google
        /// @return String of country
        std::string _get_result_country(){
            return this->_result_country;
        }

        /// @brief Get the safe search
        /// @return String of safe search
        std::string _get_safe(){
            return this->_safe;
        }

        /// @brief Get the sort order
        /// @return String of sort order
        std::string _get_sort(){
            return this->_sort;
        }

        // Setters

        /// @brief Set the number of results to be returned by google search
        /// @param num_results Integer of number of results
        void _set_num_results(
            const int num_results // number of results to return 
        ){
            this->_num_results = num_results;
        }

        /// @brief Set the index at which search result starts
        /// @param start_index Integer of start index
        void _set_start_index(
            const int start_index // index at which search result starts
        ){
            this->_start_index = start_index;
        }

        /// @brief Set the check whether duplicate is turned On or Off
        /// @param filter Integer specifying if duplicate content is on or off
        void _set_filter(
            const int filter // check whether duplicate is turned On or Off
        ){
            this->_filter = filter;
        }

        /// @brief Turn on or off Simplified and Traditional Chinese
        /// @param c2coff Integer Specifying to turn on or off Simplified and Traditional Chinese
        void _set_c2coff(
            const int c2coff // Turn on or off Simplified and Traditional Chinese
        ){
            this->_c2coff = c2coff;
        }

        /// @brief Set whether to restrict search based on date
        /// @param date_restrict Whether to restrict search based on date
        void _set_date_restrict(
            const int date_restrict // check whether search is restricted by date
        ){
            this->_date_restrict = date_restrict;
        }

        /// @brief Set extra queries to search for with the search query
        /// @param extra_query String of extra queries to search for with the search query
        void _set_extra_query(
            const std::string extra_query // extra queries to search for with the search query
        ){
            this->_extra_query = extra_query;
        }

        /// @brief Set the phrase to include in document in search results
        /// @param exact_terms String of phrase to include in document in search results
        void _set_exact_terms(
            const std::string exact_terms // phrase to include in document in search results
        ){
            this->_exact_terms = exact_terms;
        }

        /// @brief Set the terms to exclude from documents in search result
        /// @param exclude_terms String of terms to exclude from documents in search result
        void _set_exclude_terms(
            const std::string exclude_terms // terms to exclude from documents in search result
        ){
            this->_exclude_terms = exclude_terms;
        }

        /// @brief Set the site to always include or exclude from search results
        /// @param site_search String of site to always include or exclude from search results
        void _set_site_search(
            const std::string site_search // site to always include or exclude from search results
        ){
            this->_site_search = site_search;
        }

        /// @brief Set the value to always include or exclude site from search results
        /// @param site_search_filter Char of value specifying to include or exclude a site
        void _set_site_search_filter(
            const char site_search_filter // value specifying to include or exclude a site
        ){
            const auto filter = this->__site_search_filter;
            if (filter[0] == site_search_filter || filter[1] == site_search_filter)
                this->_site_search_filter = site_search_filter;
        }

        /// @brief Set the link to include in each search result
        /// @param link_site String of link to include in each search result
        void _set_link_site(
            const std::string link_site // link to include in each search result
        ){
            this->_link_site = link_site;
        }

        /// @brief Set the additional terms to include in the document in search result
        /// @param or_terms String of additional terms to include in documents
        void _set_or_terms(
            const std::string or_terms // additional terms to include in the document
        ){
            this->_or_terms = or_terms;
        }

        /// @brief Set the date restrict type to restrict search results
        /// @param date_restrict_type String of date restrict type to restrict search results
        void _set_date_restrict_type(
            const std::string date_restrict_type // date restrict type to restrict search results
        ){
            const auto types = this->__date_restrict;
            if (types[0] == date_restrict_type[0] || types[1] == date_restrict_type[0] || types[2] == date_restrict_type[0] || types[3] == date_restrict_type[0])
                this->_date_restrict_type = date_restrict_type;
        }
};
