#include <iostream>

long long int euler9() {
    long long int product = 0;
    for (int a = 1; a < 1000; ++a) {
        for (int b = a + 1; b < 1000; ++b) {
            int c = 1000 - a - b;
            if (c > b) { // Ensure c > b > a
                if (a * a + b * b == c * c) {
                    // std::cout << a << " , " << b << " , " << c << std::endl;
                    product = static_cast<long long int>(a) * b * c;
                    return product; // Return the product of the Pythagorean triple
                }
            }
        }
    }
    return 0; // If no Pythagorean triple is found
}

int main() {
    // This code is a lot cleaner if you write it as a function, because you can use `return` once you find the answer
    int const product = euler9();
    std::cout << product << std::endl;
    return 0;
}