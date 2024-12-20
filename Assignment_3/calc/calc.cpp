#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// Function to perform the calculation
double performCalculation(const std::vector<double>& numbers, char op) {
    
        double result;
    // Check the operator using if statements
    if (op == '+') {
        result = 0; // Start with 0 for addition
        for (const double& num : numbers) {
            result += num; // Add each number
        }
    } else if (op == '*') {
        result = 1; // Start with 1 for multiplication
        for (const double& num : numbers) {
            result *= num; // Multiply each number
        }
    } else if (op == '-') {
        result = 1; // Start with 1 for multiplication
        for (const double& num : numbers) {
            result -= num; // 
        }
    }else if (op == '/') {
        if (numbers.size() != 2) return 0.1; // Error if not exactly 2 numbers
        if (numbers[1] == 0) return  0.1;      // Division by zero error
        result = numbers[0] / numbers[1];    // Divide the two numbers
    } else {
        return 0.1;  // Return error for invalid operator
    }

    return result; // Return the calculated result

}

int main() {
    ifstream infile("input.txt");
    ofstream outfile("output.txt");
    

    std::string line;

    while (std::getline(infile, line)) {  // Read each line from the file
        std::istringstream ss(line);  // String stream to parse the line
        std::vector<double> numbers;
        double num;
        // char op;

        // Extract numbers from the line
        while (ss >> num) {
            numbers.push_back(num);
        }
        if (numbers.empty()) {
            outfile << "ERROR" << std::endl; // Output error if no numbers found
            continue; // Skip to the next line
        }
        // Get the operator (last character)
        ss.clear();  // Clear the state of the stringstream

         // Find the operator at the end of the line
        char op = '\0'; // Initialize the operator
        if (!line.empty()) {
            // Scan backward to find the last non-space character
            for (int i = line.size() - 1; i >= 0; --i) {
                if (!isspace(line[i])) { // Check for non-space character
                    op = line[i];        // Set the operator
                    break;               // Exit the loop
                }
            }
        }

           if (op != '\0') {
            // Perform the operation on all the numbers in the vector
            double result = performCalculation(numbers, op);
            
            // Output the result to output.txt
            if (result == 0.1) {
                outfile << "ERROR" << std::endl;  // If there was an error (like invalid operation or division by zero)
            } else {
                outfile << result << std::endl; // Output the result
            }
        } else {
            // If no operator was found
            outfile << "ERROR" << std::endl;
        }
    }

    infile.close();
    outfile.close();
    
    return 0;
}