#include "../header_files/search_configure.h"

GoogleSearch::GoogleSearch(
    const std::string search_terms, // Query to search for on google

    const int num_results, // Number of results to return for the search
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

    const std::string json_file, // Name of the file to save response data
    const std::string env_file // Name of the file that contains API and CX keys
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
    std::string env_filename // Name of the file that contains API and CX keys
){
    this->_env_file = env_filename;

    std::unordered_map<std::string, std::string> environment_variables = __load_env_file(this->_env_file);

    this->__api_key = __get_env_value(environment_variables, "SEARCH_API_KEY");
    this->__cx_key = __get_env_value(environment_variables, "SEARCH_CSE_KEY");
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
    const std::string filename // Name of the file to save json data in
){
    auto json = nlohmann::json::parse(json_data); // nlohmann object to parse json data

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
    std::cout << this->_search_url << std::endl;
};

int GoogleSearch::_get_num_results(){
    return this->_num_results;
};

int GoogleSearch::_get_start_index(){
    return this->_start_index;
};

int GoogleSearch::_get_filter(){
    return this->_filter;
};

int GoogleSearch::_get_c2coff(){
    return this->_c2coff;
};

int GoogleSearch::_get_date_restrict(){
    return this->_date_restrict;
};

std::string GoogleSearch::_get_query(){
    return this->_search_terms;
};

std::string GoogleSearch::_get_search_url(){
    return this->_search_url;
};

std::string GoogleSearch::_get_extra_query(){
    return this->_extra_query;
};

std::string GoogleSearch::_get_exact_terms(){
    return this->_exact_terms;
};

std::string GoogleSearch::_get_exclude_terms(){
    return this->_exclude_terms;
};

std::string GoogleSearch::_get_site_search(){
    return this->_site_search;
};

std::string GoogleSearch::_get_site_search_filter(){
    return this->_site_search_filter;
};

std::string GoogleSearch::_get_link_site(){
    return this->_link_site;
};

std::string GoogleSearch::_get_or_terms(){
    return this->_or_terms;
};

std::string GoogleSearch::_get_date_restrict_type(){
    return this->_date_restrict_type;
};

std::string GoogleSearch::_get_low_range(){
    return this->_low_range;
};

std::string GoogleSearch::_get_high_range(){
    return this->_high_range;
};

std::string GoogleSearch::_get_search_type(){
    return this->_search_type;
};

std::string GoogleSearch::_get_filetype(){
    return this->_filetype;
};

std::string GoogleSearch::_get_rights(){
    return this->_rights;
};

std::string GoogleSearch::_get_img_size(){
    return this->_img_size;
};

std::string GoogleSearch::_get_img_type(){
    return this->_img_type;
};

std::string GoogleSearch::_get_img_color_type(){
    return this->_img_color_type;
};

std::string GoogleSearch::_get_img_dominant_color(){
    return this->_img_dominant_color;
};

std::string GoogleSearch::_get_language(){
    return this->_language;
};

std::string GoogleSearch::_get_interface_language(){
    return this->_interface_language;
};

std::string GoogleSearch::_get_user_country(){
    return this->_user_country;
};

std::string GoogleSearch::_get_result_country(){
    return this->_result_country;
};

std::string GoogleSearch::_get_safe(){
    return this->_safe;
};

std::string GoogleSearch::_get_sort(){
    return this->_sort;
};

std::string GoogleSearch::_get_json_file(){
    return this->_json_file;
};

std::string GoogleSearch::_get_env_file(){
    return this->_env_file;
};

void GoogleSearch::_set_num_results(
    const int num_results // number of results to return 
){
    this->_num_results = num_results;
};

void GoogleSearch::_set_start_index(
    const int start_index // index at which search result starts
){
    this->_start_index = start_index;
};

void GoogleSearch::_set_filter(
    const int filter // check whether duplicate is turned On or Off
){
    this->_filter = filter;
};

void GoogleSearch::_set_c2coff(
    const int c2coff // Turn on or off Simplified and Traditional Chinese
){
    this->_c2coff = c2coff;
};

void GoogleSearch::_set_date_restrict(
    const int date_restrict // check whether search is restricted by date
){
    this->_date_restrict = date_restrict;
};

void GoogleSearch::_set_extra_query(
    const std::string extra_query // extra queries to search for with the search query
){
    this->_extra_query = extra_query;
};

void GoogleSearch::_set_exact_terms(
    const std::string exact_terms // phrase to include in document in search results
){
    this->_exact_terms = exact_terms;
};

void GoogleSearch::_set_exclude_terms(
    const std::string exclude_terms // terms to exclude from documents in search result
){
    this->_exclude_terms = exclude_terms;
};

void GoogleSearch::_set_site_search(
    const std::string site_search // site to always include or exclude from search results
){
    this->_site_search = site_search;
};

void GoogleSearch::_set_site_search_filter(
    const char site_search_filter // value specifying to include or exclude a site
){
    for (auto filter : this->__site_search_filter){
        if (filter == site_search_filter)
            this->_site_search_filter = filter;
    }
};

void GoogleSearch::_set_link_site(
    const std::string link_site // link to include in each search result
){
    this->_link_site = link_site;
};

void GoogleSearch::_set_or_terms(
    const std::string or_terms // additional terms to include in the document
){
    this->_or_terms = or_terms;
};

