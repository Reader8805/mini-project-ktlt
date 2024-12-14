#include "file_management.hpp"
#include "argument.hpp"
#include "get_data.hpp"


int main(int argc, char *argv[]) {
    std::string file_name;
    // task 2.1
    argument_parsing_task2(argc, argv, file_name);
    get_sensor_data_task21(3.0, 550.5, file_name);
    // task 2.2
    get_sensor_data_task22("dust_valid.csv");
    // task 2.3
    write_data_task_23("dust_valid.csv");
    return 0;
}