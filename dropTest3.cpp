//g++ -std=c++20 dropTest.cpp -o dropTest.out

#include <iostream>
#include <cstdlib>
#include <vector>
#include "kbhit.hpp"

#define fieldHeight 10
#define fieldWidth 20
#define dropcnt 10

using namespace std;

vector<vector<int>>zeroField(fieldHeight, vector<int>(fieldWidth, 0));

class Parts{
    public:
    int height, width;
    int BottomPos = 0;
    int LeftPos = 6;
    bool alive = true;
    vector<vector<int>>PartsField;
    vector<vector<int>>simPartsField;

    vector<vector<int>> shapeOfParts;
    Parts(vector<vector<int>> &shape, vector<vector<int>>&piledField){
        shapeOfParts = shape;
        height = shapeOfParts.size();
        width = shapeOfParts[0].size();
        BottomPos = height-1;
        if (!collisionCheck(piledField, shapeOfParts)) {
            alive = false;
        }
    }

    void mkPartsField(){
        //cout << "mkPartsField Bottom, Left ; " << BottomPos << ", " << LeftPos << endl;
        PartsField = zeroField;
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                PartsField[BottomPos-y][LeftPos+x] = shapeOfParts[y][x];
            }
        }
    }

    void setSimPartsField(){
        simPartsField = PartsField;
    }

    void rotate(vector<vector<int>>&piledField){
        //vector<vector<int>>tmp;
        vector<vector<int>>tmp(width, vector<int>(height));
        // rotation
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                tmp[x][height-1-y] = shapeOfParts[y][x];
            }
        }
        // ceiling check
        if (BottomPos+1 < tmp.size()) {
            //cout << "rotation forbidden" << endl;
            BottomPos = tmp.size() - 1;
        }
        // right wall check
        if (LeftPos+tmp[0].size() > fieldWidth) {
            cout << "collide right wall" << endl;
            LeftPos = fieldWidth - tmp[0].size();
        }
        if (collisionCheck(piledField, tmp)){
            shapeOfParts = tmp;
            PartsField = simPartsField;
            height = shapeOfParts.size();
            width = shapeOfParts[0].size();
        }
    }

    void toLeft(vector<vector<int>>&piledField){
        if (LeftPos > 0) {
            if (piledField[BottomPos][LeftPos-1] == 0) {
                LeftPos--;
                if (!collisionCheck(piledField, shapeOfParts)){
                    LeftPos++;
                }
            }
        }
        cout << "left edge : " << LeftPos << endl;
    }
    void toRight(vector<vector<int>>&piledField){
        if (LeftPos+width < fieldWidth) {
            if (piledField[BottomPos][LeftPos+width-1+1] == 0) {
                LeftPos++;
                if (!collisionCheck(piledField, shapeOfParts)){
                    LeftPos--;
                }
            }
        }
        cout << "right edge : " << LeftPos+width-1 << endl;
    }
    void down(vector<vector<int>>&piledField){
        BottomPos++;
        alive = collisionCheck(piledField, shapeOfParts);
        if (!alive) {
            BottomPos--;
        }
    }
    void toBottom(){
        // not used. down is called repeatedly instead.
        // Do not erase this function for readability.
    }

    char moveBlock(vector<vector<int>>&piledField, vector<vector<int>>&field){
        //setSimPartsField();
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
                        rotate(piledField);
                    }else if (int(c3) == 66) {
                        down(piledField);
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
            }
        }
        return c; // if fall c = ' '(space), otherwise null.
    }

    bool collisionCheck(vector<vector<int>>&piledField, vector<vector<int>>&tmp) {
        setSimPartsField();
        if (BottomPos + 0 == fieldHeight) {
            return false;
        }
        simPartsField = zeroField;
        for (int x = 0; x < tmp[0].size(); x++) {
            for (int y = 0; y < tmp.size(); y++) {
                simPartsField[BottomPos-y][LeftPos+x] = tmp[y][x];
            }
        }

        for (int i = 0; i < fieldHeight; i++) {
            for (int j = 0; j < fieldWidth; j++) {
                if (piledField[i][j] + simPartsField[i][j] == 2) {
                    return false;
                }
            }
        }
        return true;
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

class Draw{ // not good name -> Board
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
        
        Parts block(shapeOfBlock, draw.piledField);

        // if no space to drop, break here and finish game.
        //block.findCollision(draw.piledField);
        if (!block.alive) {
            cout << " G A M E   O V E R " << endl;
            draw.piledField = draw.field; // make setter?
            cout << "====================" << endl;
            //breakflag = true;
            return 0;
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
            //block.findCollision(draw.piledField);
            char c = block.moveBlock(draw.piledField, draw.field);
            do {
                if (c == ' ') {
                    block.down(draw.piledField);
                }
                //block.findCollision(draw.piledField);
                if (!block.alive) {
                    //cout << "dead!" << endl;
                    draw.piledField = draw.field; // make setter?
                    cout << "====================" << endl;
                    breakflag = true;
                    break;
                }
                block.mkPartsField();
                //block.collisionCheck();
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
     return 0;
}