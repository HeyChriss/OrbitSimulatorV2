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
        testDragonConstructorRadius();
        testDragonConstructorFragments();
        testDragonConstructorExpired();
        testDragonConstructorHasBeenHit();
        testDragonBreakApart();
        testDragonCenterRadius();
        testDragonCenterFragments();
        testDragonCenterOrigin();
        testDragonLeftRadius();
        testDragonLeftFragments();
        testDragonLeftOrigin();
        testDragonRightRadius();
        testDragonRightFragments();
        testDragonRightOrigin();

        report("Dragon");
    }

private:
    void testDragonConstructorRadius()
    {
        // Setup & Exercise
        Dragon::Dragon dragon;

        // Verify - direct member access
        assertUnit(dragon.radius == 7);
    }

    void testDragonConstructorFragments()
    {
        // Setup & Exercise
        Dragon::Dragon dragon;

        // Verify - direct member access
        assertUnit(dragon.numFragments == 2);
    }

    void testDragonConstructorExpired()
    {
        // Setup & Exercise
        Dragon::Dragon dragon;

        // Verify - direct member access
        assertUnit(dragon.isExpired == false);
    }

    void testDragonConstructorHasBeenHit()
    {
        // Setup & Exercise
        Dragon::Dragon dragon;

        // Verify - direct member access
        assertUnit(dragon.hasBeenHit == false);
    }

    void testDragonBreakApart()
    {
        // Setup
        DummySimulator sim("Dragon");
        Dragon::Dragon dragon;
        dragon.pos.x = 100;
        dragon.pos.y = 100;
        dragon.vel.dx = 50;
        dragon.vel.dy = 50;

        // Exercise
        dragon.breakApart(&sim);

        // Verify - direct member access
        assertUnit(dragon.isExpired == true);
    }

    void testDragonCenterRadius()
    {
        // Setup & Exercise
        Dragon::DragonCenter center;

        // Verify - direct member access
        assertUnit(center.radius == 6);
    }

    void testDragonCenterFragments()
    {
        // Setup & Exercise
        Dragon::DragonCenter center;

        // Verify - direct member access
        assertUnit(center.numFragments == 4);
    }

    void testDragonCenterOrigin()
    {
        // Setup & Exercise
        Dragon::DragonCenter center;

        // Verify - direct member access
        assertUnit(center.partOrigin == "Dragon");
    }

    void testDragonLeftRadius()
    {
        // Setup & Exercise
        Dragon::DragonLeft left;

        // Verify - direct member access
        assertUnit(left.radius == 6);
    }

    void testDragonLeftFragments()
    {
        // Setup & Exercise
        Dragon::DragonLeft left;

        // Verify - direct member access
        assertUnit(left.numFragments == 2);
    }

    void testDragonLeftOrigin()
    {
        // Setup & Exercise
        Dragon::DragonLeft left;

        // Verify - direct member access
        assertUnit(left.partOrigin == "Dragon");
    }

    void testDragonRightRadius()
    {
        // Setup & Exercise
        Dragon::DragonRight right;

        // Verify - direct member access
        assertUnit(right.radius == 6);
    }

    void testDragonRightFragments()
    {
        // Setup & Exercise
        Dragon::DragonRight right;

        // Verify - direct member access
        assertUnit(right.numFragments == 2);
    }

    void testDragonRightOrigin()
    {
        // Setup & Exercise
        Dragon::DragonRight right;

        // Verify - direct member access
        assertUnit(right.partOrigin == "Dragon");
    }
};

#endif /* testDragon_h */

