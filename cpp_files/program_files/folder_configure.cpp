#include "../header_files/folder_configure.h"

Folder::Folder(){}
Folder::~Folder(){}

void Folder::_create_folder(
    const std::string folder_name, // Name of the folder
    const std::string folder_path = "" // Path of the folder
) {
    std::string fullpath = folder_path + folder_name; // Location and Name of the folder to create
    std::filesystem::create_directory(fullpath.c_str());
}

void Folder::_delete_folder(
    const std::string folder_name, // Name of the folder
    const std::string folder_path = "" // Path of the folder
) {
    std::string fullpath = folder_path + folder_name; // Location and Name of the folder to delete
    std::filesystem::remove_all(fullpath.c_str());
}

void Folder::_rename_folder(
    const std::string folder_name, // Name of the folder
    const std::string new_folder_name, // New name of the folder
    const std::string folder_path = "" // Path of the folder
) {
    std::string fullpath = folder_path + folder_name; // Location and Name of the folder to rename
    std::string new_fullpath = folder_path + new_folder_name; // New location and Name of the folder
   
    std::filesystem::rename(fullpath.c_str(), new_fullpath.c_str());
}

void Folder::_move_folder(
    const std::string folder_name, // Name of the folder
    const std::string new_path, // New path of the folder
    const std::string folder_path = "" // Path of the folder
) {
    const std::string fullpath = folder_path + folder_name; // Location and Name of the folder to move
    const std::string new_fullpath = new_path + folder_name; // New location and Name of the folder
    
    std::filesystem::rename(fullpath.c_str(), new_fullpath.c_str());
}

void Folder::_copy_folder(
    const std::string folder_name, // Name of the folder
    const std::string new_path, // New path of the folder
    const std::string folder_path = "" // Path of the folder
) {
    const std::string fullpath = folder_path + folder_name; // Location and Name of the folder to copy
    const std::string new_fullpath = new_path + folder_name; // New location and Name of the folder
    
    std::filesystem::copy(fullpath.c_str(), new_fullpath.c_str());
}

void Folder::_list_folder(
    const std::string folder_name, // Name of the folder
    const std::string list_filename = "folder_list_file.txt", // Name of the list file
    const std::string list_file_path = "log_files/", // Path of the list file
    const std::string folder_path = "" // Path of the folder
) {
    std::string fullpath = folder_name + list_filename; // Location and Name of the folder to list
    std::string list_fullpath = list_file_path + fullpath; // Location and Name of the file to store folder list
    
    std::ofstream list_file; // File object to store folder list
    
    list_file.open(list_fullpath.c_str());
    for (const auto& entry : std::filesystem::directory_iterator(fullpath)) {
        list_file << entry.path() << std::endl;
    }

    list_file.close();
}

bool Folder::_check_folder(
    const std::string folder_name, // Name of the folder
    const std::string folder_path = "" // Path of the folder
) {
    std::string fullpath = folder_path + folder_name; // Location and Name of the folder to check
    return std::filesystem::exists(fullpath) && std::filesystem::is_directory(fullpath) ? true : false;
}

void Folder::_hide_folder(
    const std::string folder_name, // Name of the folder
    const std::string folder_path = "" // Path of the folder
) {
    const std::string fullpath = folder_path + folder_name; // Location and Name of the folder to hide
    const std::string new_fullpath = folder_path + "." + folder_name; // New location and Name of the hidden folder
    
    std::filesystem::rename(fullpath.c_str(), new_fullpath.c_str());
}

void Folder::_unhide_folder(
    const std::string folder_name, // Name of the folder
    const std::string folder_path = "" // Path of the folder
) {
    const std::string fullpath = folder_path + folder_name; // Location and Name of the folder to unhide
    const std::string new_fullpath = folder_path + folder_name.substr(0); // New location and Name of the unhidden folder
    
    std::filesystem::rename(fullpath.c_str(), new_fullpath.c_str());
}