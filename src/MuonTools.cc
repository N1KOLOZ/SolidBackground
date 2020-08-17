//
// Created by niko on 10.03.20.
//

// Local
#include "include/MuonTools.hh"

// System
#include <iomanip>
#include <tuple>

Point::Point() {
    x = -1;
    y = -1;
    z = -1;
}

Point::Point(Int_t _x, Int_t _y, Int_t _z) {
    x = _x;
    y = _y;
    z = _z;
}

Point::Point(const Point &point) {
    x = point.x;
    y = point.y;
    z = point.z;
}

Muon::Muon(Int_t _xCubeStart, Int_t _yCubeStart, Int_t _zCubeStart,
           Int_t _xCubeEnd, Int_t _yCubeEnd, Int_t _zCubeEnd,
           Double_t _htime,
           Double_t _mx, Double_t _my,
           Double_t _cx, Double_t _cy) :
        cubeStart(Point(_xCubeStart, _yCubeStart, _zCubeStart)),
        cubeEnd(Point(_xCubeEnd, _yCubeEnd, _zCubeEnd))
{
    htime = _htime;
    mx = _mx;
    my = _my;
    cx = _cx;
    cy = _cy;
}

bool operator==(const Point &lhs, const Point &rhs) {
    return std::tie(lhs.x, lhs.y, lhs.z) == std::tie(rhs.x, rhs.y, rhs.z);
}

bool operator!=(const Point &lhs, const Point &rhs) {
    return std::tie(lhs.x, lhs.y, lhs.z) != std::tie(rhs.x, rhs.y, rhs.z);
}

bool operator<(const Point &lhs, const Point &rhs) {
    return std::tie(lhs.x, lhs.y, lhs.z) < std::tie(rhs.x, rhs.y, rhs.z);
}

bool operator>(const Point &lhs, const Point &rhs) {
    return std::tie(lhs.x, lhs.y, lhs.z) > std::tie(rhs.x, rhs.y, rhs.z);
}

bool operator<=(const Point &lhs, const Point &rhs) {
    return std::tie(lhs.x, lhs.y, lhs.z) <= std::tie(rhs.x, rhs.y, rhs.z);
}

bool operator>=(const Point &lhs, const Point &rhs) {
    return std::tie(lhs.x, lhs.y, lhs.z) >= std::tie(rhs.x, rhs.y, rhs.z);
}

/*
std::ostream &operator<<(std::ostream &os, const Point &point) {
    os << std::setw(3) << point.x << ','
       << std::setw(3) << point.y << ','
       << std::setw(3) << point.z;
    return os;
}
*/

std::ostream &operator<<(std::ostream &os, const Point &point) {
    os << point.x << ' ' << point.y << ' ' << point.z;
    return os;
}
