#include "../header_files/search_configure.h"
#include <cstdint>
#include <fstream>
#include <string>

GoogleSearch::GoogleSearch(
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
    const std::string sort = "", // Return results in specific order

    const std::string json_file = "json_files/search_result.json", // Name of the json file to store search result
    const std::string env_file = "secret_files/.env" // Name of the env that contains Google Search API and CX Keys
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

    this->_json_file = json_file;
    this->_env_file = env_file;

    this->__get_api_cx(this->_env_file);

    if (search_terms != "")
        this->__construct_search_url();
};

GoogleSearch::~GoogleSearch(){
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

    this->_search_terms = "";
    this->_search_url = "";
    this->_json_file = "";
    this->_env_file = "";
};

std::map<std::string, std::map<std::string, std::string>> GoogleSearch::__class_info__(){
    std::map<std::string, std::string> __name_discription__ = { // Name and description of the class
        {"GoogleSearch", "Class for searching Google"}
    };

    std::map<std::string, std::string> __constuctor_paramters__ = { // Constructor paramter names and descriptions
        {"search_terms", "Query to search for on google"},
        {"num_results", "Results to return for the search"},
        {"start_index", "Position to start from when getting search results"},
        {"filter", "turn on or off duplicate content"},
        {"c2coff", "turn on or off Simplified and Traditional Chinese Search"},
        {"date_restrict", "Whether to restrict search based on dates. \"1\" for yes and \"0\" for no"},
        {"extra_query", "Extra queries to include in the search terms"},
        {"extra_terms", "A phrase to include in documents of the search"},
        {"exclude_terms", "A word or phrase to exclude from the search"},
        {"site_search", "A given site to always include or exclude from"},
        {"site_search_filter", "Whether to Include or exclude the sites specified in *site_search*"},
        {"link_site", "Specifies a link that should be in all search results"},
        {"or_terms", "Additional search terms to include in documents in search"},
        {"date_restrict_type", "Restrict results based on date"},
        {"low_range", "Query terms to append before a query"},
        {"high_range", "QUery terms to append after a query"},
        {"search_type", "Specifies the search type. Eg: \"image\""},
        {"filetype", "Restricts results to files of a specified extension"},
        {"rights", "Filters based on licensing"},
        {"img_size", "Returns images of specified size"},
        {"img_type", "Returns image of a type"},
        {"img_color_type", "Returns black and white, grayscale, transparent, or color images"},
        {"img_dominant_color", "Returns images of a specific dominant color"},
        {"language", "Language to search google in. Defualt is 'English'"},
        {"interface_language", "Sets the user interface language"},
        {"user_country", "Country to search from in google"},
        {"result_country", "Country to search for in google"},
        {"safe", "Whether to show explicit results."},
        {"sort", "Return results in specific order"},
        {"json_file", "Name of the json file to store search result"},
        {"env_file", "Name of the env file that contains Google Search API and CX Keys"},
    };

    std::map<std::string, std::string> __function_info__ = { // Function names and descriptions
        {"_get_num_results", "Returns the number of results to return"},
        {"_get_start_index", "Returns the index to start from when getting search results"},
        {"_get_filter", "Check whether duplicate is turned On or Off"},
        {"_get_c2coff", "Turn on or off Simplified and Traditional Chinese"},
        {"_get_date_restrict", "Check whether search is restricted by date"},
        {"_get_query", "Get the query used to search on google"},
        {"_get_search_url", "Get the constructed url used to query google"},
        {"_get_extra_query", "Get the extra queries used to search"},
        {"_get_exact_terms", "Get the exact terms each document will include when searching"},
        {"_get_exclude_terms", "Get the word which is excluded from appearing in documents from search result"},
        {"_get_site_search", "Get the site to always include or exclude when searching a query"},
        {"_get_site_search_filter", "Get the value specifying to include or exclude a site"},
        {"_get_link_site", "Get the link to include in each search result"},
        {"_get_or_terms", "Get the additional terms to include in the document"},
        {"_get_date_restrict_type", "Get the date restrict type to restrict search results"},
        {"_get_low_range", "Get the query appended before the search query"},
        {"_get_high_range", "Get the query appended after the search query"},
        {"_get_search_type", "Get the search type of the query"},
        {"_get_filetype", "Get the filetype of the query"},
        {"_get_rights", "Get the licensing of the query"},
        {"_get_img_size", "Get the size of the image"},
        {"_get_img_type", "Get the type of the image"},
        {"_get_img_color_type", "Get the color type of the image"},
        {"_get_img_dominant_color", "Get the dominant color of the image"},
        {"_get_language", "Get the language to search google in"},
        {"_get_interface_language", "Get the user interface language"},
        {"_get_user_country", "Get the country to search from in google"},
        {"_get_result_country", "Get the country to search for in google"},
        {"_get_safe", "Get the safe search"},
        {"_get_sort", "Get the sort order"},
        {"_get_json_file", "Get the name of the file to save response data"},
        {"_get_env_file", "Get the name of the file that contains Google Search API and CX Keys"},
        {"_set_num_results", "Set the number of results to return"},
        {"_set_start_index", "Set the index to start from when getting search results"},
        {"_set_filter", "Set to check whether duplicate is turned On or Off"},
        {"_set_c2coff", "Turn on or off Simplified and Traditional Chinese"},
        {"_set_date_restrict", "Set to check whether search is restricted by date"},
        {"_set_extra_query", "Set the extra queries to search for with the search query"},
        {"_set_exact_terms", "Set the phrase to include in document in search results"},
        {"_set_exclude_terms", "Set the terms to exclude from documents in search result"},
        {"_set_site_search", "Set the site to always include or exclude from search results"},
        {"_set_site_search_filter", "Set the value specifying to include or exclude a site"},
        {"_set_link_site", "Set the link to include in each search result"},
        {"_set_or_terms", "Set the additional terms to include in the document"},
        {"_set_date_restrict_type", "Set the date restrict type to restrict search results"},
        {"_set_low_range", "Set the query appended before the search query"},
        {"_set_high_range", "Set the query appended after the search query"},
        {"_set_search_type", "Set the search type of the query"},
        {"_set_filetype", "Set the filetype of the query"},
        {"_set_rights", "Set the licensing of the query"},
        {"_set_img_size", "Set the size of the image"},
        {"_set_img_type", "Set the type of the image"},
        {"_set_img_color_type", "Set the color type of the image"},
        {"_set_img_dominant_color", "Set the dominant color of the image"},
        {"_set_language", "Set the language to search google in"},
        {"_set_interface_language", "Set the user interface language"},
        {"_set_user_country", "Set the country to search from in google"},
        {"_set_result_country", "Set the country to search for in google"},
        {"_set_safe", "Set the safe search"},
        {"_set_sort", "Set the sort order"},
        {"_set_response_file", "Set the json file to save search result"},
        {"_set_env_file", "Set the file that contains Google Search API and CX Keys"},
        {"_search_google", "Search the google based on given query"},
        {"_get_result", "Parse Json file and retrive relevant information of specified index"}
    };

    std::map<std::string, std::string> __function_parameters__ = { // Function names and parameters
        {"_get_num_results", "Not used"},
        {"_get_start_index", "Not used"},
        {"_get_filter", "Not used"},
        {"_get_c2coff", "Not used"},
        {"_get_date_restrict", "Not used"},
        {"_get_query", "Not used"},
        {"_get_search_url", "Not used"},
        {"_get_extra_query", "Not used"},
        {"_get_exact_terms", "Not used"},
        {"_get_exclude_terms", "Not used"},
        {"_get_site_search", "Not used"},
        {"_get_site_search_filter", "Not used"},
        {"_get_link_site", "Not used"},
        {"_get_or_terms", "Not used"},
        {"_get_date_restrict_type", "Not used"},
        {"_get_low_range", "Not used"},
        {"_get_high_range", "Not used"},
        {"_get_search_type", "Not used"},
        {"_get_filetype", "Not used"},
        {"_get_rights", "Not used"},
        {"_get_img_size", "Not used"},
        {"_get_img_type", "Not used"},
        {"_get_img_color_type", "Not used"},
        {"_get_img_dominant_color", "Not used"},
        {"_get_language", "Not used"},
        {"_get_interface_language", "Not used"},
        {"_get_user_country", "Not used"},
        {"_get_result_country", "Not used"},
        {"_get_safe", "Not used"},
        {"_get_sort", "Not used"},
        {"_get_json_file", "Not used"},
        {"_get_env_file", "Not used"},
        {"_set_num_results", "num_results (int) <Required>"},
        {"_set_start_index", "start_index (int) <Required>"},
        {"_set_filter", "filter (int) <Required>"},
        {"_set_c2coff", "c2coff (int) <Required>"},
        {"_set_date_restrict", "date_restrict (int) <Required>"},
        {"_set_extra_query", "extra_query (string) <Required>"},
        {"_set_exact_terms", "exact_terms (string) <Required>"},
        {"_set_exclude_terms", "exclude_terms (string) <Required>"},
        {"_set_site_search", "site_search (string) <Required>"},
        {"_set_site_search_filter", "site_search_filter (string) <Required>"},
        {"_set_link_site", "link_site (string) <Required>"},
        {"_set_or_terms", "or_terms (string) <Required>"},
        {"_set_date_restrict_type", "date_restrict_type (string) <Required>"},
        {"_set_low_range", "low_range (string) <Required>"},
        {"_set_high_range", "high_range (string) <Required>"},
        {"_set_search_type", "search_type (string) <Required>"},
        {"_set_filetype", "filetype (string) <Required>"},
        {"_set_rights", "rights (string) <Required>"},
        {"_set_img_size", "img_size (string) <Required>"},
        {"_set_img_type", "img_type (string) <Required>"},
        {"_set_img_color_type", "img_color_type (string) <Required>"},
        {"_set_img_dominant_color", "img_dominant_color (string) <Required>"},
        {"_set_language", "language (string) <Required>"},
        {"_set_interface_language", "interface_language (string) <Required>"},
        {"_set_user_country", "user_country (string) <Required>"},
        {"_set_result_country", "result_country (string) <Required>"},
        {"_set_safe", "safe (string) <Required>"},
        {"_set_sort", "sort (string) <Required>"},
        {"_set_response_file", "json_file (string) <Required>"},
        {"_set_env_file", "env_file (string) <Required>"},
        {"_search_google", "query (string) <Required>\njson_file (string)"},
        {"_get_result", "result_index (int)\ntitle (string)\nsnippet (string)\nlink (string)\nimage (string)\njson_filename (string)\ntext_filename (string)"},
    };

    std::map<std::string, std::string> __function_parameters_description__ = { // Function names, parameters and descriptions
        {"_get_num_results", "Not used"},
        {"_get_start_index", "Not used"},
        {"_get_filter", "Not used"},
        {"_get_c2coff", "Not used"},
        {"_get_date_restrict", "Not used"},
        {"_get_query", "Not used"},
        {"_get_search_url", "Not used"},
        {"_get_extra_query", "Not used"},
        {"_get_exact_terms", "Not used"},
        {"_get_exclude_terms", "Not used"},
        {"_get_site_search", "Not used"},
        {"_get_site_search_filter", "Not used"},
        {"_get_link_site", "Not used"},
        {"_get_or_terms", "Not used"},
        {"_get_date_restrict_type", "Not used"},
        {"_get_low_range", "Not used"},
        {"_get_high_range", "Not used"},
        {"_get_search_type", "Not used"},
        {"_get_filetype", "Not used"},
        {"_get_rights", "Not used"},
        {"_get_img_size", "Not used"},
        {"_get_img_type", "Not used"},
        {"_get_img_color_type", "Not used"},
        {"_get_img_dominant_color", "Not used"},
        {"_get_language", "Not used"},
        {"_get_interface_language", "Not used"},
        {"_get_user_country", "Not used"},
        {"_get_result_country", "Not used"},
        {"_get_safe", "Not used"},
        {"_get_sort", "Not used"},
        {"_get_json_file", "Not used"},
        {"_get_env_file", "Not used"},
        {"_set_num_results", "num_results: Number of results to return. Available values are between 1 to 10"},
        {"_set_start_index", "start_index: Index to start from when getting search results"},
        {"_set_filter", "filter: Turn on or off duplicate content. Available values are [0, 1]"},
        {"_set_c2coff", "c2coff: Turn on or off Simplified and Traditional Chinese. Available values are [0, 1]"},
        {"_set_date_restrict", "date_restrict: Check whether search is restricted by date. Available values are [0, 1]"},
        {"_set_extra_query", "extra_query: Extra queries to search for with the search query"},
        {"_set_exact_terms", "exact_terms: Phrase to include in document in search results"},
        {"_set_exclude_terms", "exclude_terms: Terms to exclude from documents in search result"},
        {"_set_site_search", "site_search: Site to always include or exclude from search results"},
        {"_set_site_search_filter", "site_search_filter: Value specifying to include or exclude a site"},
        {"_set_link_site", "link_site: Link to include in each search result"},
        {"_set_or_terms", "or_terms: Additional terms to include in the document"},
        {"_set_date_restrict_type", "date_restrict_type: Date restrict type to restrict search results. Available values are ['d', 'w', 'm', 'y']"},
        {"_set_low_range", "low_range: Query appended to before the search query"},
        {"_set_high_range", "high_range: Query appended to after the search query"},
        {"_set_search_type", "search_type: Search type of the query. Available types are [\"image\"]"},
        {"_set_filetype", "filetype: Filetype of the query. Available types are [\".pdf\", \".ps\", \".csv\", \".epub\", \".kmz\", \".gpx\", \".hwp\", \".htm\", \".html\", \".xls\", \".xlsx\", \".ppt\", \".pptx\", \".doc\", \".docx\", \".odp\", \".ods\", \".odt\", \".rtf\", \".svg\", \".tex\", \".txt\", \".text\", \".bas\", \".c\", \".cc\", \".cpp\", \".cxx\", \".h\", \".hpp\", \".cs\", \".java\", \".pl\", \".py\", \".wml\", \".wap\", \".xml\", \"BMP\", \"GIF\", \"JPEG\", \"PNG\", \"WebP\", \"SVG\", \"3GP\", \"3G2\", \"ASF\", \"AVI\", \"DivX\", \"M2V\", \"M3U\", \"M3U8\", \"M4V\", \"MKV\", \"MOV\", \"MP4\", \"MPEG\", \"OGV\", \"QVT\", \"RAM\", \"RM\", \"VOB\", \"WebM\", \"WMV\", \"XAP\"]"},
        {"_set_rights", "rights: Licensing of the query. Available rights are [\"cc_publicdomain\", \"cc_attribute\", \"cc_sharealike\", \"cc_noncommercial\", \"cc_nonderived\"]"},
        {"_set_img_size", "img_size: Size of the image. Available sizes are [\"huge\", \"icon\", \"large\", \"medium\", \"small\", \"xlarge\", \"xxlarge\"]"},
        {"_set_img_type", "img_type: Type of the image. Available types are [\"clipart\", \"face\", \"lineart\", \"stock\", \"photo\", \"animated\"]"},
        {"_set_img_color_type", "img_color_type: Color type of the image. Available color types are [\"color\", \"gray\", \"mono\", \"trans\"]"},
        {"_set_img_dominant_color", "img_dominant_color: Dominant color of the image. Availablt dominant colors are [\"black\", \"blue\", \"brown\", \"gray\", \"green\", \"orange\", \"pink\", \"purple\", \"red\", \"teal\", \"white\", \"yellow\"]"},
        {"_set_language", "language: Language to search google in. Available languages are [\"lang_ar\", \"lang_bg\", \"lang_ca\", \"lang_cs\", \"lang_da\", \"lang_de\", \"lang_el\", \"lang_en\", \"lang_es\", \"lang_et\", \"lang_fi\", \"lang_fr\", \"lang_hr\", \"lang_hu\", \"lang_id\", \"lang_is\", \"lang_it\", \"lang_iw\", \"lang_ja\", \"lang_ko\", \"lang_lt\", \"lang_lv\", \"lang_nl\", \"lang_no\", \"lang_pl\", \"lang_pt\", \"lang_ro\", \"lang_ru\", \"lang_sk\", \"lang_sl\", \"lang_sr\", \"lang_sv\", \"lang_tr\", \"lang_zh-CN\", \"lang_zh-TW\"]"},
        {"_set_interface_language", "interface_language: User interface language. Available interface languages are [\"af\", \"sq\", \"sm\", \"ar\", \"az\", \"eu\", \"be\", \"bn\", \"bh\", \"bs\", \"bg\", \"ca\", \"zh-CN\", \"zh-TW\", \"hr\", \"cs\", \"da\", \"nl\", \"en\", \"eo\", \"et\", \"fo\", \"fi\", \"fr\", \"fy\", \"gl\", \"ka\", \"de\", \"el\", \"gu\", \"iw\", \"hi\", \"hu\", \"is\", \"id\", \"ia\", \"ga\", \"it\", \"ja\", \"jw\", \"kn\", \"ko\", \"la\", \"lv\", \"lt\", \"mk\", \"ms\", \"ml\", \"mt\", \"mr\", \"ne\", \"no\", \"nn\", \"oc\", \"fa\", \"pl\", \"pt-BR\", \"pt-PT\", \"pa\", \"ro\", \"ru\", \"gd\", \"sr\", \"si\", \"sk\", \"sl\", \"es\", \"su\", \"sw\", \"sv\", \"tl\", \"ta\", \"te\", \"th\", \"ti\", \"tr\", \"uk\", \"ur\", \"uz\", \"vi\", \"cy\", \"xh\", \"zu\"]"},
        {"_set_user_country", "user_country: Country to search from in google. Available user countries are [\"af\", \"al\", \"dz\", \"as\", \"ad\", \"ao\", \"ai\", \"aq\", \"ag\", \"ar\", \"am\", \"aw\", \"au\", \"at\", \"az\", \"bs\", \"bh\", \"bd\", \"bb\", \"by\", \"be\", \"bz\", \"bj\", \"bm\", \"bt\", \"bo\", \"ba\", \"bw\", \"bv\", \"br\", \"io\", \"bn\", \"bg\", \"bf\", \"bi\", \"kh\", \"cm\", \"ca\", \"cv\", \"ky\", \"cf\", \"td\", \"cl\", \"cn\", \"cx\", \"cc\", \"co\", \"km\", \"cg\", \"cd\", \"ck\", \"cr\", \"ci\", \"hr\", \"cu\", \"cy\", \"cz\", \"dk\", \"dj\", \"dm\", \"do\", \"ec\", \"eg\", \"sv\", \"gq\", \"er\", \"ee\", \"et\", \"fk\", \"fo\", \"fj\", \"fi\", \"fr\", \"gf\", \"pf\", \"tf\", \"ga\", \"gm\", \"ge\", \"de\", \"gh\", \"gi\", \"gr\", \"gl\", \"gd\", \"gp\", \"gu\", \"gt\", \"gn\", \"gw\", \"gy\", \"ht\", \"hm\", \"va\", \"hn\", \"hk\", \"hu\", \"is\", \"in\", \"id\", \"ir\", \"iq\", \"ie\", \"il\", \"it\", \"jm\", \"jp\", \"jo\", \"kz\", \"ke\", \"ki\", \"kp\", \"kr\", \"kw\", \"kg\", \"la\", \"lv\", \"lb\", \"ls\", \"lr\", \"ly\", \"li\", \"lt\", \"lu\", \"mo\", \"mk\", \"mg\", \"mw\", \"my\", \"mv\", \"ml\", \"mt\", \"mh\", \"mq\", \"mr\", \"mu\", \"yt\", \"mx\", \"fm\", \"md\", \"mc\", \"mn\", \"ms\", \"ma\", \"mz\", \"mm\", \"na\", \"nr\", \"np\", \"nl\", \"an\", \"nc\", \"nz\", \"ni\", \"ne\", \"ng\", \"nu\", \"nf\", \"mp\", \"no\", \"om\", \"pk\", \"pw\", \"ps\", \"pa\", \"pg\", \"py\", \"pe\", \"ph\", \"pn\", \"pl\", \"pt\", \"pr\", \"qa\", \"re\", \"ro\", \"ru\", \"rw\", \"sh\", \"kn\", \"lc\", \"pm\", \"vc\", \"ws\", \"sm\", \"st\", \"sa\", \"sn\", \"cs\", \"sc\", \"sl\", \"sg\", \"sk\", \"si\", \"sb\", \"so\", \"za\", \"gs\", \"es\", \"lk\", \"sd\", \"sr\", \"sj\", \"sz\", \"se\", \"ch\", \"sy\", \"tw\", \"tj\", \"tz\", \"th\", \"tl\", \"tg\", \"tk\", \"to\", \"tt\", \"tn\", \"tr\", \"tm\", \"tc\", \"tv\", \"ug\", \"ua\", \"ae\", \"uk\", \"us\", \"um\", \"uy\", \"uz\", \"vu\", \"ve\", \"vn\", \"vg\", \"vi\", \"wf\", \"eh\", \"ye\", \"zm\", \"zw\"]"},
        {"_set_result_country", "result_country: Country to search for in google. Available result countries are [\"countryAF\", \"countryAL\", \"countryDZ\", \"countryAS\", \"countryAD\", \"countryAO\", \"countryAI\", \"countryAQ\", \"countryAG\", \"countryAR\", \"countryAM\", \"countryAW\", \"countryAU\", \"countryAT\", \"countryAZ\", \"countryBS\", \"countryBH\", \"countryBD\", \"countryBB\", \"countryBY\", \"countryBE\", \"countryBZ\", \"countryBJ\", \"countryBM\", \"countryBT\", \"countryBO\", \"countryBA\", \"countryBW\", \"countryBV\", \"countryBR\", \"countryIO\", \"countryBN\", \"countryBG\", \"countryBF\", \"countryBI\", \"countryKH\", \"countryCM\", \"countryCA\", \"countryCV\", \"countryKY\", \"countryCF\", \"countryTD\", \"countryCL\", \"countryCN\", \"countryCX\", \"countryCC\", \"countryCO\", \"countryKM\", \"countryCG\", \"countryCD\", \"countryCK\", \"countryCR\", \"countryCI\", \"countryHR\", \"countryCU\", \"countryCY\", \"countryCZ\", \"countryDK\", \"countryDJ\", \"countryDM\", \"countryDO\", \"countryTP\", \"countryEC\", \"countryEG\", \"countrySV\", \"countryGQ\", \"countryER\", \"countryEE\", \"countryET\", \"countryEU\", \"countryFK\", \"countryFO\", \"countryFJ\", \"countryFI\", \"countryFR\", \"countryFX\", \"countryGF\", \"countryPF\", \"countryTF\", \"countryGA\", \"countryGM\", \"countryGE\", \"countryDE\", \"countryGH\", \"countryGI\", \"countryGR\", \"countryGL\", \"countryGD\", \"countryGP\", \"countryGU\", \"countryGT\", \"countryGN\", \"countryGW\", \"countryGY\", \"countryHT\", \"countryHM\", \"countryVA\", \"countryHN\", \"countryHK\", \"countryHU\", \"countryIS\", \"countryIN\", \"countryID\", \"countryIR\", \"countryIQ\", \"countryIE\", \"countryIL\", \"countryIT\", \"countryJM\", \"countryJP\", \"countryJO\", \"countryKZ\", \"countryKE\", \"countryKI\", \"countryKP\", \"countryKR\", \"countryKW\", \"countryKG\", \"countryLA\", \"countryLV\", \"countryLB\", \"countryLS\", \"countryLR\", \"countryLY\", \"countryLI\", \"countryLT\", \"countryLU\", \"countryMO\", \"countryMK\", \"countryMG\", \"countryMW\", \"countryMY\", \"countryMV\", \"countryML\", \"countryMT\", \"countryMH\", \"countryMQ\", \"countryMR\", \"countryMU\", \"countryYT\", \"countryMX\", \"countryFM\", \"countryMD\", \"countryMC\", \"countryMN\", \"countryMS\", \"countryMA\", \"countryMZ\", \"countryMM\", \"countryNA\", \"countryNR\", \"countryNP\", \"countryNL\", \"countryAN\", \"countryNC\", \"countryNZ\", \"countryNI\", \"countryNE\", \"countryNG\", \"countryNU\", \"countryNF\", \"countryMP\", \"countryNO\", \"countryOM\", \"countryPK\", \"countryPW\", \"countryPS\", \"countryPA\", \"countryPG\", \"countryPY\", \"countryPE\", \"countryPH\", \"countryPN\", \"countryPL\", \"countryPT\", \"countryPR\", \"countryQA\", \"countryRE\", \"countryRO\", \"countryRU\", \"countryRW\", \"countrySH\", \"countryKN\", \"countryLC\", \"countryPM\", \"countryVC\", \"countryWS\", \"countrySM\", \"countryST\", \"countrySA\", \"countrySN\", \"countryCS\", \"countrySC\", \"countrySL\", \"countrySG\", \"countrySK\", \"countrySI\", \"countrySB\", \"countrySO\", \"countryZA\", \"countryGS\", \"countryES\", \"countryLK\", \"countrySD\", \"countrySR\", \"countrySJ\", \"countrySZ\", \"countrySE\", \"countryCH\", \"countrySY\", \"countryTW\", \"countryTJ\", \"countryTZ\", \"countryTH\", \"countryTG\", \"countryTK\", \"countryTO\", \"countryTT\", \"countryTN\", \"countryTR\", \"countryTM\", \"countryTC\", \"countryTV\", \"countryUG\", \"countryUA\", \"countryAE\", \"countryUK\", \"countryUS\", \"countryUM\", \"countryUY\", \"countryUZ\", \"countryVU\", \"countryVE\", \"countryVN\", \"countryVG\", \"countryVI\", \"countryWF\", \"countryEH\", \"countryYE\", \"countryYU\", \"countryZM\", \"countryZW\"]"},
        {"_set_safe", "safe: Safe search. Available options are [\"off\", \"active\"]"},
        {"_set_sort", "sort: Sort order. Available options are [\"date\"]"},
        {"_set_response_file", "json_file: Name of the file to save response data"},
        {"_set_env_file", "env_file: Name of the file that contains Google Search API and CX Keys"},
        {"_search_google", "query: Query to search Google\njson_file: Name of the file to save response data"},
        {"_get_result", "result_index: Index of individual result to parse. Available options are 1 to 10 and -1 for all results\ntitle: Get Title. Available options are [\"True\", \"False\"]\nsnippet: Get Snippet. Available options are [\"True\", \"False\"]\nlink: Get Link. Available options are [\"True\", \"False\"]\nimage: Get Image. Available options are [\"True\", \"False\"]\njson_filename: Name of the json file to retrive response data from\ntext_filename: Name of the text file to store the results in"}
    };

    std::map<std::string, std::string> __function_return_types__ = { // Function names and return types
        {"_get_num_results", "Integer of number of results"},
        {"_get_start_index", "Integer of start index"},
        {"_get_filter", "Integer specifying if duplicate content is on or off"},
        {"_get_c2coff", "Integer specifying if Simplified and Traditional Chinese Search is on or off"},
        {"_get_date_restrict", "Integer specifying if search is restricted by date"},
        {"_get_query", "String of search query"},
        {"_get_search_url", "String of constructed url"},
        {"_get_extra_query", "String of extra queries in the search"},
        {"_get_exact_terms", "String of extra terms"},
        {"_get_exclude_terms", "String of excluded terms"},
        {"_get_site_search", "String of site which is always included or excluded"},
        {"_get_site_search_filter", "String of filter specifying whether site is included or excluded"},
        {"_get_site_search_filter", "String of filter specifying whether site is included or excluded"},
        {"_get_link_site", "String of link"},
        {"_get_or_terms", "String of extra terms"},
        {"_get_date_restrict_type", "String of date restricting the search results"},
        {"_get_low_range", "String of query appended to before the search query"},
        {"_get_high_range", "String of query appended to after the search query"},
        {"_get_search_type", "String of search type"},
        {"_get_filetype", "String of filetype"},
        {"_get_rights", "String of licensing"},
        {"_get_img_size", "String of image size"},
        {"_get_img_type", "String of image type"},
        {"_get_img_color_type", "String of image color type"},
        {"_get_img_dominant_color", "String of image dominant color"},
        {"_get_language", "String of language"},
        {"_get_interface_language", "String of user interface language"},
        {"_get_user_country", "String of country"},
        {"_get_result_country", "String of country"},
        {"_get_safe", "String of safe search"},
        {"_get_sort", "String of sort order"},
        {"_get_json_file", "String of json file name"},
        {"_get_env_file", "String of env file name"},
        {"_set_num_results", "None"},
        {"_set_start_index", "None"},
        {"_set_filter", "None"},
        {"_set_c2coff", "None"},
        {"_set_date_restrict", "None"},
        {"_set_extra_query", "None"},
        {"_set_exact_terms", "None"},
        {"_set_exclude_terms", "None"},
        {"_set_site_search", "None"},
        {"_set_site_search_filter", "None"},
        {"_set_link_site", "None"},
        {"_set_or_terms", "None"},
        {"_set_date_restrict_type", "None"},
        {"_set_low_range", "None"},
        {"_set_high_range", "None"},
        {"_set_search_type", "None"},
        {"_set_filetype", "None"},
        {"_set_rights", "None"},
        {"_set_img_size", "None"},
        {"_set_img_type", "None"},
        {"_set_img_color_type", "None"},
        {"_set_img_dominant_color", "None"},
        {"_set_language", "None"},
        {"_set_interface_language", "None"},
        {"_set_user_country", "None"},
        {"_set_result_country", "None"},
        {"_set_safe", "None"},
        {"_set_sort", "None"},
        {"_set_response_file", "None"},
        {"_set_env_file", "None"},
        {"_search_google", "None"},
        {"_get_result", "None"},
    };

    std::map<std::string, std::string> __class_examples__ = { // Class usage examples
        {"Search google for \"What are LLMs?\" and get 5 results and show me title and snippet of the 2nd result", "To search google for \"What are LLMs?\" and get 5 results and then show me title and snippet of the 2nd result use function ```function_name _set_num_results``` with parameters ```parameters { num_results = 1 }``` then use function ```function_name _search_google``` with parameters ```parameters { query = \"What are LLMs?\" }``` then use function ```function_name _get_result``` with parameters ```parameters { result_index = 1 }, { title = True }, { snippet = True }```"},
        {"Search google for \"Cats\" and get me \"pdf\" files but restrict words: \"large\"c, \"spotted\"", "To search google for \"Cats\" and get only \"pdf\" files and restrict words: \"large\", \"spotted\" use function ```function_name _set_filetype``` with parameters ```parameters { filetype = \"pdf\" }``` then use function ```function_name _set_exclude_terms``` with parameters ```parameters { exclude_terms = \"large, spotted\" }"},
        {"Turn off \"simplified chinese\" and search for \"Great wall of China\" but restrit results to past 2 years", "To turn off \"simplified chinese\" and search for \"Great wall of China\" and restrict results to past 2 years use function ```function_name _set_c2coff``` with parameters ```parameters { c2coff = 0 }``` then use function ```function_name _search_google``` with parameters ```parameters { query = \"Great wall of China\" }``` then use function ```function_name _set_date_restrict``` with parameters ```parameters { date_restrict = 1 }``` then use function ```function_name _set_date_restrict_type``` with parameters ```parameters { date_restrict_type = \"y2\" }```"},
        {"Create file \"hello.txt\" and write \"hello\" in it then hide the file", "```Sorry, this query cannot be handled by me```"},
        {"Search the news for \"USA elections\" and give me 22 results but search only the site \"bbc.com\"", "```Sorry, this query cannot be handled by me```"}
    };

    return { // Vector of maps containing the class information
        {"Name_Description", __name_discription__},
        {"Constructor_Parameters", __constuctor_paramters__},
        {"Function_Info", __function_info__},
        {"Function_Parameters", __function_parameters__},
        {"Parameter_Description", __function_parameters_description__},
        {"Function_Return", __function_return_types__},
        {"Class_Examples", __class_examples__}
    };
}

