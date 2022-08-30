//g++ -std=c++20 dropTest.cpp -o dropTest.out

#include <iostream>
#include <cstdlib>
#include <vector>

#define fieldHeight 10
#define fieldWidth 20
#define dropcnt 10

using namespace std;

class Parts{
    public:
    int height, width;
    int BottomPos = 3;
    int LeftPos = 6;
    bool alive = true;

    vector<vector<int>> shapeOfParts;
    Parts(vector<vector<int>> shape){
        shapeOfParts = shape;
        height = shapeOfParts.size();
        width = shapeOfParts[0].size();
    }
    ~Parts(){
        cout << "Block landed." << endl;
    }
    void clkwise(){}
    void counterclkwize(){}
    void aliveCheck(){
        if (BottomPos == fieldHeight-2) alive = false; // -2 is for debug
    }
};

// shape of blocks
vector<vector<int>> shapeOfEmpty = {}; // to show blank field.

vector<vector<int>> shapeOfTotsu = {
  {0, 1, 0},
  {1, 1, 1},
};
// 他の形も追加

class Draw{
    public:
    int cnt = 0;
    vector<vector<int>>field ;
    //vector<vector<int>> field(fieldHeight, vector<int>(fieldWidth,0));
    // todo usingを使ってvectorのエイリアスをつくり、短く表記できるようにする。
    Draw()
    {
        mkZeroField();
        cout << "--------------------" << endl;
    }

    void mkZeroField() {
        //vector<vector<int>>field = 
        field = 
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
    }

    void drawDisp(Parts &parts) {
        mkZeroField();

        for (int x = 0; x < parts.width; x++) {
            for (int y = 0; y < parts.height; y++) {
                field[parts.BottomPos-y][parts.LeftPos+x] = parts.shapeOfParts[y][x];
            }
        }
        for (int i = 0; i < fieldHeight; i++) {
            for (int j = 0; j < fieldWidth; j++) {
                cout << field[i][j] ;
            }
            cout << endl;
        }
        cout << "--------------------" << endl;
        //cnt++;
        cout << "cnt : " << cnt << endl;
    }

    // todo 揃ったら消すメソッド
};

int main() {
    Parts totsu(shapeOfTotsu);
    cout << "totsu height : " << totsu.height << endl;

    Draw draw;
    draw.drawDisp(totsu); // todo totsu -> empty
    for (int i = 0; i < dropcnt; i++) { // dropcnt could be fieldHeight.
        //system("reset");
        draw.mkZeroField(); // todo piledBlock 2dim vecを作ってそれに変更
        draw.drawDisp(totsu);
        draw.cnt++;
        cin.get();

        totsu.BottomPos++;
        totsu.aliveCheck();
        cout << totsu.BottomPos << endl;
        if (!totsu.alive) {break;}
    }
}