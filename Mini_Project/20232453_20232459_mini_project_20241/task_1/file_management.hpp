#pragma once


#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib> // for exit()
#include <iomanip> // for setprecision()

typedef std::ofstream outputFile; 
typedef std::ifstream inputFile;

void write_file_task1(std::ofstream &output_file, int num_sensor, std::string time, float sensor_value);
void create_output_file(std::ofstream &file, std::string fileName);
