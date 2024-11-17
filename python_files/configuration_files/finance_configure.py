import json
import requests
from bs4 import BeautifulSoup

class YahooFinance:
    """Class for Yahoo Finance
    
    Private Variables:
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
    
        __available_sub_markets__: Different sub-markets in Yahoo finance
        __available_sectors__: Different sectors in Yahoo finance
    
    Private Functions:
        __get_html__: Get the html of the given url
        __get_table_data__: Get the table data from the given html
        __is_sector_available__: Check if the given sector is available
        __is_sub_sector_available__: Check if the given sub-sector is available in the given sector
        __get_sectors_percentages__: Get the sectors weightage

    Public Functions:
        get_world_indices: Get the world indices
        get_futures: Get the futures data
        get_bonds: Get the bonds data
        get_currencies: Get the currencies data
        get_options: Get the options data
        get_sub_sectors: Get the sectors data
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

    __available_sub_markets__: dict = {
        "options": ("most-active", "gainers", "losers", "highest-implied-volatility", "highest-open-interest"), # Options market in yahoo finance
        "stock": ("most-active", "gainers", "losers", "trending", "52-week-gainers", "52-week-losers"), # Stock market in yahoo finance
        "crypto": ("all", "most-active", "gainers", "losers", "trending"), # Crypto market in yahoo finance
        "etfs": ("most-active", "gainers", "losers", "trending", "top-performing", "best-historical-performance", "top"), # ETF market in yahoo finance
        "mutual_funds": ("most-active", "gainers", "losers", "top-performing", "best-historical-performance", "top") # Mutual Funds market in yahoo finance
    }
    __available_sectors__: dict = {
        "technology": ("semiconductors", "software-infrastructure", "consumer-electronics", "software-application", "information-technology-services", "communication-equipment", "semiconductor-equipment-materials", "computer-hardware", "electronic-component", "scientific-technical-instruments", "solar", "electronics-computer-distribution"), # Technology sectors in yahoo finance
        "finance_services": ("banks-diversified", "credit-services", "asset-management", "insurance-diversified", "banks-regional", "capital-markets", "financial-data-stock-exchanges", "insurance-propery-casualty", "insurance-brokers", "insuranc-life", "insurance-specialty", "mortgage-finance", "insurance-reinsurance", "shell-companies", "financial-conglomarates"), # Finance services sectors in yahoo finance,
        "consumer_cyclical": ("internet-retail", "auto-manufacturers", "restaurants", "home-improvement-retail", "travel-services", "speciality-retail", "apparel-retail", "residential-construction", "footware-accessories", "packaging-containers", "lodging", "auto-truck-dealership", "auto-parts", "resorts-casinos", "gambling", "leisure", "apparel-manufacturing", "personal-services", "furnishings-fixtures-appliances", "recreational-vehicles", "luxury-goods", "department-stores", "textile-manufacturing"), # Consumer cyclical sectors in yahoo finance
        "healthcare": ("drug-manufactures-general", "healthcare-plans", "medical-devices", "biotechnology", "diagnostics-research", "medical-instruments-supplies", "medical-care-facilities", "drug-manufacturers-specialty-general", "medical-distribution", "health-information-services", "pharmaceutical-retailers"), # Healthcare sectors in yahoo finance 
        "communication_services": ("internet-content-information", "telecom-services", "entertainment", "electronic-gaming-multimedia", "advertising-agencies", "publishing", "broadcasting"), # Communication services sectors in yahoo finance
        "industrials": ("aerospace-defence", "specialty-industrial-machinery", "railroads", "farm-heavy-contruction-machinery", "building-products-equipment", "specialty-business-services", "integrated-freight-logistics", "engineering-construction", "waste-management", "industrial-distribution", "conglomerates", "rental-leasing-services", "electrical-equipment-parts", "trucking", "airlines", "consulting-services", "tools-accessories", "pollution-treatment-controls", "metal-fabrication", "security-protection-services", "marine-shipping", "Infrastructure-operations", "staffing-employment-services", "airports-air-services", "business-equipment-supplies"), # Industrials sectors in yahoo finance 
        "consumer_defensive": ("discount-stores", "beverages-non-alcoholic", "household-personal-products", "tobacco", "packaged-foods", "confectioners", "grocery-stores", "food-distribution", "farm-products", "beverages-brewers", "education-training-services", "beverages-wineries-distilleries", ""), # Consumer defensive sectors in yahoo finance
        "energy": ("oil-gas-integrated", "oil-gas-midstream", "oil-gas-e-p", "oil-gas-equipment-services", "oil-gas-refining-marketing", "uranium", "oil-gas-drilling", "thermal-coal"), # Energy sectors in yahoo finance
        "real_estate": ("reit-specialty", "reit-inductrial", "reit-retail", "reit-residential", "reit-healthcare-facilities", "real-estate-services", "reit-office", "reit-diversified", "reit-mortgage", "reit-hotel-motel", "reit-estate-development", "reit-estate-diversified"), # Real estate sectors in yahoo finance
        "basic_materials": ("specialty-chemicals", "gold", "building-materials", "copper", "steel", "agricultural-inputs", "chemicals", "other-industrial-metals-mining", "lumber-wood-production", "aluminium", "other-precious-metal-mining", "coking-coal", "paper-paper-products", "silver"), # Basic materials sectors in yahoo finance
        "utilities": ("utilities-regulated-electric", "utilities-renewable", "utilities-diversified", "utilities-independent-power-producers", "utilities-regulated-gas", "utilities-regulated-water") # Utilities sectors in yahoo finance
    }

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
        """Get the table data from the given html

        Args:
            html_content (str): Html to get the table data from

        Returns:
            json: Table data of the given html
        """
        
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
    
    def __get_table_data_div__(self, html_content: str, attribute_name: str = "data-testid", attribute_value: str = "sector-picker"):
        """Get the table data from the given html

        Args:
            html_content (str): Html to get the table data from
            attribute_name (str, optional): Attribute name to search for. Defaults to "data-testid".
            attribute_value (str, optional): Attribute value to search for. Defaults to "sector-picker".

        Returns:
            json: Table data of the given html
        """
        
        soup = BeautifulSoup(html_content, "html.parser")

        div = soup.find("div", attrs={attribute_name: attribute_value})
        if not div:
            print("Div not found")
            return None

        table = div.find("table")
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
    
    def __is_sector_available__(self, sector: str) -> bool:
        """Check if the given sector is available
        
        Args:
            sector (str): Sector to check
        
        Returns:
            bool: True if the sector is available, False otherwise
        """

        if sector not in list(self.__available_sectors__.keys()):
            return False
        
        return True

    def __is_sub_sector_available__(self, sector: str, sub_sector: str) -> bool:
        """Check if the given sub-sector is available in the given sector
        
        Args:
            sector (str): Sector to check
            sub_sector (str): Sub-sector to check
        
        Returns:
            bool: True if the sub-sector is available, False otherwise
        """

        if sub_sector not in list(self.__available_sectors__[sector]):
            return False
        
        return True
    
    def __get_sectors_percentages__(self, sector: str) -> list | None:
        """Get the sectors weightage

        Args:
            sector (str): Sector to get the data from

        Returns:
            list | None: Data of the sectors
        """
        
        full_url: str = self.__base_url__ + self.__sectors_url__ + sector
        html_content: str = self.__get_html__(full_url)

        table_data: dict = self.__get_table_data_div__(html_content)
        if not table_data:
            return None
        
        sectors: list = []
        for i in range(len(table_data["body"])):
            sectors.append({
                "Industry Name": table_data['body'][i][0],
                "Market Weight": table_data['body'][i][1],
                "Year To Date Return": table_data['body'][i][2]
            })
        
        return sectors
    
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
    
    def get_options(self, option_type: str = "most-active", start: int = 0, count: int = 100, json_file:str = "json_files/Y_Finance/options.json") -> str | None:
        """Get the options data

        Args:
            option_type (str, optional): Type of the options. Defaults to "most-active".
            json_file (str, optional): Name of the json file to save the data to. Defaults to "json_files/Y_Finance/options.json".

        Returns:
            str | None: Data of the options
        """
        
        if option_type not in self.__available_sub_markets__["options"]:
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

    def get_sub_sectors(self, sector: str, get_only_sector: bool = True, sub_sector: str = "", json_file:str = "json_files/Y_Finance/sectors.json") -> str | None:
        """Get the sectors data
        
        Args:
            sector (str, optional): Sector to get the data from. Defaults to "technology".
            get_only_sector (bool, optional): Whether to get only the sector data. Defaults to True.
            sub_sector (str, optional): Sub-sector to get the data from. Defaults to "".
            json_file (str, optional): Name of the json file to save the data to. Defaults to "json_files/Y_Finance/sectors.json".
        
        Returns:
            str | None: Data of the sectors
        """

        if not self.__is_sector_available__(sector):
            return None
        
        sectors = self.__get_sectors_percentages__(sector)
        if not sectors:
            return None

        if get_only_sector:
            try:
                with open(json_file, "w", encoding="utf-8") as file:
                    json.dump(sectors, file, ensure_ascii=False, indent=4)
            except:
                print("Error serializing table data to JSON")
                raise
            
            return sectors
        
        if not self.__is_sub_sector_available__(sector, sub_sector):
            return None
        
        full_url = self.__base_url__ + self.__sectors_url__ + sector + "/" + sub_sector
        html_content = self.__get_html__(full_url)

        table_data = self.__get_table_data__(html_content)
        if not table_data:
            return None
        
        sub_sectors = [{
            "All Sectors": sectors
        }]
        
        for i in range(len(table_data["body"])):
            sub_sectors.append({
                "Name": table_data['body'][i][0],
                "Last Price": table_data['body'][i][1],
                "1Y Target Estimate": table_data['body'][i][2],
                "Market Weight": table_data['body'][i][3],
                "Market Cap": table_data['body'][i][4],
                "Day Change %": table_data['body'][i][5],
                "Year To Date Return": table_data['body'][i][6],
                "Average Analyst Rating": table_data['body'][i][7],
            })
        
        try:
            with open(json_file, "w", encoding="utf-8") as file:
                json.dump(sub_sectors, file, ensure_ascii=False, indent=4)
        except:
            print("Error serializing table data to JSON")
            raise
    
    def get_stocks(self, stock_type: str = "most-active", start: int = 0, count: int = 100, json_file:str = "json_files/Y_Finance/stocks.json") -> str | None:
        """Get the stocks data
        
        Args:
            stock_type (str, optional): Type of the stocks. Defaults to "most-active".
            start (int, optional): Start index of the stocks. Defaults to 0.
            count (int, optional): Count of the stocks. Defaults to 100.
            json_file (str, optional): Name of the json file to save the data to. Defaults to "json_files/Y_Finance/stocks.json".
        
        Returns:
            str | None: Data of the stocks
        """

        if stock_type not in self.__available_sub_markets__["stock"]:
            return None
        
        full_url: str = self.__base_url__ + self.__markets_stock_url__ + stock_type + "?start=" + str(start) + "&count=" + str(count)
        html_content = self.__get_html__(full_url)

        table_data = self.__get_table_data__(html_content)
        if not table_data:
            return None

        stocks = []
        for i in range(len(table_data["body"])):
            stocks.append({
                "Symbol": table_data['body'][i][0],
                "Name": table_data['body'][i][1],
                "Price": table_data['body'][i][3].split("+")[0].split("-")[0], 
                "Change": table_data['body'][i][4],
                "Change %": table_data['body'][i][5],
                "Volume": table_data['body'][i][6],
                "Average Volume": table_data['body'][i][7],
                "Market Cap": table_data['body'][i][8],
                "P/E Ratio (TTM)": table_data['body'][i][9],
                "52 Week Change %": table_data['body'][i][10]
            })
        
        try:
            with open(json_file, "w", encoding="utf-8") as file:
                json.dump(stocks, file, ensure_ascii=False, indent=4)
        except:
            print("Error serializing table data to JSON")
            raise
    
    def get_crypto(self, crypto_type: str = "all", start: int = 0, count: int = 100, json_file:str = "json_files/Y_Finance/crypto.json") -> str | None:
        """Get the crypto data
        
        Args:
            crypto_type (str | optional): Type of the crypto. Defaults to "all".
            start (int, optional): Start index of the stocks. Defaults to 0.
            count (int, optional): Count of the stocks. Defaults to 100.
            json_file (str, optional): Name of the json file to save the data to. Defaults to "json_files/Y_Finance/crypto.json".
        
        Returns:
            str | None: Data of the stocks
        """

        if crypto_type not in self.__available_sub_markets__["crypto"]:
            return None
        
        full_url: str = self.__base_url__ + self.__markets_crypto_url__ + crypto_type + "?start=" + str(start) + "&count=" + str(count)
        html_content = self.__get_html__(full_url)

        table_data = self.__get_table_data__(html_content)
        if not table_data:
            return None

        crypto = []
        for i in range(len(table_data["body"])):
            crypto.append({
                "Symbol": table_data['body'][i][0],
                "Name": table_data['body'][i][1],
                "Price": table_data['body'][i][3].split("+")[0].split("-")[0],
                "Change": table_data['body'][i][4],
                "Change %": table_data['body'][i][5],
                "Market Cap": table_data['body'][i][6],
                "Volume": table_data['body'][i][7],
                "Volume in Currency (24hr)": table_data['body'][i][8],
                "Total Volume All Currencies (24hr)": table_data['body'][i][9],
                "Circulating Supply": table_data['body'][i][10],
                "52 Week Change %": table_data['body'][i][11],
            })
        
        try:
            with open(json_file, "w", encoding="utf-8") as file:
                json.dump(crypto, file, ensure_ascii=False, indent=4)
        except:
            print("Error serializing table data to JSON")
            raise

if __name__ == "__main__":
    yahoo = YahooFinance()
    yahoo.get_world_indices()
    yahoo.get_futures()
    yahoo.get_bonds()
    yahoo.get_currencies()
    yahoo.get_options("highest-implied-volatility")
    yahoo.get_sub_sectors("technology", False, "semiconductors")
    yahoo.get_stocks("most-active")
    yahoo.get_crypto("most-active", 100, 100)