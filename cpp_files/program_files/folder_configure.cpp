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

    std::map<std::string, std::string> __class_examples__ = { // Class usage examples 
        {"Create a folder \"CSV_files\" then move it to \"Passwords/\" and then hide it", "To create a folder \"CSV_files\" then move it to \"Passwords/\" and then hide it use function ```function_name _create_folder``` with parameters ```parameters { folder_name = \"CSV_files\" }``` then use function ```function_name _move_folder``` with parameters ```parameters { folder_name = \"CSV_files\" }, { new_path = \"Passwords/\" }``` then use function ```function_name _hide_folder``` with parameters ```parameters { folder_name = \"CSV_files\" }, { folder_path = \"Passwords/\" }"},
        {"Unhide a folder \"Passwords\" in \"Hidden_Folders/\" then list it in file \"List_file.txt\"", "To unhide a folder \"Passwords\" in \"Hidden_Folders\" then list it in file \"List_file.txt\" use function ```function_name _unhide_folder``` with parameters ```parameters { folder_name = \"Passwords\" }, { folder_path = \"Hidden_Folders/\" }``` then use function ```function_name _list_folder``` with parameters ```parameters { folder_name = \"Passwords\" }, { list_filename = \"List_file.txt\" }, { folder_path = \"Hidden_Folders/\" }```"},
        {"Copy a folder \"No_Need_files\" in directory \"Trash_Folders/\" to \"Necessary_folders/\" then delete the earlier folder", "To copy a folder \"No_Need_files\" in directory \"Trash_Folders/\" to \"Necessary_folders/\" then delete the earlier folder use function ```function_name _copy_folder``` with parameters ```parameters { folder_name = \"No_Need_files\" }, { new_path = \"Necessary_folders/\" }, { folder_path = \"Trash_Folders/\" }``` then use function ```function_name _delete_folder``` with parameters ```parameters { folder_name = \"No_Need_files\" }, { folder_path = \"Trash_Folders/\" }```"},
        {"Set model to \"gemini-1.5-pro\" and set system instruction to \"You are a great philosopher\" and then query it \"Meaning of life\" and then clear the conversation history", "```Sorry, this query cannot be handled by me```"},
        {"Search for \"Latest songs\" but restrict the results to past 2 years and give me 10 results", "```Sorry, this query cannot be handled by me```"}
    };

    return { // Vector of maps containing the class information
        {"Name_Description", __name_discription__},
        {"Constructor_Parameters", __constuctor_paramters__},
        {"Function_Info", __function_info__},
        {"Function_Parameters", __function_parameters__},
        {"Parameter_Description", __function_parameters_description__},
        {"Function_Return", __function_return_types__},
        {"Class_Examples", __class_examples__}
    };
}

void Folder::__log__(
    const std::string content // Content to write to log file
){
    std::ifstream previous_log_file; // File object to read from the previous log file
    previous_log_file.open(this->_log_filename);

    std::string previous_content((std::istreambuf_iterator<char>(previous_log_file)), std::istreambuf_iterator<char>()); // Content from the previous log file
    previous_log_file.close();

    std::ofstream new_log_file; // File object to write the new log file
    new_log_file.open(this->_log_filename);

    previous_content += content + "\n";
    new_log_file << previous_content;

    new_log_file.close();
}

void Folder::_create_folder(
    const std::string folder_name, // Name of the folder
    const std::string folder_path = "" // Path of the folder
) {
    std::string fullpath = folder_path + folder_name; // Location and Name of the folder to create
    bool folder_exists = this->_check_folder(folder_name, folder_path);
    
    if (!folder_exists)
        std::filesystem::create_directory(fullpath.c_str());


    // Log function
    std::string log_content = "Folder " + folder_name;
    if (folder_path != "")
        log_content += " at " + folder_path;
    if (folder_exists)
        log_content += " Already exists";
    else
        log_content += " Created Successfully";

    this->__log__(log_content);
}

void Folder::_delete_folder(
    const std::string folder_name, // Name of the folder
    const std::string folder_path = "" // Path of the folder
) {
    std::string fullpath = folder_path + folder_name; // Location and Name of the folder to delete

    bool folder_exists = this->_check_folder(folder_name, folder_path);
    if (folder_exists)
        std::filesystem::remove_all(fullpath.c_str());


    // Log function
    std::string log_content = "Folder " + folder_name;
    if (folder_path != "")
        log_content += " at " + folder_path;
    if (folder_exists)
        log_content += " Deleted Successfully";
    else
        log_content += " Doesn not Exist so cannot be Deleted";

    this->__log__(log_content);
}

void Folder::_rename_folder(
    const std::string folder_name, // Name of the folder
    const std::string new_folder_name, // New name of the folder
    const std::string folder_path = "" // Path of the folder
) {
    std::string fullpath = folder_path + folder_name; // Location and Name of the folder to rename
    std::string new_fullpath = folder_path + new_folder_name; // New location and Name of the folder

    bool folder_exists = this->_check_folder(folder_name, folder_path);
    if (folder_exists)
        std::filesystem::rename(fullpath.c_str(), new_fullpath.c_str());


    // Log function
    std::string log_content = "Folder " + folder_name;
    if (folder_path != "")
        log_content += " at " + folder_path;
    if (folder_exists)
        log_content += " Renamed to " + new_folder_name + " Successfully";
    else
        log_content += " Doesn not Exist so cannot be Renamed";

    this->__log__(log_content);
}

