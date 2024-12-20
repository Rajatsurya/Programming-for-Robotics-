#include <iostream>

int main() {
    // --- Your code here
    int difference;
    int i=1;
    int sum_square=0;
    int sum_whole_square=0;
    int new_sum =0;
    while(i<=100){

        sum_square=sum_square+(i*i);
        sum_whole_square=sum_whole_square+i;
        i++;

    }
    new_sum = sum_whole_square * sum_whole_square;
    difference = new_sum - sum_square;
    // ---
    std::cout << difference << std::endl;
    return 0;
}