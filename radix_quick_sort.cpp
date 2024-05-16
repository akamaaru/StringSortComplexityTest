#include <string>
#include <vector>
#include "radix_quick_sort.h"

std::vector<std::vector<std::string>> SegregatedCountingSort(std::vector<std::string> R, int L) {
    std::vector<std::vector<std::string>> result(ALPHABET_POWER);
    for (std::string str: R) {
        ++comparisons;
        result[str[L]].push_back(str);
    }

    return result;
}

std::vector<std::string> RadixQuickSort(std::vector<std::string> R, int L) {
    if (R.size() < ALPHABET_POWER) {
        ++comparisons;
        return StringQuickSort(R, L);
    }

    std::vector<std::string> R_excl;
    for (auto it = R.begin(); it != R.end();) {
        ++comparisons;
        if (it->size() == L) {
            R_excl.push_back(*it);
            it = R.erase(it);
        } else {
            ++it;
        }
    }

    auto R_rest = SegregatedCountingSort(R, L);
    for (std::vector<std::string> vector: R_rest) {
        ++comparisons;
        R_excl.insert(R_excl.end(), vector.begin(), vector.end());
    }

    return R_excl;
}
