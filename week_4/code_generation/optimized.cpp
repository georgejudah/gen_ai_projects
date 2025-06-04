#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <limits>

using namespace std;

// Linear Congruential Generator implementation
class LCG {
    uint64_t a = 1664525;
    uint64_t c = 1013904223;
    uint64_t m = static_cast<uint64_t>(1) << 32;
    uint64_t value;

public:
    LCG(uint64_t seed) : value(seed) {}

    uint64_t next() {
        value = (a * value + c) % m;
        return value;
    }
};

// Function to calculate maximum subarray sum
int64_t max_subarray_sum(int n, uint64_t seed, int min_val, int max_val) {
    LCG lcg_gen(seed);
    vector<int> random_numbers(n);
    int range = max_val - min_val + 1;

    // Generate random numbers
    for (int i = 0; i < n; ++i) {
        random_numbers[i] = lcg_gen.next() % range + min_val;
    }

    // Calculate maximum subarray sum with Kadane's algorithm
    int64_t max_sum = numeric_limits<int64_t>::min();
    int64_t current_sum = 0;

    for (int i = 0; i < n; ++i) {
        current_sum += random_numbers[i];
        if (current_sum > max_sum) {
            max_sum = current_sum;
        }
        if (current_sum < 0) {
            current_sum = 0;
        }
    }

    return max_sum;
}

// Function to calculate total max subarray sum over 20 runs
int64_t total_max_subarray_sum(int n, uint64_t initial_seed, int min_val, int max_val) {
    int64_t total_sum = 0;
    LCG lcg_gen(initial_seed);

    for (int i = 0; i < 20; ++i) {
        uint64_t seed = lcg_gen.next();
        total_sum += max_subarray_sum(n, seed, min_val, max_val);
    }

    return total_sum;
}

int main() {
    int n = 10000;                  // Number of random numbers
    uint64_t initial_seed = 42;     // Initial seed for the LCG
    int min_val = -10;              // Minimum value of random numbers
    int max_val = 10;               // Maximum value of random numbers

    auto start_time = chrono::high_resolution_clock::now();
    int64_t result = total_max_subarray_sum(n, initial_seed, min_val, max_val);
    auto end_time = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed_time = end_time - start_time;

    cout << "Total Maximum Subarray Sum (20 runs): " << result << endl;
    cout << "Execution Time: " << elapsed_time.count() << " seconds" << endl;

    return 0;
}
