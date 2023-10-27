// signals.hpp
#ifndef SIGNALS_HPP
#define SIGNALS_HPP

#include <csignal>
#include <iostream>
#include <cstdlib>
#include <unistd.h>

void handleCtrlZ(int signum) {
    std::cout << "\nCTRL-Z pressed. Stopping the current foreground process.\n";

    killpg(getpgrp(), SIGSTOP);
}

void handleCtrlC(int signum) {
    std::cout << "\nCTRL-C pressed. Interrupting the current foreground process.\n";
 
    killpg(getpgrp(), SIGINT);
}

void handleCtrlD(int signum) {
    std::cout << "\nCTRL-D pressed. Logging out of the shell.\n";
 
    exit(0);
}

#endif // SIGNALS_HPP
