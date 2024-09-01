#include "../header_files/folder_configure.h"

Folder::Folder(){}
Folder::~Folder(){}

void Folder::create_folder(
    const std::string folder_name, // Name of the folder
    const std::string folder_path // Path of the folder
) { // Creates a folder in the designated location
    std::string fullpath = folder_path + folder_name;
    std::filesystem::create_directory(fullpath.c_str());
}

void Folder::delete_folder(
    const std::string folder_name, // Name of the folder
    const std::string folder_path // Path of the folder
) { // Delete a folder from the designated location
    std::string fullpath = folder_path + folder_name;
    std::filesystem::remove_all(fullpath.c_str());
}

void Folder::rename_folder(
    const std::string folder_name, // Name of the folder
    const std::string folder_path, // Path of the folder
    const std::string new_folder_name // New name of the folder
) { // Renames a folder
    std::string fullpath = folder_path + folder_name;
    std::string new_fullpath = folder_path + new_folder_name;
    std::filesystem::rename(fullpath.c_str(), new_fullpath.c_str());
}

void Folder::move_folder(
    const std::string folder_name, // Name of the folder
    const std::string folder_path, // Path of the folder
    const std::string new_path // New path of the folder
) { // Moves a folder to a new location
    const std::string fullpath = folder_path + folder_name;
    const std::string new_fullpath = new_path + folder_name;
    std::filesystem::rename(fullpath.c_str(), new_fullpath.c_str());
}

void Folder::copy_folder(
    const std::string folder_name, // Name of the folder
    const std::string folder_path, // Path of the folder
    const std::string new_path // New path of the folder
) { // Copies a folder to a new location
    const std::string fullpath = folder_path + folder_name;
    const std::string new_fullpath = new_path + folder_name;
    std::filesystem::copy(fullpath.c_str(), new_fullpath.c_str());
}

void Folder::list_folder(
    const std::string folder_name, // Name of the folder
    const std::string folder_path, // Path of the folder
    const std::string list_filename="folder_list_file.txt", // Name of the list file
    const std::string list_file_path="log_files/" // Path of the list file
) { // lists a folder and saves the list in the list file
    std::string fullpath = folder_name + list_filename;
    std::string list_fullpath = list_file_path + fullpath;
    
    std::ofstream list_file;
    list_file.open(list_fullpath.c_str());

    for (const auto& entry : std::filesystem::directory_iterator(fullpath)) {
        list_file << entry.path() << std::endl;
    }
    list_file.close();
}

bool Folder::check_folder(
    const std::string folder_name, // Name of the folder
    const std::string folder_path // Path of the folder
) { // Checks if the folder exists at the designated location
    std::string fullpath = folder_path + folder_name;
    return std::filesystem::exists(fullpath) && std::filesystem::is_directory(fullpath) ? true : false;
}

void Folder::hide_folder(
    const std::string folder_name, // Name of the folder
    const std::string folder_path // Path of the folder
) { // hides the folder at the designated location
    const std::string fullpath = folder_path + folder_name;
    const std::string new_fullpath = folder_path + "." + folder_name;
    std::filesystem::rename(fullpath.c_str(), new_fullpath.c_str());
}

void Folder::unhide_folder(
    const std::string folder_name, // Name of the folder
    const std::string folder_path // Path of the folder
) { // Unhides the folder at the designated location
    const std::string fullpath = folder_path + folder_name;
    const std::string new_fullpath = folder_path + folder_name.substr(0);
    std::filesystem::rename(fullpath.c_str(), new_fullpath.c_str());
}