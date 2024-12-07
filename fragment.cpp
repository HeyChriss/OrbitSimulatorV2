#include "fragment.h"
#include "simulator.h"

void Fragment::update(double time, double gravity, double radius) {
    if (isExpired())
        setExpired(true);
    else
    {
        this->rotationAngle += .005;
        CelestialObject::update(time, gravity, radius);
    }
}
