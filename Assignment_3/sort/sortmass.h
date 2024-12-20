#include <iostream>
#include <vector>

using ObjMassPair = std::pair<std::string, double>; //this defines the type ObjMassPair to be std::pair<std::string, double>

//define the operator << here
inline std::ostream& operator<<(std::ostream& os, const ObjMassPair& pair) {
    os << pair.first << " " << pair.second;
    return os;
}

// Overload for vector<ObjMassPair>
inline std::ostream& operator<<(std::ostream& os, const std::vector<ObjMassPair>& vec) {
    for (const auto& pair : vec) {
        os << pair << std::endl;
    }
    return os;
}

//define a function that compares ObjMassPair objects here (for use by std::sort)
// --- Your code here
bool compareMass(const ObjMassPair& a, const ObjMassPair& b) {
    return a.second < b.second;
}




// ---
