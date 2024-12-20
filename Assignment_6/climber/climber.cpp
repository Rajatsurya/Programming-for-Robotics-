#include <algorithm>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <map>
// add the include for climber.h
// --- Your code here
#include "climber.h"



// ---

bool operator==(Coordinate const &c1, Coordinate const &c2)
{
    return (c1.x == c2.x) && (c1.y == c2.y);
}

bool operator<(Coordinate const &c1, Coordinate const &c2)
{
    if (c1.x == c2.x)
    {
        return c1.y < c2.y;
    }
    return c1.x < c2.x;
}

Coordinate operator+(Coordinate const &c1, Coordinate const &c2)
{
    return {c1.x + c2.x, c1.y + c2.y};
}

void read_input(std::map<Coordinate, int> &m, Coordinate &start, std::string const &infilename)
{
    std::ifstream infile(infilename);
    if (!infile.good()) {
        std::cerr << "No such file " << infilename << '\n';
        throw std::runtime_error("No such file!");
    }

    infile >> start.x;
    infile >> start.y;
    infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // move to next line

    int x_idx = 0;
    int y_idx = 0;
    std::string line;
    while (std::getline(infile, line))
    {
        std::stringstream ssline(line);
        int val;
        while (ssline >> val)
        {
            m[{x_idx, y_idx}] = val;
            x_idx++;
        }
        x_idx = 0;
        y_idx++;
    }
}

void climber_algorithm(std::map<Coordinate, int> const &m, Coordinate const &start, std::string const& outfilename)
{
    std::ofstream outfile(outfilename);

    // These print statements are for your debugging convenience. The autograder will only look at the output file.
    std::cout << "height at start: " << m.at(start) << std::endl;

    Coordinate current_xy = start;
    int current_height = m.at(start);

    // 'offsets' should contain the changes in XY coordinates, in the order specified in the assigmnet doc.
    // Note that the Coordinate struct has operator+ defined on it, which lets you add two Coordiantes together
    std::vector<Coordinate> offsets{
        // --- Your code here
        {1, 0},
        {-1,0},
        {0, 1},
        {0, -1}
    
        // ---
    };

    // We use a while true here, then break when we detect the climber has reached a local maximum
    while (true)
    {
        outfile << current_xy.x << " " << current_xy.y << " " << current_height << std::endl;
        // Consider creating variables to keep track of the next coordinate and the height at the next coordinate.
        // You should iterate over the valid neighbors and update these variables each time we find a new-best neighbor.
        // A valid neighor is one that is in-bounds, has height > the current height but <= the current height + 2.
        // If the current xy is the same as the next xy that means we've hit our local maxiumum and we should stop.
        
        // --- Your code here
        Coordinate b_neighbor = current_xy;
        int b_height = current_height;
        
        for (const auto& offset : offsets) {
            Coordinate neighbor = current_xy + offset;

            if (m.find(neighbor) != m.end()) {
                int neighbor_height = m.at(neighbor);

                if(neighbor_height > current_height && neighbor_height <= current_height + 2) {
                    if (neighbor_height > b_height) {
                        b_neighbor = neighbor;
                        b_height = neighbor_height;
                    }
                }
              
            }
        }
        
        if (b_neighbor == current_xy) {
            break;
        }
        current_xy = b_neighbor;
        current_height = b_height;
      
        // ---
    }


    std::cout << "location at end: " << current_xy.x << " " << current_xy.y << std::endl;
    std::cout << "height at end: " << current_height << std::endl;
}