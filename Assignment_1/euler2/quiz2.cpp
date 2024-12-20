#include <iostream>
#include <vector>

int main() {
    int a = 1;   // First Fibonacci number
    int b = 2;   // Second Fibonacci number
    std::vector<int> fib;  // Vector to store Fibonacci numbers

    fib.push_back(a);  // Add first Fibonacci number
    fib.push_back(b);  // Add second Fibonacci number

    // Generate Fibonacci numbers and store them in the vector
    while (b < 2000000000) {
        int next = a + b;
        a = b;
        b = next;
        fib.push_back(next);  // Save the Fibonacci number in the vector
    }

    // Find the index of the largest Fibonacci number less than 2 billion
    int index = fib.size() - 2; // Since the last one exceeds 2 billion, the second last one is the largest

    // Output the result
    std::cout << "Index: " << index << std::endl;
    std::cout << "Largest Fibonacci number less than 2 billion: " << fib[index] << std::endl;

    return 0;
}
