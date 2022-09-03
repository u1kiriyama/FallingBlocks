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
    bool moveOK = true;
    vector<vector<int>>partsField;
    //vector<vector<int>>simPartsField;

    vector<vector<int>> shapeOfParts;
    Parts(vector<vector<int>> &shape, const vector<vector<int>>&piledField){
        shapeOfParts = shape;
        height = shapeOfParts.size();
        width = shapeOfParts[0].size();
        BottomPos = height-1;
        /*
        if (!collisionCheck(piledField)) {
            alive = false;
        }
        */
    }

    void mkPartsField(){
        //cout << "mkPartsField Bottom, Left ; " << BottomPos << ", " << LeftPos << endl;
        partsField = zeroField;
        for (int x = 0; x < shapeOfParts[0].size(); x++) {
            for (int y = 0; y < shapeOfParts.size(); y++) {
                partsField[BottomPos-y][LeftPos+x] = shapeOfParts[y][x];
            }
        }
        cout << endl;
    }
    /*
    void setSimPartsField(){
        simPartsField = PartsField;
    }
    */

    bool rotate(const vector<vector<int>>&piledField){
        //vector<vector<int>>tmp;
        vector<vector<int>>tmp(width, vector<int>(height));
        // rotation
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                tmp[x][height-1-y] = shapeOfParts[y][x];
            }
        }
        /*
        for (int i = 0; i < tmp.size(); i++) {
            for (int j = 0; j <  tmp[0].size(); j++) {
                cout << tmp[i][j] ;
            }
            cout << endl;
        }
        cout << "===" << endl;
        */

        shapeOfParts = tmp;
        cout << "shapeOfParts height:" << shapeOfParts.size() << ",width" << shapeOfParts[0].size() << endl; 
        height = shapeOfParts.size();
        width = shapeOfParts[0].size();

        // ceiling check
        if (BottomPos+1 < shapeOfParts.size()) {
            // 天井に触るような回転をしようとした場合、BottomPosが更新されるが、
            // 更新後、collisionCheckに引っかかる場合、shapeOfPartsが更新されないので既存ブロックにめりこむ。
            BottomPos = shapeOfParts.size() - 1;
        }
        // right wall check
        if (LeftPos+shapeOfParts[0].size() > fieldWidth) {
            LeftPos = fieldWidth - shapeOfParts[0].size();
        }
        return true;
    }

    void toLeft(const vector<vector<int>>&piledField){
        if (LeftPos > 0) {
            if (piledField[BottomPos][LeftPos-1] == 0) {
                LeftPos--;
                /*
                if (!collisionCheck(piledField, shapeOfParts)){
                    LeftPos++;
                }
                */
            }
        }
        cout << "left edge : " << LeftPos << endl;
    }
    void toRight(const vector<vector<int>>&piledField){
        if (LeftPos+width < fieldWidth) {
            if (piledField[BottomPos][LeftPos+width-1+0] == 0) {
                LeftPos++;
                /*
                if (!collisionCheck(piledField, shapeOfParts)){
                    LeftPos--;
                }
                */
            }
        }
        cout << "right edge : " << LeftPos+width-1 << endl;
    }
    void down(const vector<vector<int>>&piledField){
        BottomPos++;
        alive = collisionCheck(piledField);
        if (!moveOK) {
            alive = false;
        }
        /*
        if (!alive) {
            BottomPos--;
        }
        */
    }
    void toBottom(){
        // not used. down is called repeatedly instead.
        // Do not erase this function for readability.
    }

    char moveBlock(const vector<vector<int>>&piledField, const vector<vector<int>>&field){
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
        /*
        if (!collisionCheck(piledField)) {
            alive = false;
        };
        */
        return c; // if fall c = ' '(space), otherwise null.
    }

    bool collisionCheck(const vector<vector<int>>&piledField) {
        //setSimPartsField();
        if (BottomPos + 0 == fieldHeight) {
            alive = false;
            return false;
        }
        mkPartsField();
        /*
        simPartsField = zeroField;
        for (int x = 0; x < tmp[0].size(); x++) {
            for (int y = 0; y < tmp.size(); y++) {
                simPartsField[BottomPos-y][LeftPos+x] = tmp[y][x];
            }
        }
        */
        for (int i = 0; i < fieldHeight; i++) {
            for (int j = 0; j < fieldWidth; j++) {
                if (piledField[i][j] + partsField[i][j] == 2) {
                    cout << "collision error" << endl;
                    moveOK = false;
                    //return;
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
    
    void drawField(const vector<vector<int>>&field) {
        for (int i = 0; i < fieldHeight; i++) {
            for (int j = 0; j <  fieldWidth; j++) {
                cout << field[i][j] ;
            }
            cout << endl;
        }
        cout << "--------------------" << endl;
    }

    void mergeField(const vector<vector<int>>&partsField) {
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
        block.collisionCheck(draw.piledField);
        if (!block.moveOK) {
            cout << " G A M E   O V E R " << endl;
            //draw.piledField = draw.field; // make setter?
            cout << "====================" << endl;
            //breakflag = true;
            return 0;
        }
        block.mkPartsField();
        draw.mergeField(block.partsField);

        cout << "piledField" << endl;
        draw.drawField(draw.piledField);
        cout << "partsField" << endl;
        draw.drawField(block.partsField);
        cout << "mergedField" << endl;
        draw.drawField(draw.field);

        while(1){
            //block.PartsFieldfindCollision(draw.piledField);
            Parts simBlock = block;
            char c = simBlock.moveBlock(draw.piledField, draw.field);
            do {
                if (c == ' ') {
                    simBlock.down(draw.piledField);
                }
                //simBlock.alive = simBlock.collisionCheck(draw.piledField);
                simBlock.collisionCheck(draw.piledField);
                if (!simBlock.alive) {
                    cout << "dead!" << endl;
                    draw.piledField = draw.field; // make setter?
                    cout << "====================" << endl;
                    breakflag = true;
                    break;
                }
                if (simBlock.moveOK) {
                    simBlock.mkPartsField();
                    //block.collisionCheck();
                    draw.mergeField(simBlock.partsField);
                }
            } while(c == ' ');
            if (breakflag) {
                break;
            }
            if (simBlock.moveOK) {
                block = simBlock;
            }

            cout << "piledField" << endl;
            draw.drawField(draw.piledField);
            cout << "partsField" << endl;
            draw.drawField(block.partsField);
            cout << "mergedField" << endl;
            draw.drawField(draw.field);

            //cin.get();
        }
        kind++;
    }
     return 0;
}