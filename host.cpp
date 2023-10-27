#include "header.cpp"

std::string hostname(){
    char hostname[256];
    if(gethostname(hostname, sizeof(hostname))==-1){
        perror("gethostname");
        return nullptr;
    }

    return (hostname);
}
