#include "../header_files/folder_configure.h"

Folder::Folder(){}
Folder::~Folder(){}

std::map<std::string, std::map<std::string, std::string>> Folder::__class_info__(){
    std::map<std::string, std::string> __name_discription__ = { // Name and description of the class
        {"Folder", "Class for folder manipulation"}
    };

    std::map<std::string, std::string> __constuctor_paramters__ = { // Constructor paramter names and descriptions
        {"Not used", "Not used"}
    };

    std::map<std::string, std::string> __function_info__ = { // Function names and descriptions
        {"_create_folder", "Function to create a folder"},
        {"_list_folder", "Function to list a folder contents"},
        {"_delete_folder", "Function to delete a folder"},
        {"_rename_folder", "Function to rename a folder"},
        {"_move_folder", "Function to move a folder"},
        {"_copy_folder", "Function to copy a folder"},
        {"_check_folder", "Function to check if it is a folder"},
        {"_hide_folder", "Function to hide a folder"},
        {"_unhide_folder", "Function to unhide a folder"}
    };

    std::map<std::string, std::string> __function_parameters__ = { // Function names and parameters
        {"_create_folder", "folder_name (str) <Required>\nfolder_path (str)"}, 
        {"_list_folder", "folder_name (str) <Required>\nlist_filename (str)\nlist_file_path (str)\nfolder_path (str)"},
        {"_delete_folder", "folder_name (str) <Required>\nfolder_path (str)"}, 
        {"_rename_folder", "folder_name (str) <Required>\nnew_folder_name (str) <Required>\nfolder_path (str)"}, 
        {"_move_folder", "folder_name (str) <Required>\nnew_path (str) <Required>\nfolder_path (str)"}, 
        {"_copy_folder", "folder_name (str) <Required>\nnew_path (str) <Required>\nfolder_path (str)"}, 
        {"_check_folder", "folder_name (str) <Required>\nfolder_path (str)"}, 
        {"_hide_folder", "folder_name (str) <Required>\nfolder_path (str)"}, 
        {"_unhide_folder", "folder_name (str) <Required>\nfolder_path (str)"}
    };

    std::map<std::string, std::string> __function_parameters_description__ = { // Function names, parameters and descriptions
        {"_create_folder", "folder_name: Name of the folder\nfolder_path: Path of the folder"},
        {"_list_folder", "folder_name: Name of the folder\nlist_filename: Name of the list file to store folder content list\nlist_file_path: Path of the list file\nfolder_path: Path of the folder"},
        {"_delete_folder", "folder_name: Name of the folder\nfolder_path: Path of the folder"},
        {"_rename_folder", "folder_name: Name of the folder\nnew_folder_name: New name of the folder\nfolder_path: Path of the folder"},
        {"_move_folder", "folder_name: Name of the folder\nnew_path: New path of the folder\nfolder_path: Path of the folder"},
        {"_copy_folder", "folder_name: Name of the folder\nnew_path: New path of the folder\nfolder_path: Path of the folder"},
        {"_check_folder", "folder_name: Name of the folder\nfolder_path: Path of the folder"},
        {"_hide_folder", "folder_name: Name of the folder\nfolder_path: Path of the folder"},
        {"_unhide_folder", "folder_name: Name of the folder\nfolder_path: Path of the folder"},
    };

    std::map<std::string, std::string> __function_return_types__ = { // Function names and return types
        {"_create_folder", "None"}, 
        {"_list_folder", "None"}, 
        {"_delete_folder", "None"}, 
        {"_rename_folder", "None"}, 
        {"_move_folder", "None"}, 
        {"_copy_folder", "None"}, 
        {"_check_folder", "None"}, 
        {"_hide_folder", "None"}, 
        {"_unhide_folder", "None"}
    };

    return { // Vector of maps containing the class information
        {"Name_Description", __name_discription__},
        {"Constructor_Parameters", __constuctor_paramters__},
        {"Function_Info", __function_info__},
        {"Function_Parameters", __function_parameters__},
        {"Parameter_Description", __function_parameters_description__},
        {"Function_Return", __function_return_types__}
    };
}

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
    const std::string list_filename = "folder_list_file.txt", // Name of the list folder
    const std::string list_file_path = "log_files/", // Path of the list folder
    const std::string folder_path = "" // Path of the folder
) {
    std::string fullpath = folder_name + list_filename; // Location and Name of the folder to list
    std::string list_fullpath = list_file_path + fullpath; // Location and Name of the folder to store folder list
    
    std::ofstream list_file; // folder object to store folder list
    
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