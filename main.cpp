#include <iostream>

#include "archiver.h"
#include "argument_parser.h"
#include "dearchiver.h"

int main(int argc, char** argv) {
    try {
        ArgumentParser argument_parser(argc, argv);
        if (argument_parser.IsArchive()) {
            const std::string last_file = argument_parser.files_.back();
            for (const auto &file : argument_parser.files_) {
                Archiver(file, argument_parser.archive_name_, last_file == file);
            }
        } else if (argument_parser.IsDearchive()) {
            Dearchiver(argument_parser.GetKey(2));
        } else if (argument_parser.IsHelp()) {
            std::cout << "Help info: \n";
            std::cout << "* Archiving. Use command: \"Archiver -c archive_name file1 [file2 ...]\" to archive "
                         "file1, file2, ...  and save result in file \"archive_name\". \n";
            std::cout << "* Dearchiving. Use command: \"Archiver -d archive_name\" to dearchive file "
                         "\"archive_name\" and put files in current directory. \n";
        } else {
            throw std::invalid_argument("no such command. Maybe you should press -h for help info?");
        }
    } catch (const std::invalid_argument& e) {
        std::cout << "Error: invalid argument - " << e.what() << '\n';
    } catch (const std::ios::failure& e) {
        std::cout << "Error while reading the file - " << e.what() << '\n';
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << '\n';
    } catch (...) {
        std::cout << "Error\n";
    }
}
