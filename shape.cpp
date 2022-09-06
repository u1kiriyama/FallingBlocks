#include <iostream>
#include <vector>
#include "shape.hpp"

using namespace std;

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

//vector<Shape>shapes = {
shapes{
    shapeT,shapeO,shapeS,shapeZ,shapeJ,shapeL,shapeT
};