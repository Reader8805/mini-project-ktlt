#include "get_data.hpp"
outputFile filecsv;
void get_sensor_data(int num_sensor, int sampling, int interval, std::string file_name) {
    std:: time_t current_time = std::time(NULL); //system time
    std:: time_t start_time = current_time - interval * 3600; // 1 hour = 3600 seconds 
    open_file(filecsv, file_name);
    filecsv << "id,time,value\n";
    // random sensor value and range from 0 -> 800
    random_num_generator random;
    distribution dis(0.0, 800.0);
    
    for(int i = 0; i < interval * 3600 / sampling; i++) {

        std:: time_t time_stamp = start_time + sampling * i;
        // a pointer to a std::tm struct that holds the time inforrmation
        std:: tm *readable_time = std::localtime(&time_stamp); 

        std::ostringstream time_stamp_stream;
        
        // convert the time into human readeable time

        time_stamp_stream << std:: put_time(readable_time, "%Y:%m:%d %H:%M:%S"); 
        //get the sensor values
    
        for(int id = 1; id <= num_sensor; id++) {
            double sensor_value = dis(random);
             // show the results: in format sensor_number,YYYY:MM:DD hh:mm:ss,sensor_value
            write_file(filecsv, id, time_stamp_stream.str(), sensor_value);
        }
    }
    filecsv.close();
}