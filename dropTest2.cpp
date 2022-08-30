//g++ -std=c++20 dropTest.cpp -o dropTest.out

#include <iostream>
#include <cstdlib>
#include <vector>

#define fieldHeight 10
#define fieldWidth 20
#define dropcnt 3

using namespace std;
// todo usingを使ってvectorのエイリアスをつくり、短く表記できるようにする。
vector<vector<int>> field(fieldHeight, vector<int>(fieldWidth,0));

class Parts{
    public:
    int height;
    int width;
    vector<vector<int>> shapeOfParts;
    Parts(vector<vector<int>> shape){
        shapeOfParts = shape;
        height = shapeOfParts.size();
        width = shapeOfParts[0].size();
    }
};

// shape of blocks
vector<vector<int>> shapeOfTotsu = {
  {0, 1, 0},
  {1, 1, 1},
};
// 他の形も追加

int main() {
    Parts totsu(shapeOfTotsu);
    cout << totsu.height << endl;

    for (int i = 0; i < fieldHeight; i++) {
        for (int j = 0; j < fieldWidth; j++) {
            cout << field[i][j] ;
        }
        cout << endl;
    }

    for (int i = 0; i < dropcnt; i++) {
        //system("reset");
        field[i][5]=1;
        for (int i = 0; i < fieldHeight; i++) {
            for (int j = 0; j < fieldWidth; j++) {
                cout << field[i][j] ;
            }
            cout << endl;
        }
        cout << "--------------------" << endl;
        cin.get();
    }
}