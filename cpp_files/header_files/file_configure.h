#ifndef FILE_CONFIGURE_H
#define FILE_CONFIGURE_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include <map>
#include <vector>

/// @brief Class for file manipulation
class File {
    public:
        std::string _log_filename = "log_files/function_execution_logs.txt"; // Name of the log file

        /// @brief Class Constructor
        File();

        /// @brief Class Destructor
        ~File();

        /// @brief Function to write to logs to log file
        /// @param content Content to write to log file
        void __log__(
            const std::string content // Content to write to log file
        );

        /// @brief Function to get the class information
        /// @return Vector of maps containing the class information
        std::map<std::string, std::map<std::string, std::string>> __class_info__();

        /// @brief Function to create a file
        /// @param filename Name of the file
        /// @param file_path Path of the file
        void _create_file(
            const std::string filename, // Name of the file
            const std::string file_path // Path of the file
        );

        /// @brief Function to write to a file
        /// @param filename Name of the file
        /// @param content Content of the file
        /// @param file_path Path of the file
        void _write_file(
            const std::string filename, // Name of the file
            const std::string content, // Content of the file
            const std::string file_path // Path of the file
        );

        /// @brief Function to read a file
        /// @param filename Name of the file
        /// @param file_path Path of the file
        /// @return Content of the file
        std::string _read_file(
            const std::string filename, // Name of the file
            const std::string file_path // Path of the file
        );

        /// @brief Function to delete a file
        /// @param filename Name of the file
        /// @param file_path Path of the file
        void _delete_file(
            const std::string filename, // Name of the file
            const std::string file_path // Path of the file
        );

        /// @brief Function to rename a file
        /// @param filename Name of the file
        /// @param new_filename New name of the file
        /// @param file_path Path of the file
        void _rename_file(
            const std::string filename, // Name of the file
            const std::string new_filename, // New name of the file
            const std::string file_path // Path of the file
        );

        /// @brief Function to move a file
        /// @param filename Name of the file
        /// @param new_path New path of the file
        /// @param file_path Path of the file 
        void _move_file(
            const std::string filename, // Name of the file
            const std::string new_path, // New path of the file
            const std::string file_path // Path of the file
        );

        /// @brief Function to copy a file
        /// @param filename Name of the file
        /// @param new_path New path of the file
        /// @param file_path Path of the file
        void _copy_file(
            const std::string filename, // Name of the file
            const std::string new_path, // New path of the file
            const std::string file_path // Path of the file
        );

        /// @brief Function to check if it is a file
        /// @param filename Name of the file
        /// @param file_path Path of the file
        /// @return True if it is a file, false otherwise
        bool _check_file(
            const std::string filename, // Name of the file
            const std::string file_path // Path of the file
        );

        /// @brief Function to hide a file
        /// @param filename Name of the file
        /// @param file_path Path of the file
        void _hide_file(
            const std::string filename, // Name of the file
            const std::string file_path // Path of the file
        );
        
        /// @brief Function to unhide a file
        /// @param filename Name of the file
        /// @param file_path Path of the file
        void _unhide_file(
            const std::string filename, // Name of the file
            const std::string file_path // Path of the file
        );
};

#endif