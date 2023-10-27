#include "header.cpp"
using namespace std;

 void pinfo() {
        // Get the process ID of the current shell
        pid_t pid = getpid();
        
        // Print the process ID
        cout << "pid -- " << pid << endl;


        //Read process status from /proc/{pid}/status

        ifstream statusFile("/proc/" + to_string(pid) + "/status");
        string line;
        
        while (getline(statusFile, line)) {
            if (line.find("State:") != std::string::npos) {
                std::cout << "Process Status -- {" << line.substr(7) << "}" << std::endl;
            }
            else if (line.find("VmSize:") != std::string::npos) {
                std::istringstream iss(line);
                std::string label;
                int memory;
                iss >> label >> memory;
                std::cout << "memory -- " << memory << " {Virtual Memory}" << std::endl;
            }
        }

        // Get executable path from /proc/{pid}/exe
        char execPath[4096];
        int len = readlink(("/proc/" + std::to_string(pid) + "/exe").c_str(), execPath, sizeof(execPath) - 1);
        if (len != -1) {
            execPath[len] = '\0';
            std::cout << "Executable Path -- " << execPath << std::endl;
        }
    }