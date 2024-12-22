#include "file_management.hpp"
#include "argument.hpp"
#include "get_data.hpp"
#include "check_condition.hpp"

int main(int argc, char *argv[]) {
    std::string input_file, output_file;

    argument_parsing_task3(argc, argv, input_file, output_file);
    csv_file_data_check(input_file); // check condition
    convert_data(input_file, output_file);
    return 0;
}