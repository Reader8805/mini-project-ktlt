#include "argument.hpp"


void argument_parsing_task3(int argc, char *argv[]) {
    std::ofstream log("task3.log", std::ios::app);  //append mode to write in log file
    if(argc != 3) 
    {
        log << "Error 03: invalid command\n";
        log.close();
        exit(EXIT_FAILURE);
    }
}