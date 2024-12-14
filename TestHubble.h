#ifndef testHubble_h
#define testHubble_h

#include <iostream>
#include "hubble.h"
#include <cassert>
#include "unitTest.h"
#include "simulator.h"

class TestHubble : public UnitTest
{
public:
    void run()
    {
        testDefaultConstructorRadius();
        testDefaultConstructorFragments();
        testDefaultConstructorPosition();
        testDefaultConstructorDefective();
        testBreakApart();
        testInitialHeight();
        testOneOrbit();
        testHeight();

        report("Hubble");
    }

private:
    // Test each aspect of construction separately
    void testDefaultConstructorRadius()
    {
        // Setup & Exercise
        Hubble::Hubble hubble;

        // Verify - direct member access
        assertUnit(hubble.radius == 7);
    }

    void testDefaultConstructorFragments()
    {
        // Setup & Exercise
        Hubble::Hubble hubble;

        // Verify - direct member access
        assertUnit(hubble.numFragments == 2);
    }

    void testDefaultConstructorPosition()
    {
        // Setup & Exercise
        Hubble::Hubble hubble;

        // Verify - direct member access
        assertUnit(hubble.pos.x == 0.0);
        assertUnit(hubble.pos.y == 0.0);
    }

    void testDefaultConstructorDefective()
    {
        // Setup & Exercise
        Hubble::Hubble hubble;

        // Verify - direct member access
        assertUnit(hubble.defective == false);
    }

    void testBreakApart()
    {
        // Setup
        Simulator sim;
        Hubble::Hubble hubble;
        hubble.pos.x = 100;
        hubble.pos.y = 100;
        hubble.vel.dx = 50;
        hubble.vel.dy = 50;

        // Exercise
        hubble.breakApart(&sim);

        // Verify - direct member access
        assertUnit(hubble.isExpired == true);
        assertUnit(hubble.hasBeenHit == true);
    }

    void testInitialHeight()
    {
        // Setup
        DummySimulator sim("Hubble");
        Physics p;

        // Exercise - direct member access
        CelestialObject* obj = *sim.celestialObjects.begin();
        double x = obj->pos.x;
        double y = obj->pos.y;
        double geoOrbit = p.heightAbovePlanet(x, y, p.earthRadiusMeters) + p.earthRadiusMeters;

        // Verify
        assertEqualsLarge(geoOrbit, p.geoStationaryOrbitHeightMeters);
    }

    void testOneOrbit()
    {
        // Setup
        DummySimulator sim("Hubble");

        // Exercise
        bool reachedNegativeX = false;
        int numFrames = 0;
        while (true) {
            CelestialObject* obj = *sim.celestialObjects.begin();
            double x = obj->pos.x;
            if (x < 0)
                reachedNegativeX = true;
            else if (reachedNegativeX)
                break;
            numFrames++;
            sim.update();
        }

        // Verify
        assertUnit(numFrames >= 1790 && numFrames <= 1810);
    }

    void testHeight()
    {
        // Setup
        DummySimulator sim("Hubble");
        Physics p;

        CelestialObject* obj = *sim.celestialObjects.begin();
        double x = obj->pos.x;
        double y = obj->pos.y;

        // Exercise
        for (int i = 0; i < 1200; i++)
            sim.update();

        obj = *sim.celestialObjects.begin();
        double finalHeight = p.heightAbovePlanet(obj->pos.x, obj->pos.y, p.earthRadiusMeters) + p.earthRadiusMeters;

        // Verify
        assertUnit(finalHeight > p.geoStationaryOrbitHeightMeters);
    }
};

#endif /* testHubble_h */