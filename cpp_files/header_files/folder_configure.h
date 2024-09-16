#ifndef FOLDER_CONFIGURE_H
#define FOLDER_CONFIGURE_H

#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <map>

/// @brief Class for folder manipulation
class Folder {
    public:
        /// @brief Class Constructor
        Folder();

        /// @brief Class Destructor
        ~Folder();

        /// @brief Function to get the class information
        /// @return Vector of maps containing the class information
        std::map<std::string, std::map<std::string, std::string>> __class_info__();

        /// @brief Function to create a folder
        /// @param folder_name Name of the folder
        /// @param folder_path Path of the folder
        void _create_folder(
            const std::string folder_name, // Name of the folder
            const std::string folder_path // Path of the folder
        );

        /// @brief Function to delete a folder
        /// @param folder_name Name of the folder
        /// @param folder_path Path of the folder
        void _delete_folder(
            const std::string folder_name, // Name of the folder
            const std::string folder_path // Path of the folder
        );

        /// @brief Function to list a folder contents
        /// @param folder_name Name of the folder
        /// @param list_filename Name of the list file to store folder content list
        /// @param list_file_path Path of the list file
        /// @param folder_path Path of the folder
        void _list_folder(
            const std::string folder_name, // Name of the folder
            const std::string list_filename, // Name of the list file 
            const std::string list_file_path, // Path of the list file
            const std::string folder_path // Path of the folder
        );

        /// @brief Function to rename a folder
        /// @param folder_name Name of the folder
        /// @param new_folder_name New Name of the folder
        /// @param folder_path Path of the folder
        void _rename_folder(
            const std::string folder_name, // Name of the folder
            const std::string new_folder_name, // New name of the folder
            const std::string folder_path // Path of the folder
        );

        /// @brief Function to move a folder
        /// @param folder_name Name of the folder
        /// @param new_path New path of the folder
        /// @param folder_path Path of the folder
        void _move_folder(
            const std::string folder_name, // Name of the folder
            const std::string new_path, // New path of the folder
            const std::string folder_path // Path of the folder
        );

        /// @brief Function to copy a folder
        /// @param folder_name Name of the folder
        /// @param new_path New path of the folder
        /// @param folder_path Path of the folder
        void _copy_folder(
            const std::string folder_name, // Name of the folder
            const std::string new_path, // New path of the folder
            const std::string folder_path // Path of the folder
        );

        /// @brief Function to check if folder exists
        /// @param folder_name Name of the folder
        /// @param folder_path Path of the folder
        /// @return True if folder exists, false otherwise
        bool _check_folder(
            const std::string folder_name, // Name of the folder
            const std::string folder_path // Path of the folder
        );

        /// @brief Function to hide a folder
        /// @param folder_name Name of the folder
        /// @param folder_path Path of the folder
        void _hide_folder(
            const std::string folder_name, // Name of the folder
            const std::string folder_path // Path of the folder
        );

        /// @brief Function to hide a folder
        /// @param folder_name Name of the folder
        /// @param folder_path Path of the folder
        void _unhide_folder(
            const std::string folder_name, // Name of the folder
            const std::string folder_path // Path of the folder
        );
};

#endif