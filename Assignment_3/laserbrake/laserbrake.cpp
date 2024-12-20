#include <fstream>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>

double DEG2RAD = M_PI / 180; //this definition will be useful

using namespace std;

int main() {
  ifstream scanfile("input.txt");
  ofstream outfile("output.txt");
  cout << setprecision(4); //this sets how many decimal places to print
  outfile << setprecision(4);

  
  double robot_width;
  double threshold;

  string input;
  for(int i=0; i < 2; i++)
  {
    scanfile >> input;
    if (input == "width:")
      scanfile >> robot_width;
    else if (input == "threshold:")
      scanfile >> threshold;
  }
  cout << "Width: " << robot_width << ", Threshold: " << threshold << endl;
  double temp;
  vector<double> scan_returns;
  while (scanfile >> temp) {
    scan_returns.push_back(temp);
    cout << scan_returns[scan_returns.size()-1] << " ";
  }
  cout << endl;

      if (scan_returns.size() < 2) {
        cerr << "Error: At least two laser scan returns are required." << endl;
        return 1;
    }
  
  double resolution =
      180.0 / (scan_returns.size() - 1); // assume last scan is at 180
  cout << "Resolution: " << resolution << " degrees" << endl;
  

  // convert each scan return to x,y coordinates, and write to output.txt
  // --- Your code here

 bool should_stop = false;
int stop_line = 0;

for (size_t i = 0; i < scan_returns.size(); ++i) {
    double angle = i * resolution * DEG2RAD;
    double x = scan_returns[i] * cos(angle);
    double y = scan_returns[i] * sin(angle);

    outfile << x << " " << y << endl;

    if (!should_stop && y >= 0 && abs(x) <= robot_width/2 && scan_returns[i] <= threshold) {
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