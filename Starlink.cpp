#include "starlink.h"
#include "satellite.h"
#include "part.h"
#include "simulator.h"
#include "celestialObject.h"

namespace Starlink {
    Starlink::Starlink(Position pos, Velocity vel, Angle angle) : Satellite(pos, vel, angle) {
        Satellite(pos, vel, angle);
        this->radius = 7;
        this->numFragments = 2;
    }

    void Starlink::breakApart(Simulator* sim, vector<CelestialObject*> subParts) {
        double x = this->getPosition().getMetersX();
        double y = this->getPosition().getMetersY();
        double offset = 10000;

        this->setExpired(true);
        sim->addObject(new StarlinkArray(Position(x + offset, y + offset), randomVelocity(this->getVelocity())));
        sim->addObject(new StarlinkBody(Position(x, y), randomVelocity(this->getVelocity())));
    }

    StarlinkBody::StarlinkBody(Position pos, Velocity vel, Angle angle) : Part(pos, vel, angle) {
        this->partOrigin = "Starlink";
        this->radius = 2;
        this->numFragments = 3;
    }

    StarlinkArray::StarlinkArray(Position pos, Velocity vel, Angle angle) : Part(pos, vel, angle) {
        this->partOrigin = "Starlink";
        this->radius = 4;
        this->numFragments = 3;
    }
}
