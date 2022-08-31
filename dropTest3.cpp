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
        if (BottomPos == fieldHeight) {
            alive = false;
        }else{
            BottomPos++;
        }
    }
    void toBottom(){
        /*
        while (BottomPos != fieldHeight - 1) {
            BottomPos++;
            cout << "BtottomPos" << BottomPos << endl;
        }
        */
        //alive = false;
    }
    
    void findCollision(vector<vector<int>>field){
        // if not collide, return true
        // if collide, return false
        if (BottomPos + 0 == fieldHeight) {
            alive = false;
            return;
        }
        for (int i = 0; i < width; i++) {
            if (field[BottomPos + 0][LeftPos + i] != 0) {
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

char moveBlock(Parts &parts){
    cout << "[d]own, [r]ight, [l]eft, [b]ottom : ";
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
            }else if (c == 'b') {
                //parts.toBottom();
            }
            break;
        }
    usleep(10 * 1000);
    }
    return c;
}

int main() {
    Draw draw;

    int kind = 0;
    while(1) {
        vector<vector<int>>shapeOfBlock;
        bool breakflag = false;
        
        if (kind == 0) {
            shapeOfBlock = shapeOfTotsu;
        }else{
            shapeOfBlock = shapeOfBar;
        }
        
        Parts block(shapeOfBlock);

                block.findCollision(draw.piledField);
                if (!block.alive) {
                    cout << "dead" << endl;
                    draw.piledField = draw.field; // make setter?
                    cout << "====================" << endl;
                    //breakflag = true;
                    break;
                }
        cout << "piledField" << endl;
        draw.drawField(draw.piledField);
        cout << "partsField" << endl;
        block.mkPartsField();
        draw.drawField(block.PartsField);
        cout << "mergedField" << endl;
        draw.mergeField(block.PartsField);
        draw.drawField(draw.field);

        while(1){
            block.findCollision(draw.piledField);
            char c = moveBlock(block);
            do {
                if (c == 'b') {
                    block.down();
                }
                block.findCollision(draw.piledField);
                if (!block.alive) {
                    cout << "dead" << endl;
                    draw.piledField = draw.field; // make setter?
                    cout << "====================" << endl;
                    breakflag = true;
                    break;
                }
                block.mkPartsField();
                draw.mergeField(block.PartsField);
            } while(c == 'b');
            if (breakflag) {
                break;
            }

            cout << "piledField" << endl;
            draw.drawField(draw.piledField);
            cout << "partsField" << endl;
            draw.drawField(block.PartsField);
            cout << "mergedField" << endl;
            draw.drawField(draw.field);

            //cin.get();
        }
        kind++;
    }
}