#include <cmath>
#include <iostream>
#include <fstream>

int main()
{
    double mass, w, h, d;
    std::ifstream ifs("inertia_input.txt");
    ifs >> mass;
    ifs >> w;
    ifs >> h;
    ifs >> d;
    // you'll need to store the outputs in variables Ih, Iw, and Id.
    // --- Your code here
    double Ih, Iw, Id;
    Ih= (mass)/12*(w*w + d*d);
    Iw= (mass)/12*(d*d + h*h);
    Id= (mass)/12*(w*w + h*h);
    // ---
    // std::cout << "Ih " << Ih  << std::endl;
    // std::cout << "Iw " << Iw  << std::endl;
    // std::cout << "Id " << Id  << std::endl;
    std::cout << "<ixx>" << Ih << "</ixx>\n";
    std::cout << "<iyy>" << Iw << "</iyy>\n";
    std::cout << "<izz>" << Id << "</izz>\n";
    return 0;
}