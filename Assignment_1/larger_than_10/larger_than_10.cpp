#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::string filename;
    std::cout << "Enter the filename then press enter: ";
    std::cin >> filename;
    std::ifstream ifs(filename);

    if (!ifs.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return 1;
    }

    int x;
    bool found = false; // Variable to track if we've found a number greater than 10

    while (!ifs.eof()) {
        ifs >> x;

        // Check if the input was successful to avoid processing invalid input
        if (ifs.fail()) {
            break; // Break the loop if the input failed
        }

        // --- Your code here
        if (x > 10) {
            std::cout << x << std::endl;
            found = true; // Mark that we found a number > 10
            break;
        }
        // ---
    }

    // Outside the loop, after it finishes
    // if (!found) {
    //     std::cout << "No number is greater than 10" << std::endl;
    // } this worked 

    return 0;
}
