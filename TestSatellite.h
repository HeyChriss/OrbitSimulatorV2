/***********************************************************************
 * Header File:
 *    Testing Satellite
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about testing satellites and collisions 
 ************************************************************************/
#ifndef testSatellite_h
#define testSatellite_h

#include <iostream>
#include <cassert>
#include "satellite.h"
#include "unitTest.h"
#include "simulator.h"

class TestSatellite : public UnitTest
{
public:
    void run()
    {
        testDefaultConstructorRadius();
        testDefaultConstructorFragments();
        testDefaultConstructorExpired();
        testDefaultConstructorHasBeenHit();
        testDefaultConstructorDefective();
        testDefaultConstructorPosition();
        testParameterizedConstructorPosition();
        testParameterizedConstructorVelocity();
        testParameterizedConstructorAngle();
        testUpdate();
        testBreakApart();

        report("Satellite and Collision");
    }

private:
    void testDefaultConstructorRadius()
    {
        // Setup & Exercise
        Satellite satellite;

        // Verify - direct member access
        assertUnit(satellite.radius == 10);
    }

    void testDefaultConstructorFragments()
    {
        // Setup & Exercise
        Satellite satellite;

        // Verify - direct member access
        assertUnit(satellite.numFragments == 2);
    }

    void testDefaultConstructorExpired()
    {
        // Setup & Exercise
        Satellite satellite;

        // Verify - direct member access
        assertUnit(satellite.isExpired == false);
    }

    void testDefaultConstructorHasBeenHit()
    {
        // Setup & Exercise
        Satellite satellite;

        // Verify - direct member access
        assertUnit(satellite.hasBeenHit == false);
    }

    void testDefaultConstructorDefective()
    {
        // Setup & Exercise
        Satellite satellite;

        // Verify - direct member access
        assertUnit(satellite.defective == false);
    }

    void testDefaultConstructorPosition()
    {
        // Setup & Exercise
        Satellite satellite;

        // Verify - direct member access
        assertUnit(satellite.pos.x == 0.0);
        assertUnit(satellite.pos.y == 0.0);
    }

    void testParameterizedConstructorPosition()
    {
        // Setup & Exercise
        Position pos(100.0, 200.0);
        Satellite satellite(pos);

        // Verify - direct member access
        assertUnit(satellite.pos.x == 100.0);
        assertUnit(satellite.pos.y == 200.0);
    }

    void testParameterizedConstructorVelocity()
    {
        // Setup & Exercise
        Position pos(0.0, 0.0);
        Velocity vel(10.0, 20.0);
        Satellite satellite(pos, vel);

        // Verify - direct member access
        assertUnit(satellite.vel.dx == 10.0);
        assertUnit(satellite.vel.dy == 20.0);
    }

    void testParameterizedConstructorAngle()
    {
        // Setup & Exercise
        Position pos;
        Velocity vel;
        Angle angle;
        angle.radAngle = M_PI / 2;  // 90 degrees
        Satellite satellite(pos, vel, angle);

        // Verify - direct member access
        assertUnit(satellite.rotationAngle.radAngle == M_PI / 2);
    }

    void testUpdate()
    {
        // Setup
        Satellite satellite;
        satellite.pos.x = 100.0;
        satellite.pos.y = 100.0;
        satellite.vel.dx = 10.0;
        satellite.vel.dy = 10.0;
        double time = 1.0;
        double gravity = -9.8;
        double planetRadius = 6378000.0;

        // Record initial position
        double initialX = satellite.pos.x;
        double initialY = satellite.pos.y;

        // Exercise
        satellite.update(time, gravity, planetRadius);

        // Verify - position should change
        assertUnit(satellite.pos.x != initialX || satellite.pos.y != initialY);
    }

    void testBreakApart()
    {
        // Setup
        DummySimulator sim("Hubble");
        Satellite satellite;
        satellite.pos.x = 100.0;
        satellite.pos.y = 100.0;
        satellite.vel.dx = 10.0;
        satellite.vel.dy = 10.0;
        vector<CelestialObject*> parts;

        // Exercise
        satellite.breakApart(&sim, parts);

        // Verify - direct member access
        assertUnit(satellite.hasBeenHit == true);
        assertUnit(satellite.isExpired == true);
    }
};

#endif /* testSatellite_h */
