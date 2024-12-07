/***********************************************************************
 * Header File:
 *    Part
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about part
 ************************************************************************/

#pragma once
#include "celestialObject.h"

class Part : public CelestialObject
{
public:

    friend class TestSatellite;
    friend class TestPart;

    Part(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : CelestialObject(pos, vel, angle)
    {
        this->numFragments = 0;
        this->radius = 1;
        this->invincibilityCount = 0;
    };

    bool isHit(CelestialObject* other);
    void update(double time, double gravity, double planetRadius);

    string partOrigin;
    int invincibilityCount;
};

