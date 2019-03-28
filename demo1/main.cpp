#include <iostream>
#include <chrono>
#include <thread>

#include "secret.h"


int main(int argc, char ** argv) {
    std::string password_input;

    while (std::getline(std::cin, password_input)) {
        if (check_password(password_input))
            std::cout << "Access Granted" << std::endl;
        else
            std::cout << "Access Denied" << std::endl;
    }
}
