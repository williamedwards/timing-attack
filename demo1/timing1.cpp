#include <iostream>
#include <string>
#include <chrono>
#include <vector>


#include "secret.h"

constexpr int iters = 10;
namespace chrono = std::chrono;

double mean(const std::vector<int> & vals) {
    double sum = 0.0;
    for (int val : vals)
        sum += val;
    return sum / vals.size();
}

int main() {
    std::string pass_a = "elvishwordforfrienb";
    std::string pass_b = "alvishwordforfriend";
    std::vector<int> times_a;
    std::vector<int> times_b;
    for (int i = 0; i < iters; i++) {
        auto start = chrono::steady_clock::now();
        check_password(pass_a);
        auto end = chrono::steady_clock::now();
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
        times_a.push_back(duration.count());

        start = chrono::steady_clock::now();
        check_password(pass_b);
        end = chrono::steady_clock::now();
        duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
        times_b.push_back(duration.count());
    }
    std::cout << "Mean A: " << mean(times_a) << std::endl;
    std::cout << "Mean B: " << mean(times_b) << std::endl;
}
