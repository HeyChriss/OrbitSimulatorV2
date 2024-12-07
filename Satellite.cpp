#include "satellite.h"
#include "simulator.h"

void Satellite::update(double time, double gravity, double planetRadius) {
    CelestialObject::update(time, gravity, planetRadius);
}
