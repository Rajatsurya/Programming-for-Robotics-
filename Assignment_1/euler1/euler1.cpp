#include <iostream>
#include <string>

int main() {
    unsigned long answer = 0;
    // --- Your code here
    for (int i = 0; i < 1000; i++) {
        // Check if the number is divisible by 3 or 5
        if (i % 3 == 0 || i % 5 == 0) {
            // Add the number to the answer
            answer += i;
        }
    }




    // ---
    std::cout << answer << std::endl;
    return 0;
}