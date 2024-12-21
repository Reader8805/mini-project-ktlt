#include "argument.hpp"

void argument_parsing_task1(int argc, char *argv[], int &num_sensor, int &sampling, int &interval) { 
   
    std::ofstream log("task1.log", std::ios::app);  //append mode to write in log file
    // set the default if the below conditions are not satisfied
    num_sensor = 1; 
    sampling = 60;
    interval = 24;
    // set the flag for the error conditions
    bool n_error_flag = true;
    bool st_error_flag = true;
    bool si_error_flag = true; 
    std::string check_next_arg;
    for (int i = 1; i < argc; i++) 
    {
        // check the next argc condition
        if(!(i + 1 >= argc)) 
        {
            check_next_arg = argv[i + 1];
        } else 
        {
            check_next_arg = argv[i];
        }
        // check the conditions of -n [num_sensor]
        if (std::string(argv[i]) == "-n") 
        {
            n_error_flag = false;
            // Check if there's a value after [-n]
            if (i + 1 >= argc || check_next_arg.empty() || check_next_arg == "-st" 
            || check_next_arg == "-si") 
            { 
                log << "Error 01: invalid command\n";
                log.close();
                exit(EXIT_FAILURE); 
            } 
            else 
            {
                num_sensor = std::stoi(argv[++i]);
            }
            if(num_sensor <= 0) 
            {
                log << "Error 02: invalid argument\n";
                log.close();
                exit(EXIT_FAILURE); 
            }
        }
        // check the conditions of -st [sampling] 
        else if (std::string(argv[i]) == "-st") 
        {
            st_error_flag = false;
            // Check if there's a value after [-st]
            if (i + 1 >= argc || check_next_arg.empty() || check_next_arg == "-si") 
            { 
                log << "Error 01: invalid command\n";
                log.close();
                exit(EXIT_FAILURE); 
            } 
            else 
            {
                sampling = std::stoi(argv[++i]);
            }
            if(sampling < 10) 
            {
                log << "Error 02: invalid argument\n";
                log.close();
                exit(EXIT_FAILURE); 
            }
        } 
        // check the conditions of -si [interval]
        else if(std::string(argv[i]) == "-si") 
        {
            si_error_flag = false;
            // Check if there's a value after [-si]
            if (i + 1 >= argc || check_next_arg.empty() || std::string(argv[i + 1]).front() == '-') 
            { 
                log << "Error 01: invalid command\n";
                log.close();
                exit(EXIT_FAILURE); 
            } 
            else 
            {
                interval = std::stoi(argv[++i]);
            }
            if(interval < 1) 
            {
                log << "Error 02: invalid argument\n";
                log.close();
                exit(EXIT_FAILURE); 
            }
        }
        else {
            if(n_error_flag) 
            {
                log << "Error 01: invalid command";
                log.close();
                exit(EXIT_FAILURE);
            } 
            else if(st_error_flag) 
            {
                log << "Error 01: invalid command";
                log.close();
                exit(EXIT_FAILURE);
            } 
            else if(si_error_flag) 
            {
                log << "Error 01: invalid command";
                log.close();
                exit(EXIT_FAILURE);
            }
        }
    }
    log.close();
}