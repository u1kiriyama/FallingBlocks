//g++ -std=c++20 dropTest.cpp -o dropTest.out

#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>
#include <time.h>
#include "kbhit.hpp"
#include "shape.hpp"
#include "parts.hpp"
#include "board.hpp"
#include "common.hpp"

using namespace std;

vector<vector<int>>zeroField(fieldHeight, vector<int>(fieldWidth, 0));
clock_t startTime;
clock_t previousTime;
int waitTime;

int main() {
    // once
    Board board;
    vector<Parts>piledParts;
    char level;
    cout << "Level:\33[4me\33[0masy \33[4mm\33[0medium \33[4mh\33[0mard > ";
    cin >> level;
    if (level == 'e') {
        cout << "easy mode" << endl;
        waitTime = 2*1000*1000;
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
        block.collisionCheck(board.piledFieldColor);


        if (!block.moveOK) {
            cout << " G A M E   O V E R " << endl;
            cout << "====================" << endl;
            return 0;
        }

        block.mkPartsField();
        board.mergeField(block.partsFieldColor);

        cout << "piledField" << endl;
        board.drawField(board.piledFieldColor);
        cout << "partsField" << endl;
        board.drawField(block.partsFieldColor);
        cout << "Field(created)" << endl;
        board.drawField(board.fieldColor);
        
        while (board.deleteRow(board.piledFieldColor)) { // if delete a row, reboard field.
            cout << "while loop" << endl;
            block.mkPartsField();
            board.mergeField(block.partsFieldColor);

            cout << "piledField" << endl;
            board.drawField(board.piledFieldColor);
            cout << "partsField" << endl;
            board.drawField(block.partsFieldColor);
            cout << "Field(deleted)" << endl;
            board.drawField(board.fieldColor);
        }

        while(1){
            Parts simBlock = block;
            char c = simBlock.moveBlock(board.piledFieldColor);
            cout << endl;
            do {
                if (c == ' ') {
                    simBlock.down(board.piledFieldColor);
                }
                simBlock.collisionCheck(board.piledFieldColor);
                if (!simBlock.alive) {
                    //cout << "dead!" << endl;
                    board.piledFieldColor = board.fieldColor; // make setter?
                    cout << "====================" << endl;
                    breakflag = true;
                    break;
                }
                if (simBlock.moveOK) {
                    simBlock.mkPartsField();
                    board.mergeField(simBlock.partsFieldColor);
                }
            } while(c == ' ');
            if (breakflag) {
                break;
            }
            if (simBlock.moveOK) {
                block = simBlock;
            }

            cout << "piledField" << endl;
            board.drawField(board.piledFieldColor);
            cout << "partsField" << endl;
            board.drawField(block.partsFieldColor);
            cout << "Field(moved)" << endl;
            board.drawField(board.fieldColor);

            //cin.get();
        }
    }
     return 0;
}