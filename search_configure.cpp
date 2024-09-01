#include <string>
#include <vector>

class GoogleSearch{
    private:
        // Class Variables
        std::string __api_key;
        std::string __cx_key;

        const int __filter[2] = {0, 1}; // Controls turning on or off the duplicate content filter.
        const int __c2coff[2] = {0, 1}; // Enables or disables Simplified and Traditional Chinese Search.

        const std::string __available_languages[36] = {"lang_ar", "lang_bg", "lang_ca", "lang_cs", "lang_da", "lang_de", "lang_el", "lang_en", "lang_es", "lang_et", "lang_fi", "lang_fr", "lang_hr", "lang_hu", "lang_id", "lang_is", "lang_it", "lang_iw", "lang_ja", "lang_ko", "lang_lt", "lang_lv", "lang_nl", "lang_no", "lang_pl", "lang_pt", "lang_ro", "lang_ru", "lang_sk", "lang_sl", "lang_sr", "lang_sv", "lang_tr", "lang_zh-CN", "lang_zh-TW"};
        const std::string __available_interface_languages[83] = {"af", "sq", "sm", "ar", "az", "eu", "be", "bn", "bh", "bs", "bg", "ca", "zh-CN", "zh-TW", "hr", "cs", "da", "nl", "en", "eo", "et", "fo", "fi", "fr", "fy", "gl", "ka", "de", "el", "gu", "iw", "hi", "hu", "is", "id", "ia", "ga", "it", "ja", "jw", "kn", "ko", "la", "lv", "lt", "mk", "ms", "ml", "mt", "mr", "ne", "no", "nn", "oc", "fa", "pl", "pt-BR", "pt-PT", "pa", "ro", "ru", "gd", "sr", "si", "sk", "sl", "es", "su", "sw", "sv", "tl", "ta", "te", "th", "ti", "tr", "uk", "ur", "uz", "vi", "cy", "xh", "zu"};
        const std::string __available_user_countries[249] = {"af", "al", "dz", "as", "ad", "ao", "ai", "aq", "ag", "ar", "am", "aw", "au", "at", "az", "bs", "bh", "bd", "bb", "by", "be", "bz", "bj", "bm", "bt", "bo", "ba", "bw", "bv", "br", "io", "bn", "bg", "bf", "bi", "kh", "cm", "ca", "cv", "ky", "cf", "td", "cl", "cn", "cx", "cc", "co", "km", "cg", "cd", "ck", "cr", "ci", "hr", "cu", "cy", "cz", "dk", "dj", "dm", "do", "ec", "eg", "sv", "gq", "er", "ee", "et", "fk", "fo", "fj", "fi", "fr", "gf", "pf", "tf", "ga", "gm", "ge", "de", "gh", "gi", "gr", "gl", "gd", "gp", "gu", "gt", "gn", "gw", "gy", "ht", "hm", "va", "hn", "hk", "hu", "is", "in", "id", "ir", "iq", "ie", "il", "it", "jm", "jp", "jo", "kz", "ke", "ki", "kp", "kr", "kw", "kg", "la", "lv", "lb", "ls", "lr", "ly", "li", "lt", "lu", "mo", "mk", "mg", "mw", "my", "mv", "ml", "mt", "mh", "mq", "mr", "mu", "yt", "mx", "fm", "md", "mc", "mn", "ms", "ma", "mz", "mm", "na", "nr", "np", "nl", "an", "nc", "nz", "ni", "ne", "ng", "nu", "nf", "mp", "no", "om", "pk", "pw", "ps", "pa", "pg", "py", "pe", "ph", "pn", "pl", "pt", "pr", "qa", "re", "ro", "ru", "rw", "sh", "kn", "lc", "pm", "vc", "ws", "sm", "st", "sa", "sn", "cs", "sc", "sl", "sg", "sk", "si", "sb", "so", "za", "gs", "es", "lk", "sd", "sr", "sj", "sz", "se", "ch", "sy", "tw", "tj", "tz", "th", "tl", "tg", "tk", "to", "tt", "tn", "tr", "tm", "tc", "tv", "ug", "ua", "ae", "uk", "us", "um", "uy", "uz", "vu", "ve", "vn", "vg", "vi", "wf", "eh", "ye", "zm", "zw"};
        const std::string __available_result_countries[249] = {"countryAF", "countryAL", "countryDZ", "countryAS", "countryAD", "countryAO", "countryAI", "countryAQ", "countryAG", "countryAR", "countryAM", "countryAW", "countryAU", "countryAT", "countryAZ", "countryBS", "countryBH", "countryBD", "countryBB", "countryBY", "countryBE", "countryBZ", "countryBJ", "countryBM", "countryBT", "countryBO", "countryBA", "countryBW", "countryBV", "countryBR", "countryIO", "countryBN", "countryBG", "countryBF", "countryBI", "countryKH", "countryCM", "countryCA", "countryCV", "countryKY", "countryCF", "countryTD", "countryCL", "countryCN", "countryCX", "countryCC", "countryCO", "countryKM", "countryCG", "countryCD", "countryCK", "countryCR", "countryCI", "countryHR", "countryCU", "countryCY", "countryCZ", "countryDK", "countryDJ", "countryDM", "countryDO", "countryTP", "countryEC", "countryEG", "countrySV", "countryGQ", "countryER", "countryEE", "countryET", "countryEU", "countryFK", "countryFO", "countryFJ", "countryFI", "countryFR", "countryFX", "countryGF", "countryPF", "countryTF", "countryGA", "countryGM", "countryGE", "countryDE", "countryGH", "countryGI", "countryGR", "countryGL", "countryGD", "countryGP", "countryGU", "countryGT", "countryGN", "countryGW", "countryGY", "countryHT", "countryHM", "countryVA", "countryHN", "countryHK", "countryHU", "countryIS", "countryIN", "countryID", "countryIR", "countryIQ", "countryIE", "countryIL", "countryIT", "countryJM", "countryJP", "countryJO", "countryKZ", "countryKE", "countryKI", "countryKP", "countryKR", "countryKW", "countryKG", "countryLA", "countryLV", "countryLB", "countryLS", "countryLR", "countryLY", "countryLI", "countryLT", "countryLU", "countryMO", "countryMK", "countryMG", "countryMW", "countryMY", "countryMV", "countryML", "countryMT", "countryMH", "countryMQ", "countryMR", "countryMU", "countryYT", "countryMX", "countryFM", "countryMD", "countryMC", "countryMN", "countryMS", "countryMA", "countryMZ", "countryMM", "countryNA", "countryNR", "countryNP", "countryNL", "countryAN", "countryNC", "countryNZ", "countryNI", "countryNE", "countryNG", "countryNU", "countryNF", "countryMP", "countryNO", "countryOM", "countryPK", "countryPW", "countryPS", "countryPA", "countryPG", "countryPY", "countryPE", "countryPH", "countryPN", "countryPL", "countryPT", "countryPR", "countryQA", "countryRE", "countryRO", "countryRU", "countryRW", "countrySH", "countryKN", "countryLC", "countryPM", "countryVC", "countryWS", "countrySM", "countryST", "countrySA", "countrySN", "countryCS", "countrySC", "countrySL", "countrySG", "countrySK", "countrySI", "countrySB", "countrySO", "countryZA", "countryGS", "countryES", "countryLK", "countrySD", "countrySR", "countrySJ", "countrySZ", "countrySE", "countryCH", "countrySY", "countryTW", "countryTJ", "countryTZ", "countryTH", "countryTG", "countryTK", "countryTO", "countryTT", "countryTN", "countryTR", "countryTM", "countryTC", "countryTV", "countryUG", "countryUA", "countryAE", "countryUK", "countryUS", "countryUM", "countryUY", "countryUZ", "countryVU", "countryVE", "countryVN", "countryVG", "countryVI", "countryWF", "countryEH", "countryYE", "countryYU", "countryZM", "countryZW"};
        const std::string __available_filetypes[64] = {".pdf", ".ps", ".csv", ".epub", ".kmz", ".gpx", ".hwp", ".htm", ".html", ".xls", ".xlsx", ".ppt", ".pptx", ".doc", ".docx", ".odp", ".ods", ".odt", ".rtf", ".svg", ".tex", ".txt", ".text", ".bas", ".c", ".cc", ".cpp", ".cxx", ".h", ".hpp", ".cs", ".java", ".pl", ".py", ".wml", ".wap", ".xml", "BMP", "GIF", "JPEG", "PNG", "WebP", "SVG", "3GP", "3G2", "ASF", "AVI", "DivX", "M2V", "M3U", "M3U8", "M4V", "MKV", "MOV", "MP4", "MPEG", "OGV", "QVT", "RAM", "RM", "VOB", "WebM", "WMV", "XAP"};
        const std::string __safe[2] = {"active", "off"}; // Safe search
        const std::string __sort[2] = {"date-sdate:a", "date-sdate:d"}; // ascending or descending order sort by date
        const std::string __site_search_filter[2] = {"i", "e"};
        const std::string __date_restrict[4] = {"d", "w", "m", "y"};
        const std::string __search_type[1] = {"image"};

