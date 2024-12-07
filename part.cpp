#include <stdio.h>
#include "part.h"

bool Part::isHit(CelestialObject* other) {
    if (invincibilityCount < 10) return false;

    if (dynamic_cast<Part*>(other) != nullptr) {
        if (static_cast<Part*>(other)->partOrigin == this->partOrigin) {
            return false;
        }
    }
    return CelestialObject::isHit(other);
}

void Part::update(double time, double gravity, double planetRadius) {
    this->invincibilityCount++;
    CelestialObject::update(time, gravity, planetRadius);
}
