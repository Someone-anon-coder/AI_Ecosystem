#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <sstream>

/// @brief Function to trim whitespace from a string
/// @param str The string to be trimmed
/// @return The trimmed string
std::string trim(
    const std::string& str // String to be trimmed
) {
    const std::string whitespace = " \t"; // Sub-String to trim from the main string
    
    const auto start = str.find_first_not_of(whitespace);
    if (start == std::string::npos) return "";  // No content
    const auto end = str.find_last_not_of(whitespace);
    
    return str.substr(start, end - start + 1);
}

/// @brief Function to load the .env file
/// @param filePath The path to the .env file
/// @return A map of key-value pairs
std::unordered_map<std::string, std::string> load_env_file(
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
            std::string key = trim(line.substr(0, delimiterPos));
            std::string value = trim(line.substr(delimiterPos + 1));

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
}

/// @brief Function to get a specific value for a key from the map
/// @param envMap The Unordered map to read
/// @param key The key to find
/// @return Value of the key in env file
std::string get_env_value(
    const std::unordered_map<std::string, std::string>& envMap, // The Unordered map to read
    const std::string& key // The key to find in the map
) {
    auto it = envMap.find(key);
    if (it != envMap.end()) {
        return it->second;  // Key found, return the value
    } else {
        return "";  // Key not found
    }
}