#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <sstream>


#include "secret.h"

constexpr int iters = 10000000;
constexpr int inner_iters = 100;
constexpr int warm_up = 500;
constexpr double zcrit = 2.58;
constexpr double trim_percentage = 0.1;
constexpr int num_bound = 676;
constexpr int password_length = 21;

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

std::string get_pair_from_num(int num) {
    std::stringstream ss;
    ss << (char) ('a' + (num / 26));
    ss << (char) ('a' + (num % 26));
    return ss.str();
}

std::string crack_pair(std::string prefix) {
    std::string suffix;
    for (int i = 0; i < password_length - prefix.size() - 2; i++) {
        suffix += "-";
    }
    std::cout << "suffix: " << suffix << std::endl;

    // Initialize random stuff
    std::random_device rd;
    std::default_random_engine random(rd());
    std::uniform_int_distribution<int> dist(0, num_bound - 1);

    std::vector<std::vector<int> > times;
    for (int i = 0; i < num_bound; i++)
        times.emplace_back();

    for (int i = 0; i < iters; i++) {
        int choice = dist(random);
        std::string pass = prefix + get_pair_from_num(choice) + suffix;
        std::cout << pass << std::endl;
            
        auto start = chrono::steady_clock::now();
        check_password(pass);
        auto end = chrono::steady_clock::now();
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
        times.at(choice).push_back(duration.count());
    }

    double max_mean = -1.0;
    int max_num = -1;
    int current_num = 0;
    for (const auto& time_list : times) {
        double current_mean = mean(time_list);
        if (current_mean > max_mean) {
            max_mean = current_mean;
            max_num = current_num;
        }
        current_num++;
    }
    std::string max_pair = get_pair_from_num(max_num);
    std::cout << "Max pair is: " << max_pair << std::endl;
    
    return max_pair;
}

int main() {
    std::string prefix = "";
    for (int i = 0; i < password_length; i += 2) {
        prefix += crack_pair(prefix); 
    }
    std::cout << "Final password: " << prefix << std::endl;
}
