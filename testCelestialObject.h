/***********************************************************************
 * Header File:
 *    Rest Celestial Object
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about Testing celestial objects 
 ************************************************************************/
#ifndef testCelestialObject_h
#define testCelestialObject_h

#include <iostream>
#include <cassert>
#include "celestialObject.h"
#include "unitTest.h"
#include "simulator.h"
#include "velocity.h"

using namespace std;

/*******************************
 * TEST CelestialObject
 * A friend class for CelestialObject which contains the unit tests
 ********************************/
class TestCelestialObject : public UnitTest
{
public:
    void run()
    {
        testDefaultConstructorInitialization();
        testPositionInitialization();
        testVelocityInitialization();
        testRotationInitialization();
        testRadius();
        testFragments();
        testIsHitCollision();
        testBreakApartExpired();
        testBreakApartHasBeenHit();
        testBreakApartCreateFragments();
        testGetSubPartVelCount();
        testGetSubPartVelSpeed();
        testGetSubPartPosCount();
        testGetSubPartPosOffset();
        testRandomVelocityChange();

        report("CelestialObject");
    }

private:
    void testDefaultConstructorInitialization()
    {
        // Setup & Exercise
        CelestialObject obj;

        // Verify - direct member access
        assertUnit(obj.isExpired == false);
        assertUnit(obj.hasBeenHit == false);
        assertUnit(obj.radius == 0.0);
        assertUnit(obj.numFragments == 0);
    }

    void testPositionInitialization()
    {
        // Setup & Exercise
        Position pos(100.0, 200.0);
        CelestialObject obj(pos);

        // Verify - direct member access
        assertUnit(obj.pos.x == 100.0);
        assertUnit(obj.pos.y == 200.0);
    }

    void testVelocityInitialization()
    {
        // Setup & Exercise
        Velocity vel(10.0, 20.0);
        CelestialObject obj(Position(), vel);

        // Verify - direct member access
        assertUnit(obj.vel.dx == 10.0);
        assertUnit(obj.vel.dy == 20.0);
    }

    void testRotationInitialization()
    {
        // Setup & Exercise
        Angle angle;
        angle.radAngle = 1.5;
        CelestialObject obj(Position(), Velocity(), angle);

        // Verify - direct member access
        assertUnit(obj.rotationAngle.radAngle == 1.5);
    }

    void testRadius()
    {
        // Setup & Exercise
        CelestialObject obj;
        obj.radius = 5.0;

        // Verify - direct member access
        assertUnit(obj.radius == 5.0);
    }

    void testFragments()
    {
        // Setup & Exercise
        CelestialObject obj;
        obj.numFragments = 3;

        // Verify - direct member access
        assertUnit(obj.numFragments == 3);
    }

    void testIsHitCollision()
    {
        // Setup
        CelestialObject obj1;
        CelestialObject obj2;
        obj1.radius = 6;
        obj2.radius = 6;
        obj1.pos.x = 0;
        obj1.pos.y = 0;
        obj2.pos.x = 10;
        obj2.pos.y = 0;

        // Exercise
        bool result = obj1.isHit(&obj2);

        // Verify - should collide as radiuses overlap
        assertUnit(result == true);
    }


    void testBreakApartExpired()
    {
        // Setup
        Simulator sim;
        CelestialObject obj;
        obj.numFragments = 3;

        // Exercise
        obj.breakApart(&sim);

        // Verify - direct member access
        assertUnit(obj.isExpired == true);
    }

    void testBreakApartHasBeenHit()
    {
        // Setup
        Simulator sim;
        CelestialObject obj;
        obj.numFragments = 3;

        // Exercise
        obj.breakApart(&sim);

        // Verify - direct member access
        assertUnit(obj.hasBeenHit == true);
    }

    void testBreakApartCreateFragments()
    {
        // Setup
        DummySimulator sim("Hubble");
        CelestialObject obj;
        obj.numFragments = 2;

        // Exercise
        obj.breakApart(&sim);

        // Verify - fragments should have been created in simulator
        assertUnit(sim.celestialObjects.size() > 0);
    }


    void testGetSubPartVelCount()
    {
        // Setup
        CelestialObject obj;
        obj.vel.dx = 5;
        obj.vel.dy = 0;
        int numParts = 4;

        // Exercise
        vector<Velocity> velocities = obj.getSubPartVel(numParts);

        // Verify - direct member access
        assertUnit(velocities.size() == numParts);
    }

    void testGetSubPartVelSpeed()
    {
        // Setup
        CelestialObject obj;
        obj.vel.dx = 5;
        obj.vel.dy = 0;

        // Exercise
        vector<Velocity> velocities = obj.getSubPartVel(1);

        // Verify - direct member access
        assertUnit(velocities[0].dx != 0.0 || velocities[0].dy != 0.0);
    }

    void testGetSubPartPosCount()
    {
        // Setup
        CelestialObject obj;
        vector<Velocity> directions = { Velocity(1,0), Velocity(0,1) };

        // Exercise
        vector<Position> positions = obj.getSubPartPos(directions);

        // Verify
        assertUnit(positions.size() == directions.size());
    }

    void testGetSubPartPosOffset()
    {
        // Setup
        CelestialObject obj;
        obj.pos.x = 0;
        obj.pos.y = 0;
        vector<Velocity> directions = { Velocity(1,0) };

        // Exercise
        vector<Position> positions = obj.getSubPartPos(directions);

        // Verify - position should be offset from original
        assertUnit(positions[0].x != obj.pos.x || positions[0].y != obj.pos.y);
    }

    void testRandomVelocityChange()
    {
        // Setup
        CelestialObject obj;
        Velocity originalVel(100, 100);

        // Exercise
        Velocity newVel = obj.randomVelocity(originalVel);

        // Verify - velocity should be different
        assertUnit(newVel.dx != originalVel.dx || newVel.dy != originalVel.dy);
    }
};

#endif /* testCelestialObject_h */


