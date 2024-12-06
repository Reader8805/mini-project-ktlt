#include "file_management.hpp"

// function to open file and check if it was successfully opened.
void open_output_file(std::ofstream &file, std::string fileName) {
    
    file.open(fileName);
    // check if the file was successfully opened(created).
    if(!file.is_open()) {
        std::cout << "Cannot open the file!";
        exit(EXIT_FAILURE);
    } 
    else {
        std::cout << "File " << fileName << " opened successfully!\n";
    }
}
void open_input_file(std::ifstream &file, std::string fileName) {
    file.open(fileName);
    // check if the file was successfully created.
    if(!file.is_open()) {
        std::cout << "Cannot open the file!";
        exit(EXIT_FAILURE);
    } 
    else {
        std::cout << "File " << fileName << " opened successfully!\n";
    }
}
void count_data(std::ifstream &file, int &line_count) {
    std::string fileContent;
    line_count = 0;
    while(getline(file, fileContent)) {
        line_count++; // count the data line excepts the first line
    }
}
    
void write_file_task1(std::ofstream &file, int num_sensor, std::string time, float sensor_value) {
        file << num_sensor << ',' << time << ',' << std::fixed << std::setprecision(1) <<sensor_value << '\n';
}

void write_file_task2(std::ofstream &output_file, std::vector <std::string> vt, int flag) {
    if(flag == 1) {
        output_file << "number of outliers: " << vt.size() << "\n";
    }
    if(!vt.empty()) {
        output_file << "id,time,value\n";
    } 
    for(unsigned long long i = 0; i < vt.size(); i++) {
        output_file << vt[i] << "\n";
    }
}