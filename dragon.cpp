#include "dragon.h"
#include "satellite.h"
#include "part.h"
#include "simulator.h"
#include "celestialObject.h"

namespace Dragon {
    Dragon::Dragon(Position pos, Velocity vel, Angle angle) : Satellite(pos, vel, angle) {
        Satellite(pos, vel, angle);
        this->radius = 7;
        this->numFragments = 2;
    }

    void Dragon::breakApart(Simulator* sim, vector<CelestialObject*> subParts) {
        double x = this->getPosition().getMetersX();
        double y = this->getPosition().getMetersY();
        double offset = 10000;

        this->setExpired(true);
        sim->addObject(new DragonLeft(Position(x + offset, y + offset), randomVelocity(this->getVelocity())));
        sim->addObject(new DragonCenter(Position(x, y), randomVelocity(this->getVelocity())));
        sim->addObject(new DragonRight(Position(x - offset, y - offset), randomVelocity(this->getVelocity())));
    }

    DragonCenter::DragonCenter(Position pos, Velocity vel, Angle angle) : Part(pos, vel, angle) {
        this->partOrigin = "Dragon";
        this->radius = 6;
        this->numFragments = 4;
    }

    DragonLeft::DragonLeft(Position pos, Velocity vel, Angle angle) : Part(pos, vel, angle) {
        this->partOrigin = "Dragon";
        this->radius = 6;
        this->numFragments = 2;
    }

    DragonRight::DragonRight(Position pos, Velocity vel, Angle angle) : Part(pos, vel, angle) {
        this->partOrigin = "Dragon";
        this->radius = 6;
        this->numFragments = 2;
    }
}
