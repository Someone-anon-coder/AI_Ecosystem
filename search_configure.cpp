#include <string>
#include <vector>

// Class to implement Google Custom JSON Search
class GoogleSearch{
    private:
        // Class Private Variables

        std::string __api_key; // Google custom search json API key
        std::string __cx_key; // Google custom search json Search Engine ID
        std::string __search_url = "https://www.googleapis.com/customsearch/v1?q={searchTerms}&num={count?}&start={startIndex?}&lr={language?}&safe={safe?}&cx={cx?}&sort={sort?}&filter={filter?}&gl={gl?}&cr={cr?}&googlehost={googleHost?}&c2coff={disableCnTwTranslation?}&hq={hq?}&hl={hl?}&siteSearch={siteSearch?}&siteSearchFilter={siteSearchFilter?}&exactTerms={exactTerms?}&excludeTerms={excludeTerms?}&linkSite={linkSite?}&orTerms={orTerms?}&dateRestrict={dateRestrict?}&lowRange={lowRange?}&highRange={highRange?}&searchType={searchType}&fileType={fileType?}&rights={rights?}&imgSize={imgSize?}&imgType={imgType?}&imgColorType={imgColorType?}&imgDominantColor={imgDominantColor?}&alt=json";

        const int __filter[2] = {0, 1}; // Controls turning on or off the duplicate content filter.
        const int __c2coff[2] = {0, 1}; // Enables or disables Simplified and Traditional Chinese Search.

