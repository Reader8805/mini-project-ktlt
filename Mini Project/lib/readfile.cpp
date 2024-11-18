#include "readfile.hpp"

// function to create file and check if it was successfully created.
void create_file(std::string fileName) {
    std::ofstream file;
    file.open(fileName);
    // check if the file was successfully created.
    if(!file.is_open()) {
        std::cout << "Cannot open the file!";
    } else {
        std::cout << "File opened successfully!";
    }
    file.close();
}

void read_file(std::string fileName) {
    std::string fileContent;
    std::ifstream readFile;
    readFile.open(fileName);

    while(getline(fileName, fileContent)) {

    }
}