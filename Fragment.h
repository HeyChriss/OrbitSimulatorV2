/***********************************************************************
 * Header File:
 *    Fragment
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about Fragment
 ************************************************************************/
#pragma once
#include "CelestialObject.h"
#include "uiDraw.h"

class Fragment : public CelestialObject
{
public:
    friend class TestFragment;
    friend class TestProjectile;

    Fragment(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : CelestialObject(pos, vel, angle)
    {
        this->lifetime = random(50, 100);
        this->rotationAngle = random(0.0, 2.0 * 3.141);
        this->radius = 2;

        // Fragments cannot break apart more; they simply expire after some time
        this->hasBeenHit = true;
    };

    void update(double time, double gravity, double radius);
    //   void breakApart(Simulator* sim);
    void draw() { if (!getExpired()) ogs.drawFragment(pos, rotationAngle.getDegree()); }
    bool isExpired() { if (lifetime <= 0) return true; else { lifetime--; return false; } }

protected:
    int lifetime;

};

