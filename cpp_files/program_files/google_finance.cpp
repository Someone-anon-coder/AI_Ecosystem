#include <string>
#include <vector>
#include <iostream>

#include <curl/curl.h>

/// @brief Class for Yahoo Finance
class YahooFinance{
    
    private:
        
        // Private variables in YahooFinance class
        std::string __base_url = "https://finance.yahoo.com"; // Base url for yahoo finance
        
        std::string __news_url = "/topic/"; // News page in yahoo finance
        std::string __market_url = "/markets/"; // Market page in yahoo finance
        std::string __sectors_url = "/sectors/"; // Sectors page in yahoo finance
        std::string __compare_stocks_url = "/compare/"; // Page to compare stocks in yahoo finance
        
        std::string __markets_options_url = __market_url + "options/"; // Options page in yahoo finance market
        std::string __markets_stock_url = __market_url + "stocks/"; // Stock page in yahoo finance market
        std::string __markets_crypto_url = __market_url + "crypto/"; // Crypto page in yahoo finance market
        std::string __markets_etfs_url = __market_url + "etfs/"; // ETF page in yahoo finance market
        std::string __markets_mutual_funds_url = __market_url + "mutualfunds/"; // Mutual Funds page in yahoo finance market
        
        std::string __sectors_technology_url = __sectors_url + "technology/"; // Technology page in yahoo finance sectors
        std::string __sectors_finance_services_url = __sectors_url + "financial-services/"; // Finance services page in yahoo finance sectors
        std::string __sectors_consumer_cyclical_url = __sectors_url + "consumer-cyclical/"; // Consumer cyclical page in yahoo finance sectors
        std::string __sectors_healthcare_url = __sectors_url + "healthcare/"; // Healthcare page in yahoo finance sectors
        std::string __sectors_communication_services_url = __sectors_url + "communication-services/"; // Communication services page in yahoo finance sectors
        std::string __sectors_industrials_url = __sectors_url + "industrials/"; // Industrials page in yahoo finance sectors
        std::string __sectors_consumer_defensive_url = __sectors_url + "consumer-defensive/"; // Consumer defensive page in yahoo finance sectors
        std::string __sectors_energy_url = __sectors_url + "energy/"; // Energy page in yahoo finance sectors
        std::string __sectors_real_estate_url = __sectors_url + "real-estate/"; // Real estate page in yahoo finance sectors
        std::string __sectors_basic_materials_url = __sectors_url + "basic-materials/"; // Basic materials page in yahoo finance sectors
        std::string __sectors_utilities_url = __sectors_url + "utilities/"; // Utilities page in yahoo finance sectors

        std::vector<std::string> __available_news = {"latest-news", "stock-market-news", "yahoo-finance-originals", "morning-brief", "economic-news", "housing-market", "earnings", "tech", "crypto"}; // Different news categories in Yahoo finance
        std::vector<std::string> __available_markets = {"world-indices", "commodities", "bonds", "currencies"}; // Different markets in Yahoo finance
        
        std::vector<std::string> __markets_options = {"most-active", "gainers", "losers", "highest-implied-volatility", "highest-open-interest"}; // Options market in yahoo finance
        std::vector<std::string> __markets_stock = {"most-active", "gainers", "losers", "trending", "52-week-gainers", "52-week-losers"}; // Stock market in yahoo finance
        std::vector<std::string> __markets_crypto = {"all", "most-active", "gainers", "losers", "trending"}; // Crypto market in yahoo finance
        std::vector<std::string> __markets_etfs = {"most-active", "gainers", "losers", "trending", "top-performing", "best-historical-performance", "top"}; // ETF market in yahoo finance
        std::vector<std::string> __markets_mutual_funds = {"most-active", "gainers", "losers", "top-performing", "best-historical-performance", "top"}; // Mutual Funds market in yahoo finance

