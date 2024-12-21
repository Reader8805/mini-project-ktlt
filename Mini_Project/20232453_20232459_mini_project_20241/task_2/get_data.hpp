#pragma once

#include <algorithm> // for std::sort
#include <vector>
#include <sstream>
#include "file_management.hpp"
#include "check_condition.hpp"
#include <map>

typedef struct {
    int id;
    std::string hour;
    std::vector <float> values;
} timeStamp;

typedef struct {
    int id;
    std::vector <std::string> date;
    std::vector <float> values;
} timeStatistics;

//for task 2 - 2.2
void get_sensor_data_task21(float lower_zone, float higher_zone,std::string reading_file);
float aqi_calculation(float value);
void get_sensor_data_task22(std::string fileName);
void get_hour(std::ifstream &file, std::vector<timeStamp> &time_stamp);
// task 2.3
void get_max_values(std::ifstream &file);
void get_max_statistics(int i, std::vector<timeStatistics> time_stamp, std::string &max_hour, float &value);
void get_min_statistics(int i, std::vector<timeStatistics> time_stamp, std::string &min_hour, float &value);
void write_data_task_23(std::string fileName);
void get_statistics(std::ifstream &file, std::vector<timeStatistics> &time_stamp);
int get_interval(std::string fileName);
void get_median(int i, std::vector<timeStatistics> time_stamp);
//task 2.4
void access_aqi_24(std::string open_file, std::string store_file);