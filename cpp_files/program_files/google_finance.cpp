#include <string>
#include <map>

class GoogleFinance{
    private:
        std::string base_url = "https://www.google.com/finance";

        std::map<std::string, std::string> market_types = {
            {"US", "Dow Jones\nS&P 500\nNasdaq\nRussel"},
            {"Europe", "DAX\nFTSE 100\nCAC 40\nIBEX 35\nSTOXX 50"},
            {"India", "Nifty 50\nSensex\nNifty Bank\nSensex\nNifty IT\nS&P BSE Small Cap"},
            {"Currencies", "USD / INR\nEUR / INR\nINR / JPY\nGBP / INR\nAUD / INR"},
            {"Crypto", "Bitcoin\nEther\nCardano\nXRP\nDogecoin"},
            {"Futures", "Dow Futures\nS&P Futures\nNasdaq Futures\nGold\nCrude Oil"}
        };
};