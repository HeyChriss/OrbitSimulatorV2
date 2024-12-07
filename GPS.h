/***********************************************************************
 * Header File:
 *    GPS
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about GPS
 ************************************************************************/

#ifndef GPS_H
#define GPS_H
#include "satellite.h"

namespace GPS {
    class GPS : public Satellite {
    public:
        friend class TestGPS;
        GPS(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle());
        void breakApart(Simulator* sim, vector<CelestialObject*> subParts = {});
        void draw() { ogs.drawGPS(pos, rotationAngle.getDegree()); }
    };

    class GPSCenter : public Part {
    public:
        GPSCenter(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle());
        void draw() { ogs.drawGPSCenter(pos, rotationAngle.getDegree()); }

    };

    class GPSLeft : public Part {
    public:
        GPSLeft(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle());
        void draw() { ogs.drawGPSLeft(pos, rotationAngle.getDegree()); }

    };

    class GPSRight : public Part {
    public:
        GPSRight(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle());
        void draw() { ogs.drawGPSRight(pos, rotationAngle.getDegree()); }

    };
}

#endif // GPS_H

