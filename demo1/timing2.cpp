#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>


#include "secret.h"

constexpr int iters = 1000;
constexpr int warm_up = 500;
constexpr double zcrit = 2.58;
constexpr double trim_percentage = 0.1;
namespace chrono = std::chrono;

void trim(std::vector<int> & vals) {
    std::sort(vals.begin(), vals.end());
    int num_drop = vals.size() * trim_percentage;
    vals.erase(vals.begin(), vals.begin() + num_drop);
    vals.erase(vals.end() - num_drop, vals.end());
}

double mean(const std::vector<int> & vals) {
    double sum = 0.0;
    for (int val : vals)
        sum += val;
    return sum / vals.size();
}

double stdev(const std::vector<int> & vals) {
    double sample_mean = mean(vals);
    double sum_squared_diff = 0.0;
    for (int val : vals)
        sum_squared_diff += (val - sample_mean) * (val - sample_mean);
    return sqrt(sum_squared_diff / (vals.size() - 1));
}

std::pair<double, double> ci(const std::vector<int> & vals) {
    double sample_mean = mean(vals);
    double sample_stdev = stdev(vals);
    double standard_error = sample_stdev / sqrt(vals.size());
    double lower_bound = sample_mean - zcrit * standard_error;
    double upper_bound = sample_mean + zcrit * standard_error;
    return std::make_pair(lower_bound, upper_bound);
}

int main() {
    std::string pass_a = "edvishwordforfriend";
    std::string pass_b = "edvishwordforfriend";
    std::vector<int> times_a;
    std::vector<int> times_b;

    // Initialize random stuff
    std::random_device rd;
    std::default_random_engine random(rd());
    std::uniform_int_distribution<int> dist(1,2);

    for (int i = 0; i < iters; i++) {
        int choice = dist(random);
        std::string pass;
        if (choice == 1)
            pass = pass_a;
        else
            pass = pass_b;
            
        auto start = chrono::steady_clock::now();
        check_password(pass);
        auto end = chrono::steady_clock::now();
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
        if (choice == 1)
            times_a.push_back(duration.count());
        else
            times_b.push_back(duration.count());
    }
    // // Skip warm-up
    // times_a.erase(times_a.begin(), times_a.begin() + warm_up);
    // times_b.erase(times_b.begin(), times_b.begin() + warm_up);
    // Trim the data
    trim(times_a);
    trim(times_b);

    // Compute and print statistics
    std::cout << "Mean A: " << mean(times_a) << std::endl;
    std::cout << "StDev A: " << stdev(times_a) << std::endl;
    auto ci_a = ci(times_a);
    std::cout << "99% CI (" << ci_a.first << ", " << ci_a.second << ")" << std::endl;
    std::cout << "Mean B: " << mean(times_b) << std::endl;
    std::cout << "StDev B: " << stdev(times_b) << std::endl;
    auto ci_b = ci(times_b);
    std::cout << "99% CI (" << ci_b.first << ", " << ci_b.second << ")" << std::endl;
}
