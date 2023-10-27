#include <iostream>
#include <vector>
#include <string>
#include <dirent.h>
#include <cstring>
#include <unistd.h>
#include <termios.h>
#include "help_tab.cpp"
// Function to get a list of files/directories in the current directory
std::vector<std::string> getFilesInCurrentDirectory() {
    std::vector<std::string> files;
    DIR *dir;
    struct dirent *entry;

    if ((dir = opendir(".")) != nullptr) {
        while ((entry = readdir(dir)) != nullptr) {
            files.push_back(entry->d_name);
        }
        closedir(dir);
    }

    return files;
}

// Function to enable/disable terminal canonical mode for tab key handling
void setCanonicalMode(bool enable) {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    if (enable) {
        term.c_lflag |= ICANON;
    } else {
        term.c_lflag &= ~ICANON;
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

// Function to perform tab-based autocomplete
void tabAutoComplete() {
    setCanonicalMode(false); // Disable canonical mode for direct keypress handling

    std::vector<std::string> files = getFilesInCurrentDirectory();
    std::string input;

    while (true) {
        std::cout << "> ";
        std::cin >> input;

        if (input.empty()) {
            continue;
        }

        if (input == "exit") {
            break;
        }

        bool foundMatch = false;
        for (const std::string& file : files) {
            if (file.rfind(input, 0) == 0) { // Check if file starts with input
                if (foundMatch) {
                    std::cout << " ";
                }
                std::cout << file;
                foundMatch = true;
            }
        }

        if (foundMatch) {
            std::cout << std::endl;
        }
    }

    setCanonicalMode(true); // Restore canonical mode
}
