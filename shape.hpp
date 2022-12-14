using namespace std;

class Shape{
    public:
    vector<vector<int>>shape;
    string color;
};

Shape shapeI = {
    {
        {1,1,1}
    },
    "\33[36m"
};

Shape shapeO = {
    {
        {1,1},
        {1,1}
    },
    "\33[33m"
};

Shape shapeS = {
    {
        {0,1,1},
        {1,1,0}
    },
    "\33[32m"
};

Shape shapeZ = {
    {
        {1,1,0},
        {0,1,1}
    },
    "\33[31m"
};

Shape shapeJ = {
    {
        {1,0,0},
        {1,1,1}
    },
    "\33[34m"
};

Shape shapeL = {
    {
        {1,1,1},
        {1,0,0}
    },
    "\33[4;34m"
};

Shape shapeT = {
    {
        {0,1,0},
        {1,1,1}
    },
    "\33[35m"
};