#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include "quick_sort.h"
#include "merge_sort.h"
#include "radix_counting_sort.h"
#include "radix_quick_sort.h"

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

    Strategy quick_sort = Strategy([](std::vector<std::string> test) {
        std::sort(test.begin(), test.end(), Compare);
    });

    Strategy merge_sort = Strategy([](std::vector<std::string> test) {
        std::stable_sort(test.begin(), test.end(), Compare);
    });

    Strategy string_quick_sort = Strategy([](std::vector<std::string> test) {
        StringQuickSort(std::move(test));
    });

    Strategy string_merge_sort = Strategy([](std::vector<std::string> test) {
        StringMergeSort(std::move(test));
    });

    Strategy radix_counting_sort = Strategy([](std::vector<std::string> test) {
        RadixCountingSort(test, 0, test.size(), 0);
    });

    Strategy radix_quick_sort = Strategy([](std::vector<std::string> test) {
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

    for (const Strategy &strategy: algorithm_strategies) {
        TestAlgorithm(test, strategy);
    }

    return 0;
}
