#include <iostream>
#include <iomanip>

int main() {
    double mi, km;
    
    // Read miles from standard input
    std::cin >> mi;
    
    // Convert miles to kilometers
    km = mi * 1.609344;
    
    // Output the result with the required precision and format
    std::cout << std::setprecision(3);
    std::cout <<  km <<  std::endl;
    
    return 0;
}
