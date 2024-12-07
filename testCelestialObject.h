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
        testDefaultConstructor();
        testIsHit();
        testBreakApart();
        testGetSubPartVel();
        testGetSubPartPos();

        report("CelestialObject");
    }

private:
    void testDefaultConstructor()
    {
        // Setup
        CelestialObject obj;

        // Verify
        assertUnit(obj.getExpired() == false);
        assertUnit(obj.getHasBeenHit() == false);
        assertUnit(obj.getRadius() == 0.0);
        assertUnit(obj.getNumFragments() == 0);
    }

    void testIsHit()
    {
        // Setup
        Position pos1(0, 0);
        Position pos2(10, 0); // 10 units away on the x-axis
        Velocity vel;
        CelestialObject obj1(pos1, vel);
        CelestialObject obj2(pos2, vel);

        obj1.setExpired(false);
        obj1.setHasBeenHit(false);
        obj2.setExpired(false);
        obj2.setHasBeenHit(false);
        obj1.radius = 6; // Set radius to 6 units
        obj2.radius = 6; // Set radius to 6 units

        // Exercise
        bool collision = obj1.isHit(&obj2);

        // Verify
        assertUnit(collision == true);
    }

    void testBreakApart()
    {
        // Setup
        Simulator sim;
        Position pos(0, 0);
        Velocity vel(5, 5);
        CelestialObject obj(pos, vel);
        obj.numFragments = 3; // Set the number of fragments

        // Exercise
        obj.breakApart(&sim);

        // Verify
        assertUnit(obj.getExpired() == true);
        assertUnit(obj.getHasBeenHit() == true);
        // Additional checks for simulator objects can be added based on `sim.addObject`.
    }

    void testGetSubPartVel()
    {
        // Setup
        CelestialObject obj;
        obj.vel = Velocity(5, 0); // Initial velocity
        int numSubParts = 4;

        // Exercise
        vector<Velocity> velocities = obj.getSubPartVel(numSubParts);

        // Verify
        assertUnit(velocities.size() == numSubParts);
        for (const auto& velocity : velocities)
        {
            assertUnit(velocity.getSpeed() > 0.0);
        }
    }

    void testGetSubPartPos()
    {
        // Setup
        CelestialObject obj;
        obj.pos = Position(0, 0); // Initial position
        vector<Velocity> directions = {
            Velocity(1, 0),
            Velocity(0, 1),
            Velocity(-1, 0),
            Velocity(0, -1)
        };

        // Exercise
        vector<Position> positions = obj.getSubPartPos(directions);

        // Verify
        assertUnit(positions.size() == directions.size());
        for (const auto& position : positions)
        {
            assertUnit(position.getMetersX() != 0 || position.getMetersY() != 0);
        }
    }
};

#endif /* testCelestialObject_h */