        // Class Functions
        void __get_api_cx(
            std::string filename = "secret_files/.env"
        ){ // Load API key and CX key to class variables
            this->__api_key = "";
            this->__cx_key = "";
        }
        
    public:
        // https://www.googleapis.com/customsearch/v1?q={searchTerms}&searchType={searchType}&fileType={fileType?}&rights={rights?}&imgSize={imgSize?}&imgType={imgType?}&imgColorType={imgColorType?}&imgDominantColor={imgDominantColor?}&alt=json

        GoogleSearch(
            const int num_results = 10, // Results to return for the search
            const int start_index = 0, // Position to start from when getting search results
            const int filter = 0, // turn on or off duplicate content
            const int c2coff = 0, // turn on or off Simplified and Traditional Chinese Search
            const int date_restrict = 0,
            
            const std::string extra_query = "",
            const std::string exact_terms = "",
            const std::string exclude_terms = "",
            const std::string site_search = "",
            const std::string site_search_filter = "",
            const std::string link_site = "",
            const std::string or_terms = "",
            const std::string date_restrict_type = "",
            const std::string low_range = "", // query terms to append before the search query
            const std::string high_range = "", // query terms to append after the search query
            const std::string search_type = "",
            const std::string filetype = "",

            const std::string language = "lang_en", // Language to search google in. Defualt is 'English'
            const std::string interface_language = "en",
            const std::string user_country = "us", // Country to search from in google
            const std::string result_country = "countryUS", // Country to search for in google
            const std::string safe = "active", // Whether to show explicit results.
            const std::string sort = "descending", // Return results in specific order

        ){}
        ~GoogleSearch(){}
};