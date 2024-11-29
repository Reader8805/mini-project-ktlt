#pragma once


#include <random>
#include <ctime>
#include <vector>
#include "file_management.hpp"

// generate random sensor frequency for task 2.4 (i guess so)
typedef std::default_random_engine random_num_generator;
typedef std::uniform_real_distribution<double> distribution;

void get_sensor_data(int num_sensor, int sampling, int interval, std::string file_name);

