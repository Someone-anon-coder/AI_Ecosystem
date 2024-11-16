import json
import requests
from bs4 import BeautifulSoup

class YahooFinance:
    """Class for Yahoo Finance
    
    Private Vars:
        __base_url__: Base url for yahoo finance
    
        __news_url__: News page in yahoo finance
        __market_url__: Market page in yahoo finance
        __sectors_url__: Sectors page in yahoo finance
        __compare_stocks_url__: Page to compare stocks in yahoo finance

        __market_options_url__: Options page in yahoo finance market
        __market_stock_url__: Stock page in yahoo finance market
        __market_crypto_url__: Crypto page in yahoo finance market
        __market_etfs_url__: ETF page in yahoo finance market
        __market_mutual_funds_url__: Mutual Funds page in yahoo finance market

        __sectors_technology_url__: Technology page in yahoo finance sectors
        __sectors_finance_services_url__: Finance services page in yahoo finance sectors
        __sectors_consumer_cyclical_url__: Consumer cyclical page in yahoo finance sectors
        __sectors_healthcare_url__: Healthcare page in yahoo finance sectors
        __sectors_communication_services_url__: Communication services page in yahoo finance sectors
        __sectors_industrials_url__: Industrials page in yahoo finance sectors
        __sectors_consumer_defensive_url__: Consumer defensive page in yahoo finance sectors
        __sectors_energy_url__: Energy page in yahoo finance sectors
        __sectors_real_estate_url__: Real estate page in yahoo finance sectors
        __sectors_basic_materials_url__: Basic materials page in yahoo finance sectors
        __sectors_utilities_url__: Utilities page in yahoo finance sectors

        __available_news__: Different news categories in Yahoo finance
        __available_markets__: Different markets in Yahoo finance

        __market_options__: Options market in yahoo finance
        __market_stock__: Stock market in yahoo finance
        __market_crypto__: Crypto market in yahoo finance
        __market_etfs__: ETF market in yahoo finance
        __market_mutual_funds__: Mutual Funds market in yahoo finance

        __sectors_technology__: Technology sectors in yahoo finance
        __sectors_finance_services__: Finance services sectors in yahoo finance
        __sectors_consumer_cyclical__: Consumer cyclical sectors in yahoo finance
        __sectors_healthcare__: Healthcare sectors in yahoo finance
        __sectors_communication_services__: Communication services sectors in yahoo finance
        __sectors_industrials__: Industrials sectors in yahoo finance
        __sectors_consumer_defensive__: Consumer defensive sectors in yahoo finance
        __sectors_energy__: Energy sectors in yahoo finance
        __sectors_real_estate__: Real estate sectors in yahoo finance
        __sectors_basic_materials__: Basic materials sectors in yahoo finance
        __sectors_utilities__: Utilities sectors in yahoo finance
    
    """
    
    __base_url__: str = "https://finance.yahoo.com" # Base url for yahoo finance

    __news_url__: str = "/topic/" # News page in yahoo finance
    __market_url__: str = "/markets/" # Market page in yahoo finance
    __sectors_url__: str = "/sectors/" # Sectors page in yahoo finance
    __compare_stocks_url__: str = "/compare/" # Page to compare stocks in yahoo finance

    __markets_options_url__: str = __market_url__ + "options/" # Options page in yahoo finance market
    __markets_stock_url__: str = __market_url__ + "stocks/" # Stock page in yahoo finance market
    __markets_crypto_url__: str = __market_url__ + "crypto/" # Crypto page in yahoo finance market
    __markets_etfs_url__: str = __market_url__ + "etfs/" # ETF page in yahoo finance market
    __markets_mutual_funds_url__: str = __market_url__ + "mutualfunds/" # Mutual Funds page in yahoo finance market

    __sectors_technology_url__: str = __sectors_url__ + "technology/" # Technology page in yahoo finance sectors
    __sectors_finance_services_url__: str = __sectors_url__ + "financial-services/" # Finance services page in yahoo finance sectors
    __sectors_consumer_cyclical_url__: str = __sectors_url__ + "consumer-cyclical/" # Consumer cyclical page in yahoo finance sectors
    __sectors_healthcare_url__: str = __sectors_url__ + "healthcare/" # Healthcare page in yahoo finance sectors
    __sectors_communication_services_url__: str = __sectors_url__ + "communication-services/" # Communication services page in yahoo finance sectors
    __sectors_industrials_url__: str = __sectors_url__ + "industrials/" # Industrials page in yahoo finance sectors
    __sectors_consumer_defensive_url__: str = __sectors_url__ + "consumer-defensive/" # Consumer defensive page in yahoo finance sectors
    __sectors_energy_url__: str = __sectors_url__ + "energy" # Energy page in yahoo finance sectors
    __sectors_real_estate_url__: str = __sectors_url__ + "real-estate" # Real estate page in yahoo finance sectors
    __sectors_basic_materials_url__: str = __sectors_url__ + "basic-materials/" # Basic materials page in yahoo finance sectors
    __sectors_utilities_url__: str = __sectors_url__ + "utilities/" # Utilities page in yahoo finance sectors

    __available_news__: tuple = ("latest-news", "stock-market-news", "yahoo-finance-originals", "morning-brief", "economic-news", "housing-market", "earnings", "tech", "crypto") # Different news categories in Yahoo finance
    __available_markets__: tuple = ("world-indices", "commodities", "bonds", "currencies") # Different markets in Yahoo finance
    
    __markets_options__: tuple = ("most-active", "gainers", "losers", "highest-implied-volatility", "highest-open-interest") # Options market in yahoo finance
    __markets_stock__: tuple = ("most-active", "gainers", "losers", "trending", "52-week-gainers", "52-week-losers") # Stock market in yahoo finance
    __markets_crypto__: tuple = ("all", "most-active", "gainers", "losers", "trending") # Crypto market in yahoo finance
    __markets_etfs__: tuple = ("most-active", "gainers", "losers", "trending", "top-performing", "best-historical-performance", "top") # ETF market in yahoo finance
    __markets_mutual_funds__: tuple = ("most-active", "gainers", "losers", "top-performing", "best-historical-performance", "top") # Mutual Funds market in yahoo finance
    
    __sectors_technology__: tuple = ("semiconductors", "software-infrastructure", "consumer-electronics", "software-application", "information-technology-services", "communication-equipment", "semiconductor-equipment-materials", "computer-hardware", "electronic-component", "scientific-technical-instruments", "solar", "electronics-computer-distribution") # Technology sectors in yahoo finance
    __sectors_finance_services__: tuple = ("banks-diversified", "credit-services", "asset-management", "insurance-diversified", "banks-regional", "capital-markets", "financial-data-stock-exchanges", "insurance-propery-casualty", "insurance-brokers", "insuranc-life", "insurance-specialty", "mortgage-finance", "insurance-reinsurance", "shell-companies", "financial-conglomarates") # Finance services sectors in yahoo finance
    __sectors_consumer_cyclical__: tuple = ("internet-retail", "auto-manufacturers", "restaurants", "home-improvement-retail", "travel-services", "speciality-retail", "apparel-retail", "residential-construction", "footware-accessories", "packaging-containers", "lodging", "auto-truck-dealership", "auto-parts", "resorts-casinos", "gambling", "leisure", "apparel-manufacturing", "personal-services", "furnishings-fixtures-appliances", "recreational-vehicles", "luxury-goods", "department-stores", "textile-manufacturing") # Consumer cyclical sectors in yahoo finance
    __sectors_healthcare__: tuple = ("drug-manufactures-general", "healthcare-plans", "medical-devices", "biotechnology", "diagnostics-research", "medical-instruments-supplies", "medical-care-facilities", "drug-manufacturers-specialty-general", "medical-distribution", "health-information-services", "pharmaceutical-retailers") # Healthcare sectors in yahoo finance
    __sectors_communication_services__: tuple = ("internet-content-information", "telecom-services", "entertainment", "electronic-gaming-multimedia", "advertising-agencies", "publishing", "broadcasting") # Communication services sectors in yahoo finance
    __sectors_industrials__: tuple = ("aerospace-defence", "specialty-industrial-machinery", "railroads", "farm-heavy-contruction-machinery", "building-products-equipment", "specialty-business-services", "integrated-freight-logistics", "engineering-construction", "waste-management", "industrial-distribution", "conglomerates", "rental-leasing-services", "electrical-equipment-parts", "trucking", "airlines", "consulting-services", "tools-accessories", "pollution-treatment-controls", "metal-fabrication", "security-protection-services", "marine-shipping", "Infrastructure-operations", "staffing-employment-services", "airports-air-services", "business-equipment-supplies") # Industrials sectors in yahoo finance
    __sectors_consumer_defensive__: tuple = ("discount-stores", "beverages-non-alcoholic", "household-personal-products", "tobacco", "packaged-foods", "confectioners", "grocery-stores", "food-distribution", "farm-products", "beverages-brewers", "education-training-services", "beverages-wineries-distilleries", "") # Consumer defensive sectors in yahoo finance
    __sectors_energy__: tuple = ("oil-gas-integrated", "oil-gas-midstream", "oil-gas-e-p", "oil-gas-equipment-services", "oil-gas-refining-marketing", "uranium", "oil-gas-drilling", "thermal-coal") # Energy sectors in yahoo finance
    __sectors_real_estate__: tuple = ("reit-specialty", "reit-inductrial", "reit-retail", "reit-residential", "reit-healthcare-facilities", "real-estate-services", "reit-office", "reit-diversified", "reit-mortgage", "reit-hotel-motel", "reit-estate-development", "reit-estate-diversified") # Real estate sectors in yahoo finance
    __sectors_basic_materials__: tuple = ("specialty-chemicals", "gold", "building-materials", "copper", "steel", "agricultural-inputs", "chemicals", "other-industrial-metals-mining", "lumber-wood-production", "aluminium", "other-precious-metal-mining", "coking-coal", "paper-paper-products", "silver") # Basic materials sectors in yahoo finance
    __sectors_utilities__: tuple = ("utilities-regulated-electric", "utilities-renewable", "utilities-diversified", "utilities-independent-power-producers", "utilities-regulated-gas", "utilities-regulated-water") # Utilities sectors in yahoo finance

    def __get_html__(self, url: str) -> str:
        """Get the html of the given url
        
        Args:
            url (str): Url to get the html from
        
        Returns:
            str: Html of the given url
        """
        
        response = requests.get(url)
        return response.text

    def __get_table_data__(self, html_content: str) -> json:
        soup = BeautifulSoup(html_content, "html.parser")

        table = soup.find("table", attrs={"data-testid": "table-container"})
        if not table:
            print("Table not found")
            return None
        
        table_data = {}

        thead = table.find("thead")
        if thead:
            table_data["head"] = []
            for row in thead.find_all("tr"):
                table_data["head"].append([cell.get_text(strip=True) for cell in row.find_all(["th", "td"])])

        tbody = table.find("tbody")
        if tbody:
            table_data["body"] = []
            for row in tbody.find_all("tr"):
                table_data["body"].append([cell.get_text(strip=True) for cell in row.find_all("td")])
        
        return table_data
    
    def get_world_indices(self, index: str = "", json_file:str = "json_files/Y_Finance/world_indices.json") -> str | None:
        """Get the world indices

        Args:
            index (str, optional): Index to get the data from. Defaults to "".
            json_file (str, optional): Name of the json file to save the data to. Defaults to "world_indices.json".

        Returns:
            str | None: Data of the world indices
        """
        
        full_url = self.__base_url__ + self.__market_url__ + self.__available_markets__[0]
        html_content = self.__get_html__(full_url)
        
        table_data = self.__get_table_data__(html_content)
        if not table_data:
            return None
        
        world_indexes = []
        for i in range(len(table_data["body"])):
            world_indexes.append({
                "Symbol": table_data['body'][i][0],
                "Name": table_data['body'][i][1],
                "Price": table_data['body'][i][3].split("+")[0].split("-")[0],
                "Change": table_data['body'][i][4],
                "Change %": table_data['body'][i][5],
                "Volume": table_data['body'][i][6],
            })

        try:
            with open(json_file, "w", encoding="utf-8") as file:
                json.dump(world_indexes, file, ensure_ascii=False, indent=4)
        except (TypeError, OverflowError) as e:
            print(f"Error serializing table data to JSON: {e}")
            raise
    
    def get_futures(self, index: str = "", json_file:str = "json_files/Y_Finance/futures.json") -> str | None:
        """Get the futures data
        
        Args:
            index (str, optional): Index to get the data from. Defaults to "".
            json_file (str, optional): Name of the json file to save the data to. Defaults to "futures.json".
        
        Returns:
            str | None: Data of the futures
        """

        full_url = self.__base_url__ + self.__market_url__ + self.__available_markets__[1]
        html_content = self.__get_html__(full_url)
        
        table_data = self.__get_table_data__(html_content)
        if not table_data:
            return None
        
        futures = []
        for i in range(len(table_data["body"])):
            futures.append({
                "Symbol": table_data['body'][i][0],
                "Name": table_data['body'][i][1],
                "Price": table_data['body'][i][3].split("+")[0].split("-")[0],
                "Market-Time": table_data['body'][i][4],
                "Change": table_data['body'][i][5],
                "Change %": table_data['body'][i][6],
                "Volume": table_data['body'][i][7],
                "Open Interest": table_data['body'][i][8],
            })

        try:
            with open(json_file, "w", encoding="utf-8") as file:
                json.dump(futures, file, ensure_ascii=False, indent=4)
        except:
            print("Error serializing table data to JSON")
            raise
    
    def get_bonds(self, index: str = "", json_file:str = "json_files/Y_Finance/bonds.json") -> str | None:
        """Get the bonds data
        
        Args:
            index (str, optional): Index to get the data from. Defaults to "".
            json_file (str, optional): Name of the json file to save the data to. Defaults to "bonds.json".
        
        Returns:
            str | None: Data of the bonds
        """

        full_url = self.__base_url__ + self.__market_url__ + self.__available_markets__[2]
        html_content = self.__get_html__(full_url)
        
        table_data = self.__get_table_data__(html_content)
        if not table_data:
            return None
        
        bonds = []
        for i in range(len(table_data["body"])):
            bonds.append({
                "Symbol": table_data['body'][i][0],
                "Name": table_data['body'][i][1],
                "Price": table_data['body'][i][3].split("+")[0].split("-")[0],
                "Change": table_data['body'][i][4],
                "Change %": table_data['body'][i][5],
            })
        
        try:
            with open(json_file, "w", encoding="utf-8") as file:
                json.dump(bonds, file, ensure_ascii=False, indent=4)
        except:
            print("Error serializing table data to JSON")
            raise

    def get_currencies(self, index: str = "", json_file:str = "json_files/Y_Finance/currencies.json") -> str | None:
        """Get the currencies data
        
        Args:
            index (str, optional): Index to get the data from. Defaults to "".
            json_file (str, optional): Name of the json file to save the data to. Defaults to "currencies.json".
        
        Returns:
            str | None: Data of the currencies
        """

        full_url = self.__base_url__ + self.__market_url__ + self.__available_markets__[3]
        html_content = self.__get_html__(full_url)

        table_data = self.__get_table_data__(html_content)
        if not table_data:
            return None

        currencies = []
        for i in range(len(table_data["body"])):
            currencies.append({
                "Symbol": table_data['body'][i][0],
                "Name": table_data['body'][i][1],
                "Price": table_data['body'][i][3].split("+")[0].split("-")[0],
                "Change": table_data['body'][i][4],
                "Change %": table_data['body'][i][5],
            })
        
        try:
            with open(json_file, "w", encoding="utf-8") as file:
                json.dump(currencies, file, ensure_ascii=False, indent=4)
        except:
            print("Error serializing table data to JSON")
            raise
    
    def get_options(self, option_type: str = "", start: int = 0, count: int = 100, json_file:str = "json_files/Y_Finance/options.json") -> str | None:
        """Get the options data

        Args:
            option_type (str, optional): Type of the options. Defaults to "".
            json_file (str, optional): Name of the json file to save the data to. Defaults to "options.json".

        Returns:
            str | None: Data of the options
        """
        
        if option_type not in self.__markets_options__:
            return None
        
        full_url: str = self.__base_url__ + self.__markets_options_url__ + option_type + "?start=" + str(start) + "&count=" + str(count)
        html_content = self.__get_html__(full_url)

        table_data = self.__get_table_data__(html_content)
        if not table_data:
            return None

        options = []
        for i in range(len(table_data["body"])):
            options.append({
                "Symbol": table_data['body'][i][0],
                "Name": table_data['body'][i][1],
                "Underlying-Symbol": table_data['body'][i][2],
                "Strike": table_data['body'][i][3],
                "Expiration-Date": table_data['body'][i][4],
                "Price": table_data['body'][i][5].split("+")[0].split("-")[0],
                "Change": table_data['body'][i][6],
                "Change %": table_data['body'][i][7],
                "Bid": table_data['body'][i][8],
                "Ask": table_data['body'][i][9],
                "Volume": table_data['body'][i][10],
                "Open-Interest": table_data['body'][i][11],
            })
        
        try:
            with open(json_file, "w", encoding="utf-8") as file:
                json.dump(options, file, ensure_ascii=False, indent=4)
        except:
            print("Error serializing table data to JSON")
            raise
    
    def get_sectors(self, index: str = "", json_file:str = "json_files/Y_Finance/sectors.json") -> str | None:
        """Get the sectors data
        
        Args:
            index (str, optional): Index to get the data from. Defaults to "".
            json_file (str, optional): Name of the json file to save the data to. Defaults to "sectors.json".
        
        Returns:
            str | None: Data of the sectors
        """

if __name__ == "__main__":
    yahoo = YahooFinance()
    yahoo.get_world_indices()
    yahoo.get_futures()
    yahoo.get_bonds()
    yahoo.get_currencies()
    yahoo.get_options("highest-implied-volatility")