#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include "quick_sort.h"
#include "merge_sort.h"
#include "radix_counting_sort.h"
#include "radix_quick_sort.h"

std::vector<std::string> readCSV(const std::string &fileName) {
    std::ifstream stream(fileName);

    std::vector<std::string> result;
    std::string line;

    while (std::getline(stream, line)) {
        result.push_back(line);
    }

    return result;
}

void writeCSV(const std::string &fileName, const std::vector<std::vector<double>>& data) {
    std::filesystem::create_directory("result");

    std::ofstream stream("result/" + fileName);

    auto header = { "size",
                    "data_random comparisons", "data_random time (ms)",
                    "data_descending comparisons", "data_descending time (ms)",
                    "data_almost_sorted comparisons", "data_almost_sorted time (ms)", };
    for (auto number : header) {
        stream << number << ",";
    }

    for (const auto& row : data) {
        for (auto number : row) {
            stream << number << ",";
        }

        stream << std::endl;
    }
}

int main() {
//    std::vector<std::string> data_random = {
//            "bbc",
//            "aldskjf;lsdjfsdlkfjf",
//            "tpoiueprotiuproit",
//            "vmnc,nvx,mcnv,xmnv,mcn,",
//            "aaaaaaaaaaaaaaa",
//            "fd",
//            "a;ldskf;alsdjf;lkdfsdfdffdfd",
//            "vmnc,nvx,sfsdffdfdff"
//    };

    std::vector<std::string> data_random = readCSV("data_random.csv");
    std::vector<std::string> data_descending = readCSV("data_descending.csv");
    std::vector<std::string> data_almost_sorted = readCSV("data_almost_sorted.csv");

    Strategy quick_sort = Strategy("quick_sort", [](std::vector<std::string> test) {
        // std::sort doesn't work on more than 16 elements with custom comparator for some reason :(
        std::sort(test.begin(), test.begin() + 16, Compare);
    });

    Strategy merge_sort = Strategy("merge_sort", [](std::vector<std::string> test) {
        std::stable_sort(test.begin(), test.end(), Compare);
    });

    Strategy string_quick_sort = Strategy("string_quick_sort", [](std::vector<std::string> test) {
        StringQuickSort(std::move(test));
    });

    Strategy string_merge_sort = Strategy("string_merge_sort", [](std::vector<std::string> test) {
        StringMergeSort(std::move(test));
    });

    Strategy radix_counting_sort = Strategy("radix_counting_sort", [](std::vector<std::string> test) {
        RadixCountingSort(test, 0, test.size(), 0);
    });

    Strategy radix_quick_sort = Strategy("radix_quick_sort", [](std::vector<std::string> test) {
        RadixQuickSort(std::move(test));
    });

    std::vector<Strategy> algorithm_strategies = {
            quick_sort,
            merge_sort,
            string_quick_sort,
            string_merge_sort,
            radix_counting_sort,
            radix_quick_sort
    };

    const int iterations = 20;
    for (const Strategy &strategy: algorithm_strategies) {
        std::vector<std::vector<double>> result = {};

        for (int size = 100; size <= 3000; size += 100) {
            result.push_back({(double) size});
            size_t index = result.size() - 1;

            for (const auto &data: {
                    std::vector(data_random.begin(), data_random.begin() + size),
                    std::vector(data_descending.begin(), data_descending.begin() + size),
                    std::vector(data_almost_sorted.begin(), data_almost_sorted.begin() + size)
            }) {
                size_t comparisons_sum = 0;
                double time_sum = 0;

                for (int i = 0; i < iterations; ++i) {
                    auto pair = TestAlgorithm(data, strategy);
                    comparisons_sum += pair.first;
                    time_sum += pair.second;
                }

                double comparisons_average = (double) comparisons_sum / iterations;
                double time_average = (double) time_sum / iterations;

                result[index].push_back(comparisons_average);
                result[index].push_back(time_average);
            }
        }

        writeCSV(strategy.name + ".csv", result);
    }

    return 0;
}
