/***********************************************************************
 * Header File:
 *    Test Sputnik
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
        testConstructorRadius();
        testConstructorFragments();
        testConstructorExpired();
        testConstructorHasBeenHit();
        testConstructorDefective();
        testConstructorPosition();
        testBreakApart();

        report("Sputnik");
    }

private:
    void testConstructorRadius()
    {
        // Setup & Exercise
        Sputnik sputnik;

        // Verify - direct member access
        assertUnit(sputnik.radius == 4);
    }

    void testConstructorFragments()
    {
        // Setup & Exercise
        Sputnik sputnik;

        // Verify - direct member access
        assertUnit(sputnik.numFragments == 4);
    }

    void testConstructorExpired()
    {
        // Setup & Exercise
        Sputnik sputnik;

        // Verify - direct member access
        assertUnit(sputnik.isExpired == false);
    }

    void testConstructorHasBeenHit()
    {
        // Setup & Exercise
        Sputnik sputnik;

        // Verify - direct member access
        assertUnit(sputnik.hasBeenHit == false);
    }

    void testConstructorDefective()
    {
        // Setup & Exercise
        Sputnik sputnik;

        // Verify - direct member access
        assertUnit(sputnik.defective == false);
    }

    void testConstructorPosition()
    {
        // Setup & Exercise
        Sputnik sputnik;

        // Verify - direct member access
        assertUnit(sputnik.pos.x == 0.0);
        assertUnit(sputnik.pos.y == 0.0);
    }

    void testBreakApart()
    {
        // Setup
        DummySimulator sim("Sputnik");
        Sputnik sputnik;
        sputnik.pos.x = 100;
        sputnik.pos.y = 100;
        sputnik.vel.dx = 50;
        sputnik.vel.dy = 50;

        // Exercise
        sputnik.breakApart(&sim);

        // Verify - direct member access
        assertUnit(sputnik.isExpired == true);
        assertUnit(sputnik.hasBeenHit == true);
    }
};

#endif /* testSputnik_h */

