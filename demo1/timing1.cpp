#include <iostream>
#include <string>
#include <chrono>


#include "secret.h"

constexpr int iters = 10;
namespace chrono = std::chrono;

int main() {
    std::string pass_a = "elvishwordforfrienb";
    std::string pass_b = "alvishwordforfriend";
    for (int i = 0; i < iters; i++) {
        auto start = chrono::steady_clock::now();
        check_password(pass_a);
        auto end = chrono::steady_clock::now();
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
        std::cout << duration.count() << " ns" << std::endl;
    }
}
