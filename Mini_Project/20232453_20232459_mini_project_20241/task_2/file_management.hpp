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
void create_output_file(std::ofstream &file, std::string fileName);
void open_input_file(std::ifstream &file, std::string fileName);
void write_file_task21(std::ofstream &output_file, std::vector <std::string> vt, int flag);