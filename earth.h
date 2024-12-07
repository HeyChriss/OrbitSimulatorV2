/***********************************************************************
 * Header File:
 *    Earth
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about earth
 ************************************************************************/

#pragma once
#include "celestialObject.h"

class Earth : public CelestialObject
{
public:
    Earth(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : CelestialObject(pos, vel, angle) {
        this->radius = 6378000.0;
        this->gravity = -9.8067;
    };

    double getGravity() { return this->gravity; };
    void draw() override { ogs.drawEarth(pos, rotationAngle.getRadian()); }

    double getRadius() const override { return this->radius; }

    void update(double time, double gravity = 0.0, double radius = 0.0) override {
        Angle a;
        a.addRadian(-(2 * 3.142 / 30) * 24.0 * 60.0 / 86400.0);
        this->rotationAngle += a.getRadian();
    }
private:
    double gravity;
};

