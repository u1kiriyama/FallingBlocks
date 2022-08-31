//g++ -std=c++20 dropTest.cpp -o dropTest.out

#include <iostream>
#include <cstdlib>
#include <vector>

#define fieldHeight 10
#define fieldWidth 20
#define dropcnt 10

using namespace std;

const vector<vector<int>>zeroField =
{
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

class Parts{
    public:
    int height, width;
    int BottomPos = 3;
    int LeftPos = 6;
    bool alive = true;
    vector<vector<int>>PartsField;

    vector<vector<int>> shapeOfParts;
    Parts(vector<vector<int>> shape){
        shapeOfParts = shape;
        height = shapeOfParts.size();
        width = shapeOfParts[0].size();
    }

    void mkPartsField(){
        PartsField = zeroField;
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                PartsField[BottomPos-y][LeftPos+x] = shapeOfParts[y][x];
            }
        }

    }
    void clkwise(){}
    void toLeft(){}
    void toRight(){}
    void down(){}
    void toBottom(){}
    void aliveCheck(){
        if (BottomPos == fieldHeight-2) alive = false; // -2 is for debug
    }
};

// shape of blocks
vector<vector<int>> shapeOfEmpty = {}; // to show blank field.

vector<vector<int>> shapeOfTotsu = {
  {0, 1, 0},
  {1, 1, 1},
};
vector<vector<int>> shapeOfBar = {
    {1, 1, 1}
};
// 他の形も追加

class Draw{ // not good name
    public:
    int cnt = 0;
    vector<vector<int>>field;
    vector<vector<int>>piledField;
    Draw()
    {
        field = zeroField;
        piledField = zeroField;
    }
    
    void drawField(vector<vector<int>>field) {
        for (int i = 0; i < fieldHeight; i++) {
            for (int j = 0; j < fieldWidth; j++) {
                cout << field[i][j] ;
            }
            cout << endl;
        }
        cout << "--------------------" << endl;

    }

    void mergeField(vector<vector<int>>partsField) {
        for (int i = 0; i < fieldHeight; i++) {
            for (int j = 0; j < fieldWidth; j++) {
                field[i][j] = piledField[i][j] + partsField[i][j];
            }
        }
    }

    void findColision(){

    }
};

int main() {
    Draw draw;

    int kind = 0;
    while(1) {
        vector<vector<int>>shapeOfBlock;
        
        if (kind == 0) {
            shapeOfBlock = shapeOfTotsu;
        }else{
            shapeOfBlock = shapeOfBar;
        }
        
        Parts block(shapeOfBlock);

        for (int i = 0; i < dropcnt; i++) { // dropcnt could be fieldHeight.
            cout << "piledField" << endl;
            draw.drawField(draw.piledField);
            cout << "partsField" << endl;
            block.mkPartsField();
            draw.drawField(block.PartsField);
            cout << "mergedField" << endl;
            draw.mergeField(block.PartsField);
            draw.drawField(draw.field);
            draw.cnt++;

            block.BottomPos++;
            block.aliveCheck();
            if (!block.alive) {
                cout << "dead" << endl;
                draw.piledField = draw.field; // make setter?
                draw.cnt = 0;
                cout << "====================" << endl;
                break;
            }
            cin.get();
        }
        kind++;
    }
}