void Folder::_move_folder(
    const std::string folder_name, // Name of the folder
    const std::string new_path, // New path of the folder
    const std::string folder_path = "" // Path of the folder
) {
    const std::string fullpath = folder_path + folder_name; // Location and Name of the folder to move
    const std::string new_fullpath = new_path + folder_name; // New location and Name of the folder
    
    bool folder_exists = this->_check_folder(folder_name, folder_path);
    if (folder_exists)
        std::filesystem::rename(fullpath.c_str(), new_fullpath.c_str());


    // Log function
    std::string log_content = "Folder " + folder_name;
    if (folder_path != "")
        log_content += " at " + folder_path;
    if (folder_exists)
        log_content += " Moved to " + new_path + " Successfully";
    else
        log_content += " Doesn not Exist so cannot be Moved";

    this->__log__(log_content);
}

void Folder::_copy_folder(
    const std::string folder_name, // Name of the folder
    const std::string new_path, // New path of the folder
    const std::string folder_path = "" // Path of the folder
) {
    const std::string fullpath = folder_path + folder_name; // Location and Name of the folder to copy
    const std::string new_fullpath = new_path + folder_name; // New location and Name of the folder
    
    bool folder_exists = this->_check_folder(folder_name, folder_path);
    if (folder_exists)
        std::filesystem::copy(fullpath.c_str(), new_fullpath.c_str());


    // Log function
    std::string log_content = "Folder " + folder_name;
    if (folder_path != "")
        log_content += " at " + folder_path;
    if (folder_exists)
        log_content += " Copied to " + new_path + " Successfully";
    else
        log_content += " Doesn not Exist so cannot be Copied";

    this->__log__(log_content);
}

void Folder::_list_folder(
    const std::string folder_name, // Name of the folder
    const std::string list_filename = "folder_list_file.txt", // Name of the list folder
    const std::string list_file_path = "log_files/", // Path of the list folder
    const std::string folder_path = "" // Path of the folder
) {
    std::string fullpath = folder_path + folder_name; // Location and Name of the folder to list
    std::string list_fullpath = list_file_path + list_filename; // Location and Name of the folder to store folder list
    
    bool folder_exists = this->_check_folder(folder_name, folder_path);
    if (folder_exists){
        std::ofstream list_file; // folder object to store folder list

        list_file.open(list_fullpath.c_str());
        for (const auto& entry : std::filesystem::directory_iterator(fullpath)) {
            list_file << entry.path() << std::endl;
        }

        list_file.close();
    }

    // Log function
    std::string log_content = "Folder " + folder_name;
    if (folder_path != "")
        log_content += " at " + folder_path;
    if (folder_exists)
        log_content += " contents listed in " + list_file_path + list_filename + " Successfully";
    else
        log_content += " Doesn not Exist so cannot be Listed";

    this->__log__(log_content);
}

bool Folder::_check_folder(
    const std::string folder_name, // Name of the folder
    const std::string folder_path = "" // Path of the folder
) {
    std::string fullpath = folder_path + folder_name; // Location and Name of the folder to check
    bool folder_exists = false;

    if (std::filesystem::exists(fullpath) && std::filesystem::is_directory(fullpath))
        folder_exists = true;

    
    // Log function
    std::string log_content = "Folder " + folder_name;
    if (folder_path != "")
        log_content += " at " + folder_path;
    if (folder_exists)
        log_content += " Checked and it exists";
    else
        log_content += " Checked and it does not exists";

    this->__log__(log_content);

    return folder_exists;
}

void Folder::_hide_folder(
    const std::string folder_name, // Name of the folder
    const std::string folder_path = "" // Path of the folder
) {
    const std::string fullpath = folder_path + folder_name; // Location and Name of the folder to hide
    const std::string new_fullpath = folder_path + "." + folder_name; // New location and Name of the hidden folder
    
    bool folder_exists = this->_check_folder(folder_name, folder_path);
    if (folder_exists)
        std::filesystem::rename(fullpath.c_str(), new_fullpath.c_str());


    // Log function
    std::string log_content = "Folder " + folder_name;
    if (folder_path != "")
        log_content += " at " + folder_path;
    if (folder_exists)
        log_content += " Hidden Successfully";
    else
        log_content += " Doesn not Exist so cannot be Hidden";

    this->__log__(log_content);
}

void Folder::_unhide_folder(
    const std::string folder_name, // Name of the folder
    const std::string folder_path = "" // Path of the folder
) {
    const std::string fullpath = folder_path + folder_name; // Location and Name of the folder to unhide
    
    bool folder_exists = this->_check_folder(folder_name, folder_path);
    if (folder_exists){
        std::string new_folder_name = "";
        for (long unsigned int i = 1; i <= folder_name.length(); i++){
            new_folder_name += folder_name[i];
        }

        const std::string new_fullpath = folder_path + new_folder_name; // New location and Name of the unhidden folder
        std::filesystem::rename(fullpath.c_str(), new_fullpath.c_str());
    }

    // Log function
    std::string log_content = "Folder " + folder_name;
    if (folder_path != "")
        log_content += " at " + folder_path;
    if (folder_exists)
        log_content += " UnHidden Successfully";
    else
        log_content += " Doesn not Exist so cannot be UnHidden";

    this->__log__(log_content);
}