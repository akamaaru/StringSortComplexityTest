#include <string>
#include <vector>
#include "utils.h"

using LcpVector = std::vector<std::pair<std::string, int>>;

LcpVector StringMerge(
        LcpVector P,
        LcpVector Q
) {
    LcpVector R = {};
    size_t i, j;
    i = j = 0;

    while (i < P.size() and j < Q.size()) {
        if (P[i].second > Q[j].second) {
            R.push_back(P[i]);
            ++i;
            ++comparisons;
        } else if (P[i].second < Q[j].second) {
            R.push_back(Q[j]);
            ++j;
            ++comparisons;
        } else {
            std::pair<int, int> comparedResult =
                    LcpCompare(P[i].first, Q[j].first, P[i].second);

            if (comparedResult.first < 0) {
                R.push_back(P[i]);
                ++i;
                Q[j].second = comparedResult.second;
                ++comparisons;
            } else {
                R.push_back(Q[j]);
                ++j;
                P[i].second = comparedResult.second;
                ++comparisons;
            }
        }
    }

    while (i < P.size()) {
        R.push_back(P[i]);
        ++i;
        ++comparisons;
    }

    while (j < Q.size()) {
        R.push_back(Q[j]);
        ++j;
        ++comparisons;
    }

    return R;
}

LcpVector StringMergeSort(std::vector<std::string> R) {
    if (R.empty()) {
        return {};
    }

    if (R.size() == 1) {
        return {{R[0], 0}};
    }

    int m = (int) (R.size() / 2);
    auto P = StringMergeSort(std::vector<std::string>(R.begin(), R.begin() + m));
    auto Q = StringMergeSort(std::vector<std::string>(R.begin() + m + 1, R.end()));

    return StringMerge(P, Q);
}