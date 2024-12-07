/***********************************************************************
 * Header File:
 *    test Part
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about testing parts
 ************************************************************************/
#ifndef testPart_h
#define testPart_h

#include <iostream>
#include "part.h"
#include <cassert>
#include "unitTest.h"
#include "simulator.h"

/*******************************
 * TEST Part
 * A friend class for Part which contains the Part unit tests
 ********************************/
class TestPart : public UnitTest
{
public:
    void run()
    {
        testConstructor();
        testInvincibility();
        testSameOriginCollision();
        testDifferentOriginCollision();
        testUpdate();

        report("Part");
    }

private:
    class TestPartDerived : public Part {
    public:
        TestPartDerived(string origin = "Test") {
            this->partOrigin = origin;
            this->radius = 1;
            this->numFragments = 0;
        }
    };

    void testConstructor()
    {
        // Setup & Exercise
        Position pos(100.0, 200.0);
        Velocity vel(50.0, -30.0);
        Angle angle(1.5);
        Part part(pos, vel, angle);

        // Verify initial state
        assertUnit(part.getRadius() == 100000.0);  // 1 * 100000
        assertUnit(part.getNumFragments() == 0);
        assertUnit(!part.getExpired());
        assertUnit(!part.getHasBeenHit());
        assertUnit(part.invincibilityCount == 0);

        // Verify position and velocity
        assertEquals(part.getPosition().getMetersX(), 100.0);
        assertEquals(part.getPosition().getMetersY(), 200.0);
        assertEquals(part.getVelocity().getDx(), 50.0);
        assertEquals(part.getVelocity().getDy(), -30.0);
    }

    void testInvincibility()
    {
        // Setup
        TestPartDerived part;
        TestPartDerived otherPart("Different");

        // Test invincibility period
        assertUnit(!part.isHit(&otherPart));  // Should be invincible initially

        // Update multiple times to exceed invincibility
        for (int i = 0; i < 15; i++) {
            part.update(1.0, 0.0, 0.0);
        }

        // Should now be vulnerable
        assertUnit(part.invincibilityCount >= 10);
    }

    void testSameOriginCollision()
    {
        // Setup
        TestPartDerived part1("Test");
        TestPartDerived part2("Test");

        // Update to end invincibility
        for (int i = 0; i < 15; i++) {
            part1.update(1.0, 0.0, 0.0);
            part2.update(1.0, 0.0, 0.0);
        }

        // Verify parts from same origin don't collide
        assertUnit(!part1.isHit(&part2));
        assertUnit(!part2.isHit(&part1));
    }

    void testDifferentOriginCollision()
    {
        // Setup
        TestPartDerived part1("Origin1");
        TestPartDerived part2("Origin2");

        // Update to end invincibility
        for (int i = 0; i < 15; i++) {
            part1.update(1.0, 0.0, 0.0);
            part2.update(1.0, 0.0, 0.0);
        }

        // Position them for collision
        Position pos1(0, 0);
        Position pos2(1, 0);  // Close enough for collision based on radius
        part1.setPosition(pos1);
        part2.setPosition(pos2);

        // Verify parts from different origins can collide
        assertUnit(part1.isHit(&part2));
        assertUnit(part2.isHit(&part1));
    }

    void testUpdate()
    {
        // Setup
        TestPartDerived part;
        assertUnit(part.invincibilityCount == 0);

        // Exercise - single update
        part.update(1.0, 0.0, 0.0);

        // Verify invincibilityCount increases
        assertUnit(part.invincibilityCount == 1);

        // Exercise - multiple updates
        for (int i = 0; i < 5; i++) {
            part.update(1.0, 0.0, 0.0);
        }

        // Verify invincibilityCount continues to increase
        assertUnit(part.invincibilityCount == 6);
    }
};

#endif /* testPart_h */
