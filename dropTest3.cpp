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
    Parts(vector<vector<int>> &shape){
        shapeOfParts = shape;
        height = shapeOfParts.size();
        width = shapeOfParts[0].size();
    }

    void mkPartsField(){
        cout << "mkPartsField Bottom, Left ; " << BottomPos << ", " << LeftPos << endl;
        PartsField = zeroField;
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                PartsField[BottomPos-y][LeftPos+x] = shapeOfParts[y][x];
            }
        }
    }

    void rotate(){
        cout << "here" << endl;
        //vector<vector<int>>tmp;
        vector<vector<int>>tmp(width, vector<int>(height));
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                tmp[x][y] = shapeOfParts[y][x];
            }
        }
        shapeOfParts = tmp;
        height = shapeOfParts.size();
        width = shapeOfParts[0].size();
    }

    void toLeft(vector<vector<int>>&piledField){
        if (LeftPos > 0) {
            if (piledField[BottomPos][LeftPos-1] == 0) {
                LeftPos--;
            }
        }
        cout << "left edge : " << LeftPos << endl;
    }
    void toRight(vector<vector<int>>&piledField){
        if (LeftPos+width < fieldWidth) {
            if (piledField[BottomPos][LeftPos+width-1+1] == 0) {
                LeftPos++;
            }
        }
        cout << "right edge : " << LeftPos+width-1 << endl;
    }
    void down(){
        if (BottomPos == fieldHeight) {
            alive = false;
        }else{
            BottomPos++;
        }
    }
    void toBottom(){
        // not used. down is called repeatedly instead.
        // Do not erase this function for readability.
    }

    char moveBlock(vector<vector<int>>&piledField){
        cout << "fall:<space> rotate:UP DOWN RIGHT LEFT > ";
        char c = '\0';
        while(1) {
            if (kbhit()) {
                cout << endl;
                char c1 = getchar();
                if (int(c1) == 0x1b) {
                    getchar();
                    char c3 = getchar();

                    if (int(c3) == 65) {
                        rotate();
                    }else if (int(c3) == 66) {
                        down();
                    }else if (int(c3) == 67) {
                        toRight(piledField);
                    }else if (int(c3) == 68) {
                        toLeft(piledField);
                    }else{

                    }
                    break;
                }
                if (c1 == ' ') {
                    // fall
                    c = c1;
                }
                break;
                /*
                if (c == 'd') {
                    down();
                }else if (c == 'l') {
                    toLeft(piledField);
                }else if (c == 'r') {
                    toRight(piledField);
                }else if (c == 'r') {
                    rotate();
                }
                }else if (c == 'b') {
                    //parts.toBottom();
                }
                break;
                */
            }
        //usleep(10 * 1000);
        }
        return c; // if fall c = ' '(space), otherwise null.
    }

    
    void findCollision(vector<vector<int>>&field){
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
    
    void drawField(vector<vector<int>>&field) {
        for (int i = 0; i < fieldHeight; i++) {
            for (int j = 0; j < fieldWidth; j++) {
                cout << field[i][j] ;
            }
            cout << endl;
        }
        cout << "--------------------" << endl;
    }

    void mergeField(vector<vector<int>>&partsField) {
        for (int i = 0; i < fieldHeight; i++) {
            for (int j = 0; j < fieldWidth; j++) {
                field[i][j] = piledField[i][j] + partsField[i][j];
            }
        }
    }
};

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

        // if no space to drop, break here and finish game.
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
            char c = block.moveBlock(draw.piledField);
            do {
                if (c == ' ') {
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
            } while(c == ' ');
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