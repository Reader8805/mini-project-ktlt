#pragma once


#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <vector>

typedef std::ofstream outputFile; 
typedef std::ifstream inputFile;

void create_output_file(std::ofstream &file, std::string fileName);
void open_input_file(std::ifstream &file, std::string fileName);
