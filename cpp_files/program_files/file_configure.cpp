#include "../header_files/file_configure.h"

File::File(){}
File::~File(){}

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