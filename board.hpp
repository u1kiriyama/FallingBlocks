using namespace std;

class Board{
    public:
    vector<vector<int>>field;
    vector<vector<int>>piledField;
    vector<vector<int>>fieldColor;
    vector<vector<int>>piledFieldColor;
    Board();
    void drawField(const vector<vector<int>>&field);
    void mergeField(const vector<vector<int>>&partsField);
    bool deleteRow(vector<vector<int>>&piledField);
    void updatePiledField();
};