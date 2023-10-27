#include "header.cpp"
using namespace std;





// void echo(string input) {
  
//     string output = input.substr(5);
//     int first_quote = output.find('"');
//     int last_quote = output.rfind('"');
    
//     if (first_quote != string::npos && last_quote != string::npos) {
//         output = output.substr(first_quote + 1, last_quote - first_quote - 1);
//     }
    
//     cout << output << endl;
// }

void echo(string input) {
    // Remove leading and trailing quotes from the output
    string output = input.substr(5);
    int first_quote = output.find('"');
    int last_quote = output.rfind('"');
    
    if (first_quote != string::npos && last_quote != string::npos) {
        output = output.substr(first_quote + 1, last_quote - first_quote - 1);
    }

    // Remove extra spaces from the output
    string cleaned_output;
    bool previous_space = false;
    for (char c : output) {
        if (!isspace(c)) {
            cleaned_output += c;
            previous_space = false;
        } else {
            if (!previous_space) {
                cleaned_output += ' ';
            }
            previous_space = true;
        }
    }

    cout << cleaned_output << endl;
}





