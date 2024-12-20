#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

// Function to process each line by replacing characters and updating the counter
void processLine(std::string& line, int lineNumber, int* counter) {
    int lineSum = 0;
    for (char& ch : line) {
        if (ch == 'e') {
            ch = '3';
            lineSum += 3;
        } else if (ch == 'l') {
            ch = '1';
            lineSum += 1;
        } else if (ch == 't') {
            ch = '7';
            lineSum += 7;
        }
    }
    *counter += lineSum * lineNumber;
}

// Function to create a counter initialized to 0 using dynamic memory allocation
int* createCounter() {
    int* counter = new int(0); // Allocate memory on the heap and initialize to 0
    return counter;
}

int main() {
    std::ifstream input("input.txt");
    std::vector<std::string> lines;
    std::string line;

    // Create a reference to the pointed value
    int& counter = *createCounter();

    // Read all lines from the input file
    while (std::getline(input, line)) {
        lines.push_back(line);
    }

    // Process each line and update the counter
    for (size_t i = 0; i < lines.size(); ++i) {
        processLine(lines[i], i, &counter);
    }

    // Reverse the order of lines
    std::reverse(lines.begin(), lines.end());

    // Output processed lines and total sum to output.txt
    std::ofstream output("output.txt");
    for (const auto& processedLine : lines) {
        output << processedLine << "\n";
    }
    output << counter << "\n";

    // Clean up dynamically allocated memory
    delete &counter;

    return 0;
}
