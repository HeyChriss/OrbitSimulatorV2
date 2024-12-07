/***********************************************************************
 * Header File:
 *    Dragon
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about the Crew Dragon 
 ************************************************************************/
#ifndef DRAGON_H
#define DRAGON_H
#include "satellite.h"

namespace Dragon {
    class Dragon : public Satellite {
    public:
        friend class TestDragon;
        Dragon(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle());
        void breakApart(Simulator* sim, vector<CelestialObject*> subParts = {});
        void draw() { ogs.drawCrewDragon(pos, rotationAngle.getDegree()); }
    };

    class DragonCenter : public Part {
    public:
        DragonCenter(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle());
        void draw() { ogs.drawCrewDragonCenter(pos, rotationAngle.getDegree()); }

    };

    class DragonLeft : public Part {
    public:
        DragonLeft(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle());
        void draw() { ogs.drawCrewDragonLeft(pos, rotationAngle.getDegree()); }

    };

    class DragonRight : public Part {
    public:
        DragonRight(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle());
        void draw() { ogs.drawCrewDragonRight(pos, rotationAngle.getDegree()); }

    };
}

#endif // DRAGON_H
