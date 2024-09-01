#ifndef FILE_CONFIGURE_H
#define FILE_CONFIGURE_H

#include <iostream>
#include <fstream>

class File {
    public:
        File();
        ~File();

        void create_file(
            const std::string filename, // Name of the file
            const std::string file_path="" // Path of the file
        );

        void write_file(
            const std::string filename, // Name of the file
            const std::string content, // Content of the file
            const std::string file_path="" // Path of the file
        );

        std::string read_file(
            const std::string filename, // Name of the file
            const std::string file_path="" // Path of the file
        );

        void delete_file(
            const std::string filename, // Name of the file
            const std::string file_path="" // Path of the file
        );

        void rename_file(
            const std::string filename, // Name of the file
            const std::string new_filename, // New name of the file
            const std::string file_path="" // Path of the file
        );

        void move_file(
            const std::string filename, // Name of the file
            const std::string new_path, // New path of the file
            const std::string file_path="" // Path of the file
        );

        void copy_file(
            const std::string filename, // Name of the file
            const std::string new_path, // New path of the file
            const std::string file_path="" // Path of the file
        );

        bool check_file(
            const std::string filename, // Name of the file
            const std::string file_path="" // Path of the file
        );

        void hide_file(
            const std::string filename, // Name of the file
            const std::string file_path="" // Path of the file
        );
        
        void unhide_file(
            const std::string filename, // Name of the file
            const std::string file_path="" // Path of the file
        );
};

#endif