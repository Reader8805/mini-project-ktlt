#pragma once


#include <random>
#include <ctime>
#include <vector>
#include <sstream>
#include "file_management.hpp"

// generate random sensor frequency for task 2.4 (i guess so)
typedef std::default_random_engine random_num_generator;
typedef std::uniform_real_distribution<double> distribution;

void get_sensor_data_task1(int num_sensor, int sampling, int interval, std::string file_name);
void get_sensor_data_task2(float lower_zone, float higher_zone,std::string reading_file);

