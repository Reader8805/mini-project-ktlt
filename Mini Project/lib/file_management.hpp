#pragma once


#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>

typedef std::ofstream outputFile; 

void read_file(std::string fileName);
void write_file(std::ofstream &output_file, int num_sensor, std::string time, float sensor_value);
void open_file(std::ofstream &file, std::string fileName);