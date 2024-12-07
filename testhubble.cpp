#include "TestHubble.h"


void TestHubble::testInitialHeight() {
    // Setup
    DummySimulator sim("Hubble");
    Physics p;

    // Exercise
    double x = (**sim.celestialObjects.begin()).getPosition().getMetersX();
    double y = (**sim.celestialObjects.begin()).getPosition().getMetersY();
    double geoOrbit = p.heightAbovePlanet(x, y, p.earthRadiusMeters) + p.earthRadiusMeters;

    // Verify
    assertEqualsLarge(geoOrbit, p.geoStationaryOrbitHeightMeters);
}

void TestHubble::testOneOrbit() {
    // Setup
    DummySimulator sim("Hubble");
    CelestialObject satellite;

    // Exercise
    bool reachedNegativeX = false;

    int numFrames = 0;
    while (true) {
        double x = (**sim.celestialObjects.begin()).pos.getMetersX();
        if (x < 0)
            reachedNegativeX = true;
        else if (reachedNegativeX)
            break;
        numFrames++;
        sim.update();
    }

    // Verify
    assertUnit(numFrames >= 1790 && numFrames <= 1810);
} // Teardown


void TestHubble::testHeight() {
    // Setup
    DummySimulator sim("Hubble");
    CelestialObject satellite;
    Physics p;
    double height;

    double x = (**sim.celestialObjects.begin()).pos.getMetersX();
    double y = (**sim.celestialObjects.begin()).pos.getMetersY();

    height = p.heightAbovePlanet(x, y, p.earthRadiusMeters) + p.earthRadiusMeters;
    // Exercise
    for (int i = 0; i < 1200; i++)
        sim.update();

    x = (**sim.celestialObjects.begin()).pos.getMetersX();
    y = (**sim.celestialObjects.begin()).pos.getMetersY();

    height = p.heightAbovePlanet(x, y, p.earthRadiusMeters) + p.earthRadiusMeters;

    // Verify
    assertUnit(height > p.geoStationaryOrbitHeightMeters);
} // Teardown
