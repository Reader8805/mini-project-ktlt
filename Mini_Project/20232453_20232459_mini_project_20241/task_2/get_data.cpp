#include "get_data.hpp"

void get_sensor_data_task21(float lower_zone, float higher_zone, std::string reading_file) {
    outputFile outlier;
    outputFile valid;
    inputFile readingFile;
    std::ofstream log("task2.log", std::ios::app);  //append mode to write in log file
    // open or create the files
    open_input_file(readingFile, reading_file);
    //csv_format_check(reading_file);
    create_output_file(valid, "dust_valid.csv");
    create_output_file(outlier, "dust_outlier.csv");

    int count;
    count_data(readingFile, count);
    // check the max data points
    if(count > 10000) // max data points is 10000
    { 
        log << "Error 06: input file is too large\n";
        log.close();
        exit(EXIT_FAILURE);
    }
    readingFile.clear(); //reset the EOF flag
    readingFile.seekg(0); //reset the file pointer to the beginning
    std::string line;
    int line_number = 0;
    std::vector<std::string> duplicate_content;
    std::vector <std::string> outliers;
    std::vector <std::string> valids;
    lower_zone = 3;
    higher_zone = 550.5;
    // check the header
    if (std::getline(readingFile, line)) {
        std::stringstream ss(line);
        std::string id, time, value;
        std::getline(ss, id, ',');
        std::getline(ss, time, ',');
        std::getline(ss, value, ',');

        if (id == "id" && time == "time" && value == "value") {
            line_number++; // Increment line number for header
        } else {
            log << "Error 02: invalid csv file format\n";
            log.flush();
            log.close();
            readingFile.close();
            exit(EXIT_FAILURE);
        }
    }


    while(getline(readingFile, line)) 
    {
        std::stringstream ss(line);
        std::string id, time, value;
        std::getline(ss, id, ',');
        std::getline(ss, time, ',');
        std::getline(ss, value, ',');

        // skip the header file

        if (id == "id" && time == "time" && value == "value") 
        {
        continue;
        }
        // check and skip the missing or error data

        if(id.empty() || time.empty() || value.empty() || id_check(id) ==  false 
        || time_check(time) == false || value_check(value) == false) 
        {
            continue;
        } 
        //check and skip the duplicate data

        bool duplicate = false;
        for(unsigned int i = 0; i < duplicate_content.size(); i++) 
        {
            if(duplicate_content[i] == line) 
            {
                duplicate = true;
                break;
            }
        }
        if(duplicate) 
        {
            continue;
        } 
        else 
        {
            duplicate_content.push_back(line);
        }

        float sensorValue = std::stof(value);
        if (sensorValue >= lower_zone && sensorValue <= higher_zone)
        {
            valids.push_back(line);
        }
        else
        {
            outliers.push_back(line);
        }
    }

    write_file_task21(valid, valids, 0);
    write_file_task21(outlier, outliers, 1);
    //close the files
    readingFile.close();
    valid.close();
    outlier.close();
}

float aqi_calculation(float value) {
    float aqi = 0;
    float rate_of_change = 0;
    if(value >= 0 && value <= 12) 
    {
        rate_of_change = 50 / 12;
        aqi = value * rate_of_change + 0.5;   
    } 
    else if(value >= 12 && value < 35.5) 
    {
        rate_of_change = (100.0 - 50) / (35.5-12);
        aqi = 50.0 + (value - 12) * rate_of_change + 0.5;
    } 
    else if(value >= 35.5 && value < 55.5) 
    {
        rate_of_change = (150.0 - 100) / (55.5-35.5);
        aqi = 100.0 + (value - 35.5) * rate_of_change + 0.5;
    } 
    else if(value >= 55.5 && value < 150.5) 
    {
        rate_of_change = (200.0 - 150) / (150.5-55.5);
        aqi = 150.0 + (value - 55.5) * rate_of_change + 0.5;
    } 
    else if(value >= 150.5 && value < 250.5) 
    {
        rate_of_change = (300.0 - 200) / (250.5 - 150.5);
        aqi = 200.0 + (value - 150.5) * rate_of_change + 0.5;
    } 
    else if(value >= 250.5 && value < 350.5) 
    {
        rate_of_change = (400.0 - 300) / (350.5 - 250.5);
        aqi = 300.0 + (value - 250.5) * rate_of_change+ 0.5;
    } 
    else if(value >= 350.5 && value <= 550.5) 
    {
        rate_of_change = (500.0 - 400) / (550.5 - 350.5);
        aqi = 400.0 + (value - 350.5) * rate_of_change + 0.5;
    } 
    return aqi;
}