        const std::string __available_languages[36] = {"lang_ar", "lang_bg", "lang_ca", "lang_cs", "lang_da", "lang_de", "lang_el", "lang_en", "lang_es", "lang_et", "lang_fi", "lang_fr", "lang_hr", "lang_hu", "lang_id", "lang_is", "lang_it", "lang_iw", "lang_ja", "lang_ko", "lang_lt", "lang_lv", "lang_nl", "lang_no", "lang_pl", "lang_pt", "lang_ro", "lang_ru", "lang_sk", "lang_sl", "lang_sr", "lang_sv", "lang_tr", "lang_zh-CN", "lang_zh-TW"}; // Availalble languages for documents to search in
        const std::string __available_interface_languages[83] = {"af", "sq", "sm", "ar", "az", "eu", "be", "bn", "bh", "bs", "bg", "ca", "zh-CN", "zh-TW", "hr", "cs", "da", "nl", "en", "eo", "et", "fo", "fi", "fr", "fy", "gl", "ka", "de", "el", "gu", "iw", "hi", "hu", "is", "id", "ia", "ga", "it", "ja", "jw", "kn", "ko", "la", "lv", "lt", "mk", "ms", "ml", "mt", "mr", "ne", "no", "nn", "oc", "fa", "pl", "pt-BR", "pt-PT", "pa", "ro", "ru", "gd", "sr", "si", "sk", "sl", "es", "su", "sw", "sv", "tl", "ta", "te", "th", "ti", "tr", "uk", "ur", "uz", "vi", "cy", "xh", "zu"}; // Language to display results in
        const std::string __available_user_countries[249] = {"af", "al", "dz", "as", "ad", "ao", "ai", "aq", "ag", "ar", "am", "aw", "au", "at", "az", "bs", "bh", "bd", "bb", "by", "be", "bz", "bj", "bm", "bt", "bo", "ba", "bw", "bv", "br", "io", "bn", "bg", "bf", "bi", "kh", "cm", "ca", "cv", "ky", "cf", "td", "cl", "cn", "cx", "cc", "co", "km", "cg", "cd", "ck", "cr", "ci", "hr", "cu", "cy", "cz", "dk", "dj", "dm", "do", "ec", "eg", "sv", "gq", "er", "ee", "et", "fk", "fo", "fj", "fi", "fr", "gf", "pf", "tf", "ga", "gm", "ge", "de", "gh", "gi", "gr", "gl", "gd", "gp", "gu", "gt", "gn", "gw", "gy", "ht", "hm", "va", "hn", "hk", "hu", "is", "in", "id", "ir", "iq", "ie", "il", "it", "jm", "jp", "jo", "kz", "ke", "ki", "kp", "kr", "kw", "kg", "la", "lv", "lb", "ls", "lr", "ly", "li", "lt", "lu", "mo", "mk", "mg", "mw", "my", "mv", "ml", "mt", "mh", "mq", "mr", "mu", "yt", "mx", "fm", "md", "mc", "mn", "ms", "ma", "mz", "mm", "na", "nr", "np", "nl", "an", "nc", "nz", "ni", "ne", "ng", "nu", "nf", "mp", "no", "om", "pk", "pw", "ps", "pa", "pg", "py", "pe", "ph", "pn", "pl", "pt", "pr", "qa", "re", "ro", "ru", "rw", "sh", "kn", "lc", "pm", "vc", "ws", "sm", "st", "sa", "sn", "cs", "sc", "sl", "sg", "sk", "si", "sb", "so", "za", "gs", "es", "lk", "sd", "sr", "sj", "sz", "se", "ch", "sy", "tw", "tj", "tz", "th", "tl", "tg", "tk", "to", "tt", "tn", "tr", "tm", "tc", "tv", "ug", "ua", "ae", "uk", "us", "um", "uy", "uz", "vu", "ve", "vn", "vg", "vi", "wf", "eh", "ye", "zm", "zw"}; // Available contries for users to search from
        const std::string __available_result_countries[249] = {"countryAF", "countryAL", "countryDZ", "countryAS", "countryAD", "countryAO", "countryAI", "countryAQ", "countryAG", "countryAR", "countryAM", "countryAW", "countryAU", "countryAT", "countryAZ", "countryBS", "countryBH", "countryBD", "countryBB", "countryBY", "countryBE", "countryBZ", "countryBJ", "countryBM", "countryBT", "countryBO", "countryBA", "countryBW", "countryBV", "countryBR", "countryIO", "countryBN", "countryBG", "countryBF", "countryBI", "countryKH", "countryCM", "countryCA", "countryCV", "countryKY", "countryCF", "countryTD", "countryCL", "countryCN", "countryCX", "countryCC", "countryCO", "countryKM", "countryCG", "countryCD", "countryCK", "countryCR", "countryCI", "countryHR", "countryCU", "countryCY", "countryCZ", "countryDK", "countryDJ", "countryDM", "countryDO", "countryTP", "countryEC", "countryEG", "countrySV", "countryGQ", "countryER", "countryEE", "countryET", "countryEU", "countryFK", "countryFO", "countryFJ", "countryFI", "countryFR", "countryFX", "countryGF", "countryPF", "countryTF", "countryGA", "countryGM", "countryGE", "countryDE", "countryGH", "countryGI", "countryGR", "countryGL", "countryGD", "countryGP", "countryGU", "countryGT", "countryGN", "countryGW", "countryGY", "countryHT", "countryHM", "countryVA", "countryHN", "countryHK", "countryHU", "countryIS", "countryIN", "countryID", "countryIR", "countryIQ", "countryIE", "countryIL", "countryIT", "countryJM", "countryJP", "countryJO", "countryKZ", "countryKE", "countryKI", "countryKP", "countryKR", "countryKW", "countryKG", "countryLA", "countryLV", "countryLB", "countryLS", "countryLR", "countryLY", "countryLI", "countryLT", "countryLU", "countryMO", "countryMK", "countryMG", "countryMW", "countryMY", "countryMV", "countryML", "countryMT", "countryMH", "countryMQ", "countryMR", "countryMU", "countryYT", "countryMX", "countryFM", "countryMD", "countryMC", "countryMN", "countryMS", "countryMA", "countryMZ", "countryMM", "countryNA", "countryNR", "countryNP", "countryNL", "countryAN", "countryNC", "countryNZ", "countryNI", "countryNE", "countryNG", "countryNU", "countryNF", "countryMP", "countryNO", "countryOM", "countryPK", "countryPW", "countryPS", "countryPA", "countryPG", "countryPY", "countryPE", "countryPH", "countryPN", "countryPL", "countryPT", "countryPR", "countryQA", "countryRE", "countryRO", "countryRU", "countryRW", "countrySH", "countryKN", "countryLC", "countryPM", "countryVC", "countryWS", "countrySM", "countryST", "countrySA", "countrySN", "countryCS", "countrySC", "countrySL", "countrySG", "countrySK", "countrySI", "countrySB", "countrySO", "countryZA", "countryGS", "countryES", "countryLK", "countrySD", "countrySR", "countrySJ", "countrySZ", "countrySE", "countryCH", "countrySY", "countryTW", "countryTJ", "countryTZ", "countryTH", "countryTG", "countryTK", "countryTO", "countryTT", "countryTN", "countryTR", "countryTM", "countryTC", "countryTV", "countryUG", "countryUA", "countryAE", "countryUK", "countryUS", "countryUM", "countryUY", "countryUZ", "countryVU", "countryVE", "countryVN", "countryVG", "countryVI", "countryWF", "countryEH", "countryYE", "countryYU", "countryZM", "countryZW"}; // Available countries to get results from
        const std::string __available_filetypes[64] = {".pdf", ".ps", ".csv", ".epub", ".kmz", ".gpx", ".hwp", ".htm", ".html", ".xls", ".xlsx", ".ppt", ".pptx", ".doc", ".docx", ".odp", ".ods", ".odt", ".rtf", ".svg", ".tex", ".txt", ".text", ".bas", ".c", ".cc", ".cpp", ".cxx", ".h", ".hpp", ".cs", ".java", ".pl", ".py", ".wml", ".wap", ".xml", "BMP", "GIF", "JPEG", "PNG", "WebP", "SVG", "3GP", "3G2", "ASF", "AVI", "DivX", "M2V", "M3U", "M3U8", "M4V", "MKV", "MOV", "MP4", "MPEG", "OGV", "QVT", "RAM", "RM", "VOB", "WebM", "WMV", "XAP"}; // Available filetypes extension for documents
        const std::string __safe[2] = {"active", "off"}; // Safe search
        const std::string __sort[2] = {"date-sdate:a", "date-sdate:d"}; // ascending or descending order sort by date
        const std::string __site_search_filter[2] = {"i", "e"}; // Whether to include or exclude a particular site
        const std::string __date_restrict[4] = {"d", "w", "m", "y"}; // Whether to restrict search based on day, week, month or year
        const std::string __search_type[1] = {"image"}; // Whether to search for images
        const std::string __rights[5] = {"cc_publicdomain", "cc_attribute", "cc_sharealike", "cc_noncommercial", "cc_nonderived"}; // Available rights on the documents
        const std::string __image_sizes[7] = {"huge", "icon", "large", "medium", "small", "xlarge", "xxlarge"}; // Available sizes for image search
        const std::string __image_types[6] = {"clipart", "face", "lineart", "stock", "photo", "animated"}; // Available style of images
        const std::string __image_color_types[4] = {"color", "gray", "mono", "trans"}; // Available color types to search images
        const std::string __image_dominant_color_types[12] = {"black", "blue", "brown", "gray", "green", "orange", "pink", "purple", "red", "teal", "white", "yellow"}; // Available dominant colors to search for images

