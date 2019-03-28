#include<iostream>

constexpr char secret_password[] = "elvishwordforfriend";

int main(int argc, char ** argv) {
    if (argc != 2) {
        std::cout << "Please enter the password" << std::endl;
        return 1;
    }
    std::string password = argv[1];

    if (password == secret_password)
        std::cout << "Access Granted" << std::endl;
    else
        std::cout << "Access Denied" << std::endl;
}
