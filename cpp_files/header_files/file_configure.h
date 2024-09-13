#ifndef FILE_CONFIGURE_H
#define FILE_CONFIGURE_H

#include <iostream>
#include <fstream>

/// @brief Class for file manipulation
class File {
    public:
        /// @brief Class Constructor
        File();

        /// @brief Class Destructor
        ~File();

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