void GoogleSearch::__log__(
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

std::string GoogleSearch::__trim(
    const std::string& str // String to be trimmed
) {
    const std::string whitespace = " \t"; // Sub-String to trim from the main string
    
    const auto start = str.find_first_not_of(whitespace);
    if (start == std::string::npos) return "";  // No content
    const auto end = str.find_last_not_of(whitespace);
    
    return str.substr(start, end - start + 1);
};

std::unordered_map<std::string, std::string> GoogleSearch::__load_env_file(
    const std::string& filePath // Path of the env file
) {
    std::unordered_map<std::string, std::string> envMap; // Map for environmental variables
    std::ifstream file(filePath); // Start reading the file
    std::string line; // Current line in file

    if (!file.is_open()) {
        std::cerr << "Error: Could not open the .env file.\n";
        return envMap;
    }

    while (std::getline(file, line)) {
        // Ignore empty lines or comments
        if (line.empty() || line[0] == '#') {
            continue;
        }

        // Find the delimiter (equals sign)
        size_t delimiterPos = line.find('=');
        if (delimiterPos != std::string::npos) {
            // Extract the key and value, and trim any extra spaces
            std::string key = __trim(line.substr(0, delimiterPos));
            std::string value = __trim(line.substr(delimiterPos + 1));

            // Remove any quotes around the value if present
            if (value.front() == '"' && value.back() == '"') {
                value = value.substr(1, value.size() - 2);
            }

            // Insert the key-value pair into the map
            envMap[key] = value;
        }
    }

    file.close();
    return envMap;
};

std::string GoogleSearch::__get_env_value(
    const std::unordered_map<std::string, std::string>& envMap, // The Unordered map to read
    const std::string& key // The key to find in the map
) {
    auto it = envMap.find(key);
    if (it != envMap.end()) {
        return it->second;  // Key found, return the value
    } else {
        return "";  // Key not found
    }
};

void GoogleSearch::__get_api_cx(
    std::string env_filename = "secret_files/.env" // Name of the file that contains API and CX keys
){
    this->_env_file = env_filename;

    std::unordered_map<std::string, std::string> environment_variables = __load_env_file(this->_env_file);

    this->__api_key = __get_env_value(environment_variables, "SEARCH_API_KEY");
    this->__cx_key = __get_env_value(environment_variables, "SEARCH_CX_KEY");
};

size_t GoogleSearch::__WriteCallBack(
    void* contents, // pointer to buffer containing the downloaded data
    size_t size, // size of the downloaded data
    size_t nmemb, // number of elements in the downloaded data
    std::string* output // Pointer to user defined data
){
    size_t total_size = size * nmemb; // Total size of the data
    output->append((char*)contents, total_size);
    
    return total_size;
};

std::string GoogleSearch::__fetch_json_data(
    const std::string& url // Url to fetch data from
){
    CURL* curl = curl_easy_init(); // Curl object to get result string
    CURLcode res; // Response for curl
    std::string response_string; // String to store response

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, __WriteCallBack);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            return "";
        }

        curl_easy_cleanup(curl);
    }

    return response_string;
};

