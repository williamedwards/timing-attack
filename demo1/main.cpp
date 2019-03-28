#include <iostream>
#include <chrono>
#include <thread>

constexpr char secret_password[] = "elvishwordforfriend";

int main(int argc, char ** argv) {
    std::string password_input;

    while (std::getline(std::cin, password_input)) {
        if (password_input == secret_password)
            std::cout << "Access Granted" << std::endl;
        else
            std::cout << "Access Denied" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
