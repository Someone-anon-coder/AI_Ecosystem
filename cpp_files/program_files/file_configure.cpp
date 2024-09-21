#include "../header_files/file_configure.h"

File::File(){}
File::~File(){}

std::map<std::string, std::map<std::string, std::string>> File::__class_info__(){
    std::map<std::string, std::string> __name_discription__ = { // Name and description of the class
        {"File", "Class for file manipulation"}
    };

    std::map<std::string, std::string> __constuctor_paramters__ = { // Constructor paramter names and descriptions
        {"Not used", "Not used"}
    };

    std::map<std::string, std::string> __function_info__ = { // Function names and descriptions
        {"_create_file", "Function to create a file"},
        {"_write_file", "Function to write to a file"},
        {"_read_file", "Function to read a file"},
        {"_delete_file", "Function to delete a file"},
        {"_rename_file", "Function to rename a file"},
        {"_move_file", "Function to move a file"},
        {"_copy_file", "Function to copy a file"},
        {"_check_file", "Function to check if it is a file"},
        {"_hide_file", "Function to hide a file"},
        {"_unhide_file", "Function to unhide a file"}
    };

    std::map<std::string, std::string> __function_parameters__ = { // Function names and parameters
        {"_create_file", "filename (str) <Required>\nfile_path (str)"}, 
        {"_write_file", "filename (str) <Required>\ncontent (str)\nfile_path (str)"}, 
        {"_read_file", "filename (str) <Required>\nfile_path (str)"}, 
        {"_delete_file", "filename (str) <Required>\nfile_path (str)"}, 
        {"_rename_file", "filename (str) <Required>\nnew_filename (str) <Required>\nfile_path (str)"}, 
        {"_move_file", "filename (str) <Required>\nnew_path (str) <Required>\nfile_path (str)"}, 
        {"_copy_file", "filename (str) <Required>\nnew_path (str) <Required>\nfile_path (str)"}, 
        {"_check_file", "filename (str) <Required>\nfile_path (str)"}, 
        {"_hide_file", "filename (str) <Required>\nfile_path (str)"}, 
        {"_unhide_file", "filename (str) <Required>\nfile_path (str)"}
    };

    std::map<std::string, std::string> __function_parameters_description__ = { // Function names, parameters and descriptions
        {"_create_file", "filename: Name of the file\nfile_path: Path of the file"},
        {"_write_file", "filename: Name of the file\ncontent: Content of the file\nfile_path: Path of the file"},
        {"_read_file", "filename: Name of the file\nfile_path: Path of the file"},
        {"_delete_file", "filename: Name of the file\nfile_path: Path of the file"},
        {"_rename_file", "filename: Name of the file\nnew_filename: New name of the file\nfile_path: Path of the file"},
        {"_move_file", "filename: Name of the file\nnew_path: New path of the file\nfile_path: Path of the file"},
        {"_copy_file", "filename: Name of the file\nnew_path: New path of the file\nfile_path: Path of the file"},
        {"_check_file", "filename: Name of the file\nfile_path: Path of the file"},
        {"_hide_file", "filename: Name of the file\nfile_path: Path of the file"},
        {"_unhide_file", "filename: Name of the file\nfile_path: Path of the file"},
    };

    std::map<std::string, std::string> __function_return_types__ = { // Function names and return types
        {"_create_file", "None"}, 
        {"_write_file", "None"}, 
        {"_read_file", "Content of the file"}, 
        {"_delete_file", "None"}, 
        {"_rename_file", "None"}, 
        {"_move_file", "None"}, 
        {"_copy_file", "None"}, 
        {"_check_file", "None"}, 
        {"_hide_file", "None"}, 
        {"_unhide_file", "None"}
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

void File::_create_file(
    const std::string filename, // Name of the file
    const std::string file_path = "" // Path of the file
) {
    const std::string fullpath = file_path + filename; // Location and Name of the file to be created
    std::ofstream file_create; // File object to create the file

    file_create.open(fullpath.c_str());
    file_create.close();
}

void File::_write_file(
    const std::string filename, // Name of the file
    const std::string content, // Content of the file
    const std::string file_path = "" // Path of the file
) {
    const std::string fullpath = file_path + filename; // Location and Name of the file to write in
    std::ofstream file_write; // File object to write in the file
    
    file_write.open(fullpath.c_str());
    file_write << content;
    
    file_write.close();
}

std::string File::_read_file(
    const std::string filename, // Name of the file
    const std::string file_path = "" // Path of the file
) {
    const std::string fullpath = file_path + filename; // Location and Name of the file to read from
    std::ifstream file_read; // File object to read from the file
    
    file_read.open(fullpath.c_str());
    std::string content((std::istreambuf_iterator<char>(file_read)), std::istreambuf_iterator<char>()); // Content from the file
    
    file_read.close();
    return content;
}

void File::_delete_file(
    const std::string filename, // Name of the file
    const std::string file_path = "" // Path of the file
) {
    std::string fullpath = file_path + filename; // Location and Name of the file to delete
    std::remove(fullpath.c_str());
}

void File::_rename_file(
    const std::string filename, // Name of the file
    const std::string new_filename, // New name of the file
    const std::string file_path = "" // Path of the file
) {
    std::string fullpath = file_path + filename; // Location and Name of the file to rename
    std::string new_fullpath = file_path + new_filename; // New location and Name of the file

    std::rename(fullpath.c_str(), new_fullpath.c_str());
}

void File::_move_file(
    const std::string filename, // Name of the file
    const std::string new_path, // New path of the file
    const std::string file_path = "" // Path of the file
) {
    std::string fullpath = file_path + filename; // Location and Name of the file
    std::string new_fullpath = new_path + filename; // New location and Name of the file

    std::rename(fullpath.c_str(), new_fullpath.c_str());
}

void File::_copy_file(
    const std::string filename, // Name of the file
    const std::string new_path, // New path of the file
    const std::string file_path = "" // Path of the file
) {
    std::string fullpath = file_path + filename; // Location and Name of the file
    std::string new_fullpath = new_path + filename; // New location and Name of the file

    std::ifstream read_file; // File object to read from a file
    std::ofstream write_file; // File object to write in a file
    
    read_file.open(fullpath.c_str());
    write_file.open(new_fullpath.c_str());
    
    write_file << read_file.rdbuf();
    
    read_file.close();
    write_file.close();
}

bool File::_check_file(
    const std::string filename, // Name of the file
    const std::string file_path = "" // Path of the file
) {
    std::string fullpath = file_path + filename; // Location and Name of the file to check
    std::ifstream read_file; // File object to read from a file
    
    read_file.open(fullpath);
    if (read_file.is_open()) {
        read_file.close();
        
        return true;
    } else {
        read_file.close();
        
        return false;
    }
}

void File::_hide_file(
    const std::string filename, // Name of the file
    const std::string file_path = "" // Path of the file
){
    const std::string fullpath = file_path + filename; // Location and Name of the file to hide
    const std::string new_fullpath = file_path + "." + filename; // New location and Name of the  hidden file

    std::rename(fullpath.c_str(), new_fullpath.c_str());
}

void File::_unhide_file(
    const std::string filename, // Name of the file
    const std::string file_path = "" // Path of the file
){
    const std::string fullpath = file_path + filename; // Location and Name of the file to unhide

    std::string new_filename = "";
    for (long unsigned int i = 1; i <= filename.length(); i++){
        new_filename += filename[i];
    }
    
    const std::string new_fullpath = file_path + new_filename;
    std::rename(fullpath.c_str(), new_fullpath.c_str());
}