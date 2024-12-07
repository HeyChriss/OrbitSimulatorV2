/***********************************************************************
 * Header File:
 *    Test Sptunik
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about testing sputnik
 ************************************************************************/

#ifndef testSputnik_h
#define testSputnik_h

#include <iostream>
#include "sputnik.h"
#include <cassert>
#include "unitTest.h"
#include "simulator.h"

/*******************************
 * TEST Sputnik
 * A friend class for Sputnik which contains the Sputnik unit tests
 ********************************/
class TestSputnik : public UnitTest
{
public:
    void run()
    {
        testConstructor();
        testBreakApart();
        testInitialState();

        report("Sputnik");
    }

private:
    void testConstructor()
    {
        // Setup & Exercise
        Sputnik sputnik;

        // Verify initial state
        assertUnit(sputnik.getRadius() == 400000.0); 
        assertUnit(sputnik.getNumFragments() == 4);
        assertUnit(!sputnik.getExpired());
        assertUnit(!sputnik.getHasBeenHit());
    }

    void testBreakApart()
    {
        // Setup
        Position pos(100, 100);
        Velocity vel(50, 50);
        DummySimulator* sim = new DummySimulator("Sputnik");
        Sputnik* sputnik = new Sputnik(pos, vel);
        sim->addObject(sputnik);

        // Exercise
        sputnik->breakApart(sim);

        // Verify
        assertUnit(sputnik->getExpired() == true);
        assertUnit(sputnik->getHasBeenHit() == true);

        // Cleanup
        delete sim;
    }

    void testInitialState()
    {
        // Setup
        Position testPos(-36515095.13, 21082000.0);
        Velocity testVel(2050.0, 2684.68);
        Sputnik sputnik(testPos, testVel);

        // Verify position
        assertUnit(sputnik.getPosition().getMetersX() == -36515095.13);
        assertUnit(sputnik.getPosition().getMetersY() == 21082000.0);

        assertEquals(sputnik.getVelocity().getDx(), 2050.0);
        assertEquals(sputnik.getVelocity().getDy(), 2684.68);

        // Verify other properties
        assertUnit(sputnik.getRadius() == 400000.0);  // 4 * 100000
        assertUnit(sputnik.getNumFragments() == 4);
    }
};

#endif /* testSputnik_h */