void bubble_sort(std::vector<timeStamp> &time_stamp) {
    for (unsigned long step = 0; step < time_stamp.size(); step++) 
    {
        for (unsigned long i = 0; i < time_stamp.size() - step - 1; i++) 
        {
            if (time_stamp[i].hour > time_stamp[i + 1].hour || 
                (time_stamp[i].hour == time_stamp[i + 1].hour && time_stamp[i].id > time_stamp[i + 1].id)) 
                {
                // Swap if they are out of order
                std::swap(time_stamp[i], time_stamp[i + 1]);
            }
        }
    }
}
                                                     
void get_hour(std::ifstream &file, std::vector<timeStamp> &time_stamp) {
    std::string line;
    while(getline(file, line)) 
    {
        
        std::stringstream ss(line);
        std::string id, time, value;
        std::getline(ss, id, ',');
        std::getline(ss, time, ',');
        std::getline(ss, value, ',');
        // skip the header file
        if (id == "id" && time == "time" && value == "value") 
        {
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
        // get the time_stamp e.g:2024:12:7 23:00:00
        if(final_hour < 10) 
        {
            full_times = time.substr(0, 11) + "0" + std::to_string(final_hour) + ":00:00";      
        } 
        else 
        {
            full_times = time.substr(0, 11) + std::to_string(final_hour) + ":00:00";
        }
        // to check if the time has already in the vector e.g: 2024:12:7 23:00:00
        bool flag = false;
        for(unsigned int i = 0; i < time_stamp.size(); i++) {
            if(time_stamp[i].hour == full_times && time_stamp[i].id == stoi(id)) 
            {
                time_stamp[i].values.push_back(sensor_value);
                flag = true;
                break;
            }
        } 
        bubble_sort(time_stamp);
        if(flag == false) // if the time are not in the vector
        {
            // create new struct for the new hour
            timeStamp newTime;
            newTime.id = stoi(id);
            newTime.hour = full_times;
            newTime.values.push_back(sensor_value);
            // push the new struct into the vector
            time_stamp.push_back(newTime);
        }
    }
}

std::string pollution_level(int aqi) {
    if(aqi >= 0 && aqi < 50) 
    {
        return "Good";
    } 
    else if(aqi >= 50 && aqi < 100) 
    {
        return "Moderate";
    } 
    else if(aqi >= 100 && aqi < 150) 
    {
        return "Slightly unhealthy";
    } 
    else if(aqi >= 150 && aqi < 200) 
    {
        return "Unhealthy";
    } 
    else if(aqi >= 200 && aqi < 300) 
    {
        return "Very unhealthy";
    } 
    else if(aqi >= 300 && aqi < 400) 
    {
        return "Hazardous";
    } 
    else if(aqi >= 400 && aqi <= 500) 
    {
        return "Extremely hazardous";
    } 
    else 
        return "Unknown";
}

void get_sensor_data_task22(std::string fileName) {
    inputFile readingFile;
    outputFile output;

    open_input_file(readingFile, fileName);
    create_output_file(output, "dust_aqi.csv");

    std::vector<timeStamp> time_stamp;
    // calculate the average value/hour and aqi with respect to it 
    get_hour(readingFile, time_stamp);

    output <<  "id,time,value,aqi,pollution\n";

    for(unsigned long i = 0; i < time_stamp.size(); i++) 
    {
        float sum = 0.0;
        for(unsigned long j = 0; j < time_stamp[i].values.size(); j++) 
        {
            sum += time_stamp[i].values[j];
        }
        float average = sum / time_stamp[i].values.size();
        int aqi = aqi_calculation(average);
        std::string pollution = pollution_level(aqi);
        output << time_stamp[i].id << ',' << time_stamp[i].hour << ',' 
        << std::fixed << std::setprecision(1) << average << ',' << aqi << ',' << pollution << '\n';
    }
        output.close();
        readingFile.close();
}

void get_max_statistics(int i, std::vector<timeStatistics> time_stamp, std::string &max_hour, float &value) {
        float temp = 0;
        // int position = 0;
        for(unsigned long long j = 0; j < time_stamp[i].values.size(); j++) 
        {
            if(time_stamp[i].values[j] > temp) 
            {
                temp = time_stamp[i].values[j];
                max_hour = time_stamp[i].date[j];
            }
        }
        value = temp;
    }
void get_min_statistics(int i, std::vector<timeStatistics> time_stamp, std::string &min_hour, float &value) {
       float temp = time_stamp[0].values[0];
        // int position = 0;
        for(unsigned long long j = 0; j < time_stamp[i].values.size(); j++) 
        {
            if(time_stamp[i].values[j] < temp) 
            {
                temp = time_stamp[i].values[j];
                min_hour = time_stamp[i].date[j];
            }
        }
        value = temp;
}

void get_average_statistics(int i, std::vector<timeStatistics> time_stamp, float &value) {
    float sum = 0;
        // int position = 0;
        for(unsigned long long j = 0; j < time_stamp[i].values.size(); j++) 
        {
           sum += time_stamp[i].values[j];
        }
    value = sum / time_stamp[i].values.size();
}

void get_statistics(std::ifstream &file, std::vector<timeStatistics> &time_stamp) {
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
        float sensor_value = stof(value);
        // set the flag
        bool flag = false;
        for(unsigned int i = 0; i < time_stamp.size(); i++) 
        {
            if(time_stamp[i].id == stoi(id)) // if id already existed
            {
                time_stamp[i].values.push_back(sensor_value);
                time_stamp[i].date.push_back(time);
                flag = true;
                break;
            }
        } 
        if(flag == false) // if the id are not in the vector
        { 
            // create new struct for the new hour
            timeStatistics newTime;
            newTime.id = stoi(id);
            newTime.date.push_back(time);
            newTime.values.push_back(sensor_value);
            // push the new struct into the vector
            time_stamp.push_back(newTime);
        }
    }
}

