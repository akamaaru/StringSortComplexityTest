#pragma once

#include <string>
#include <vector>
#include "utils.h"

using LcpVector = std::vector<std::pair<std::string, int>>;

LcpVector StringMerge(
        LcpVector P,
        LcpVector Q
);

LcpVector StringMergeSort(std::vector<std::string> R);