//
// Created by niko on 10.03.20.
//

// Local
#include "include/MuonTrackFinder.hh"

// System
#include <iostream>
#include <exception>
#include <cmath>

// ROOT
#include "TCanvas.h"
#include "TH3D.h"

MuonTrackFinder::MuonTrackFinder(const Muon& muon) :
        _track(0),
        _muon(muon),
        _previousCube(-1, -1, -1),
        _startCube(-1, -1, -1),
        _anotherDirectionCube(-1, -1, -1)
{
    _nOfTwists = 0;
}

Double_t MuonTrackFinder::Distance(const Point& cube1, const Point& cube2)
{
    return std::sqrt( (cube1.x - cube2.x) * (cube1.x - cube2.x)
               + (cube1.y - cube2.y) * (cube1.y - cube2.y)
               + (cube1.z - cube2.z) * (cube1.z - cube2.z) );
}

Point MuonTrackFinder::FindStartCube(const Point &cube)
{
    Int_t x = cube.x; Int_t y = cube.y; Int_t z = cube.z;
    std::vector<Point> cubes;

    for (Int_t i = -1; i <= 1; ++i) {
        for (Int_t j = -1; j <= 1; ++j) {
            for (Int_t k = -1; k <= 1; ++k) {
                if ( IsTrack(Point(x + i, y + j, z + k)) ) cubes.emplace_back(x + i, y + j, z + k);
            }
        }
    }

    Double_t minDist = 10000;
    Int_t minID = -1;
    for (Int_t i = 0; i < cubes.size(); ++i) {
        Double_t dist = Distance(cubes[i], _muon.cubeEnd);
        if (dist  < minDist) {
            minDist = dist;
            minID = i;
        }
    }

    if (minID == -1) {
       throw std::logic_error("Start cube is not found. Probably the beginning сube is from the trajectory on 2 cubes");
    }

    return cubes[minID];
}

bool MuonTrackFinder::IsEnd(const Point &cube) const {
    Int_t x = cube.x; Int_t y = cube.y; Int_t z = cube.z;
    bool check = false;

    for (Int_t i = -1; i <= 1; ++i) {
        for (Int_t j = -1; j <= 1; ++j) {
            for (int k = -1; k <= 1; ++k) {
                check = ( _muon.cubeEnd == Point(x + i, y + j, z + k) ) || check;
            }
        }
    }

    return check;
}

bool MuonTrackFinder::InVolume(const Point &cube) const {
    return cube.x >= 0 && cube.x <= 15
           && cube.y >= 0 && cube.y <= 15
           && cube.z >= 0 && cube.z <= 50;
}

bool MuonTrackFinder::IsTrack(const Point &cube) const {
    if ( !InVolume(cube) ) {
        return false;
    }

    Double_t x, y, z;
    Int_t intPoint = 0; // counts number of intersection points

    // plane x = cube.x
    x = cube.x;
    z = (x - _muon.cx) / _muon.mx;
    y = _muon.my * z + _muon.cy;
    if (z < cube.z + 1 && z > cube.z && y < cube.y + 1 && y > cube.y) {
        ++intPoint;
    }
    // plane y = cube.y
    y = cube.y;
    z = (y - _muon.cy) / _muon.my;
    x = _muon.mx * z + _muon.cx;
    if (z < cube.z + 1 && z > cube.z && x < cube.x + 1 && x > cube.x) {
        ++intPoint;
    }
    // plane z = cube.z
    z = cube.z;
    x = _muon.mx * z + _muon.cx;
    y = _muon.my * z + _muon.cy;
    if (x < cube.x + 1 && x > cube.x && y < cube.y + 1 && y > cube.y) {
        ++intPoint;
    }
    // plane x = cube.x + 1
    x = cube.x + 1;
    z = (x - _muon.cx) / _muon.mx;
    y = _muon.my * z + _muon.cy;
    if (z < cube.z + 1 && z > cube.z && y < cube.y + 1 && y > cube.y) {
        ++intPoint;
    }
    // plane y = cube.y + 1
    y = cube.y + 1;
    z = (y - _muon.cy) / _muon.my;
    x = _muon.mx * z + _muon.cx;;
    if (z < cube.z + 1 && z > cube.z && x < cube.x + 1 && x > cube.x) {
        ++intPoint;
    }
    // plane z = cube.z + 1
    z = cube.z + 1;
    x = _muon.mx * z + _muon.cx;
    y = _muon.my * z + _muon.cy;
    if (x < cube.x + 1 && x > cube.x && y < cube.y + 1 && y > cube.y) {
        ++intPoint;
    }

    return intPoint == 2; // if there are two intersection points - the cube is crossed with line
}

