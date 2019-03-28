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
constexpr double zcrit = 2.58;
constexpr int num_bound = 676;
constexpr int password_length = 19;

namespace chrono = std::chrono;

double mean(const std::vector<int> & vals) {
    double sum = 0.0;
    for (int val : vals)
        sum += val;
    return sum / vals.size();
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
    // std::cout << "suffix: " << suffix << std::endl;

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
        //std::cout << pass << std::endl;
            
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

bool final_char(std::string prefix) {
    for (int i = 0; i < 26; i++) {
        std::string pass = prefix + (char) ('a' + i);
        if (check_password(pass)) {
            std::cout << "Password Cracked: " << pass << std::endl;
            return true;
        }
    }
    return false;
}

int main() {
    std::string prefix = "";
    for (int i = 0; i < password_length; i += 2) {
        if (i == password_length - 1) {
            if (final_char(prefix)) {
                std::cout << "Done" << std::endl;
                break;
            }
            else {
                std::cout << "Failed" << std::endl;
            }
        }
        prefix += crack_pair(prefix); 
    }
}
