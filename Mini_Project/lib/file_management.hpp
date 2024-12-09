#pragma once


#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <vector>

typedef std::ofstream outputFile; 
typedef std::ifstream inputFile;

void count_data(std::ifstream &file, int &line_count);
void write_file_task1(std::ofstream &output_file, int num_sensor, std::string time, float sensor_value);
void open_output_file(std::ofstream &file, std::string fileName);
void open_input_file(std::ifstream &file, std::string fileName);
void write_file_task2(std::ofstream &output_file, std::vector <std::string> vt, int flag);