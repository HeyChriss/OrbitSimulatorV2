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
        testStarlinkConstructorRadius();
        testStarlinkConstructorFragments();
        testStarlinkConstructorExpired();
        testStarlinkConstructorHasBeenHit();
        testStarlinkConstructorDefective();
        testStarlinkBreakApart();

        testStarlinkBodyRadius();
        testStarlinkBodyFragments();
        testStarlinkBodyOrigin();
        testStarlinkBodyExpired();
        testStarlinkBodyHasBeenHit();

        testStarlinkArrayRadius();
        testStarlinkArrayFragments();
        testStarlinkArrayOrigin();
        testStarlinkArrayExpired();
        testStarlinkArrayHasBeenHit();

        report("Starlink");
    }

private:
    // Main Starlink tests
    void testStarlinkConstructorRadius()
    {
        // Setup & Exercise
        Starlink::Starlink starlink;

        // Verify - direct member access
        assertUnit(starlink.radius == 7);
    }

    void testStarlinkConstructorFragments()
    {
        // Setup & Exercise
        Starlink::Starlink starlink;

        // Verify - direct member access
        assertUnit(starlink.numFragments == 2);
    }

    void testStarlinkConstructorExpired()
    {
        // Setup & Exercise
        Starlink::Starlink starlink;

        // Verify - direct member access
        assertUnit(starlink.isExpired == false);
    }

    void testStarlinkConstructorHasBeenHit()
    {
        // Setup & Exercise
        Starlink::Starlink starlink;

        // Verify - direct member access
        assertUnit(starlink.hasBeenHit == false);
    }

    void testStarlinkConstructorDefective()
    {
        // Setup & Exercise
        Starlink::Starlink starlink;

        // Verify - direct member access
        assertUnit(starlink.defective == false);
    }

    void testStarlinkBreakApart()
    {
        // Setup
        DummySimulator sim("Starlink");
        Starlink::Starlink starlink;
        starlink.pos.x = 100;
        starlink.pos.y = 100;
        starlink.vel.dx = 50;
        starlink.vel.dy = 50;

        // Exercise
        starlink.breakApart(&sim);

        // Verify - direct member access
        assertUnit(starlink.isExpired == true);
    }

    // StarlinkBody tests
    void testStarlinkBodyRadius()
    {
        // Setup & Exercise
        Starlink::StarlinkBody body;

        // Verify - direct member access
        assertUnit(body.radius == 2);
    }

    void testStarlinkBodyFragments()
    {
        // Setup & Exercise
        Starlink::StarlinkBody body;

        // Verify - direct member access
        assertUnit(body.numFragments == 3);
    }

    void testStarlinkBodyOrigin()
    {
        // Setup & Exercise
        Starlink::StarlinkBody body;

        // Verify - direct member access
        assertUnit(body.partOrigin == "Starlink");
    }

    void testStarlinkBodyExpired()
    {
        // Setup & Exercise
        Starlink::StarlinkBody body;

        // Verify - direct member access
        assertUnit(body.isExpired == false);
    }

    void testStarlinkBodyHasBeenHit()
    {
        // Setup & Exercise
        Starlink::StarlinkBody body;

        // Verify - direct member access
        assertUnit(body.hasBeenHit == false);
    }

    // StarlinkArray tests
    void testStarlinkArrayRadius()
    {
        // Setup & Exercise
        Starlink::StarlinkArray array;

        // Verify - direct member access
        assertUnit(array.radius == 4);
    }

    void testStarlinkArrayFragments()
    {
        // Setup & Exercise
        Starlink::StarlinkArray array;

        // Verify - direct member access
        assertUnit(array.numFragments == 3);
    }

    void testStarlinkArrayOrigin()
    {
        // Setup & Exercise
        Starlink::StarlinkArray array;

        // Verify - direct member access
        assertUnit(array.partOrigin == "Starlink");
    }

    void testStarlinkArrayExpired()
    {
        // Setup & Exercise
        Starlink::StarlinkArray array;

        // Verify - direct member access
        assertUnit(array.isExpired == false);
    }

    void testStarlinkArrayHasBeenHit()
    {
        // Setup & Exercise
        Starlink::StarlinkArray array;

        // Verify - direct member access
        assertUnit(array.hasBeenHit == false);
    }
};

#endif /* testStarlink_h */

