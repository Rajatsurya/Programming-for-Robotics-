
#include <fstream>
#include <iostream>
#include <vector>
#include<algorithm>
#include "sortmass.h"

using namespace std;

// struct ObjMassPair {
//     std::string name;
//     double mass;
// };



int main() {
  ifstream objects("objects.txt");
  ofstream outfile("output.txt");
  string name;
  double mass;

  vector<ObjMassPair> obj_mass;
  //read the contents of the objects file in to the obj_mass vector
  // --- Your code here

    // Read from the file and populate the vector
    while (objects >> name >> mass) {
        obj_mass.push_back({name, mass});
    }

    // Close the input file

        // for (const auto& pair : obj_mass) {
        // std::cout << "Object: " << pair.name << ", Mass: " << pair.mass << std::endl;
        // }


  // ---

  //use std::sort to sort obj_mass. You will need to define
  //a function that compares ObjMassPair objects that is of
  //the form expected by std::sort

  // --- Your code here
 sort(obj_mass.begin(), obj_mass.end(), compareMass); 

  // ---

  //you will need to properly overload the << operator (in sortmass.h)
  //to print obj_mass to cout
  //look at the form expected in the given output.txt
  cout << obj_mass;
  outfile << obj_mass;
  return 0;
}
