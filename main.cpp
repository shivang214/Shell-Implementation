#include "header.cpp"
#include "ls.cpp"
#include "host.cpp"
#include "pwd.cpp"
#include "echo.cpp"
#include "pinfo.cpp"
#include "search.cpp"
#include "cd.cpp"
#include "signals.cpp"
#include "pipe.cpp"
#include "redir.cpp"
// #include "history.cpp"

// #include "background.cpp"





char *username = getenv("USER");
// void tabAutoComplete();

int main(int argc, char *argv[])
{
    std::string input;
     CdModule cdModule;
    //  CommandShell shell;
    signal(SIGTSTP, handleCtrlZ);
    signal(SIGINT, handleCtrlC);
    while (input != "exit")
    {
        char pwd2[100];
        std::cout << username << "@" << hostname() << ":~" << getcwd(pwd2, 100)<<"~>";

        getline(cin, input);

        char cstrInput[1000];
        strcpy(cstrInput, input.c_str());

     
    char * multitoken=strtok(cstrInput,";");
            std::vector<std::string> multitokens;

    while(multitoken!=NULL)
    {

        while (multitoken != nullptr) 
        {
            multitokens.emplace_back(multitoken);
            multitoken = strtok(nullptr, ";");
        }
    }
   

    for(int i=0;i<multitokens.size();i++)
    {
        char* token = strtok(cstrInput, " \t");
        std::vector<std::string> tokens;
        

        while (token != nullptr) 
        {
            tokens.emplace_back(token);
            token = strtok(nullptr, " ");
        }

        if (tokens.empty()) 
        {
            continue;
        }

        if (tokens[i] == "ls") {
            new_list(tokens);
            // shell.addToHistory(input);
        }

        else if (tokens[i] == "user") {
            cout << username;
            // shell.addToHistory(input);
 
        }
        else if (tokens[i] == "host") {
            cout << hostname();
            // shell.addToHistory(input);

        }
        else if (tokens[i] == "pwd") {
            pwd();
            // shell.addToHistory(input);

        }
        else if (tokens[i].substr(0, 4) == "echo") {
            echo(input);
            // shell.addToHistory(input);

        }
        else if (tokens[i] == "pinfo") {
            pinfo();
            // shell.addToHistory(input);
   
            
        }
       else if (tokens[i] == "search") {
        // shell.addToHistory(input);

    if (tokens.size() >= 2) {
        std::string targetName = tokens[1];
        std::string currentDir = "."; // You can change this to the desired search directory

        bool exists = searchFileOrFolderRecursively(currentDir, targetName);

        if (exists) {
            std::cout << "True" << std::endl;
        } else {
            std::cout << "False" << std::endl;
        }
    } else {
        std::cout << "Provide correct input" << std::endl;
    }
}
// else if(input.back()=='&'){
// bool run_in_background = (input.back() == '&');
//         run_command(input, run_in_background);
// }


        else if (tokens[i] == "cd") {
            // shell.addToHistory(input);

            if (tokens.size() == 2) {
                if (cdModule.changeDirectory(tokens[1])) {
                    std::cout << cdModule.getCurrentDirectory() << std::endl;
                }
            } else {
                std::cout << "Error" << std::endl;
            }
        }

        else if(input.find("|")){
            // shell.addToHistory(input);
            execute_pipeline(input);

        }





    if (!std::getline(std::cin, input)) {
            // If getline returns false (CTRL-D), log out of the shell
            handleCtrlD(0);
        }

    else if(input.find("<")) {
        // shell.addToHistory(input);
        handle_input_redirection(input);
        execute_command(input);
       

    }


    else if(input.find(">")) {
        // shell.addToHistory(input);
        handle_output_redirection(input,true);
        execute_command(input);

    }


    else if(tokens[i] == "exit"){
        // shell.addToHistory(input);
        close(1);
 
    }
    else if (!std::getline(std::cin, input)) {
            // If getline returns false (CTRL-D), log out of the shell
            handleCtrlD(0);
        }

 
//  else if (tokens[i] == "history") {
//     // shell.addToHistory(input);

//     // shell.displayHistory();
    

//     }
    else {
    

    // Convert the input string to a C-style string for execv
    char* cstrInput = (char*)input.c_str();

    // Tokenize the input string to separate the command and its arguments
    char* token = strtok(cstrInput, " \t");

    // Create a vector to hold the command and its arguments
    std::vector<char*> args;

    while (token != nullptr) {
        args.push_back(token);
        token = strtok(nullptr, " \t");
    }

    if (args.empty()) {
        continue;
    }

    // Make sure the vector is null-terminated for execv
    args.push_back(nullptr);

    // Attempt to execute the command using execv
    if (execv(args[0], &args[0]) == -1) {
        // If execv fails, it will return -1
        // Handle the case where execv fails
        perror("execv");
        exit(1); // Exit the child process with an error code
    }
}


        std::cout << std::endl;


        
    }


    }
   
        
    return 0;
}