int get_interval(std::string fileName) {
    inputFile readingFile(fileName);
    std::string line;
    int interval = 0;
    std::vector<int> stored_hour; // Stored existed hour

    while(getline(readingFile, line)) 
    {
        std::stringstream ss(line);
        std::string id, time, value;
        std::getline(ss, id, ',');
        std::getline(ss, time, ',');
        std::getline(ss, value, ',');

        // Remove header
        if (id == "id" && time == "time" && value == "value") 
        {
            continue;
        }

        // Get hour from time stamp
        std::stringstream ss1(time);
        std::string date, hour_and_value;
        std::getline(ss1, date, ' ');
        std::getline(ss1, hour_and_value, ' ');

        std::stringstream ss2(hour_and_value);
        std::string initial_hour;
        std::getline(ss2, initial_hour, ':');
        int hour = stoi(initial_hour);

        // Check if the hour existed
        bool flag = false;
        for (unsigned int i = 0; i < stored_hour.size(); i++) 
        {
            if (stored_hour[i] == hour) 
            {
                flag = true; // hour existed
            }
        }

        if (!flag) //if this hour is not existed, store it in stored_hour
        { 
            stored_hour.push_back(hour);
            interval++; // increase interval 
        }
    }

    return interval;
}

void get_median(int i, std::vector<timeStatistics> time_stamp, float &value) {
    // sort the values
    std::sort(time_stamp[i].values.begin(), time_stamp[i].values.end());
    unsigned long long size = time_stamp[i].values.size();

    if (size % 2 == 1) // If the size is odd, return the middle element
    {
        value = time_stamp[i].values[size / 2];
    }
    else // If the size is even, return the average of the two middle elements
    {
        value = (time_stamp[i].values[size / 2 - 1] 
        + time_stamp[i].values[size / 2]) / 2.0;
    }
}
void write_data_task_23(std::string fileName) {

    outputFile summary;
    inputFile readingFile;
    open_input_file(readingFile, fileName);
    create_output_file(summary, "dust_summary.csv");

    std::vector <timeStatistics> time_stat;
    get_statistics(readingFile, time_stat);

    summary << "id,parameter,time,value\n";

    for(unsigned int i = 0; i < time_stat.size(); i++) 
    {
        std::string max_hour;
        std::string min_hour;
        float min_value = 0;
        float max_value = 0;
        float average_value = 0;
        float median_value = 0;
        int interval = get_interval("dust_aqi.csv");
        // get the average value and its hour
        get_average_statistics(i, time_stat, average_value);
        // get the max value and its hour
        get_max_statistics(i, time_stat, max_hour, max_value);
        // get the min value and its hour
        get_min_statistics(i, time_stat, min_hour, min_value);
        // get the median and its value
        get_median(i, time_stat, median_value);

        summary << time_stat[i].id << ',' << "max" << ',' << max_hour << ',' 
        << std::fixed << std::setprecision(1) << max_value << '\n';
        summary << time_stat[i].id << ',' << "min" << ',' << min_hour << ','
        << std::fixed << std::setprecision(1) << min_value << '\n'; 
        summary << time_stat[i].id << ',' << "mean" << ',' << interval << ":00:00,"
        << std::fixed << std::setprecision(2) << average_value << '\n'; 
        summary << time_stat[i].id << ',' << "median" << ',' << interval << ":00:00," 
        << std::fixed << std::setprecision(1) << median_value << '\n';
    }
}

