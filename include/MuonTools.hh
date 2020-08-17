//
// Created by niko on 10.03.20.
//

#ifndef MuonTools_hh
#define MuonTools_hh

// ROOT
#include "RtypesCore.h"

// System
#include <iostream>
#include <vector>

class Point {
public:
    Point();
    Point(Int_t _x, Int_t _y, Int_t _z);
    Point(const Point& point);

    Int_t x;
    Int_t y;
    Int_t z;
};

//using Points = std::vector<Point>;
using Points = std::vector<Point>;

class Muon {
public:
    Point cubeStart;
    Point cubeEnd;

    Double_t htime;
    Double_t mx;
    Double_t my;
    Double_t cx;
    Double_t cy;

    Muon();

    Muon(Int_t _xCubeStart, Int_t _yCubeStart, Int_t _zCubeStart,
            Int_t _xCubeEnd, Int_t _yCubeEnd, Int_t _zCubeEnd,
         Double_t _htime,
         Double_t _mx, Double_t _my,
         Double_t _cx, Double_t _cy);
};

std::ostream& operator << (std::ostream& os, const Point& point);
bool operator == (const Point& lhs, const Point& rhs);
bool operator != (const Point& lhs, const Point& rhs);
bool operator<(const Point &lhs, const Point &rhs);
bool operator>(const Point &lhs, const Point &rhs);
bool operator<=(const Point &lhs, const Point &rhs);
bool operator>=(const Point &lhs, const Point &rhs);

#endif //MuonTools_hh
