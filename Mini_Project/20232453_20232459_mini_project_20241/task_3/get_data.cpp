#include "get_data.hpp"

void convert_time_to_unix(std::string &time_stamp, unsigned int &unix_time) {
    struct tm time = {};
    std::istringstream ss(time_stamp); // to read formatted data from string time_stamp
    ss >> std::get_time(&time, "%Y:%m:%d %H:%M:%S");
    unix_time = (unsigned int)mktime(&time);
}

void time_to_byte(unsigned int unix_time, std::vector<std::string> &packet) {
    unsigned int converted_time;
    for(int i = 0; i < 4; i++) 
    {
        converted_time = unix_time >> (i * 8) & 0xFF; // shift each byte, & with 0xFF(255) to get the LSB
        std::ostringstream hex; // to format converted_time to hex type
        hex << std::hex << std::setw(2) << std::setfill('0') << converted_time; 
        packet.push_back(hex.str());  // push this into the packet
    }
}

void convert_PM25_to_byte(float value, std::vector<std::string> &packet) {
    union {
        float value;
        unsigned char bytes[4]; /*to access each byte of the float*/
    } toByte; // pc is little-endian

    toByte.value = value;
    
    for(int i = 0; i < 4; i++) {
        std::ostringstream hex; // to format byte as hex
        hex << std::hex << std::setw(2) << std::setfill('0') << (toByte.bytes[i] & 0xFF);
        packet.push_back(hex.str());
    }
}

void convert_aqi(int aqi, std::vector<std::string> &packet) {
    union {
        int value;
        unsigned char bytes[2]; /*to access each byte of the float*/
    } toByte; // pc is little-endian
    toByte.value = aqi;
    for(int i = 0; i < 2; i++) {
        std::ostringstream hex; // to format byte as hex
        hex << std::hex << std::setw(2) << std::setfill('0') << (toByte.bytes[i] & 0xFF);

        packet.push_back(hex.str());
    }
}

char pollution_level(int aqi) {
    if(aqi >= 0 && aqi < 50) 
    {
        return 'A';
    } 
    else if(aqi >= 50 && aqi < 100) 
    {
        return 'B';
    } 
    else if(aqi >= 100 && aqi < 150) 
    {
        return 'C';
    } 
    else if(aqi >= 150 && aqi < 200) 
    {
        return 'D';
    } 
    else if(aqi >= 200 && aqi < 300) 
    {
        return 'E';
    } 
    else if(aqi >= 300 && aqi < 400) 
    {
        return 'F';
    } 
    else if(aqi >= 400 && aqi <= 500) 
    {
        return 'G';
    } 
    else 
    {
        return 'U';
    }
}


void convert_pollution_code(char code, std::vector<std::string> &packet) {
    int hex_code = code;
    std::ostringstream hex;
    hex << std::hex << std::setw(2) << std::setfill('0') << hex_code;
    packet.push_back(hex.str());
}


void checksum(std::vector<std::string> &packet) {

    int sum = 0; // sum of  [packet length, id, time, PM2.5, AQI, pollution code] 

    for (unsigned int i = 1; i < packet.size(); i++) {

        int value = stoi(packet[i], nullptr, 16); // Convert hex string to integer
        sum += value;
    }
    unsigned char check_sum = ~sum + 1;
    std::ostringstream hex; // Convert checksum to hex
    hex << std::hex << std::setw(2) << std::setfill('0') << (int)(check_sum & 0xFF);
    packet.push_back(hex.str()); 
}


void calculate_packet_length(std::vector<std::string> &packet) {
    unsigned int packet_length = packet.size() + 2; // include both start and stop bytes
    std::ostringstream hex;
    hex << std::hex << std::setw(2) << std::setfill('0') << packet_length;
    packet[1] = hex.str();
}

void convert_data(std::string &readFile, std::string &writeFile) {
    inputFile file;
    outputFile output;
    std::ofstream log("task3.log", std::ios::app);  //append mode to write in log file
    open_input_file(file, readFile);
    create_output_file(output, writeFile);
    std::string line;
    int line_count = 0;

    while(getline(file, line)) {
        line_count++;
        std::stringstream ss(line);
        std::string id, time, value, aqi, pollution;
        std::getline(ss, id, ',');
        std::getline(ss, time, ',');
        std::getline(ss, value, ',');
        std::getline(ss, aqi, ',');
        std::getline(ss, pollution, ',');

        if (id.empty() || time.empty() || value.empty() || aqi.empty() || pollution.empty()) 
        {
        continue; // Skip this line
        }
        //skip header file
        if (id == "id" && time == "time" && value == "value" && aqi == "aqi" 
        && pollution == "pollution") 
        {
        continue;
        }
        std::vector<std::string> packet;
        packet.push_back("aa"); // push the start byte(1 byte)
        packet.push_back("00"); // push the initial packet length
        if(id.length() == 1) 
        {
            packet.push_back("0" + id); 
        } 
        else {
            packet.push_back(id); // push the id
        }
        unsigned int unix_time = 0;
        convert_time_to_unix(time, unix_time);
        time_to_byte(unix_time, packet); // push converted time to packet

        float data_value = stof(value);
        convert_PM25_to_byte(data_value, packet); // push converted value to packet

        int aqi_value  = stoi(aqi);
        convert_aqi(aqi_value, packet); //  push converted aqi to packet

        char pollution_code = pollution_level(aqi_value);
        convert_pollution_code(pollution_code, packet); // push converted pollution code to packet

        calculate_packet_length(packet); // push the packet length

        checksum(packet); // push calculated checksum to packet

        packet.push_back("ff"); // push the stop byte
        //write to file
        for (unsigned int i = 0; i < packet.size(); i++) {
            output << packet[i] << ' ';
        }
        output << std::endl;
    }
    file.close();
    output.close();
} 

