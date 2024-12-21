#include "file_management.hpp"

// function to open file and check if it was successfully opened.
void create_output_file(std::ofstream &file, std::string fileName) {
    std::ofstream log("task2.log", std::ios::app);  //append mode to write in log file
    file.open(fileName);
    // check if the file was successfully opened(created).
    if(!file.is_open()) 
    {
        log << "Error 07: Cannot create the " << fileName << " file";
        log.close();
        exit(EXIT_FAILURE);
    } 
    else 
    {
        std::cout << "File " << fileName << " created successfully!\n";
    }
}
void open_input_file(std::ifstream &file, std::string fileName) {
    std::ofstream log("task2.log", std::ios::app);  //append mode to write in log file
    file.open(fileName);
    // check if the file was successfully created.
    if(!file.is_open()) 
    {
        log << "Error 01: input file not found or not accessible\n";
        log.close();
        exit(EXIT_FAILURE);
    } 
    // else 
    // {
    //     std::cout << "File " << fileName << " opened successfully!\n";
    // }
}
void count_data(std::ifstream &file, int &line_count) {
    std::string fileContent;
    line_count = 0;
    while(getline(file, fileContent)) 
    {
        line_count++; // count the data line excepts the first line
    }
}
    
void write_file_task21(std::ofstream &output_file, std::vector <std::string> vt, int flag) {
    if(flag == 1) 
    {
        output_file << "number of outliers: " << vt.size() << "\n";
    }
    if(!vt.empty()) 
    {
        output_file << "id,time,value\n";
    } 
    for(unsigned long long i = 0; i < vt.size(); i++) 
    {
        output_file << vt[i] << "\n";
    }
}