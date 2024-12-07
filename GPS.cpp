#include "satellite.h"
#include "part.h"
#include "simulator.h"
#include "celestialObject.h"

namespace GPS {
    GPS::GPS(Position pos, Velocity vel, Angle angle) : Satellite(pos, vel, angle) {
        Satellite(pos, vel, angle);
        this->radius = 7;
        this->numFragments = 2;
    }

    void GPS::breakApart(Simulator* sim, vector<CelestialObject*> subParts) {
        double x = this->getPosition().getMetersX();
        double y = this->getPosition().getMetersY();
        double offset = 10000;

        this->setExpired(true);
        sim->addObject(new GPSLeft(Position(x + offset, y + offset), randomVelocity(this->getVelocity())));
        sim->addObject(new GPSCenter(Position(x, y), randomVelocity(this->getVelocity())));
        sim->addObject(new GPSRight(Position(x - offset, y - offset), randomVelocity(this->getVelocity())));
    }

    GPSCenter::GPSCenter(Position pos, Velocity vel, Angle angle) : Part(pos, vel, angle) {
        this->partOrigin = "GPS";
        this->radius = 7;
        this->numFragments = 3;
    }

    GPSLeft::GPSLeft(Position pos, Velocity vel, Angle angle) : Part(pos, vel, angle) {
        this->partOrigin = "GPS";
        this->numFragments = 3;
        this->radius = 8;
    }

    GPSRight::GPSRight(Position pos, Velocity vel, Angle angle) : Part(pos, vel, angle) {
        this->partOrigin = "GPS";
        this->numFragments = 3;
        this->radius = 8;
    }
}
