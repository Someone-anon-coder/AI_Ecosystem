#ifndef FOLDER_CONFIGURE_H
#define FOLDER_CONFIGURE_H

#include <string>
#include <filesystem>
#include <fstream>

class Folder {
    public:
        Folder();
        ~Folder();

        void create_folder(
            const std::string folder_name, // Name of the folder
            const std::string folder_path // Path of the folder
        );

        void delete_folder(
            const std::string folder_name, // Name of the folder
            const std::string folder_path // Path of the folder
        );

        void list_folder(
            const std::string folder_name, // Name of the folder
            const std::string folder_path, // Path of the folder
            const std::string list_filename, // Name of the list file 
            const std::string list_file_path // Path of the list file
        );

        void rename_folder(
            const std::string folder_name, // Name of the folder
            const std::string folder_path, // Path of the folder
            const std::string new_folder_name // New name of the folder
        );

        void move_folder(
            const std::string folder_name, // Name of the folder
            const std::string folder_path, // Path of the folder
            const std::string new_path // New path of the folder
        );

        void copy_folder(
            const std::string folder_name, // Name of the folder
            const std::string folder_path, // Path of the folder
            const std::string new_path // New path of the folder
        );

        bool check_folder(
            const std::string folder_name, // Name of the folder
            const std::string folder_path // Path of the folder
        );

        void hide_folder(
            const std::string folder_name, // Name of the folder
            const std::string folder_path // Path of the folder
        );

        void unhide_folder(
            const std::string folder_name, // Name of the folder
            const std::string folder_path // Path of the folder
        );
};

#endif