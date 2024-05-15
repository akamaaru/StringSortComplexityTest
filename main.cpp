#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include "quick_sort.h"
#include "merge_sort.h"

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
        std::sort(test.begin(), test.end(), Compare);
    });

    Strategy mergesort = Strategy([](std::vector<std::string> test) {
        std::stable_sort(test.begin(), test.end(), Compare);
    });

    Strategy string_quicksort = Strategy([](std::vector<std::string> test) {
        StringQuickSort(std::move(test));
    });

    Strategy string_mergesort = Strategy([](std::vector<std::string> test) {
        StringMergeSort(std::move(test));
    });

    std::vector<Strategy> algorithm_strategies = {
            quicksort,
            mergesort,
            string_quicksort,
            string_mergesort
    };

    for (const Strategy &strategy: algorithm_strategies) {
        TestAlgorithm(test, strategy);
    }

    return 0;
}
