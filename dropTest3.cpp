//g++ -std=c++20 dropTest.cpp -o dropTest.out

#include <iostream>
#include <cstdlib>
#include <vector>
#include <random>
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
    vector<vector<int>>partsFieldColor;
    int shapeIndex;

    vector<vector<int>> shapeOfParts;
    Parts(vector<vector<int>>shape, const int idx, const vector<vector<int>>&piledField){
        shapeIndex = idx;
        shapeOfParts = shape;
        height = shapeOfParts.size();
        width = shapeOfParts[0].size();
        BottomPos = height-1;
    }

    void mkPartsField(){
        partsFieldColor = zeroField;
        for (int x = 0; x < shapeOfParts[0].size(); x++) {
            for (int y = 0; y < shapeOfParts.size(); y++) {
                partsFieldColor[BottomPos-y][LeftPos+x] = (shapeIndex + 1) * shapeOfParts[y][x];
            }
        }
    }

    bool rotate(const vector<vector<int>>&piledField){
        vector<vector<int>>tmp(width, vector<int>(height));
        // rotation
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                tmp[x][height-1-y] = shapeOfParts[y][x];
            }
        }

        shapeOfParts = tmp;
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
            LeftPos--;
        }
        cout << "left edge : " << LeftPos << endl;
    }
    void toRight(const vector<vector<int>>&piledField){
        if (LeftPos+width < fieldWidth) {
            LeftPos++;
        }
        cout << "right edge : " << LeftPos+width-1 << endl;
    }
    void down(const vector<vector<int>>&piledField){
        BottomPos++;
        collisionCheck(piledField);
        if (!moveOK) {
            alive = false;
        }
    }
    void toBottom(){
        // not used. down is called repeatedly instead.
        // Do not erase this function for readability.
    }

    char moveBlock(const vector<vector<int>>&piledField, const vector<vector<int>>&field){
        cout << "fall:<space> rotate:UP DOWN RIGHT LEFT > ";
        char c = '\0';
        while(1) {
            if (kbhit()) {
                //cout << endl;
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

    void collisionCheck(const vector<vector<int>>&piledField){ 
        if (BottomPos + 0 == fieldHeight) {
            alive = false;
            return;
        }
        mkPartsField();

        // ZeroOneField
        vector<vector<int>>ZeroOnePiledField = zeroField;
        vector<vector<int>>ZeroOnePartsField = zeroField;
        for (int i = 0; i < fieldHeight; i++) {
            for (int j = 0; j < fieldWidth; j++) {
                if (piledField[i][j] > 0) {
                    ZeroOnePiledField[i][j] = 1;
                }
                if (partsFieldColor[i][j] > 0) {
                    ZeroOnePartsField[i][j] = 1;
                }
            }
        }

        for (int i = 0; i < fieldHeight; i++) {
            for (int j = 0; j < fieldWidth; j++) {
                if (ZeroOnePiledField[i][j] + ZeroOnePartsField[i][j] > 1) {
                    moveOK = false;
                }
            }
        }
    }
};

// shape of blocks
struct SHAPES
{
    vector<vector<int>>shape;
    string color;
};
vector<SHAPES> initShapes() {
    vector<SHAPES>shapes =
    {
        {
            {
                {1,1,1}
            },
            "\33[36m"
        },
        {
            {
                {1,1},
                {1,1}
            },
            "\33[33m"
        },
        {
            {
                {0,1,1},
                {1,1,0}
            },
            "\33[32m"
        },
        {
            {
                {1,1,0},
                {0,1,1}
            },
            "\33[31m"
        },
        {
            {
                {1,0,0},
                {1,1,1}
            },
            "\33[34m"
        },
        {
            {
                {0,0,1},
                {1,1,1}
            },
            "\33[4;34m"
        },
        {
            {
                {0,1,0},
                {1,1,1},
            },
            "\33[35m"
        }
    };
    return shapes;
};
vector<SHAPES>shapes = initShapes();

// 他の形も追加

class Draw{ // not good name -> Board
    public:
    vector<vector<int>>field;
    vector<vector<int>>piledField;
    vector<vector<int>>fieldColor;
    vector<vector<int>>piledFieldColor;
    Draw()
    {
        fieldColor = zeroField;
        piledFieldColor = zeroField;
    }
    
    void drawField(const vector<vector<int>>&field) {
        string color;
        for (int i = 0; i < fieldHeight; i++) {
            for (int j = 0; j <  fieldWidth; j++) {
                if (field[i][j] == 0) {
                    color = "\33[30m\33[100m"; // zero is glay
                }else if (field[i][j]-1 < shapes.size()) {
                    color = shapes[field[i][j]-1].color;
                }
                cout << color;
                cout << field[i][j];
                cout << "\33[m"; // default color
            }
            cout << endl;
        }
        cout << "--------------------" << endl;
    }

    void mergeField(const vector<vector<int>>&partsField) {
        for (int i = 0; i < fieldHeight; i++) {
            for (int j = 0; j < fieldWidth; j++) {
                fieldColor[i][j] = piledFieldColor[i][j] + partsField[i][j];
            }
        }
    }

    bool deleteRow(vector<vector<int>>&piledField) {
        for (int j = 0; j < fieldHeight; j++) {
            bool complete = true;
            for (int x = 0; x < fieldWidth; x++) {
                if (piledField[fieldHeight-1-j][x] == 0) {
                    complete = false;
                    continue;
                }
            }
            if (!complete) {continue;}
            for (int y = fieldHeight-1-j; y > 0; y--) {
                for (int x = 0; x < fieldWidth; x++) {
                    piledField[y][x] = piledField[y-1][x];
                }
            }
            for (int x = 0; x < fieldWidth; x++) {
                piledField[0][x] = 0;
            }
            return true;
        }
        return false;
    }

};

int main() {
    // once
    Draw draw;
    vector<Parts>piledParts;

    while(1) { // game loop
        random_device rnd;
        int shapeIndex = rnd()%shapes.size();
        vector<vector<int>>shapeOfBlock;
        string shapeColor;
        bool breakflag = false;
        
        shapeOfBlock = shapes[shapeIndex].shape;
        shapeColor = shapes[shapeIndex].color;
        
        Parts block(shapeOfBlock, shapeIndex, draw.piledFieldColor);
        // if no space to drop, break here and finish game.
        block.collisionCheck(draw.piledFieldColor);
        if (!block.moveOK) {
            cout << " G A M E   O V E R " << endl;
            cout << "====================" << endl;
            return 0;
        }

        block.mkPartsField();
        draw.mergeField(block.partsFieldColor);

        cout << "piledField" << endl;
        draw.drawField(draw.piledFieldColor);
        cout << "partsField" << endl;
        draw.drawField(block.partsFieldColor);
        cout << "Field(created)" << endl;
        draw.drawField(draw.fieldColor);
        
        while (draw.deleteRow(draw.piledFieldColor)) { // if delete a row, redraw field.
            cout << "while loop" << endl;
            block.mkPartsField();
            draw.mergeField(block.partsFieldColor);

            cout << "piledField" << endl;
            draw.drawField(draw.piledFieldColor);
            cout << "partsField" << endl;
            draw.drawField(block.partsFieldColor);
            cout << "Field(deleted)" << endl;
            draw.drawField(draw.fieldColor);
        }

        while(1){
            Parts simBlock = block;
            char c = simBlock.moveBlock(draw.piledFieldColor, draw.fieldColor);
            cout << endl;
            do {
                if (c == ' ') {
                    simBlock.down(draw.piledFieldColor);
                }
                simBlock.collisionCheck(draw.piledFieldColor);
                if (!simBlock.alive) {
                    //cout << "dead!" << endl;
                    draw.piledFieldColor = draw.fieldColor; // make setter?
                    cout << "====================" << endl;
                    breakflag = true;
                    break;
                }
                if (simBlock.moveOK) {
                    simBlock.mkPartsField();
                    draw.mergeField(simBlock.partsFieldColor);
                }
            } while(c == ' ');
            if (breakflag) {
                break;
            }
            if (simBlock.moveOK) {
                block = simBlock;
            }

            cout << "piledField" << endl;
            draw.drawField(draw.piledFieldColor);
            cout << "partsField" << endl;
            draw.drawField(block.partsFieldColor);
            cout << "Field(moved)" << endl;
            draw.drawField(draw.fieldColor);

            //cin.get();
        }
    }
     return 0;
}