// Each cube has 6 planes x, y, z, x + 1, y + 1, z + 1
// The idea is to find intersection point between line and plane
std::vector<Point> MuonTrackFinder::FindNeighbors(const Point &cube) {
    if (!InVolume(cube)) {
        return std::vector<Point>();
    }

    Double_t x, y, z;
    std::vector<Point> neighbCubes;

    // plane x = cube.x
    x = cube.x;
    z = (x - _muon.cx) / _muon.mx;
    y = _muon.my * z + _muon.cy;
    if (z < cube.z + 1 && z > cube.z && y < cube.y + 1 && y > cube.y) {
        neighbCubes.emplace_back(Point(cube.x - 1, cube.y, cube.z));
    }
    // plane y = cube.y
    y = cube.y;
    z = (y - _muon.cy) / _muon.my;
    x = _muon.mx * z + _muon.cx;
    if (z < cube.z + 1 && z > cube.z && x < cube.x + 1 && x > cube.x) {
        neighbCubes.emplace_back(Point(cube.x, cube.y - 1, cube.z));
    }
    // plane z = cube.z
    z = cube.z;
    x = _muon.mx * z + _muon.cx;
    y = _muon.my * z + _muon.cy;
    if (x < cube.x + 1 && x > cube.x && y < cube.y + 1 && y > cube.y) {
        neighbCubes.emplace_back(Point(cube.x, cube.y, cube.z - 1));
    }
    // plane x = cube.x + 1
    x = cube.x + 1;
    z = (x - _muon.cx) / _muon.mx;
    y = _muon.my * z + _muon.cy;
    if (z < cube.z + 1 && z > cube.z && y < cube.y + 1 && y > cube.y) {
        neighbCubes.emplace_back(Point(cube.x + 1, cube.y, cube.z));
    }
    // plane y = cube.y + 1
    y = cube.y + 1;
    z = (y - _muon.cy) / _muon.my;
    x = _muon.mx * z + _muon.cx;;
    if (z < cube.z + 1 && z > cube.z && x < cube.x + 1 && x > cube.x) {
        neighbCubes.emplace_back(Point(cube.x, cube.y + 1, cube.z));
    }
    // plane z = cube.z + 1
    z = cube.z + 1;
    x = _muon.mx * z + _muon.cx;
    y = _muon.my * z + _muon.cy;
    if (x < cube.x + 1 && x > cube.x && y < cube.y + 1 && y > cube.y) {
        neighbCubes.emplace_back(Point(cube.x, cube.y, cube.z + 1));
    }

    if (neighbCubes.empty()) {
        throw std::logic_error("No neighboring cube is found");
    } else if (neighbCubes.size() == 1) {
        throw std::logic_error("One neighboring cube is found");
    } else if (neighbCubes.size() > 2) {
        throw std::logic_error("More than two neighboring cubes are found");
    }

    return neighbCubes;
}

std::vector<Point> MuonTrackFinder::GetTrack() {
    Point cCube = FindStartCube(_muon.cubeStart); // current cube
//    std::cout << "cubeStart " << _muon.cubeStart << std::endl;
    _track.push_back(cCube);

    do {
        cCube = FindNextCube(cCube);
        _track.push_back(cCube);
    } while (!IsEnd(cCube));

    return _track;
}

#include <thread>
#include <chrono>
Point MuonTrackFinder::FindNextCube(const Point &cube) {
    if (!InVolume(cube)) {
        throw std::logic_error("Cube is outside the detector volume");
    }

    std::vector<Point> neighbCubes = FindNeighbors(cube);

//    std::cout << "FindNextCube" << std::endl;
//    std::cout << "|||||||||||||||||||||||||||||" << std::endl;
//    std::cout << cube << std::endl;
//    std::cout << neighbCubes[0] << std::endl;
//    std::cout << neighbCubes[1] << std::endl;
//    std::this_thread::sleep_for (std::chrono::milliseconds(500));

    // Choosing the right cube
    if (_previousCube == Point(-1, -1, -1)) {
        _startCube = cube;
        _previousCube = cube;
//        std::cout << "Starting cube " << _startCube << std::endl;
//        std::cout << "Previous cube " << _previousCube << std::endl;
        if ( InVolume(neighbCubes[0]) && InVolume(neighbCubes[1]) ) {
            _anotherDirectionCube = neighbCubes[1];
//            std::cout << "Another direction cube " << _anotherDirectionCube << std::endl;
            return neighbCubes[0];
        } else if ( !InVolume(neighbCubes[0]) ){
//            std::cout << "Another direction cube " << _anotherDirectionCube << std::endl;
            return neighbCubes[1];
        } else if ( !InVolume(neighbCubes[1]) ) {
//            std::cout << "Another direction cube " << _anotherDirectionCube << std::endl;
            return neighbCubes[0];
        }
    }

    if (neighbCubes[1] == _previousCube) {
        if ( !InVolume(neighbCubes[0]) ) {
            if ( _nOfTwists == 1 ) {
                throw std::logic_error("Probably the ending сube is from the trajectory on 2 cubes");
            }
            SwitchDirection();
            return _anotherDirectionCube;
        }
        _previousCube = cube;
        return neighbCubes[0];
    } else {
        if ( !InVolume(neighbCubes[1]) ) {
            if ( _nOfTwists == 1 ) {
                throw std::logic_error("Probably the endCube is away from the trajectory on 2 cubes");
            }
            SwitchDirection();
            return _anotherDirectionCube;
        }
        _previousCube = cube;
        return neighbCubes[1];
    }
}

void MuonTrackFinder::SwitchDirection() {
    _track.clear();
    _track.shrink_to_fit();
    _track.push_back(_startCube);
    _previousCube = _startCube;
    _nOfTwists = 1;
}

// Leave if you want _track to be deleted once the variable which stores returned vector deletes from GetTrack method
MuonTrackFinder::~MuonTrackFinder() {
//    std::cerr << "Destructor of MuonTrackFinder has been invoked" << std::endl;
}
