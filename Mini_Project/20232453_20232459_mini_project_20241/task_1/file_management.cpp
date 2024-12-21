#include "file_management.hpp"

// function to open file and check if it was successfully opened.
void create_output_file(std::ofstream &file, std::string fileName) {
    std::ofstream log("task1.log", std::ios::app);
    if (!log.is_open()) {
        std::cerr << "Error 04: Cannot open task1.log.\n";
        exit(EXIT_FAILURE);
    }
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

void write_file_task1(std::ofstream &file, int num_sensor, std::string time, float sensor_value) {
        file << num_sensor << ',' << time << ',' 
        << std::fixed << std::setprecision(1) <<sensor_value << '\n';
}
