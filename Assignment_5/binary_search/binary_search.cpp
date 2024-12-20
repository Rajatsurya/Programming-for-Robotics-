#include <cmath>
#include <fstream>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

// Iterative version of binary search; you should handle the case when the
// element is not in the sequence
template <typename T>
int iterativeBinarySearch(const std::vector<T>& vals, T key, int& numTimesCalled) {
    int left = 0;
    int right = vals.size() - 1;
    numTimesCalled = 0; // Reset counter

    while (left <= right) {
        numTimesCalled++;
        int mid = left + (right - left) / 2; // Find the middle index

        if (vals[mid] == key) {
            return mid; // Key found, return index
        } else if (vals[mid] < key) {
            left = mid + 1; // Search in the right half
        } else {
            right = mid - 1; // Search in the left half
        }
    }
    return -1; // Key not found
}

// Recursive version of binary search
template <typename T>
int recursiveBinarySearch(const std::vector<T>& vals, T key, int l, int r, int& numTimesCalled) {
    numTimesCalled++; // Increment each time function is called

    if (l > r) {
        return -1; // Key not found
    }

    int mid = l + (r - l) / 2;

    if (vals[mid] == key) {
        return mid; // Key found, return index
    } else if (vals[mid] < key) {
        return recursiveBinarySearch(vals, key, mid + 1, r, numTimesCalled); // Search right half
    } else {
        return recursiveBinarySearch(vals, key, l, mid - 1, numTimesCalled); // Search left half
    }
}

int main() {
    std::ifstream input{"input.txt"};
    std::ofstream output{"output.txt"};

    std::string line;

    while (input.peek() != EOF) {
        std::vector<int> nums;
        int num;
        while ((input.peek() != '\n') && (input >> num)) {
            nums.push_back(num);
        }
        if (input.peek() == '\n') {
            input.get();
        }
        int lookup;
        input >> lookup;
        if (input.peek() == '\n') {
            input.get();
        }

        int numIterativeCalled = 0;
        int numRecursiveCalled = 0;

        int indexIterative = iterativeBinarySearch(nums, lookup, numIterativeCalled);
        int indexRecursive = recursiveBinarySearch(nums, lookup, 0, nums.size() - 1, numRecursiveCalled);

        if (indexIterative != indexRecursive) {
            output << "inconsistent indices found via iterative and recursive binary search\n";
        }

        if (indexIterative == -1) {
            output << "ERROR" << std::endl;
        } else {
            output << indexIterative << ' ' << numIterativeCalled << ' ' << numRecursiveCalled << std::endl;
        }
    }
}
