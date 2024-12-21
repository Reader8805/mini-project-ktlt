#include "argument.hpp"

void argument_parsing_task2(int argc, char *argv[], std::string &file_name) {
    outputFile log("task2.log", std::ios::app);  //append mode to write in log file
    if(argc > 1 && argc < 3) 
    {
        file_name = argv[1];
    } 
    else if(argc == 1)
    {
        file_name = "dust_sensor.csv";
    } 
    else 
    {
        log << "Error 03: invalid command";
        log.close();
        exit(EXIT_FAILURE);
    }
    
}