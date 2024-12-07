/***********************************************************************
 * Header File:
  * Starlink  
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about Starlink
 ************************************************************************/
#ifndef STARLINK_H
#define STARLINK_H
#include "satellite.h"

namespace Starlink {
    class Starlink : public Satellite {
    public:
        friend class TestStarlink;
        Starlink(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle());
        void breakApart(Simulator* sim, vector<CelestialObject*> subParts = {});
        void draw() { ogs.drawStarlink(pos, rotationAngle.getDegree()); }
    };

    class StarlinkArray : public Part {
    public:
        StarlinkArray(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle());
        void draw() { ogs.drawStarlinkArray(pos, rotationAngle.getDegree()); }

    };

    class StarlinkBody : public Part {
    public:
        StarlinkBody(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle());
        void draw() { ogs.drawStarlinkBody(pos, rotationAngle.getDegree()); }

    };
}

#endif // STARLINK_H

