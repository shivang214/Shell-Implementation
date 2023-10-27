#ifndef CD_MODULE_H
#define CD_MODULE_H
#include <string>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
using namespace std;



class CdModule {
public:
    CdModule() {
        if (getcwd(initial_directory, sizeof(initial_directory)) == nullptr) {
            perror("getcwd");
            std::exit(1);
        }
        if (getcwd(cwd, sizeof(cwd)) == nullptr) {
            perror("getcwd");
            std::exit(1);
        }
    }

    bool changeDirectory(const std::string& path) {
        if (path == "-") {
            // Change to the previous directory
            if (chdir(initial_directory) == 0) {
                // Swap current and previous directories
                std::swap(cwd, initial_directory);
                return true;
            } else {
                perror("chdir");
                return false;
            }
        } else if (path == "~") {
            // Change to the user's home directory
            const char* homeDirectory = getenv("HOME");
            if (homeDirectory) {
                if (chdir(homeDirectory) == 0) {
                    if (getcwd(cwd, sizeof(cwd)) != nullptr) {
                        return true;
                    } else {
                        perror("getcwd");
                    }
                } else {
                    perror("chdir");
                }
            } else {
                std::cerr << "HOME environment variable not set." << std::endl;
            }
            return false;
        } else if (path == "..") {
            // Change to the parent directory
            if (chdir("..") == 0) {
                if (getcwd(cwd, sizeof(cwd)) != nullptr) {
                    return true;
                } else {
                    perror("getcwd");
                }
            } else {
                perror("chdir");
            }
        }
        
        else if (path == "-"){
            if (chdir(initial_directory) == 0) {
            // Swap current and previous directories
            std::swap(cwd, initial_directory);
            return true;
        } else {
            perror("chdir");
            return false;
        }
        }
 
        
         else {
            if (chdir(path.c_str()) == 0) {
                if (getcwd(cwd, sizeof(cwd)) != nullptr) {
                    return true;
                } else {
                    perror("getcwd");
                }
            } else {
                perror("chdir");
            }
        }
        return false;
    }

    std::string getCurrentDirectory() const {
        return std::string(cwd);
    }

private:
    char initial_directory[100];
    char cwd[100];
};

#endif // CD_MODULE_H