using namespace std;

class Parts{
    int height, width;
    int BottomPos = 0;
    int LeftPos = 6;
    bool alive = true;
    bool moveOK = true;

public:
    vector<vector<int>>partsFieldColor;
    int shapeIndex;
    vector<vector<int>> shapeOfParts;

    Parts(vector<vector<int>>shape, const int idx, const vector<vector<int>>&piledField);
    bool getmoveOK();
    bool getalive();
    void mkPartsField();
    bool rotate(const vector<vector<int>>&piledField);
    void toLeft(const vector<vector<int>>&piledField);
    void toRight(const vector<vector<int>>&piledField);
    void down(const vector<vector<int>>&piledField);
    void toBottom();
    char moveBlock(const vector<vector<int>>&piledField);
    void collisionCheck(const vector<vector<int>>&piledField);
};