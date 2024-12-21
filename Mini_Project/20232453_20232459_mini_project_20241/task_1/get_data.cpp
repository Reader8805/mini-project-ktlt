#include "get_data.hpp"


void get_sensor_data_task1(int num_sensor, int sampling, int interval, std::string file_name) {
    outputFile filecsv_task1;
    
    std:: time_t current_time = std::time(NULL); // seconds have passed since 00:00 jan 1 1970
    std:: time_t start_time = current_time - interval * 3600; // 1 hour = 3600 seconds 
    create_output_file(filecsv_task1, file_name);
    
    filecsv_task1 << "id,time,value\n";
    // random sensor value and range from 0 -> 800
    random_num_generator random;
    distribution dis(0.0, 800.0);
    
    for(int i = 0; i < interval * 3600 / sampling; i++) 
    {

        std:: time_t time_stamp = start_time + sampling * i;
        // a pointer to a std::tm struct that holds the time inforrmation
        std:: tm *readable_time = std::localtime(&time_stamp); 

        std::ostringstream time_stamp_stream;
        
        // convert the time into human readeable time

        time_stamp_stream << std:: put_time(readable_time, "%Y:%m:%d %H:%M:%S"); 
        //get the sensor values
    
        for(int id = 1; id <= num_sensor; id++) 
        {
            double sensor_value = dis(random);
             // show the results: in format sensor_number,YYYY:MM:DD hh:mm:ss,sensor_value
            write_file_task1(filecsv_task1, id, time_stamp_stream.str(), sensor_value);
        }
    }
    filecsv_task1.close();
}