void GoogleSearch::__save_json_data(
    const std::string json_data, // Json data to save
    const std::string filename = "json_files/search_result.json" // Name of the file to save json data in
){
    auto json = nlohmann::json::parse(json_data); // nlohmann object to parse json data
    if (json["queries"]["nextPage"].size() == 1){
        json["queries"]["nextPage"][0]["cx"] = "[cx?]";
        json["queries"]["request"][0]["cx"] = "[cx?]";
    }

    std::ofstream json_file(filename); // Json file to save data
    json_file << std::setw(4) << json << std::endl;
    
    json_file.close();
};

std::string GoogleSearch::__encode_url(
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

void GoogleSearch::__construct_search_url(){
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

    this->_search_url = this->__encode_url(search_url);
    // std::cout << this->_search_url << std::endl << std::endl;
};

int GoogleSearch::_get_num_results(){
    std::string log_content = "Number of results is " + std::to_string(this->_num_results) + " to search google.";
    this->__log__(log_content);

    return this->_num_results;
};

int GoogleSearch::_get_start_index(){
    std::string log_content = "Start index is " + std::to_string(this->_start_index) + " to search google.";
    this->__log__(log_content);

    return this->_start_index;
};

int GoogleSearch::_get_filter(){
    std::string log_content = "Filter is " + std::to_string(this->_filter) + " to search google.";
    this->__log__(log_content);

    return this->_filter;
};

int GoogleSearch::_get_c2coff(){
    std::string log_content = "Simplified and Traditional Chinese is " + std::to_string(this->_c2coff) + " to search google.";
    this->__log__(log_content);

    return this->_c2coff;
};

int GoogleSearch::_get_date_restrict(){
    std::string log_content = "Date restrict is " + std::to_string(this->_date_restrict) + " to search google.";
    this->__log__(log_content);

    return this->_date_restrict;
};

std::string GoogleSearch::_get_query(){
    std::string log_content = "Query is " + this->_search_terms + " to search google.";
    this->__log__(log_content);

    return this->_search_terms;
};

std::string GoogleSearch::_get_search_url(){
    std::string log_content = "Search url is " + this->_search_url + " to search google.";
    this->__log__(log_content);

    return this->_search_url;
};

std::string GoogleSearch::_get_extra_query(){
    std::string log_content = "Extra query is " + this->_extra_query + " to search google.";
    this->__log__(log_content);

    return this->_extra_query;
};

std::string GoogleSearch::_get_exact_terms(){
    std::string log_content = "Exact terms is " + this->_exact_terms + " to search google.";
    this->__log__(log_content);

    return this->_exact_terms;
};

std::string GoogleSearch::_get_exclude_terms(){
    std::string log_content = "Exclude terms is " + this->_exclude_terms + " to search google.";
    this->__log__(log_content);

    return this->_exclude_terms;
};

std::string GoogleSearch::_get_site_search(){
    std::string log_content = "Site search is " + this->_site_search + " to search google.";
    this->__log__(log_content);

    return this->_site_search;
};

std::string GoogleSearch::_get_site_search_filter(){
    std::string log_content = "Site search filter is " + this->_site_search_filter + " to search google.";
    this->__log__(log_content);

    return this->_site_search_filter;
};

std::string GoogleSearch::_get_link_site(){
    std::string log_content = "Link site is " + this->_link_site + " to search google.";
    this->__log__(log_content);

    return this->_link_site;
};

std::string GoogleSearch::_get_or_terms(){
    std::string log_content = "Or terms is " + this->_or_terms + " to search google.";
    this->__log__(log_content);

    return this->_or_terms;
};

std::string GoogleSearch::_get_date_restrict_type(){
    std::string log_content = "Date restrict type is " + this->_date_restrict_type + " to search google.";
    this->__log__(log_content);

    return this->_date_restrict_type;
};

std::string GoogleSearch::_get_low_range(){
    std::string log_content = "Low range is " + this->_low_range + " to search google.";
    this->__log__(log_content);

    return this->_low_range;
};

std::string GoogleSearch::_get_high_range(){
    std::string log_content = "High range is " + this->_high_range + " to search google.";
    this->__log__(log_content);

    return this->_high_range;
};

std::string GoogleSearch::_get_search_type(){
    std::string log_content = "Search type is " + this->_search_type + " to search google.";
    this->__log__(log_content);

    return this->_search_type;
};

std::string GoogleSearch::_get_filetype(){
    std::string log_content = "Filetype is " + this->_filetype + " to search google.";
    this->__log__(log_content);

    return this->_filetype;
};

std::string GoogleSearch::_get_rights(){
    std::string log_content = "Rights is " + this->_rights + " to search google.";
    this->__log__(log_content);

    return this->_rights;
};

std::string GoogleSearch::_get_img_size(){
    std::string log_content = "Image size is " + this->_img_size + " to search google.";
    this->__log__(log_content);

    return this->_img_size;
};

std::string GoogleSearch::_get_img_type(){
    std::string log_content = "Image type is " + this->_img_type + " to search google.";
    this->__log__(log_content);

    return this->_img_type;
};

std::string GoogleSearch::_get_img_color_type(){
    std::string log_content = "Image color type is " + this->_img_color_type + " to search google.";
    this->__log__(log_content);

    return this->_img_color_type;
};

std::string GoogleSearch::_get_img_dominant_color(){
    std::string log_content = "Image dominant color is " + this->_img_dominant_color + " to search google.";
    this->__log__(log_content);

    return this->_img_dominant_color;
};

std::string GoogleSearch::_get_language(){
    std::string log_content = "Language is " + this->_language + " to search google.";
    this->__log__(log_content);

    return this->_language;
};

std::string GoogleSearch::_get_interface_language(){
    std::string log_content = "User interface language is " + this->_interface_language + " to search google.";
    this->__log__(log_content);

    return this->_interface_language;
};

std::string GoogleSearch::_get_user_country(){
    std::string log_content = "User country is " + this->_user_country + " to search google.";
    this->__log__(log_content);

    return this->_user_country;
};

std::string GoogleSearch::_get_result_country(){
    std::string log_content = "Result country is " + this->_result_country + " to search google.";
    this->__log__(log_content);

    return this->_result_country;
};

std::string GoogleSearch::_get_safe(){
    std::string log_content = "Safe search is " + this->_safe + " to search google.";
    this->__log__(log_content);

    return this->_safe;
};

std::string GoogleSearch::_get_sort(){
    std::string log_content = "Sort order is " + this->_sort + " to search google.";
    this->__log__(log_content);

    return this->_sort;
};

std::string GoogleSearch::_get_json_file(){
    std::string log_content = "Json file is " + this->_json_file + " to search google.";
    this->__log__(log_content);

    return this->_json_file;
};

std::string GoogleSearch::_get_env_file(){
    std::string log_content = "Env file is " + this->_env_file + " to search google.";
    this->__log__(log_content);

    return this->_env_file;
};

void GoogleSearch::_set_num_results(
    const int num_results // number of results to return 
){
    this->_num_results = num_results;


    // Log function
    std::string log_content = "Number of results set to " + std::to_string(num_results) + ".";
    this->__log__(log_content);
};

void GoogleSearch::_set_start_index(
    const int start_index // index at which search result starts
){
    this->_start_index = start_index;


    // Log function
    std::string log_content = "Start index set to " + std::to_string(start_index) + ".";
    this->__log__(log_content);
};

void GoogleSearch::_set_filter(
    const int8_t filter // check whether duplicate is turned On or Off
){
    bool correct_filter = false;

    for (char filter_in_filter: this->__filter){
        if (filter_in_filter == filter){
            correct_filter = true;
            this->_filter = filter;
            break;
        }
    }


    // Log function
    std::string log_content;
    if (correct_filter)
        log_content = "Filter set to " + std::to_string(filter) + ".";
    else
        log_content = "Filter could not be set to " + std::to_string(filter) + " as it is not a correct filter value";
    
    this->__log__(log_content);
};

void GoogleSearch::_set_c2coff(
    const int8_t c2coff // Turn on or off Simplified and Traditional Chinese
){
    bool correct_c2coff = false;

    for (char c2coff_in_c2coff: this->__c2coff){
        if (c2coff_in_c2coff == c2coff){
            correct_c2coff = true;
            this->_c2coff = c2coff;
            break;
        }
    }


    // Log function
    std::string log_content;
    if (correct_c2coff)
        log_content = "Simplified and Traditional Chinese is set to " + std::to_string(c2coff) + ".";
    else
        log_content = "Simplified and Traditional Chinese could not be set to " + std::to_string(c2coff) + " as it is not a correct value";
    
    this->__log__(log_content);
};

void GoogleSearch::_set_date_restrict(
    const int8_t date_restrict // Set whether search is to be restricted by date
){
    bool correct_date_restrict = false;

    if (date_restrict == 0 || date_restrict == 1){
        correct_date_restrict = true;
        this->_date_restrict = date_restrict;
    }


    // Log function
    std::string log_content;
    if (correct_date_restrict)
        log_content = "Date restrict is set to " + std::to_string(date_restrict) + ".";
    else
        log_content = "Date restrict could not be set to " + std::to_string(date_restrict) + " as it is not a correct value";
    
    this->__log__(log_content);
};

void GoogleSearch::_set_extra_query(
    const std::string extra_query // extra queries to search for with the search query
){
    this->_extra_query = extra_query;


    // Log function
    std::string log_content = "Extra queries set to " + extra_query + ".";
    this->__log__(log_content);
};

void GoogleSearch::_set_exact_terms(
    const std::string exact_terms // phrase to include in document in search results
){
    this->_exact_terms = exact_terms;


    // Log function
    std::string log_content = "Exact terms set to " + exact_terms + ".";
    this->__log__(log_content);
};

void GoogleSearch::_set_exclude_terms(
    const std::string exclude_terms // terms to exclude from documents in search result
){
    this->_exclude_terms = exclude_terms;


    // Log function
    std::string log_content = "Exclude terms set to " + exclude_terms + ".";
    this->__log__(log_content);
};

void GoogleSearch::_set_site_search(
    const std::string site_search // site to always include or exclude from search results
){
    this->_site_search = site_search;


    // Log function
    std::string log_content = "Site search set to " + site_search + ".";
    this->__log__(log_content);
};

void GoogleSearch::_set_site_search_filter(
    const char site_search_filter // value specifying to include or exclude a site
){
    bool correct_search_filter = false;

    for (char site_filter: this->__site_search_filter){
        if (site_filter == site_search_filter){
            correct_search_filter = true;
            this->_site_search_filter = site_search_filter;
            break;
        }
    }


    // Log function
    std::string log_content;
    if (correct_search_filter)
        log_content = "Site search filter set to " + std::to_string(site_search_filter) + ".";
    else
        log_content = "Site search filter could not be set to " + std::to_string(site_search_filter) + " as it is not a correct value";
    
    this->__log__(log_content);
};

void GoogleSearch::_set_link_site(
    const std::string link_site // link to include in each search result
){
    this->_link_site = link_site;


    // Log function
    std::string log_content = "Link site set to " + link_site + ".";
    this->__log__(log_content);
};

void GoogleSearch::_set_or_terms(
    const std::string or_terms // additional terms to include in the document
){
    this->_or_terms = or_terms;


    // Log function
    std::string log_content = "Or terms set to " + or_terms + ".";
    this->__log__(log_content);
};

void GoogleSearch::_set_date_restrict_type(
    const std::string date_restrict_type // date restrict type to restrict search results
){
    bool correct_date_type = false;

    for (char date_type: this->__date_restrict){
        if (date_type == date_restrict_type[0]){
            correct_date_type = true;
            this->_date_restrict_type = date_restrict_type;
            
            break;
        }
    }


    // Log function
    std::string log_content;
    if (correct_date_type)
        log_content = "Date restrict type set to " + date_restrict_type + ".";
    else
        log_content = "Date restrict type could not be set to " + date_restrict_type + " as it is not a correct value";
    
    this->__log__(log_content);
};

void GoogleSearch::_set_low_range(
    const std::string low_range // query appended to before the search query
){
    this->_low_range = low_range;


    // Log function
    std::string log_content = "Low range set to " + low_range + ".";
    this->__log__(log_content);
};

void GoogleSearch::_set_high_range(
    const std::string high_range // query appended to after the search query
){
    this->_high_range = high_range;


    // Log function
    std::string log_content = "High range set to " + high_range + ".";
    this->__log__(log_content);
};

void GoogleSearch::_set_search_type(
    const std::string search_type // search type of the query
){
    bool correct_search_type = false;

    for (std::string type : this->__search_type){
        if (type == search_type){
            correct_search_type = true;
            this->_search_type = search_type;
            break;
        }
    }


    // Log function
    std::string log_content;
    if (correct_search_type)
        log_content = "Search type set to " + search_type + ".";
    else
        log_content = "Search type could not be set to " + search_type + " as it is not a correct value";
    
    this->__log__(log_content);
};

void GoogleSearch::_set_filetype(
    const std::string filetype // filetype of the query;
){
    bool correct_file_type = false;

    for (std::string type : this->__available_filetypes){
        if (type == filetype){
            correct_file_type = true;
            this->_filetype = filetype;
            break;
        }
    }


    // Log function
    std::string log_content;
    if (correct_file_type)
        log_content = "Filetype set to " + filetype + ".";
    else
        log_content = "Filetype could not be set to " + filetype + " as it is not a correct value";
    
    this->__log__(log_content);
};

void GoogleSearch::_set_rights(
    const std::string right // licensing of the query
){
    bool correct_right = false;

    for (std::string right_in_right : this->__rights){
        if (right_in_right == right){
            correct_right = true;
            this->_rights = right;
            break;
        }
    }


    // Log function
    std::string log_content;
    if (correct_right)
        log_content = "Rights set to " + right + ".";
    else
        log_content = "Rights could not be set to " + right + " as it is not a correct value";
    
    this->__log__(log_content);
};

void GoogleSearch::_set_img_size(
    const std::string img_size // size of the image
){
    bool correct_img_size = false;

    for (std::string size : this->__image_sizes){
        if (size == img_size){
            correct_img_size = true;
            this->_img_size = img_size;
            break;
        }
    }


    // Log function
    std::string log_content;
    if (correct_img_size)
        log_content = "Image size set to " + img_size + ".";
    else
        log_content = "Image size could not be set to " + img_size + " as it is not a correct value";
    
    this->__log__(log_content);
};

void GoogleSearch::_set_img_type(
    const std::string img_type // type of the image
){
    bool correct_img_type = false;

    for (std::string type : this->__image_types){
        if (type == img_type){
            correct_img_type = true;
            this->_img_type = img_type;
            break;
        }
    }


    // Log function
    std::string log_content;
    if (correct_img_type)
        log_content = "Image type set to " + img_type + ".";
    else
        log_content = "Image type could not be set to " + img_type + " as it is not a correct value";
    
    this->__log__(log_content);
};

void GoogleSearch::_set_img_color_type(
    const std::string img_color_type // color type of the image
){
    bool correct_img_color_type = false;

    for (std::string color_type : this->__image_color_types){
        if (color_type == img_color_type){
            correct_img_color_type = true;
            this->_img_color_type = img_color_type;
            break;
        }
    }


    // Log function
    std::string log_content;
    if (correct_img_color_type)
        log_content = "Image color type set to " + img_color_type + ".";
    else
        log_content = "Image color type could not be set to " + img_color_type + " as it is not a correct value";
    
    this->__log__(log_content);
};

void GoogleSearch::_set_img_dominant_color(
    const std::string img_dominant_color // dominant color of the image
){
    bool correct_img_dominant_color = false;

    for (std::string dominant_color : this->__image_dominant_color_types){
        if (dominant_color == img_dominant_color){
            correct_img_dominant_color = true;
            this->_img_dominant_color = img_dominant_color;
            break;
        }
    }


    // Log function
    std::string log_content;
    if (correct_img_dominant_color)
        log_content = "Image dominant color set to " + img_dominant_color + ".";
    else
        log_content = "Image dominant color could not be set to " + img_dominant_color + " as it is not a correct value";
    
    this->__log__(log_content);
};

void GoogleSearch::_set_language(
    const std::string language // language to search google
){
    bool correct_language = false;

    for (std::string language_in_language : this->__available_languages){
        if (language_in_language == language){
            correct_language = true;
            this->_language = language;
            break;
        }
    }


    // Log function
    std::string log_content;
    if (correct_language)
        log_content = "Language set to " + language + ".";
    else
        log_content = "Language could not be set to " + language + " as it is not a correct value";
    
    this->__log__(log_content);
};

void GoogleSearch::_set_interface_language(
    const std::string interface_language // user interface language
){
    bool correct_interface_language = false;

    for (std::string language_in_interface_language : this->__available_languages){
        if (language_in_interface_language == interface_language){
            correct_interface_language = true;
            this->_interface_language = interface_language;
            break;
        }
    }


    // Log function
    std::string log_content;
    if (correct_interface_language)
        log_content = "User interface language set to " + interface_language + ".";
    else
        log_content = "User interface language could not be set to " + interface_language + " as it is not a correct value";
    
    this->__log__(log_content);
};

void GoogleSearch::_set_user_country(
    const std::string user_country // country to search from in google
){
    bool correct_user_country = false;

    for (std::string country_in_user_country : this->__available_user_countries){
        if (country_in_user_country == user_country){
            correct_user_country = true;
            this->_user_country = user_country;
            break;
        }
    }


    // Log function
    std::string log_content;
    if (correct_user_country)
        log_content = "User country set to " + user_country + ".";
    else
        log_content = "User country could not be set to " + user_country + " as it is not a correct value";
    
    this->__log__(log_content);
};

void GoogleSearch::_set_result_country(
    const std::string result_country // country to search for in google
){
    bool correct_result_country = false;

    for (std::string country_in_result_country : this->__available_result_countries){
        if (country_in_result_country == result_country){
            correct_result_country = true;
            this->_result_country = result_country;
            break;
        }
    }


    // Log function
    std::string log_content;
    if (correct_result_country)
        log_content = "Result country set to " + result_country + ".";
    else
        log_content = "Result country could not be set to " + result_country + " as it is not a correct value";
    
    this->__log__(log_content);
};

void GoogleSearch::_set_safe(
    const std::string safe // safe search
){
    bool correct_safe;

    for (std::string safe_in_safe : this->__safe){
        if (safe_in_safe == safe){
            correct_safe = true;
            this->_safe = safe;
            break;
        }
    }


    // Log function
    std::string log_content;
    if (correct_safe)
        log_content = "Safe search set to " + safe + ".";
    else
        log_content = "Safe search could not be set to " + safe + " as it is not a correct value";
    
    this->__log__(log_content);
};

void GoogleSearch::_set_sort(
    const std::string sort // sort order
){
    bool correct_sort = false;

    for (std::string sort_in_sort : this->__sort){
        if (sort_in_sort == sort){
            correct_sort = true;
            this->_sort = sort;
            break;
        }
    }


    // Log function
    std::string log_content;
    if (correct_sort)
        log_content = "Sort order set to " + sort + ".";
    else
        log_content = "Sort order could not be set to " + sort + " as it is not a correct value";
    
    this->__log__(log_content);
};

void GoogleSearch::_set_response_file(
    const std::string json_file // Name of the file to save response data
){
    this->_json_file = json_file;


    // Log function
    std::string log_content = "Json file set to " + json_file + ".";
    this->__log__(log_content);
};

void GoogleSearch::_set_env_file(
    const std::string env_file // Name of the file that contains Google Search API and CX Keys
){
    this->_env_file = env_file;

    
    // Log function
    std::string log_content = "Env file set to " + env_file + ".";
    this->__log__(log_content);
};

void GoogleSearch::_search_google(
    const std::string query, // Query to search Google
    const std::string json_file = "json_files/search_result.json" // Name of the file to save response data
){
    this->_search_terms = query;
    this->__construct_search_url();

    std::string json_data = this->__fetch_json_data(this->_search_url); // Json data from the result
    this->__save_json_data(json_data, json_file);


    // Log function
    std::string log_content = "Searched google for query " + query + " and stored search results in file " + json_file + ".";
    this->__log__(log_content);
};

void GoogleSearch::_get_result(
    const int result_index = 0, // Index of individual result to parse
            
    const std::string title = "True", // Get Title
    const std::string snippet = "True", // Get Snippet
    const std::string link = "False", // Get Link
    const std::string image = "False", // Get Image
    
    const std::string json_filename = "json_files/search_result.json", // Name of the file to retrive response data from
    const std::string text_filename = "text_files/search_results.txt" // Name of the text file to store results
){
    bool results_saved = false;

    std::ifstream json_file(json_filename); // Json file to retrive data
    nlohmann::json json_data; // nlohmann object to parse json data
    json_file >> json_data;

    json_file.close();

    if (json_data.contains("items") && json_data["items"].is_array()){
        std::ofstream result_file; // Text file to store results
        result_file.open(text_filename);

        if (result_index < json_data["items"].size() && result_index >= 0){
            results_saved = true;
            auto result = json_data["items"][result_index];

            if (title == "True" && result.contains("title"))
                result_file << "Title: " << result["title"] << std::endl;
            if (snippet == "True" && result.contains("snippet"))
                result_file << "Snippet: " << result["snippet"] << std::endl;
            if (link == "True" && result.contains("link"))
                result_file << "Link: " << result["link"] << std::endl;
            if (image == "True" && result.contains("pagemap") && result["pagemap"].contains("cse_image") && result["pagemap"]["cse_image"].is_array())
                result_file << "Image: " << result["pagemap"]["cse_image"][0]["src"] << std::endl;
        }

        if (result_index == -1){
            results_saved = true;
            auto results = json_data["items"];

            for (auto result : results){
                if (title == "True" && result.contains("title"))
                    result_file << "Title: " << result["title"] << std::endl;
                if (snippet == "True" && result.contains("snippet"))
                    result_file << "Snippet: " << result["snippet"] << std::endl;
                if (link == "True" && result.contains("link"))
                    result_file << "Link: " << result["link"] << std::endl;
                if (image == "True" && result.contains("pagemap") && result["pagemap"].contains("cse_image") && result["pagemap"]["cse_image"].is_array())
                    result_file << "Image: " << result["pagemap"]["cse_image"][0]["src"] << std::endl;

                result_file << std::endl;
            }
        }
        result_file.close();
    }


    // Log function
    std::string log_content;
    if (results_saved)
        log_content = "Search results saved to file " + text_filename + " Successfully.";
    else
        log_content = "Search results could not saved to file " + text_filename;

    this->__log__(log_content);
};