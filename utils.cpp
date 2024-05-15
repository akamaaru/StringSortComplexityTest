#include <iostream>
#include <chrono>
#include <iomanip>
#include <utility>
#include <vector>
#include <string>
#include "utils.h"

Strategy::Strategy(std::function<void(std::vector<std::string> &)> algorithm) : algorithm(std::move(algorithm)) {
}

int Compare(
        const std::string &a,
        const std::string &b
) {
    const char *s1 = a.data();
    const char *s2 = b.data();

    ++comparisons;
    while (*s1 && (*s1 == *s2)) {
        ++s1;
        ++s2;
        ++comparisons;
    }

    return *(const unsigned char *) s1 - *(const unsigned char *) s2;
}

int LCP(
        const std::string &a,
        const std::string &b
) {
    const char *s1 = a.data();
    const char *s2 = b.data();
    int common_prefix_length = 0;

    ++comparisons;
    while (*s1 && (*s1 == *s2)) {
        ++s1;
        ++s2;
        ++comparisons;
        ++common_prefix_length;
    }

    return common_prefix_length;
}

std::pair<int, int> LcpCompare(
        const std::string &a,
        const std::string &b,
        int k
) {
    const char *s1 = a.data() + k;
    const char *s2 = b.data() + k;
    int common_prefix_length = k;

    ++comparisons;
    while (*s1 && (*s1 == *s2)) {
        ++s1;
        ++s2;
        ++comparisons;
        ++common_prefix_length;
    }

    return {
            *(const unsigned char *) s1 - *(const unsigned char *) s2,
            common_prefix_length
    };
}

void TestAlgorithm(std::vector<std::string> input, const Strategy &strategy) {
    comparisons = 0;

    auto start = std::chrono::high_resolution_clock::now();
    strategy.algorithm(input);
    auto finish = std::chrono::high_resolution_clock::now();
    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);

    std::cout << "Comparisons: " << comparisons << std::endl;
    std::cout << "Time:        "
              << std::setprecision(3) << std::fixed
              << (double) microseconds.count() / 1000 << " ms" << std::endl;
}
