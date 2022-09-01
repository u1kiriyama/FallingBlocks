#include <iostream>
#include <vector>

int main() {
    //std::vector<int> v1 = {1,2,3}; //OK
    std::vector<int> v1;
    v1 = {1,2,3};
    v1 = {2,3,4};
    v1 = {5,6};
    std::cout << "1-dim vector v1" << std::endl;
    for (int i = 0; i < v1.size(); i++) {
        std::cout << v1[i] << std::endl;
    }

    std::vector<std::vector<int>>v2;
    v2 = { {1,2,3},{4,5,6} };
    v2 = { {10,11},{12,13},{14,15} };
    std::cout << "2-dim vector v2" << std::endl;
    for (int i = 0; i < v2.size(); i++) {
        for (int j = 0; j < v2[0].size(); j++) {
            std::cout << v2[i][j] << std::endl;
        }
    }
    std::cout << "2-dim vector tmp" << std::endl;
    std::vector<std::vector<int>>tmp(3, std::vector<int>(2));
    for (int i = 0; i < v2.size(); i++) {
        for (int j = 0; j < v2[0].size(); j++) {
            tmp[i][j] = v2[i][j];
        }
    }
    for (int i = 0; i < v2.size(); i++) {
        for (int j = 0; j < v2[0].size(); j++) {
            std::cout << tmp[i][j] << std::endl;
        }
    }


    return 0;
}