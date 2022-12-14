#include <iostream>
#include <vector>
#include "common.hpp"
#include "board.hpp"
//#include "parts.hpp"

using namespace std;

extern vector<vector<int>>zeroField;
extern struct Shape
{
    vector<vector<int>>shape;
    string color;
};
extern vector<Shape>shapes;

Board::Board()
{
    fieldColor = zeroField;
    piledFieldColor = zeroField;
}

void Board::drawField(const vector<vector<int>>&field) {
    string color;
    for (int i = 0; i < fieldHeight; i++) {
        for (int j = 0; j <  fieldWidth; j++) {
            if (field[i][j] == 0) {
                color = "\33[30m\33[100m";
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

void Board::mkPartsField(Parts &block){
    block.partsFieldColor = zeroField;
    for (int x = 0; x < block.shapeOfParts[0].size(); x++) {
        for (int y = 0; y < block.shapeOfParts.size(); y++) {
            block.partsFieldColor[block.BottomPos-y][block.LeftPos+x] = (block.shapeIndex + 1) * block.shapeOfParts[y][x];
        }
    }
}

void Board::mergeField(const vector<vector<int>>&partsField) {
    for (int i = 0; i < fieldHeight; i++) {
        for (int j = 0; j < fieldWidth; j++) {
            fieldColor[i][j] = piledFieldColor[i][j] + partsField[i][j];
        }
    }
}

bool Board::deleteRow(vector<vector<int>>&piledField) {
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

void Board::updatePiledField() {
    piledFieldColor = fieldColor;
}

void Board::collisionCheck(const vector<vector<int>>&piledField, Parts &block){ 
    if (block.BottomPos + 0 == fieldHeight) {
        block.alive = false;
        return;
    }
    Board::mkPartsField(block);

    // ZeroOneField
    vector<vector<int>>ZeroOnePiledField = zeroField;
    vector<vector<int>>ZeroOnePartsField = zeroField;
    for (int i = 0; i < fieldHeight; i++) {
        for (int j = 0; j < fieldWidth; j++) {
            if (piledField[i][j] > 0) {
                ZeroOnePiledField[i][j] = 1;
            }
            if (block.partsFieldColor[i][j] > 0) {
                ZeroOnePartsField[i][j] = 1;
            }
        }
    }

    for (int i = 0; i < fieldHeight; i++) {
        for (int j = 0; j < fieldWidth; j++) {
            if (ZeroOnePiledField[i][j] + ZeroOnePartsField[i][j] > 1) {
                block.moveOK = false;
            }
        }
    }
}