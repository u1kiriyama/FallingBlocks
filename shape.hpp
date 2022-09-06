#include <iostream>
#include <vector>

using namespace std;
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
