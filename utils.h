#pragma once

#include <iostream>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>

static const int MIN_SIZE_FOR_MEDIAN_PIVOT = 50;
const int ALPHABET_POWER = 123;

class Strategy {
public:
    std::string name;
    std::function<void(std::vector<std::string> &)> algorithm;

    explicit Strategy(
            std::function<void(std::vector<std::string> &)> algorithm
    );
};

inline size_t comparisons;

int Compare(
        const std::string &a,
        const std::string &b
);

int LCP(
        const std::string &a,
        const std::string &b
);

std::pair<int, int> LcpCompare(
        const std::string &a,
        const std::string &b,
        int k
);

void TestAlgorithm(std::vector<std::string> input, const Strategy &strategy);