#pragma once
#include "ship.h"
#include "projectile.h"

void Spaceship::update(double time, double gravity, double planetRadius) {
    if (this->getThrust())
        this->vel.addMeters(200, rotationAngle);
    CelestialObject::update(time, gravity, planetRadius);
}

bool Spaceship::isHit(CelestialObject* other) {
    if (dynamic_cast<Projectile*>(other) != nullptr) return false;
    return CelestialObject::isHit(other);
}


void DummySpaceship::update(double time, double gravity, double planetRadius) {
    Spaceship::update(time, gravity, planetRadius);
}
