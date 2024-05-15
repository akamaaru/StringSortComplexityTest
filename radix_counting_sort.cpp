#include <string>
#include <vector>
#include <algorithm>
#include "radix_counting_sort.h"

void RadixCountingSort(std::vector <std::string> &R, int low, int high, int place) {
    if (high <= low) {
        ++comparisons;
        return;
    }

    std::vector<int> C(ALPHABET_POWER + 2, 0);
    std::unordered_map<int, std::string> temp;

    for (int i = low; i < high; ++i) {
        ++comparisons;
        ++C[R[i][place] + 2];
    }

    for (int i = 0; i < ALPHABET_POWER + 1; ++i) {
        ++comparisons;
        C[i + 1] += C[i];
    }

    for (int i = low; i < high; ++i) {
        ++comparisons;
        temp[C[(R[i][place] + 1)]++] = R[i];
    }

    for (int i = low; i < high; ++i) {
        ++comparisons;
        R[i] = temp[i - low];
    }

    for (int i = 0; i < ALPHABET_POWER; ++i) {
        ++comparisons;
        RadixCountingSort(R, low + C[i], low + C[i + 1] - 1, place + 1);
    }
}
