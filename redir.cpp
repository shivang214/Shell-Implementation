#include "header.cpp"


bool handle_input_redirection(std::string& command) {
    int  pos = command.find("<");
    if (pos != std::string::npos) {
        std::string input_file = command.substr(pos + 1);
        input_file.erase(0, input_file.find_first_not_of(" \t\n\r\f\v")); // Remove leading whitespace
        input_file.erase(input_file.find_last_not_of(" \t\n\r\f\v") + 1); // Remove trailing whitespace
        std::ifstream input(input_file);
        if (!input.is_open()) {
            std::cerr << "Error: Input file '" << input_file << "' does not exist." << std::endl;
            return false;
        }
        std::cin.rdbuf(input.rdbuf()); // Redirect stdin
        command = command.substr(0, pos);
    }
    return true;
}




bool handle_output_redirection(std::string& command, bool append = false) {
    size_t pos = command.find(">");
    if (pos != std::string::npos) {
  

        std::string output_file = command.substr(pos + 1);
        output_file = output_file.substr(output_file.find_first_not_of(" \t\n\r\f\v"));
        
      
        std::ios_base::openmode open_mode = std::ios::out;
        if (append) {
            open_mode |= std::ios::app;
        }
        
        
        std::ofstream output(output_file, open_mode);
        if (!output.is_open()) {
            std::cerr << "Error: Cannot open output file '" << output_file << "'." << std::endl;
            return false;
        }
        

        std::cout.rdbuf(output.rdbuf());
        
        
        command = command.substr(0, pos) + " " + output_file;
    }
    return true;
}



// Function to execute a command
void execute_command(const std::string& command) {
    system(command.c_str());
}