void GoogleSearch::_set_date_restrict_type(
    const std::string date_restrict_type // date restrict type to restrict search results
){
    for (auto types : this->__date_restrict){
        if (types == date_restrict_type[0])
            this->_date_restrict_type = date_restrict_type;
    }
};

void GoogleSearch::_set_low_range(
    const std::string low_range // query appended to before the search query
){
    this->_low_range = low_range;
};

void GoogleSearch::_set_high_range(
    const std::string high_range // query appended to after the search query
){
    this->_high_range = high_range;
};

void GoogleSearch::_set_search_type(
    const std::string search_type // search type of the query
){
    for (auto search_types : this->__search_type){
        if (search_types == search_type)
            this->_search_type = search_type;
    }
};

void GoogleSearch::_set_filetype(
    const std::string filetype // filetype of the query;
){
    for (auto filetypes : this->__available_filetypes){
        if (filetypes == filetype)
            this->_filetype = filetype;
    }
};

void GoogleSearch::_set_rights(
    const std::string right // licensing of the query
){
    for (auto rights : this->__rights){
        if (rights == right)
            this->_rights = right;
    }
};

void GoogleSearch::_set_img_size(
    const std::string img_size // size of the image
){
    for (auto sizes : this->__image_sizes){
        if (sizes == img_size)
            this->_img_size = img_size;
    }
};

void GoogleSearch::_set_img_type(
    const std::string img_type // type of the image
){
    for (auto types : this->__image_types){
        if (types == img_type)
            this->_img_type = img_type;
    }
};

void GoogleSearch::_set_img_color_type(
    const std::string img_color_type // color type of the image
){
    for (auto colors : this->__image_color_types){
        if (colors == img_color_type)
            this->_img_color_type = img_color_type;
    }
};

void GoogleSearch::_set_img_dominant_color(
    const std::string img_dominant_color // dominant color of the image
){
    for (auto colors : this->__image_dominant_color_types){
        if (colors == img_dominant_color)
            this->_img_dominant_color = img_dominant_color;
    }
};

void GoogleSearch::_set_language(
    const std::string language // language to search google
){
    this->_language = language;
};

void GoogleSearch::_set_interface_language(
    const std::string interface_language // user interface language
){
    this->_interface_language = interface_language;
};

void GoogleSearch::_set_user_country(
    const std::string user_country // country to search from in google
){
    this->_user_country = user_country;
};

void GoogleSearch::_set_result_country(
    const std::string result_country // country to search for in google
){
    this->_result_country = result_country;
};

void GoogleSearch::_set_safe(
    const std::string safe // safe search
){
    for (auto safes : this->__safe){
        if (safes == safe)
            this->_safe = safe;
    }
};

void GoogleSearch::_set_sort(
    const std::string sort // sort order
){
    for (auto sorts : this->__sort){
        if (sorts == sort)
            this->_sort = sort;
    }
};

void GoogleSearch::_set_response_file(
    const std::string json_file // Name of the file to save response data
){
    this->_json_file = json_file;
};

void GoogleSearch::_set_env_file(
    const std::string env_file // Name of the file that contains Google Search API and CX Keys
){
    this->_env_file = env_file;
};

void GoogleSearch::_search_google(
    const std::string query, // Query to search Google
    const std::string json_file // Name of the file to save response data
){
    this->_search_terms = query;
    this->__construct_search_url();

    std::string json_data = this->__fetch_json_data(this->_search_url); // Json data from the result
    this->__save_json_data(json_data, json_file);
};

void GoogleSearch::_get_result(
    const int result_index, // Index of individual result to parse
    
    const bool title, // Get Title
    const bool snippet, // Get Snippet
    const bool link, // Get Link
    const bool image, // Get Image
    
    const std::string filename // Name of the file to retrive response data from
){
    std::ifstream json_file(filename); // Json file to retrive data
    nlohmann::json json_data; // nlohmann object to parse json data
    json_file >> json_data;

    json_file.close();

    if (json_data.contains("items") && json_data["items"].is_array()){
        if (result_index < json_data["items"].size() && result_index >= 0){
            auto result = json_data["items"][result_index];

            if (title && result.contains("title"))
                std::cout << "Title: " << result["title"] << std::endl;
            if (snippet && result.contains("snippet"))
                std::cout << "Snippet: " << result["snippet"] << std::endl;
            if (link && result.contains("link"))
                std::cout << "Link: " << result["link"] << std::endl;
            if (image && result.contains("pagemap") && result["pagemap"].contains("cse_image") && result["pagemap"]["cse_image"].is_array())
                std::cout << "Image: " << result["pagemap"]["cse_image"][0]["src"] << std::endl;
        }

        if (result_index == -1){
            auto results = json_data["items"];

            for (auto result : results){
                std::cout << "Title: " << result["title"] << std::endl;
                std::cout << "Snippet: " << result["snippet"] << std::endl;
                std::cout << "Link: " << result["link"] << std::endl;
                std::cout << "Image: " << result["pagemap"]["cse_image"][0]["src"] << std::endl;

                std::cout << std::endl;
            }
        }
    }
};

// int main(){
//     GoogleSearch google = GoogleSearch();
//     google._search_google("hello world");

//     return 0;
// }