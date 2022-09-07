#include <iostream>
#include <vector>
#include "kbhit.hpp"
#include "common.hpp"
#include "parts.hpp"

using namespace std;

extern vector<vector<int>>zeroField;
extern clock_t startTime;
extern clock_t previousTime;
extern int waitTime;

Parts::Parts(vector<vector<int>>shape, const int idx, const vector<vector<int>>&piledField){
    shapeIndex = idx;
    shapeOfParts = shape;
    height = shapeOfParts.size();
    width = shapeOfParts[0].size();
    BottomPos = height-1;
}

void Parts::mkPartsField(){
    partsFieldColor = zeroField;
    for (int x = 0; x < shapeOfParts[0].size(); x++) {
        for (int y = 0; y < shapeOfParts.size(); y++) {
            partsFieldColor[BottomPos-y][LeftPos+x] = (shapeIndex + 1) * shapeOfParts[y][x];
        }
    }
}

bool Parts::rotate(const vector<vector<int>>&piledField){
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

void Parts::toLeft(const vector<vector<int>>&piledField){
    if (LeftPos > 0) {
        LeftPos--;
    }
}
void Parts::toRight(const vector<vector<int>>&piledField){
    if (LeftPos+width < fieldWidth) {
        LeftPos++;
    }
}
void Parts::down(const vector<vector<int>>&piledField){
    BottomPos++;
    collisionCheck(piledField);
    if (!moveOK) {
        alive = false;
    }
}
void Parts::toBottom(){
    // not used. down is called repeatedly instead.
    // Do not erase this function for readability.
}

char Parts::moveBlock(const vector<vector<int>>&piledField){
    cout << "fall:<space> rotate:UP DOWN RIGHT LEFT > ";
    char c = '\0';
    while(1) {
        startTime = clock();
        if (clock() - previousTime > waitTime) {
            previousTime = clock();
            down(piledField);
            return 'a'; // return '\0' causes segmentation falt.
        }
        if (kbhit()) {
            //cout << endl;
            previousTime = clock();
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

void Parts::collisionCheck(const vector<vector<int>>&piledField){ 
    if (BottomPos + 0 == fieldHeight) {
        alive = false;
        return;
    }
    Parts::mkPartsField();

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