/***********************************************************************
 * Header File:
 *    Satellite
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about Satellite
 ************************************************************************/
#pragma once
#include "part.h"


class Satellite : public CelestialObject
{
public:
    friend class TestSatellite;
    friend class TestHubble;

    Satellite(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : CelestialObject(pos, vel, angle)
    {
        this->radius = 10;
        this->numFragments = 2;
        this->defective = 0;
    };

    virtual void update(double time, double gravity, double planetRadius);
    virtual void breakApart(Simulator* sim, vector<CelestialObject*> subParts = {})
    {
        CelestialObject::breakApart(sim, subParts);
    }

protected:
    bool defective;
};

