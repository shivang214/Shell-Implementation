#include "header.cpp"
using namespace std;
 
 void pwd() {

        char pwd[100];
        getcwd(pwd, 100);
        cout<<pwd << std::endl;
}