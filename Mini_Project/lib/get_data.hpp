#pragma once


#include <random>
#include <ctime>
#include <vector>
#include <sstream>
#include "file_management.hpp"

typedef struct {
    std::string hour;
    std::vector <float> values;
} timeStamp;

// generate random sensor frequency zz
typedef std::default_random_engine random_num_generator;
typedef std::uniform_real_distribution<double> distribution;
// for task 1
void get_sensor_data_task1(int num_sensor, int sampling, int interval, std::string file_name);
//for task 2
void get_sensor_data_task21(float lower_zone, float higher_zone,std::string reading_file);
float aqi_calculation(float value);
void get_sensor_data_task22(std::string fileName);
void get_hour(std::ifstream &file, std::vector<timeStamp> &time_stamp);