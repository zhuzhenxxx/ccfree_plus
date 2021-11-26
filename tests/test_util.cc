#include "ccfree/ccfree.h"
#include <assert.h>

ccfree::Logger::ptr g_logger = CCFREE_LOG_ROOT();

void test_assert() {
    CCFREE_LOG_INFO(g_logger) << ccfree::BacktraceToString(10);
    //CCFREE_ASSERT2(0 == 1, "abcdef xx");
}

int main(int argc, char** argv) {
    test_assert();

    int arr[] = {1,3,5,7,9,11};

    CCFREE_LOG_INFO(g_logger) << ccfree::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 0);
    CCFREE_LOG_INFO(g_logger) << ccfree::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 1);
    CCFREE_LOG_INFO(g_logger) << ccfree::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 4);
    CCFREE_LOG_INFO(g_logger) << ccfree::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 13);
    CCFREE_ASSERT(ccfree::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 0) == -1);
    CCFREE_ASSERT(ccfree::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 1) == 0);
    CCFREE_ASSERT(ccfree::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 2) == -2);
    CCFREE_ASSERT(ccfree::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 3) == 1);
    CCFREE_ASSERT(ccfree::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 4) == -3);
    CCFREE_ASSERT(ccfree::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 5) == 2);
    CCFREE_ASSERT(ccfree::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 6) == -4);
    CCFREE_ASSERT(ccfree::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 7) == 3);
    CCFREE_ASSERT(ccfree::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 8) == -5);
    CCFREE_ASSERT(ccfree::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 9) == 4);
    CCFREE_ASSERT(ccfree::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 10) == -6);
    CCFREE_ASSERT(ccfree::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 11) == 5);
    CCFREE_ASSERT(ccfree::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 12) == -7);
    return 0;
}
