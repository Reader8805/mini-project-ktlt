#include "file_management.hpp"
#include "argument.hpp"
#include "get_data.hpp"

int main(int argc, char *argv[]) {
    int num_sensor, sampling, interval;
    // create file
    std::string file_name = "dust_sensor.csv";
    
    argument_parsing_task1(argc, argv, num_sensor, sampling, interval);
    get_sensor_data_task1(num_sensor, sampling, interval, file_name);
    return 0;
}