        // Class Private Functions

        // Function to load API and CX keys from a file
        void __get_api_cx(
            std::string filename = "secret_files/.env" // Name of the file that contains API and CX keys
        ){
            this->__api_key = "";
            this->__cx_key = "";
        }
        
    public:
        // Class Public Functions

        // Class Constructor
        GoogleSearch(
            const int _num_results = 10, // Results to return for the search
            const int _start_index = 0, // Position to start from when getting search results
            const int _filter = 0, // turn on or off duplicate content
            const int _c2coff = 0, // turn on or off Simplified and Traditional Chinese Search
            const int _date_restrict = 0, // Whether to restrict search based on dates. "1" for yes and "0" for no
            
            const std::string _extra_query = "", // Extra queries to include in the search terms
            const std::string _exact_terms = "", // A phrase that all documents in the search results must contain
            const std::string _exclude_terms = "", // A word or phrase that should not appear in any documents in the search results
            const std::string _site_search = "", // A given site which should always be included or excluded from results. Based on *_site_search_filter*
            const std::string _site_search_filter = "", // Whether to Include or exclude the sites specified in *_site_search*
            const std::string _link_site = "", // Specifies that all search results should contain a link to a particular URL
            const std::string _or_terms = "", // Provides additional search terms to check for in a document, where each document in the search results must contain at least one of the additional search terms
            const std::string _date_restrict_type = "", // Restricts results to URLs based on date. In format dateType[number]. Example: m3 restricts to past 3 months
            const std::string _low_range = "", // query terms to append before the search query
            const std::string _high_range = "", // query terms to append after the search query
            const std::string _search_type = "", // Specifies the search type: image. If unspecified, results are limited to webpages
            const std::string _filetype = "", // Restricts results to files of a specified extension
            const std::string _rights = "", // Filters based on licensing
            const std::string _img_size = "", // Returns images of a specified size
            const std::string _img_type = "", // Returns images of a type
            const std::string _img_color_type = "", // Returns black and white, grayscale, transparent, or color images
            const std::string _img_dominant_color = "", // Returns images of a specific dominant color

            const std::string _language = "lang_en", // Language to search google in. Defualt is 'English'
            const std::string _interface_language = "en", // Sets the user interface language
            const std::string _user_country = "us", // Country to search from in google
            const std::string _result_country = "countryUS", // Country to search for in google
            const std::string _safe = "active", // Whether to show explicit results.
            const std::string _sort = "descending" // Return results in specific order

        ){}
        ~GoogleSearch(){}
};