void access_aqi_24(std::string open_file, std::string store_file) {
    //open and write into file
    outputFile dust_statistics;
    inputFile dust_aqi;
    open_input_file(dust_aqi, open_file);
    create_output_file(dust_statistics, store_file);
    //---------------------------------------------
    std::string id,time,value,aqi,pollution;
    std::string line;
    std::map<std::string,std::map<std::string,int>> id_pollution_count; 
    std::vector<std::string> pollution_sort = {"Good","Moderate","Slightly unhealthy"
    ,"Unhealthy","Very unhealthy","Hazardous","Extremely hazardous"};
    int line_count = 0;
    while(getline(dust_aqi,line)){
        //skip the first line of "dust_aqi.csv"
        line_count ++;
        if(line_count == 1) continue;
        //-------------------------------
        std::stringstream ss(line);
        std::getline(ss,id,',');
        std::getline(ss,time,',');
        std::getline(ss,value,',');
        std::getline(ss,aqi,',');
        std::getline(ss,pollution,',');
        /*set all frequency of category of pollution with 0 so the code can 
        write all the frequency (including each id have no type of pollutions)*/
        if(id_pollution_count.find(id) == id_pollution_count.end())
        {
            for(auto sort : pollution_sort)
            {
                id_pollution_count[id][sort] = 0;
            }
        }
        //--------------------------------------------------------------------
        //using map to count the frequency of each id of pollutions
        id_pollution_count[id][pollution]++;
    }
    
    dust_statistics << "id,pollution,duration" <<std::endl;
    for(auto real_id_pollution : id_pollution_count){
        std::string real_id =  real_id_pollution.first ;
        //write with the same order pollution like the requirement of the task2.4
        for(std::size_t i = 0;i < pollution_sort.size();i++)
        {
            dust_statistics << real_id<<"," << pollution_sort[i] << "," 
            << real_id_pollution.second[pollution_sort[i]]<<std::endl;
        }
    }
    dust_statistics.close();
    dust_aqi.close();
}