/* OVERALL MENTAL MODEL
    1. Open /proc file location
    2. List out all it process using their PID
    3. Open /proc/<PID>/status
    4. Extract & display the process ID & Name. 
*/

#include "/home/anomaly/Documents/C++/Linux Internals/Process/Header/get_process.h"
#include <filesystem>   
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>

void get_PID_Name(std::string pid);

// Enumerate current running process from /proc file path.
void get_process(){
    const std::filesystem::path &dir_path = "/proc"; // Instatiating /proc object file path
    for (const auto &dir : std::filesystem::directory_iterator(dir_path)){ // Iterate /proc directory whilst refrencing it memory location
        const std::string &PID = dir.path().filename().string(); // Referencing PID memory location and converting the filename (PID) to string
        if (std::filesystem::is_directory(dir) && std::all_of(PID.begin(), PID.end(), isdigit)){ // Checking if dir is made of positive int
            // Read each PID status file
            get_PID_Name(PID);

        } else {
            continue;
        }
    
    }
}

void get_PID_Name(std::string pid){
    std::cout << "PID: " << pid << "\n";
    std::string line = ""; // Variable to read /proc/<pid>/status content to
    std::ifstream myLinuxProcessFilePath("/proc/"+pid+"/status"); // Creating file object in read mode
    // Checking if file opens successfully
    if (!(myLinuxProcessFilePath.is_open())){
        std::cerr << "Error Opening File." << std::endl;
    } else {
        while (getline(myLinuxProcessFilePath, line)){
            // Display only first line since it the Process name comes first
            std::cout << line << "\n" << std::endl;
            break;
        }
    }
    myLinuxProcessFilePath.close();
}


