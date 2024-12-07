/***********************************************************************
 * Header File:
 *    Test Starlink
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about starlink
 ************************************************************************/
#ifndef testStarlink_h
#define testStarlink_h

#include <iostream>
#include "starlink.h"
#include <cassert>
#include "unitTest.h"
#include "simulator.h"

/*******************************
 * TEST Starlink
 * A friend class for Starlink which contains the Starlink unit tests
 ********************************/
class TestStarlink : public UnitTest
{
public:
    void run()
    {
        testConstructor();
        testBreakApart();
        testStarlinkParts();
        testInitialState();

        report("Starlink");
    }

private:
    void testConstructor()
    {
        // Setup & Exercise
        Starlink::Starlink starlink;

        // Verify
        assertUnit(starlink.getRadius() == 700000.0);  // 7 * 100000
        assertUnit(starlink.getNumFragments() == 2);
        assertUnit(!starlink.getExpired());
        assertUnit(!starlink.getHasBeenHit());
    }

    void testBreakApart()
    {
        // Setup
        Position pos(100, 100);
        Velocity vel(50, 50);
        DummySimulator* sim = new DummySimulator("Starlink");
        Starlink::Starlink* starlink = new Starlink::Starlink(pos, vel);
        sim->addObject(starlink);

        // Exercise
        starlink->breakApart(sim);

        // Verify
        assertUnit(starlink->getExpired() == true);

        // Cleanup
        delete sim;
    }

    void testStarlinkParts()
    {
        // Test StarlinkBody
        Starlink::StarlinkBody body;
        assertUnit(body.getRadius() == 200000.0);  // 2 * 100000
        assertUnit(body.getNumFragments() == 3);
        assertUnit(body.partOrigin == "Starlink");

        // Test StarlinkArray
        Starlink::StarlinkArray array;
        assertUnit(array.getRadius() == 400000.0);  // 4 * 100000
        assertUnit(array.getNumFragments() == 3);
        assertUnit(array.partOrigin == "Starlink");
    }

    void testInitialState()
    {
        // Setup
        Position testPos(0.0, -13020000.0);
        Velocity testVel(5800.0, 0.0);
        Starlink::Starlink starlink(testPos, testVel);

        // Verify position
        assertEquals(starlink.getPosition().getMetersX(), 0.0);
        assertEquals(starlink.getPosition().getMetersY(), -13020000.0);

        // Verify velocity
        assertEquals(starlink.getVelocity().getDx(), 5800.0);
        assertEquals(starlink.getVelocity().getDy(), 0.0);

        // Verify other properties
        assertUnit(starlink.getRadius() == 700000.0);  // 7 * 100000
        assertUnit(starlink.getNumFragments() == 2);
    }
};

#endif /* testStarlink_h */

