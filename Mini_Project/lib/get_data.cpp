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

void get_sensor_data_task21(float lower_zone, float higher_zone, std::string reading_file) {
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

float aqi_calculation(float value) {
    float aqi = 0;
    float rate_of_change = 0;
    if(value >= 0 && value <= 12) {
        rate_of_change = 50 / 12;
        aqi = value * rate_of_change + 0.5;   
    } 
    else if(value >= 12 && value < 35.5) {
        rate_of_change = (100.0 - 50) / (35.5-12);
        aqi = 50 + (value - 12) * rate_of_change + 0.5;
    } 
    else if(value >= 35.5 && value < 55.5) {
        rate_of_change = (150.0 - 150) / (55.5-35.5);
        aqi = 100 + (value - 35.5) * rate_of_change + 0.5;
    } 
    else if(value >= 55.5 && value < 150.5) {
        rate_of_change = (200.0 - 150) / (150.5-55.5);
        aqi = int(150 + (value - 55.5) * rate_of_change) + 0.5;
    } 
    else if(value >= 150.5 && value < 250.5) {
        rate_of_change = (300.0 - 200) / (250.5 - 150.5);
        aqi = 200 + (value - 150.5) * rate_of_change + 0.5;
    } 
    else if(value >= 250.5 && value < 350.5) {
        rate_of_change = (400.0 - 300) / (350.5 - 250.5);
        aqi = 300 + (value - 250.5) * rate_of_change+ 0.5;
    } 
    else if(value >= 350.5 && value <= 550.5) {
        rate_of_change = (500.0 - 400) / (550.5 - 350.5);
        aqi = 400 + (value - 350.5) * rate_of_change + 0.5;
    } 
    return aqi;
}

void get_hour(std::ifstream &file, std::vector<timeStamp> &time_stamp) {
    std::string line;
    while(getline(file, line)) {
        
        std::stringstream ss(line);
        std::string id, time, value;
        std::getline(ss, id, ',');
        std::getline(ss, time, ',');
        std::getline(ss, value, ',');
        // skip the header file
        if (id == "id" && time == "time" && value == "value") {
        continue;
        }
        // get the hour
        std::stringstream ss1(time);
        std::string date, hour_and_value;
        std::getline(ss1, date, ' ');
        std::getline(ss1, hour_and_value, ' ');
        std::stringstream ss2(hour_and_value);
        std::string initial_hour;
        std::getline(ss2, initial_hour, ':');
        int final_hour = stoi(initial_hour);
        final_hour++;
        std::string full_times;
        float sensor_value = stof(value);
        if(final_hour < 10) {
            full_times = id + ',' + time.substr(0, 11) + "0" + std::to_string(final_hour) + ":00:00";      
        } else {
            full_times = id + ',' + time.substr(0, 11) + std::to_string(final_hour) + ":00:00";
        }
        // get the time_stamp e.g:1,2024:12:7 23:00:00
        
        bool flag = false; // to check if the time has already in the vector e.g: 2024:12:7 23:00:00
        for(unsigned int i = 0; i < time_stamp.size(); i++) {
            if(time_stamp[i].hour == full_times) {
                time_stamp[i].values.push_back(sensor_value);
                flag = true;
                break;
            }
        } 
        if(flag == false) { // if the time are not in the vector
            // create new struct for the new hour
            timeStamp newTime;
            newTime.hour = full_times;
            newTime.values.push_back(sensor_value);
            // push the new struct into the vector
            time_stamp.push_back(newTime);
        }
    }
}

std::string pollution_level(int aqi) {
    if(aqi >= 0 && aqi < 50) {
            return "Good";
        } 
        else if(aqi >= 50 && aqi < 100) {
            return "Moderate";
        } 
        else if(aqi >= 100 && aqi < 150) {
            return "Slightly unhealthy";
        } 
        else if(aqi >= 150 && aqi < 200) {
            return "Unhealthy";
        } 
        else if(aqi >= 200 && aqi < 300) {
            return "Very unhealthy";
        } 
        else if(aqi >= 300 && aqi < 400) {
            return "Hazardous";
        } 
        else if(aqi >= 400 && aqi <= 500) {
            return "Extremely hazardous ";
        } else 
            return "Unknown";
}

void get_sensor_data_task22(std::string fileName) {
    inputFile readingFile;
    outputFile output;

    open_input_file(readingFile, fileName);
    open_output_file(output, "dust_aqi.csv");

    std::vector<timeStamp> time_stamp;
    // calculate the average value/hour and aqi with respect to it 
    get_hour(readingFile, time_stamp);

    output <<  "id,time,value,aqi,pollution\n";

    for(unsigned long i = 0; i < time_stamp.size(); i++) {
        float sum = 0.0;
        for(unsigned long j = 0; j < time_stamp[i].values.size(); j++) {
            sum += time_stamp[i].values[j];
        }
        float average = sum / time_stamp[i].values.size();
        int aqi = aqi_calculation(average);
        std::string pollution = pollution_level(aqi);
        output << time_stamp[i].hour << ',' << std::fixed << std::setprecision(1) << average << ',' << aqi << ',' << pollution << '\n';
    }
        output.close();
        readingFile.close();
}