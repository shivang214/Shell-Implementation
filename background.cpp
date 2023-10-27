#include "header.cpp"


void run_command(const std::string& command, bool background) {
    // Split the command into arguments
    std::vector<std::string> args;
    std::string token;
    std::istringstream iss(command);
    while (iss >> token) {
        args.push_back(token);
    }

    // Check if the command should run in the background
    if (background) {
        args.pop_back(); // Remove the '&' symbol
    }

    // Convert arguments to C-style array
    char* argv[args.size() + 1];
    for (size_t i = 0; i < args.size(); ++i) {
        argv[i] = const_cast<char*>(args[i].c_str());
    }
    argv[args.size()] = nullptr;

    pid_t pid;
    pid = fork();

    if (pid == 0) {
        // Child process
        if (execvp(argv[0], argv) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else if (pid > 0) {
        // Parent process
        if (!background) {
            // Wait for the child process to complete if not running in the background
            int status;
            waitpid(pid, &status, 0);
        } else {
            std::cout <<  "pid:"<<pid << std::endl;
        }
    } else {
        perror("fork");
    }
}