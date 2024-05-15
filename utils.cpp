#include <iostream>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>

static const int MIN_SIZE_FOR_MEDIAN_PIVOT = 50;

class Strategy {
public:
    std::string name;
    std::function<void(std::vector<std::string> &)> algorithm;

    explicit Strategy(
            std::function<void(std::vector<std::string> &)> algorithm
    ) : algorithm(std::move(algorithm)) {
    }
};

size_t comparisons;

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