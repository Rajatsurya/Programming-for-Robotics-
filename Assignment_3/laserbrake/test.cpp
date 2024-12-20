#include <fstream>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

const double DEG2RAD = M_PI / 180;

using namespace std;

int main() {
    ifstream scanfile("input.txt");
    ofstream outfile("output3.txt");
    cout << setprecision(4);
    outfile << setprecision(4);

    double robot_width;
    double threshold;

    string input;
    for (int i = 0; i < 2; i++) {
        scanfile >> input;
        if (input == "width:")
            scanfile >> robot_width;
        else if (input == "threshold:")
            scanfile >> threshold;
    }

    vector<double> scan_returns;
    double temp;
    while (scanfile >> temp) {
        scan_returns.push_back(temp);
    }

    if (scan_returns.size() < 2) {
        cerr << "Error: At least two laser scan returns are required." << endl;
        return 1;
    }

    double resolution = 180.0 / (scan_returns.size() - 1);

 bool should_stop = false;
int stop_line = 0;

for (size_t i = 0; i < scan_returns.size(); ++i) {
    double angle = i * resolution * DEG2RAD;
    double x = scan_returns[i] * cos(angle);
    double y = scan_returns[i] * sin(angle);

    outfile << x << " " << y << endl;

    if (!should_stop && y >= 0 && abs(x) <= robot_width && scan_returns[i] <= threshold) {
        should_stop = true;
        stop_line = i ; // +1 to convert from 0-based to 1-based indexing
    }
}

if (should_stop) {
    outfile << "Stop! " << stop_line;
} else {
    outfile << "OK";
}
    scanfile.close();
    outfile.close();

    return 0;
}