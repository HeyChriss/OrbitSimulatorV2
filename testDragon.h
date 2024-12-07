/***********************************************************************
 * Header File:
 *    Test Dragon
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about Testing Dragon
 ************************************************************************/
#ifndef testDragon_h
#define testDragon_h

#include <iostream>
#include "dragon.h"
#include <cassert>
#include "unitTest.h"
#include "simulator.h"

/*******************************
 * TEST Dragon
 * A friend class for Dragon which contains the Dragon unit tests
 ********************************/
class TestDragon : public UnitTest
{
public:
    void run()
    {
        testConstructor();
        testBreakApart();
        testDragonParts();

        report("Dragon");
    }

private:
    void testConstructor()
    {
        // Setup & Exercise
        Dragon::Dragon dragon;

        // Verify
        assertUnit(dragon.getRadius() == 700000.0);  // 7 * 100000
        assertUnit(dragon.getNumFragments() == 2);
        assertUnit(!dragon.getExpired());
        assertUnit(!dragon.getHasBeenHit());
    }

    void testBreakApart()
    {
        // Setup
        Position pos(100, 100);
        Velocity vel(50, 50);
        DummySimulator* sim = new DummySimulator("Dragon");  // Specify Dragon type
        Dragon::Dragon* dragon = new Dragon::Dragon(pos, vel);
        sim->addObject(dragon);  // Add dragon to simulator

        // Exercise
        dragon->breakApart(sim);

        // Verify
        assertUnit(dragon->getExpired() == true);

        // Cleanup
        delete sim;
    }

    void testDragonParts()
    {
        // Test DragonCenter
        Dragon::DragonCenter center;
        assertUnit(center.getRadius() == 600000.0);  // 6 * 100000
        assertUnit(center.getNumFragments() == 4);
        assertUnit(center.partOrigin == "Dragon");

        // Test DragonLeft
        Dragon::DragonLeft left;
        assertUnit(left.getRadius() == 600000.0);    // 6 * 100000
        assertUnit(left.getNumFragments() == 2);
        assertUnit(left.partOrigin == "Dragon");

        // Test DragonRight
        Dragon::DragonRight right;
        assertUnit(right.getRadius() == 600000.0);   // 6 * 100000
        assertUnit(right.getNumFragments() == 2);
        assertUnit(right.partOrigin == "Dragon");
    }
};

#endif /* testDragon_h */

