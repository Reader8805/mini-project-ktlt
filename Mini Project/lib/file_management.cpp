#include "file_management.hpp"

// function to create file and check if it was successfully created.
void open_file(std::ofstream &file, std::string fileName) {
    
    file.open(fileName);
    // check if the file was successfully created.
    if(!file.is_open()) {
        std::cout << "Cannot open the file!";
        exit(EXIT_FAILURE);
    } 
    else {
        std::cout << "File opened successfully!";
    }
}

void read_file(std::string fileName) {
    std::string fileContent;
    std::ifstream readFile;
    readFile.open(fileName);

    while(getline(readFile, fileContent)) {
        
    }
}
    
void write_file(std::ofstream &output_file, int num_sensor, std::string time, float sensor_value) {
        output_file << num_sensor << ',' << time << ',' << std::fixed << std::setprecision(1) <<sensor_value << '\n';
}