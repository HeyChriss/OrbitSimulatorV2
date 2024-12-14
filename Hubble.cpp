#include "hubble.h"
#include "satellite.h"
#include "part.h"
#include "simulator.h"
#include "celestialObject.h"

namespace Hubble {
    Hubble::Hubble(Position pos, Velocity vel, Angle angle) : Satellite(pos, vel, angle) {
        Satellite(pos, vel, angle);
        this->radius = 7;
        this->numFragments = 2;
    }

    void Hubble::breakApart(Simulator* sim, vector<CelestialObject*> subParts) {
        double x = this->getPosition().getMetersX();
        double y = this->getPosition().getMetersY();
        double offset = 10000;

        this->setExpired(true);
        this->setHasBeenHit(true);
        sim->addObject(new HubbleLeft(Position(x + offset, y + offset), randomVelocity(this->getVelocity())));
        sim->addObject(new HubbleComputer(Position(x, y), randomVelocity(this->getVelocity())));
        sim->addObject(new HubbleRight(Position(x - offset, y - offset), randomVelocity(this->getVelocity())));
        sim->addObject(new HubbleTelescope(Position(x - offset + 10000, y), randomVelocity(this->getVelocity())));
    }

    HubbleComputer::HubbleComputer(Position pos, Velocity vel, Angle angle) : Part(pos, vel, angle) {
        this->partOrigin = "Hubble";
        this->radius = 7;
        this->numFragments = 2;
    }

    HubbleLeft::HubbleLeft(Position pos, Velocity vel, Angle angle) : Part(pos, vel, angle) {
        this->partOrigin = "Hubble";
        this->numFragments = 2;
        this->radius = 8;
    }

    HubbleRight::HubbleRight(Position pos, Velocity vel, Angle angle) : Part(pos, vel, angle) {
        this->partOrigin = "Hubble";
        this->numFragments = 2;
        this->radius = 8;
    }

    HubbleTelescope::HubbleTelescope(Position pos, Velocity vel, Angle angle) : Part(pos, vel, angle)
    {
        this->partOrigin = "Hubble";
        this->numFragments = 3;
        this->radius = 10;
    }
}
