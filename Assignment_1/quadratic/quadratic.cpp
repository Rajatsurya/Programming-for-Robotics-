#include <cmath>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <algorithm>

double calculateDiscriminant(double a, double b, double c)
{
    return pow(b, 2) - 4 * a * c;
}

bool realRootExist(double discriminant)
{
    return discriminant >= 0;
}

void computeRealQuadraticRoots(double &root_1, double &root_2, double a, double b, double c)
{
    double discriminant = calculateDiscriminant(a, b, c);
    if (realRootExist(discriminant))
    {
        root_1 = (-b + sqrt(discriminant)) / (2 * a);
        root_2 = (-b - sqrt(discriminant)) / (2 * a);
    }
    else
    {
        root_1 = std::nan("");
        root_2 = std::nan("");
    }
}

void getSmallestAndLargestRoots(double &smallest_root, double &largest_root, double root_1, double root_2)
{
    smallest_root = std::min(root_1, root_2);
    largest_root = std::max(root_1, root_2);
}

void displayRoots(double root_1, double root_2)
{
    if (std::isnan(root_1) && std::isnan(root_2))
    {
        std::cout << "None" << std::endl;
    }
    else if (root_1 == root_2)
    {
        std::cout << root_1 << std::endl;
    }
    else if (root_1 != root_2)
    {
        double smallest_root, largest_root;
        getSmallestAndLargestRoots(smallest_root, largest_root, root_1, root_2);

        std::cout << smallest_root << std::endl;
        std::cout << largest_root << std::endl;
    }
    else
    {
        std::cout << "Error occurred. Unexpected combination of roots" << std::endl;
    }
}

int main()
{
    double a, b, c;
    std::cout << "Type in a, b, and c. Press 'Enter' between each\n";
    std::cin >> a;
    std::cin >> b;
    std::cin >> c;
    std::cout << std::setprecision(4);

    double root_1, root_2;

    computeRealQuadraticRoots(root_1, root_2, a, b, c);

    displayRoots(root_1, root_2);

    return 0;
}
