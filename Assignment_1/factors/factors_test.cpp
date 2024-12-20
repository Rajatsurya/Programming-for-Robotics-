#include <iostream>

int main() {
    int x;
    std::cin >> x;
    
    bool is_factor = (x % 2 == 0 || x % 3 == 0);

    if (!is_factor) {
        std::cout << "The number " << x << " is not divisible by 2 or 3." << std::endl;
    } else {
        std::cout << "The number " << x << " is divisible by 2 or 3." << std::endl;
    }

    // Output the boolean result as 1 or 0
    std::cout << is_factor << std::endl; // true or false (1 or 0)

    return 0;
}
