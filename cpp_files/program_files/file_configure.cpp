#include "../header_files/file_configure.h"

File::File(){}
File::~File(){}

void File::create_file(
    const std::string filename, // Name of the file
    const std::string file_path="" // Path of the file
) { // Creates a file in the designated location
    const std::string fullpath = file_path + filename;
    std::ofstream file_create;

    file_create.open(fullpath.c_str());
    file_create.close();
}

void File::write_file(
    const std::string filename, // Name of the file
    const std::string content, // Content of the file
    const std::string file_path="" // Path of the file
) { // Writes content to a file in the designated location
    const std::string fullpath = file_path + filename;
    std::ofstream file_write;
    
    file_write.open(fullpath.c_str());
    file_write << content;
    file_write.close();
}

std::string File::read_file(
    const std::string filename, // Name of the file
    const std::string file_path="" // Path of the file
) { // Reads content from a file and returns it
    const std::string fullpath = file_path + filename;
    std::ifstream file_read;
    
    file_read.open(fullpath.c_str());
    std::string content((std::istreambuf_iterator<char>(file_read)), std::istreambuf_iterator<char>());
    
    file_read.close();
    return content;
}

void File::delete_file(
    const std::string filename, // Name of the file
    const std::string file_path="" // Path of the file
) { // Deletes a file
    std::string fullpath = file_path + filename;
    std::remove(fullpath.c_str());
}

void File::rename_file(
    const std::string filename, // Name of the file
    const std::string new_filename, // New name of the file
    const std::string file_path="" // Path of the file
) { // Renames a file
    std::string fullpath = file_path + filename;
    std::string new_fullpath = file_path + new_filename;
    std::rename(fullpath.c_str(), new_fullpath.c_str());
}

void File::move_file(
    const std::string filename, // Name of the file
    const std::string new_path, // New path of the file
    const std::string file_path="" // Path of the file
) { // Moves a file to a new location
    std::string fullpath = file_path + filename;
    std::string new_fullpath = new_path + filename;
    std::rename(fullpath.c_str(), new_fullpath.c_str());
}

void File::copy_file(
    const std::string filename, // Name of the file
    const std::string new_path, // New path of the file
    const std::string file_path="" // Path of the file
) { // Copies a file to a new location
    std::string fullpath = file_path + filename;
    std::string new_fullpath = new_path + filename;

    std::ifstream read_file;
    std::ofstream write_file;
    
    read_file.open(fullpath.c_str());
    write_file.open(new_fullpath.c_str());
    write_file << read_file.rdbuf();
    
    read_file.close();
    write_file.close();
}

bool File::check_file(
    const std::string filename, // Name of the file
    const std::string file_path="" // Path of the file
) { // Checks if a file exists
    std::string fullpath = file_path + filename;
    std::ifstream read_file;
    
    read_file.open(fullpath);
    if (read_file.is_open()) {
        read_file.close();
        return true;
    } else {
        read_file.close();
        return false;
    }
}

void File::hide_file(
    const std::string filename, // Name of the file
    const std::string file_path="" // Path of the file
){ // hides a file at the specified location
    const std::string fullpath = file_path + filename;
    const std::string new_fullpath = file_path + "." + filename;

    std::rename(fullpath.c_str(), new_fullpath.c_str());
}

void File::unhide_file(
    const std::string filename, // Name of the file
    const std::string file_path="" // Path of the file
){ // hides a file at the specified location
    const std::string fullpath = file_path + filename;
    const std::string new_fullpath = file_path + filename.substr(0);

    std::rename(fullpath.c_str(), new_fullpath.c_str());
}