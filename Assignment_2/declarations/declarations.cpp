// --- Your code here

#include<iostream>
#include <cmath>
#include <iomanip>


long double multiply(long long a, long long b) {
    return static_cast<long double>(a) * b;
}


std::string repeatString(const std::string& str, int n) {
    // Initialize an empty result string
    std::string result;
    
    // Append the original string to the result n times
    for (int i = 0; i < n; ++i) {
        result += str;
    }
    
    return result;
}



// ---

// include the standard library files that defines the std:: functions
int main() {
    // --- Your code here
    
    // ---
    
	// declare the variables used below
	double some_number = 5.5;
    // std::endl and '\n' are equivalent
	std::cout << some_number << ' ' << std::round(some_number + M_PI) << '\n';

    // this one may be a bit tricky since you can't assign a string literal to char* in C++ 
	std::string some_string = "my string";
	std::cout << some_string << '\n';

    // implement this function
    // should print empty string
    std::cout << repeatString(some_string, 0) << std::endl;
    // should print it 5 times, with nothing separating them
    std::cout << repeatString(some_string, 5) << std::endl;
	
    // Declare large_number as long long to prevent overflow when multiplied by 3
    long long large_number = 1000000;
    large_number *= 3;
    std::cout << large_number << std::endl;

    // Declare even_larger_number as long long since it is large_number squared
    long long even_larger_number = large_number * large_number;
    std::cout << even_larger_number << std::endl;

    // Use multiply function to multiply large_number and even_larger_number
    std::cout << std::fixed << std::setprecision(1) << multiply(large_number, even_larger_number) << std::endl;

    // Declare negative_number as int since it fits within the range of int
    int negative_number = -250;
    std::cout << negative_number << std::endl;

    return 0;
}