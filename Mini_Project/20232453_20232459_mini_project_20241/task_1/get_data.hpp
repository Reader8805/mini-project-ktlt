#pragma once

#include <random>
#include <ctime>
#include <sstream>
#include "file_management.hpp"

//generate random sensor 
typedef std::default_random_engine random_num_generator;
typedef std::uniform_real_distribution<double> distribution;
// for task 1
void get_sensor_data_task1(int num_sensor, int sampling, int interval, std::string file_name);