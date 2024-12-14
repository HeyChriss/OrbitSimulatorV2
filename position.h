/***********************************************************************
 * Header File:
 *    Position
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about Position
 ************************************************************************/
#pragma once

#include <iostream> 
#include <cmath>
#include "angle.h"

class TestPosition;
class Acceleration;
class Velocity;

/*********************************************
 * Position
 * A single position on the field in Meters
 *********************************************/
class Position
{
public:
    friend TestPosition;
    friend class TestHubble;
    friend class TestDragon;
    friend class TestGPS;
    friend class TestShip;
    friend class TestSputnik;
    friend class TestStarlink;
    friend class TestCelestialObject;
    friend class TestSatellite;
    friend class TestProjectile;
    friend class TestFragment;
    friend class TestPart;

    Position() : x(0.0), y(0.0) {}
    Position(double x, double y);
    Position(const Position& pt) : x(pt.x), y(pt.y) {}
    Position& operator = (const Position& pt);

    // getters
    double getMetersX()       const { return x; }
    double getMetersY()       const { return y; }
    double getPixelsX()       const { return x / metersFromPixels; }
    double getPixelsY()       const { return y / metersFromPixels; }

    // setters
    void setMeters(double xMeters, double yMeters) { x = xMeters; y = yMeters; }
    void setMetersX(double xMeters) { x = xMeters; }
    void setMetersY(double yMeters) { y = yMeters; }
    void setPixelsX(double xPixels) { x = xPixels * metersFromPixels; }
    void setPixelsY(double yPixels) { y = yPixels * metersFromPixels; }
    void addMetersX(double dxMeters) { setMetersX(getMetersX() + dxMeters); }
    void addMetersY(double dyMeters) { setMetersY(getMetersY() + dyMeters); }
    void addPixelsX(double dxPixels) { setPixelsX(getPixelsX() + dxPixels); }
    void addPixelsY(double dyPixels) { setPixelsY(getPixelsY() + dyPixels); }
    void addPixels(double totalPixels, Angle angle) {
        double xPixels = totalPixels * sin(angle.getRadian());
        double yPixels = totalPixels * cos(angle.getRadian());

        this->addPixelsX(xPixels);
        this->addPixelsY(yPixels);
    }

    void setZoom(double metersFromPixels)
    {
        this->metersFromPixels = metersFromPixels;
    }

    double getZoom() const { return metersFromPixels; }

private:
    double x;                 // horizontal position
    double y;                 // vertical position
    static double metersFromPixels;
};

/*********************************************
 * COMPUTE DISTANCE
 * Find the distance between two positions
 *********************************************/
inline double computeDistance(const Position& pos1, const Position& pos2)
{
    double differenceX = pos1.getMetersX() - pos2.getMetersX();
    double differenceY = pos1.getMetersY() - pos2.getMetersY();
    return sqrt((differenceX * differenceX) +
        (differenceY * differenceY));
}

// stream I/O useful for debugging
std::ostream& operator << (std::ostream& out, const Position& pt);
std::istream& operator >> (std::istream& in, Position& pt);


/*********************************************
 * PT
 * Trivial point
 *********************************************/
struct PT
{
    double x;
    double y;
};




