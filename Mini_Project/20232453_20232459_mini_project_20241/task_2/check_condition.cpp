#include "check_condition.hpp"

bool id_check(std::string &id) {
    int checked_id  = stoi(id);
    if(checked_id > 0) 
        return true;
    else 
        return false;
}
bool value_check(std::string &value) {
    float checked_value = stof(value);
    if(checked_value > 0) 
        return true;
    else 
        return false;
}
bool time_check(std::string &time) {
    if(time.length() == 19 && time[4] == ':' && time[7] == ':' 
    && time[10] == ' ' && time[13] == ':' && time[16] == ':') 
    {
       return true; 
    }
    else {
        return false;
    }
}

void csv_file_data_check(std::string &fileName) { // check the data and write to log
    inputFile file(fileName);
    outputFile log("task2.log", std::ios::app);  //append mode to write in log file
    
    //open_input_file(file, fileName);
    if(!file.is_open()) 
    {
        log << "Error 01: input file not found or not accessible\n";
        log.close();
        exit(EXIT_FAILURE);
    }
    int count;
    count_data(file, count);
    // check the max data points
    if(count > 10000) // max data points is 10000
    { 
        log << "Error 06: input file is too large\n";
        log.close();
        exit(EXIT_FAILURE);
    }
    file.clear(); //reset the EOF flag
    file.seekg(0); //reset the file pointer to the beginning

    
    std::string line;
    int line_number = 0;
    int position;
    std::vector<int> duplicate_position;
    std::vector<std::string> duplicate_content;
    // check the header
    if (std::getline(file, line)) {
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
            file.close();
            exit(EXIT_FAILURE);
        }
    }
    
    while(getline(file, line)) 
    {
        line_number++;
        std::stringstream ss(line);
        std::string id, time, value;
        std::getline(ss, id, ',');
        std::getline(ss, time, ',');
        std::getline(ss, value, ',');
        // skip the header file
        
        // check for missing/invalid data
        if(id.empty() || time.empty() || value.empty()) 
        {
            log  <<  "Error 04: data is missing at line " << line_number << "\n";
            log.flush();
            continue;
        } 
        else if(id_check(id) ==  false || time_check(time) == false || value_check(value) == false) 
        {
            log  <<  "Error 02: invalid csv file format\n";
            log.flush();
            continue;
        }
        // check the duplicate data
        bool duplicate = false;
        for(unsigned int i = 0; i < duplicate_content.size(); i++) {
            if(duplicate_content[i] == line) {
                position = duplicate_position[i];
                duplicate = true;
                break;
            }
        }
        if(duplicate) {
            log << "Error 05: data is duplicated at line " << line_number
            << " and " << position << '\n';
            log.flush();
        } 
        else 
        {
            duplicate_content.push_back(line);
            duplicate_position.push_back(line_number);
        }
    }

    log.close();
    file.close();
}

