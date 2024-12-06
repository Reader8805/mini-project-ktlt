#include "file_management.hpp"
#include "argument.hpp"
#include "get_data.hpp"

int main(int argc, char *argv[]) {
    std::string file_name;
    argument_parsing_task2(argc, argv, file_name);
    get_sensor_data_task2(3.0, 550.5, file_name);
    
    return 0;
}