//
// Created by niko on 10.03.20.
//

#ifndef MuonTrackFinder_hh
#define MuonTrackFinder_hh

// Local
#include "include/MuonTools.hh"

// System
#include <vector>
#include <utility>

class MuonTrackFinder {
public:
    explicit MuonTrackFinder(const Muon &muon);

    ~MuonTrackFinder();

    std::vector<Point> GetTrack();

private:
    bool IsEnd(const Point &cube) const;

    bool InVolume(const Point &cube) const;

    bool IsTrack(const Point &cube) const;

    static Double_t Distance(const Point &cube1, const Point &cube2);

    std::vector<Point> FindNeighbors(const Point &cube);

    Point FindStartCube(const Point &cube);

    Point FindNextCube(const Point &cube);

    void SwitchDirection();

    Int_t _nOfTwists; // number of twists

    Muon _muon;

    Point _previousCube;
    Point _startCube;
    Point _anotherDirectionCube;

    std::vector<Point> _track;
};

#endif //MuonTrackFinder_hh
