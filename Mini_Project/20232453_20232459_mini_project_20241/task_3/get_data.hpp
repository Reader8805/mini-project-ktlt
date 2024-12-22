#pragma once

#include <vector>
#include <sstream>
#include "file_management.hpp"
#include "check_condition.hpp"
#include <map>

void convert_time_to_unix(std::string &time_stamp, unsigned int &unix_time);
void time_to_byte(unsigned int unix_time, std::vector<std::string> &packet);
void convert_PM25_to_byte(float value, std::vector<std::string> &packet);
void convert_aqi(int aqi, std::vector<std::string> &packet);
char pollution_level(int aqi);
void convert_pollution_code(char code, std::vector<std::string> &packet);
void convert_data(std::string &readFile, std::string &writeFile);