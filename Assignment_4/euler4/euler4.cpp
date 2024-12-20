#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>


bool isPalindrome(unsigned long number) {
    std::string str = std::to_string(number); // Convert number to string
    std::string reversed_str = str;
    std::reverse(reversed_str.begin(), reversed_str.end()); // Reverse the string
    return str == reversed_str; // Check if original and reversed are the same
}

int main() {
    unsigned long largest_palandrome{0};

    // Iterate through all pairs of 3-digit numbers
    for (int i = 999; i >= 100; --i) {
        for (int j = i; j >= 100; --j) { // Start from 'i' to avoid redundant checks
            unsigned long product = i * j;

            // Check if the product is a palindrome
            if (isPalindrome(product)) {
                // Update largest palindrome if the current one is larger
                if (product > largest_palandrome) {
                    largest_palandrome = product;
                }
            }
        }
    }

    std::cout << largest_palandrome << std::endl;
    return 0;
}