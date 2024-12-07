/***********************************************************************
 * Header File:
 *    Hubble
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about hubble
 ************************************************************************/

#ifndef HUBBLE_H
#define HUBBLE_H
#include "satellite.h"

namespace Hubble {
    class Hubble : public Satellite {
    public:
        Hubble(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle());
        void breakApart(Simulator* sim, vector<CelestialObject*> subParts = {});
        void draw() { ogs.drawHubble(pos, rotationAngle.getDegree()); }
    };

    class HubbleComputer : public Part {
    public:
        HubbleComputer(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle());
        void draw() { ogs.drawHubbleComputer(pos, rotationAngle.getDegree()); }

    };

    class HubbleLeft : public Part {
    public:
        HubbleLeft(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle());
        void draw() { ogs.drawHubbleLeft(pos, rotationAngle.getDegree()); }

    };

    class HubbleRight : public Part {
    public:
        HubbleRight(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle());
        void draw() { ogs.drawHubbleRight(pos, rotationAngle.getDegree()); }

    };

    class HubbleTelescope : public Part {
    public:
        HubbleTelescope(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle());
        void draw() { ogs.drawHubbleTelescope(pos, rotationAngle.getDegree()); }
    };


    class DummyHubble : public Hubble {
    public:
        DummyHubble() {}

        void breakApart(Simulator* sim, vector<CelestialObject*> subParts = {}) { assert(false); }
        void draw() { assert(false); }

    };
}

#endif // HUBBLE_H

