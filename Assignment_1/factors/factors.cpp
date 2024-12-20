

#include <iostream>

int main() {
    // Determines whether a number (from stdin) is a factor of 2 or 3
    // The answer should be stored in a variable `is_factor`. Printing of this variable
    // is handled for you, but you must create the variable, or you'll get a compiler error.
    int x;
    bool is_factor = false; // Initialize as false
    std::cout << "Type an integer then press Enter: ";
    std::cin >> x;
    
    // Check if the number is a factor of 2 or 3
    if (x % 2 == 0 || x % 3 == 0) {
        is_factor = true;
    } 

    // Output the result
    // if (is_factor==0){
    //     std::cout << "the number " << x << " is not a factor of 3 or 2" << std::endl;
    // }
    // else {
    //     std::cout << "the number " << x << " is a factor of 3 or 2" << std::endl;
    // }
    std::cout << is_factor << std::endl; // true or false (1 or 0)
    return 0;
}
 