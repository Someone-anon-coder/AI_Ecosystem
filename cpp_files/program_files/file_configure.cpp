#include "../header_files/file_configure.h"

File::File(){}
File::~File(){}

std::map<std::string, std::string> _class_info(){
    std::string __name__ = "File";
    std::string __discription__ = "Class for file manipulation";

    std::string __constuctor_paramters__[] = {};

    std::string __class_functions__[] = {
        "_create_file", "_write_file", "_read_file", "_delete_file", 
        "_rename_file", "_move_file", "_copy_file", "_check_file", 
        "_hide_file", "_unhide_file"
    };

    std::map<std::string, std::string> __function_info__ = {
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

    std::map<std::string, std::string> __function_parameters__ = {
        {"_create_file", "filename, file_path"}, 
        {"_write_file", "filename, content, file_path"}, 
        {"_read_file", "filename, file_path"}, 
        {"_delete_file", "filename, file_path"}, 
        {"_rename_file", "filename, new_filename, file_path"}, 
        {"_move_file", "filename, new_path, file_path"}, 
        {"_copy_file", "filename, new_path, file_path"}, 
        {"_check_file", "filename, file_path"}, 
        {"_hide_file", "filename, file_path"}, 
        {"_unhide_file", "filename, file_path"}
    };

    std::map<std::string, std::map<std::string, std::string>> __function_parameters_description__ = {
        {
            "_create_file", {
                {"filename", "Name of the file"},
                {"file_path", "Path of the file"}
            }
        },
        {
            "_write_file", {
                {"filename", "Name of the file"},
                {"content", "Content of the file"},
                {"file_path", "Path of the file"}
            }
        }
    };

    std::map<std::string, std::string> __function_return_types__ = {
        {"_create_file", "void"}, 
        {"_write_file", "void"}, 
        {"_read_file", "std::string"}, 
        {"_delete_file", "void"}, 
        {"_rename_file", "void"}, 
        {"_move_file", "void"}, 
        {"_copy_file", "void"}, 
        {"_check_file", "bool"}, 
        {"_hide_file", "void"}, 
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
    const std::string new_fullpath = file_path + filename.substr(0); // New location and Name of the unhidden file

    std::rename(fullpath.c_str(), new_fullpath.c_str());
}