//g++ -std=c++20 dropTest.cpp -o dropTest.out

#include <iostream>
#include <cstdlib>
#include <vector>

int cnt = 0;
std::vector<std::vector<int>> data{
  {7, 4, 0, 8},
  {2, 0, 3, 5},
  {6, 1, 7, 0},
};
int main() {
    for (int i = 0; i < 10; i++) {
        std::system("reset");
        for (int j = 0; j < i; j++) {
            std::cout << std::endl;
        }
        std::cout << "o" << std::endl;
        for (int k = 0; k < 10-j; k++) {
            std::cout << std::endl;
        }
        std::cout << "--------------------" << std::endl;
        std::cin.get();
    }
}