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
    vector<vector<int>>partsField;

    vector<vector<int>> shapeOfParts;
    Parts(vector<vector<int>> &shape, const vector<vector<int>>&piledField){
        shapeOfParts = shape;
        height = shapeOfParts.size();
        width = shapeOfParts[0].size();
        BottomPos = height-1;
    }

    void mkPartsField(){
        partsField = zeroField;
        for (int x = 0; x < shapeOfParts[0].size(); x++) {
            for (int y = 0; y < shapeOfParts.size(); y++) {
                partsField[BottomPos-y][LeftPos+x] = shapeOfParts[y][x];
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
            if (piledField[BottomPos][LeftPos-1] == 0) {
                LeftPos--;
            }
        }
        cout << "left edge : " << LeftPos << endl;
    }
    void toRight(const vector<vector<int>>&piledField){
        if (LeftPos+width < fieldWidth) {
            if (piledField[BottomPos][LeftPos+width-1+0] == 0) {
                LeftPos++;
            }
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
        for (int i = 0; i < fieldHeight; i++) {
            for (int j = 0; j < fieldWidth; j++) {
                if (piledField[i][j] + partsField[i][j] == 2) {
                    //cout << "collision error" << endl;
                    moveOK = false;
                }
            }
        }
    }
};

// shape of blocks
//vector<vector<int>>shapeEmpty = {}; // to show blank field.
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
            "\33[4;35m"
        }
    };
    return shapes;
}

/*
class shapeI{
    public:
    vector<vector<int>>shape = {
        {1,1,1}
    };
    string color = "\33[36m";
};

class shapeO{
    public:
    vector<vector<int>>shape = {
        {1,1},
        {1,1}
    };
    string color = "\33[33m";
};

class shapeS{
    public:
    vector<vector<int>>shape = {
        {0,1,1},
        {1,1,0}
    };
    string color = "\33[32m";
};

class shapeZ{
    public:
    vector<vector<int>>shapeZ = {
        {1,1,0},
        {0,1,1}
    };
    string color = "\33[31m";
};

class shapeJ{
    public:
    vector<vector<int>>shapeJ = {
        {1,0,0},
        {1,1,1}
    };
    string color = "\33[34m";
};

class shapeL{
    public:
    vector<vector<int>>shapeL = {
        {0,0,1},
        {1,1,1}
    };
    string color = "\33[4;34m";
};
*/

class shapeT{
    public:
    vector<vector<int>>shape = {
        {0,1,0},
        {1,1,1},
    };
    string color = "\33[4;35m";
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
    
    void drawField(const vector<vector<int>>&field, string color) {
        for (int i = 0; i < fieldHeight; i++) {
            for (int j = 0; j <  fieldWidth; j++) {
                if (field[i][j] == 1) {
                    cout << color;
                }
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
                field[i][j] = piledField[i][j] + partsField[i][j];
            }
        }
    }

    bool deleteRow(vector<vector<int>>&piledField) {
        //bool complete = true;
        for (int x = 0; x < fieldWidth; x++) {
            if (piledField[fieldHeight-1][x] == 0) {
                //complete = false;
                return false;
            }
        }
        for (int y = fieldHeight-1; y > 0; y--) {
            for (int x = 0; x < fieldWidth; x++) {
                //cout << "y,x:" << y << "," << x << endl;
                piledField[y][x] = piledField[y-1][x];
            }
        }
        for (int x = 0; x < fieldWidth; x++) {
            piledField[0][x] = 0;
        }
        return true;
    }

};

int main() {
    // once
    Draw draw;
    vector<SHAPES>shapes = initShapes();

    int kind = 0;
    while(1) { // game loop
    random_device rnd;
    int randomnumber = rnd()%shapes.size();
    //cout << randomnumber << endl;
    //cout << shapes[randomnumber].color << "test" << endl;
        vector<vector<int>>shapeOfBlock;
        string shapeColor;
        bool breakflag = false;
        
        shapeOfBlock = shapes[randomnumber].shape;
        shapeColor = shapes[randomnumber].color;
        /*
        if (kind == 0) {
            shapeT shapetype;
            shapeOfBlock = shapetype.shape;
            shapeColor = shapetype.color;
        }else{
            shapeI shapetype;
            shapeOfBlock = shapetype.shape;
            shapeColor = shapetype.color;
        }
        */
        //shapeOfBlock = shapetype.shape;
        
        Parts block(shapeOfBlock, draw.piledField);
        // if no space to drop, break here and finish game.
        block.collisionCheck(draw.piledField);
        if (!block.moveOK) {
            cout << " G A M E   O V E R " << endl;
            cout << "====================" << endl;
            return 0;
        }

        block.mkPartsField();
        draw.mergeField(block.partsField);

        cout << "piledField" << endl;
        draw.drawField(draw.piledField, shapeColor);
        cout << "partsField" << endl;
        draw.drawField(block.partsField, shapeColor);
        cout << "Field" << endl;
        draw.drawField(draw.field, shapeColor);
        
        while (draw.deleteRow(draw.piledField)) {
        //if (draw.deleteRow(draw.piledField)) {
            block.mkPartsField();
            draw.mergeField(block.partsField);

            cout << "piledField" << endl;
            draw.drawField(draw.piledField, shapeColor);
            cout << "partsField" << endl;
            draw.drawField(block.partsField, shapeColor);
            cout << "mergedField" << endl;
            draw.drawField(draw.field, shapeColor);
        }

        while(1){
            Parts simBlock = block;
            char c = simBlock.moveBlock(draw.piledField, draw.field);
            cout << endl;
            do {
                if (c == ' ') {
                    simBlock.down(draw.piledField);
                }
                simBlock.collisionCheck(draw.piledField);
                if (!simBlock.alive) {
                    //cout << "dead!" << endl;
                    draw.piledField = draw.field; // make setter?
                    cout << "====================" << endl;
                    breakflag = true;
                    break;
                }
                if (simBlock.moveOK) {
                    simBlock.mkPartsField();
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
            draw.drawField(draw.piledField, shapeColor);
            cout << "partsField" << endl;
            draw.drawField(block.partsField, shapeColor);
            cout << "mergedField" << endl;
            draw.drawField(draw.field, shapeColor);

            //cin.get();
        }
        kind++;
    }
     return 0;
}