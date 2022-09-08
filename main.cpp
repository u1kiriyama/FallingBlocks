#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>
#include <time.h>
#include "common.hpp"
#include "shape.hpp"
#include "board.hpp"
#include "parts.hpp"

using namespace std;

vector<vector<int>>zeroField(fieldHeight, vector<int>(fieldWidth, 0));
clock_t startTime;
clock_t previousTime;
int waitTime;

vector<Shape>shapes = {
    shapeI,shapeO,shapeS,shapeZ,shapeJ,shapeL,shapeT
};

int main() {
    // once
    Board board;
    vector<Parts>piledParts;
    char level;
    cout << "Level:\33[4me\33[0masy \33[4mm\33[0medium \33[4mh\33[0mard > ";
    cin >> level;
    if (level == 'e') {
        cout << "easy mode" << endl;
        waitTime = 100*2*1000*1000;
    }else if (level == 'm') {
        cout << "medium mode" << endl;
        waitTime = 1*1000*1000;
    }else if (level == 'h') {
        cout << "hard mode" << endl;
        waitTime = 500*1000;
    }else{
        cout << "medium mode" << endl;
        waitTime = 1*1000*1000;
    }

    previousTime = clock();
    while(1) { // game loop
        random_device rnd;
        int shapeIndex = rnd()%shapes.size();
        vector<vector<int>>shapeOfBlock;
        string shapeColor;
        bool breakflag = false;
        
        shapeOfBlock = shapes[shapeIndex].shape;
        shapeColor = shapes[shapeIndex].color;
        
        Parts block(shapeOfBlock, shapeIndex, board.piledFieldColor);
        // if no space to drop, break here and finish game.

        //block.collisionCheck(board.piledFieldColor);
        board.collisionCheck(board.piledFieldColor, block);

        if (!block.getmoveOK()) {
            cout << " G A M E   O V E R " << endl;
            cout << "====================" << endl;
            return 0;
        }

        //block.mkPartsField();
        cout << "initial" << endl;
        board.mkPartsField(block);
        board.mergeField(block.partsFieldColor);
        board.drawField(board.fieldColor);
        
        // if delete a row, redraw field.
        while (board.deleteRow(board.piledFieldColor)) {
            //block.mkPartsField();
            cout << "completed a row";
            board.mkPartsField(block);
            board.mergeField(block.partsFieldColor);
            board.drawField(board.fieldColor);
        }

        while(1){
            Parts simBlock = block; // create a block for sim of next step.
            char c = simBlock.moveBlock(board.piledFieldColor);
            cout << endl;
            do {
                if (c == ' ') {
                    simBlock.down(board.piledFieldColor);
                    board.collisionCheck(board.piledFieldColor, simBlock);
                    if (!simBlock.moveOK)
                    {
                        simBlock.alive = false;
                    }
                }
                board.collisionCheck(board.piledFieldColor, simBlock);
                if (int(c) == 66) {
                    if (!simBlock.moveOK)
                    {
                        simBlock.alive = false;
                    }
                }
                //simBlock.collisionCheck(board);
                if (!simBlock.getalive()) { //dead
                    board.updatePiledField();
                    cout << "====================" << endl;
                    breakflag = true;
                    break;
                }
                if (simBlock.getmoveOK()) {
                    /*
                    cout << "moveOK" << endl;
                    board.mkPartsField(simBlock);
                    board.mergeField(simBlock.partsFieldColor);
                    board.drawField(board.fieldColor); //
                    */
                    board.mkPartsField(simBlock);
                    board.mergeField(simBlock.partsFieldColor);
                    block = simBlock;
                }else{
                    /*
                    board.mkPartsField(simBlock);
                    board.mergeField(simBlock.partsFieldColor);
                    breakflag = true;
                    break;
                    */
                }
            } while(c == ' ');
            if (breakflag) {
                break;
            }
            if (simBlock.getmoveOK()) {
                cout << "moveOK. update block" << endl;
                //block = simBlock;
                /*
                board.mkPartsField(simBlock); //
                board.mergeField(simBlock.partsFieldColor);//
                board.drawField(board.fieldColor);
                */
            }

            cout << "last" << endl;
            board.mkPartsField(block); //
            board.mergeField(block.partsFieldColor);//
            board.drawField(board.fieldColor);
        }
    }
     return 0;
}