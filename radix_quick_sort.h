#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include "utils.h"
#include "quick_sort.h"

std::vector<std::vector<std::string>> SegregatedCountingSort(std::vector<std::string> R, int L);

std::vector<std::string> RadixQuickSort(std::vector<std::string> R, int L = 0);

