#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <stdexcept>

struct Coordinate {
    int x, y;

    bool operator<(const Coordinate &other) const {
        return (x < other.x) || (x == other.x && y < other.y);
    }
};

void read_input(std::map<Coordinate, int> &m, Coordinate &start, const std::string &infilename) {
    std::ifstream infile(infilename);
    if (!infile) {
        std::cerr << "Error opening file: " << infilename << std::endl;
        throw std::ios_base::failure("Error opening file");
    }

    // Read starting coordinate
    if (!(infile >> start.x >> start.y)) {
        std::cerr << "Error reading starting coordinates from the file" << std::endl;
        throw std::invalid_argument("Invalid starting coordinate data");
    }

    int y = 0;
    std::string line;
    int prev_x_count = -1;  // To track number of columns in each row

    // Read the height map line by line
    while (std::getline(infile, line)) {
        if (line.empty()) continue;  // Skip empty lines
        std::istringstream iss(line);
        int x = 0;
        int height;
        int column_count = 0;

        // Read each height in the line and store in the map
        while (iss >> height) {
            m[{x, y}] = height;
            ++x;
            ++column_count;
        }

        // Ensure that all rows have the same number of columns
        if (prev_x_count != -1 && prev_x_count != column_count) {
            std::cerr << "Error: Rows have inconsistent lengths" << std::endl;
            throw std::invalid_argument("Inconsistent row lengths in input file");
        }

        prev_x_count = column_count;
        ++y;
    }

    infile.close();
}

void printmap(const std::map<Coordinate, int> &m) {
    for (const auto &entry : m) {
        const Coordinate &coord = entry.first;
        int value = entry.second;
        std::cout << coord.x << ", " << coord.y << " val: " << value << std::endl;
    }
}

int main(int argc, char *argv[]) {
    std::string infilename = "input.txt";
    std::string outfilename = "output.txt";

    // Allows the user to override the input and output filenames
    if (argc >= 2) {
        infilename = argv[1];
    }
    if (argc == 3) {
        outfilename = argv[2];
    }

    std::map<Coordinate, int> m;
    Coordinate start;

    try {
        read_input(m, start, infilename);
        printmap(m);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
