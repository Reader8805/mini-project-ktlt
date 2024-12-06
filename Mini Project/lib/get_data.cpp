#include "get_data.hpp"

void get_sensor_data_task1(int num_sensor, int sampling, int interval, std::string file_name) {
    outputFile filecsv_task1;
    std:: time_t current_time = std::time(NULL); //system time
    std:: time_t start_time = current_time - interval * 3600; // 1 hour = 3600 seconds 
    open_output_file(filecsv_task1, file_name);
    filecsv_task1 << "id,time,value\n";
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
            write_file_task1(filecsv_task1, id, time_stamp_stream.str(), sensor_value);
        }
    }
    filecsv_task1.close();
}

void get_sensor_data_task2(float lower_zone, float higher_zone, std::string reading_file) {
    outputFile outlier;
    outputFile valid;
    inputFile readingFile;
    // open or create the files
    open_input_file(readingFile, reading_file);
    open_output_file(valid, "dust_valid.csv");
    open_output_file(outlier, "dust_outlier.csv");

    int count;
    count_data(readingFile, count);
    // check the max data points
    if(count > 10000) { // max data points is 10000
        std::cerr << "Too many data points!";
        exit(EXIT_FAILURE);
    }

    readingFile.clear(); //reset the EOF flag
    readingFile.seekg(0); //reset the file pointer to the beginning
    std::string line;
    std::vector <std::string> outliers;
    std::vector <std::string> valids;
    lower_zone = 3;
    higher_zone = 550.5;
    while(getline(readingFile, line)) {
        
        std::stringstream ss(line);
        std::string id, time, value;
        std::getline(ss, id, ',');
        std::getline(ss, time, ',');
        std::getline(ss, value, ',');
        // skip the header file
        if (id == "id" && time == "time" && value == "value") {
        continue;
        }

        float sensorValue = std::stof(value);
        if (sensorValue >= lower_zone && sensorValue <= higher_zone){
            valids.push_back(line);
        }
        else{
            outliers.push_back(line);
        }
    }

    write_file_task2(valid, valids, 0);
    write_file_task2(outlier, outliers, 1);
    //close the files
    readingFile.close();
    valid.close();
    outlier.close();
}