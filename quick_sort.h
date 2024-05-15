#pragma once

#include <unordered_set>
#include <string>
#include <vector>
#include <algorithm>
#include "utils.h"

std::string MedianOfThree(
        const std::string &a,
        const std::string &b,
        const std::string &c
);

std::string ChoosePivot(const std::vector<std::string> &R);

std::vector<std::string> StringQuickSort(std::vector<std::string> R, int L = 0);
