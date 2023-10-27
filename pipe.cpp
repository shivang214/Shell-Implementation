#include "help_pipe.cpp"
#include "header.cpp"

int execute_pipeline(const std::string& input) {
    std::vector<std::string> commands;
    std::istringstream iss(input);
    std::string token;

    // Split the input string by '|'
    while (std::getline(iss, token, '|')) {
        commands.push_back(token);
    }

    int input_fd = 0; // Initialize input file descriptor to 0 (stdin)

    for (size_t i = 0; i < commands.size(); ++i) {
        int output_fd = (i == commands.size() - 1) ? 1 : -1;
        std::vector<std::string> args;
        std::string command = commands[i];

        // Trim leading and trailing whitespaces
        size_t start = command.find_first_not_of(" ");
        size_t end = command.find_last_not_of(" ");
        command = command.substr(start, end - start + 1);

        // Create a pipe for commands except the last one
        int pipe_fds[2];
        if (i < commands.size() - 1) {
            if (pipe(pipe_fds) == -1) {
                std::cerr << "Pipe creation failed" << std::endl;
                return 1;
            }
            output_fd = pipe_fds[1]; // Output of the current command is the write end of the pipe
        }

        // Tokenize the command into arguments
        char* token = strtok(const_cast<char*>(command.c_str()), " ");
        while (token != nullptr) {
            args.push_back(token);
            token = strtok(nullptr, " ");
        }

        // Execute the command
        pid_t pid = fork();

        if (pid < 0) {
            std::cerr << "Fork failed" << std::endl;
            return -1;
        } else if (pid == 0) {
            // Child process

            if (input_fd != 0) {
                dup2(input_fd, STDIN_FILENO);
                close(input_fd);
            }

            if (output_fd != 1) {
                dup2(output_fd, STDOUT_FILENO);
                close(output_fd);
            }

            // Convert vector<string> to char* array
            std::vector<char*> argv;
            for (const std::string& arg : args) {
                argv.push_back(const_cast<char*>(arg.c_str()));
            }
            argv.push_back(nullptr);

            execvp(argv[0], argv.data());

            std::cerr << "Execution failed for command: " << args[0] << std::endl;
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            int status;
            waitpid(pid, &status, 0);

            if (input_fd != 0) {
                close(input_fd);
            }

            if (i < commands.size() - 1) {
                close(pipe_fds[1]); // Close write end of the pipe
                input_fd = pipe_fds[0]; // Input of the next command is the read end of the pipe
            }

            if (status != 0) {
                std::cerr << "Command failed with exit code: " << status << std::endl;
                return status;
            }
        }
    }

    return 0;
}