        std::vector<std::string> __sectors_technology = {"semiconductors", "software-infrastructure", "consumer-electronics", "software-application", "information-technology-services", "communication-equipment", "semiconductor-equipment-materials", "computer-hardware", "electronic-component", "scientific-technical-instruments", "solar", "electronics-computer-distribution"}; // Technology sectors in yahoo finance
        std::vector<std::string> __sectors_finance_services = {"banks-diversified", "credit-services", "asset-management", "insurance-diversified", "banks-regional", "capital-markets", "financial-data-stock-exchanges", "insurance-propery-casualty", "insurance-brokers", "insuranc-life", "insurance-specialty", "mortgage-finance", "insurance-reinsurance", "shell-companies", "financial-conglomarates"}; // Finance services sectors in yahoo finance
        std::vector<std::string> __sectors_consumer_cyclical = {"internet-retail", "auto-manufacturers", "restaurants", "home-improvement-retail", "travel-services", "speciality-retail", "apparel-retail", "residential-construction", "footware-accessories", "packaging-containers", "lodging", "auto-truck-dealership", "auto-parts", "resorts-casinos", "gambling", "leisure", "apparel-manufacturing", "personal-services", "furnishings-fixtures-appliances", "recreational-vehicles", "luxury-goods", "department-stores", "textile-manufacturing"}; // Consumer cyclical sectors in yahoo finance
        std::vector<std::string> __sectors_healthcare = {"drug-manufactures-general", "healthcare-plans", "medical-devices", "biotechnology", "diagnostics-research", "medical-instruments-supplies", "medical-care-facilities", "drug-manufacturers-specialty-general", "medical-distribution", "health-information-services", "pharmaceutical-retailers"}; // Healthcare sectors in yahoo finance
        std::vector<std::string> __sectors_communication_services = {"internet-content-information", "telecom-services", "entertainment", "electronic-gaming-multimedia", "advertising-agencies", "publishing", "broadcasting"}; // Communication services sectors in yahoo finance
        std::vector<std::string> __sectors_industrials = {"aerospace-defence", "specialty-industrial-machinery", "railroads", "farm-heavy-contruction-machinery", "building-products-equipment", "specialty-business-services", "integrated-freight-logistics", "engineering-construction", "waste-management", "industrial-distribution", "conglomerates", "rental-leasing-services", "electrical-equipment-parts", "trucking", "airlines", "consulting-services", "tools-accessories", "pollution-treatment-controls", "metal-fabrication", "security-protection-services", "marine-shipping", "Infrastructure-operations", "staffing-employment-services", "airports-air-services", "business-equipment-supplies"}; // Industrials sectors in yahoo finance
        std::vector<std::string> __sectors_consumer_defensive = {"discount-stores", "beverages-non-alcoholic", "household-personal-products", "tobacco", "packaged-foods", "confectioners", "grocery-stores", "food-distribution", "farm-products", "beverages-brewers", "education-training-services", "beverages-wineries-distilleries", ""}; // Consumer defensive sectors in yahoo finance
        std::vector<std::string> __sectors_energy = {"oil-gas-integrated", "oil-gas-midstream", "oil-gas-e-p", "oil-gas-equipment-services", "oil-gas-refining-marketing", "uranium", "oil-gas-drilling", "thermal-coal"}; // Energy sectors in yahoo finance
        std::vector<std::string> __sectors_real_estate = {"reit-specialty", "reit-inductrial", "reit-retail", "reit-residential", "reit-healthcare-facilities", "real-estate-services", "reit-office", "reit-diversified", "reit-mortgage", "reit-hotel-motel", "reit-estate-development", "reit-estate-diversified"}; // Real estate sectors in yahoo finance
        std::vector<std::string> __sectors_basic_materials = {"specialty-chemicals", "gold", "building-materials", "copper", "steel", "agricultural-inputs", "chemicals", "other-industrial-metals-mining", "lumber-wood-production", "aluminium", "other-precious-metal-mining", "coking-coal", "paper-paper-products", "silver"}; // Basic materials sectors in yahoo finance
        std::vector<std::string> __sectors_utilities = {"utilities-regulated-electric", "utilities-renewable", "utilities-diversified", "utilities-independent-power-producers", "utilities-regulated-gas", "utilities-regulated-water"}; // Utilities sectors in yahoo finance

        // Private Functions in YahooFinance class

        /// @brief Callback function to write data to a string
        /// @param contents Data downloaded from the url
        /// @param size Size of the data
        /// @param nmemb Number of elements in the data
        /// @param userp Pointer to the user data
        /// @return Size of the data
        size_t __WriteCallback(
            void* contents, 
            size_t size,
            size_t nmemb, 
            void* userp
        ) {
            ((std::string*)userp)->append((char*)contents, size * nmemb);
            return size * nmemb;
        }

        /// @brief Get html content from the url
        /// @param url Url to get html content from
        /// @return Html content from the url
        std::string get_html_content(\
            const std::string& url
        ) {
            CURL* curl;
            CURLcode res;
            std::string html_content;

            curl_global_init(CURL_GLOBAL_DEFAULT);  // Initialize libcurl globally
            curl = curl_easy_init();  // Initialize libcurl session

            if(curl) {
                curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &YahooFinance::__WriteCallback);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &html_content);

                res = curl_easy_perform(curl);
                if(res != CURLE_OK) {
                    std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
                }
                
                curl_easy_cleanup(curl);
            }

            curl_global_cleanup();  // Cleanup libcurl globally
            return html_content;
        }
    
};
