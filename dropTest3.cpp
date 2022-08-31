//g++ -std=c++20 dropTest.cpp -o dropTest.out

#include <iostream>
#include <cstdlib>
#include <vector>
#include "kbhit.hpp"

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
    int BottomPos = 1;
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
    void toLeft(){
        cout << "left edge : " << LeftPos << endl;
        if (LeftPos > 0) {
            LeftPos--;
        }
    }
    void toRight(){
        cout << "right edge : " << LeftPos+width;
        if (LeftPos+width < fieldWidth) {
            LeftPos++;
        }
    }
    void down(){
        BottomPos++;
    }
    void toBottom(){}
    
    void findCollision(vector<vector<int>>field){
        // if not collide, return true
        // if collide, return false
        if (BottomPos + 1 == fieldHeight) {
            alive = false;
            return;
        }
        for (int i = 0; i < width; i++) {
            if (field[BottomPos+1][LeftPos+i] != 0) {
                alive = false;
                return;
            }
        }
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
    //int cnt = 0;
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
};

int moveBlock(Parts &parts){
    cout << "[d]own, [r]ight, [l]eft : ";
    char c;
    while(1) {
        if (kbhit()) {
            cout << endl;
            c = getchar();
            if (c == 'd') {
                parts.down();
            }else if (c == 'l') {
                parts.toLeft();
            }else if (c == 'r') {
                parts.toRight();
            }
            break;
            //printf("the key was : %c\n", getchar());
        }
    usleep(10 * 1000);
    }

    return 0;
}

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
        block.findCollision(draw.field);
        if (!block.alive) {
            cout << "GAME OVER!" << endl;
            break;
        }

        while(1){
            cout << "piledField" << endl;
            draw.drawField(draw.piledField);
            cout << "partsField" << endl;
            block.mkPartsField();
            draw.drawField(block.PartsField);
            cout << "mergedField" << endl;
            draw.mergeField(block.PartsField);
            draw.drawField(draw.field);

            block.findCollision(draw.field);
            //draw.cnt++;
            if (block.alive) {
                moveBlock(block);
            }
            //block.BottomPos++;
            //block.aliveCheck();
            if (!block.alive) {
                cout << "dead" << endl;
                draw.piledField = draw.field; // make setter?
                //draw.cnt = 0;
                cout << "====================" << endl;
                break;
            }
            //cin.get();
        }
        kind++;
    }
}