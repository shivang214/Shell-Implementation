#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

const int MAX_HISTORY_SIZE = 20;
const int DISPLAY_HISTORY_SIZE = 10;

class CommandShell {
private:
    std::vector<std::string> history;
    int currentIndex;

public:
    CommandShell() : history(MAX_HISTORY_SIZE), currentIndex(-1) {}

    // Function to add a command to history
    void addToHistory(const std::string& command) {
        currentIndex = (currentIndex + 1) % MAX_HISTORY_SIZE;
        history[currentIndex] = command;
    }

    // Function to display the last 'num' commands
    void displayHistory(int num = DISPLAY_HISTORY_SIZE) {
        if (num <= 0 || num > MAX_HISTORY_SIZE) {
            throw std::invalid_argument("Invalid number of commands to display");
        }

        int start = (currentIndex - num + 1 + MAX_HISTORY_SIZE) % MAX_HISTORY_SIZE;
        for (int i = 0; i < num; ++i) {
            std::cout << history[start] << std::endl;
            start = (start + 1) % MAX_HISTORY_SIZE;
        }
    }
    
};
