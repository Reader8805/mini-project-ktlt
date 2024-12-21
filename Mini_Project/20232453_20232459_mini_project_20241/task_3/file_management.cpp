#include "file_management.hpp"

// function to open file and check if it was successfully opened.
void create_output_file(std::ofstream &file, std::string fileName) {
    std::ofstream log("task3.log", std::ios::app);  //append mode to write in log file
    file.open(fileName);
    // check if the file was successfully opened(created).
    if(!file.is_open()) 
    {
        log << "Error 07: Cannot create the " << fileName << " file!";
        log.close();
        exit(EXIT_FAILURE);
    } 
    else 
    {
        std::cout << "File " << fileName << " created successfully!\n";
    }
}
void open_input_file(std::ifstream &file, std::string fileName) {
    std::ofstream log("task3.log", std::ios::app);  //append mode to write in log file
    file.open(fileName);
    // check if the file was successfully created.
    if(!file.is_open()) 
    {
        log << "Error 01: input file not found or not accessible\n";
        log.close();
        exit(EXIT_FAILURE);
    } 
    else 
    {
        std::cout << "File " << fileName << " opened successfully!\n";
    }
}

