#pragma once


#include "file_management.hpp"
#include "get_data.hpp"

void csv_format_check(std::string &fileName);
bool value_check(std::string &value);
bool id_check(std::string &id);
bool time_check(std::string &time);
void csv_file_data_check(std::string &fileName);
