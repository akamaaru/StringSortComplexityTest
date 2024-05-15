#include <iostream>
#include <chrono>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <iomanip>

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

int counting_comparator(
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

void test_algorithm(std::vector<std::string> input, const Strategy &strategy) {
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

std::vector<std::string> TernaryQuickSort(std::vector<std::string> R, int L = 0) {
    if (R.size() <= 1) {
        return R;
    }

    std::vector<std::string> R_excl;
    for (auto it = R.begin(); it != R.end();) {
        if (it->size() == L) {
            R_excl.push_back(*it);
            it = R.erase(it);
        } else {
            ++it;
        }
    }

    std::string pivot = R[R.size() / 2];

    std::vector<std::string> R_less, R_equal, R_great;
    for (const auto &element: R) {
        int comparator = counting_comparator(element, pivot);
        if (comparator < 0) {
            R_less.push_back(element);
        } else if (comparator > 0) {
            R_great.push_back(element);
        } else {
            R_equal.push_back(element);
        }
    }

    R_less = TernaryQuickSort(R_less, L);
    R_equal = TernaryQuickSort(R_equal, L + 1);
    R_great = TernaryQuickSort(R_great, L);

    for (std::vector<std::string> vector: {R_less, R_equal, R_great}) {
        R_excl.insert(R_excl.end(), vector.begin(), vector.end());
    }

    return R_excl;
}

int main() {
    std::vector<std::string> test = {
            "bbc",
            "aldskjf;lsdjfsdlkfjf",
            "tpoiueprotiuproit",
            "vmnc,nvx,mcnv,xmnv,mcn,",
            "aaaaaaaaaaaaaaa",
            "fd",
            "a;ldskf;alsdjf;lkdfsdfdffdfd",
            "vmnc,nvx,sfsdffdfdff"
    };

    Strategy quicksort = Strategy([](std::vector<std::string> test) {
        std::sort(test.begin(), test.end(), counting_comparator);
    });

    Strategy mergesort = Strategy([](std::vector<std::string> test) {
        std::stable_sort(test.begin(), test.end(), counting_comparator);
    });

    Strategy string_quicksort = Strategy([](std::vector<std::string> test) {
        TernaryQuickSort(std::move(test));
    });

    Strategy string_mergesort = Strategy([](std::vector<std::string> test) {

    });

    std::vector<Strategy> algorithm_strategies = {
            quicksort,
            mergesort,
            string_quicksort
    };

    for (const Strategy &strategy: algorithm_strategies) {
        test_algorithm(test, strategy);
    }

    return 0;
}
