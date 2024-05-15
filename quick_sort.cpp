#include <unordered_set>
#include <string>
#include <vector>
#include <algorithm>
#include "utils.cpp"

std::string MedianOfThree(
        const std::string &a,
        const std::string &b,
        const std::string &c
) {
    if (Compare(a, b) < 0) {
        // partial order = a,b
        if (Compare(b, c) < 0) {
            // 2 comparisons: order is a,b,c
            return b;
        }

        // order is a,c,b or c,a,b
        if (Compare(a, c) < 0) {
            // order is a,c,b -- 3 comparisons
            return c;
        }

        // order is c,a,b -- 3 comparisons
        return a;
    }

    // partial order = b,a
    if (Compare(c, b) < 0) {
        // 2 comparisons: order is c,b,a
        return b;
    }

    // order is b,c,a or b,a,c
    if (Compare(c, a) > 0) {
        // order is b,a,c -- 3 comparisons
        return a;
    }

    // order is b,c,a -- 3 comparisons
    return c;
}

std::string ChoosePivot(const std::vector<std::string> &R) {
    std::string pivot;
    if (R.size() < MIN_SIZE_FOR_MEDIAN_PIVOT) {
        pivot = R[R.size() / 2];
    } else {
        std::unordered_set<size_t> indices;
        while (indices.size() < 3) {
            // TODO switch to std::uniform_int_distribution
            indices.emplace(rand() % R.size());
        }

        size_t first = *std::next(indices.begin(), 0);
        size_t second = *std::next(indices.begin(), 1);
        size_t third = *std::next(indices.begin(), 2);

        pivot = MedianOfThree(R[first], R[second], R[third]);
    }

    return pivot;
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

    std::string pivot = ChoosePivot(R);

    std::vector<std::string> R_less, R_equal, R_great;
    for (const auto &element: R) {
        int comparedResult = Compare(element, pivot);
        if (comparedResult < 0) {
            R_less.push_back(element);
        } else if (comparedResult > 0) {
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