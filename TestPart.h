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
#include <cassert>
#include "part.h"
#include "unitTest.h"
#include "simulator.h"

class TestPart : public UnitTest
{
public:
    void run()
    {
        testDefaultConstructorRadius();
        testDefaultConstructorFragments();
        testDefaultConstructorInvincibilityCount();
        testDefaultConstructorPartOrigin();
        testDefaultConstructorPosition();
        testNonDefaultConstructorPosition();
        testNonDefaultConstructorVelocity();
        testNonDefaultConstructorAngle();
        testIsHitWithInvincibility();
        testIsHitAfterInvincibility();
        testIsHitWithSameOrigin();
        testIsHitWithDifferentOrigin();
        testUpdateInvincibilityCount();
        testUpdatePosition();

        report("Part");
    }

private:
    void testDefaultConstructorRadius()
    {
        // Setup & Exercise
        Part part;

        // Verify - direct member access
        assertUnit(part.radius == 1);
    }

    void testDefaultConstructorFragments()
    {
        // Setup & Exercise
        Part part;

        // Verify - direct member access
        assertUnit(part.numFragments == 0);
    }

    void testDefaultConstructorInvincibilityCount()
    {
        // Setup & Exercise
        Part part;

        // Verify - direct member access
        assertUnit(part.invincibilityCount == 0);
    }

    void testDefaultConstructorPartOrigin()
    {
        // Setup & Exercise
        Part part;

        // Verify - direct member access
        assertUnit(part.partOrigin.empty());
    }

    void testDefaultConstructorPosition()
    {
        // Setup & Exercise
        Part part;

        // Verify - direct member access
        assertUnit(part.pos.x == 0.0);
        assertUnit(part.pos.y == 0.0);
    }

    void testNonDefaultConstructorPosition()
    {
        // Setup & Exercise
        Position pos(100.0, 200.0);
        Part part(pos);

        // Verify - direct member access
        assertUnit(part.pos.x == 100.0);
        assertUnit(part.pos.y == 200.0);
    }

    void testNonDefaultConstructorVelocity()
    {
        // Setup & Exercise
        Position pos;
        Velocity vel(10.0, 20.0);
        Part part(pos, vel);

        // Verify - direct member access
        assertUnit(part.vel.dx == 10.0);
        assertUnit(part.vel.dy == 20.0);
    }

    void testNonDefaultConstructorAngle()
    {
        // Setup & Exercise
        Position pos;
        Velocity vel;
        Angle angle;
        angle.radAngle = M_PI / 2;
        Part part(pos, vel, angle);

        // Verify - direct member access
        assertUnit(part.rotationAngle.radAngle == M_PI / 2);
    }

    void testIsHitWithInvincibility()
    {
        // Setup
        Part part;
        part.invincibilityCount = 5;  // Less than 10
        CelestialObject other;

        // Exercise
        bool result = part.isHit(&other);

        // Verify
        assertUnit(result == false);
    }

    void testIsHitAfterInvincibility()
    {
        // Setup
        Part part;
        part.invincibilityCount = 15;  // Greater than 10
        part.radius = 5;
        CelestialObject other;
        other.pos.x = 8.0;  // Close enough to collide
        other.radius = 5;

        // Exercise
        bool result = part.isHit(&other);

        // Verify
        assertUnit(result == true);
    }

    void testIsHitWithSameOrigin()
    {
        // Setup
        Part part1;
        Part part2;
        part1.partOrigin = "TestOrigin";
        part2.partOrigin = "TestOrigin";
        part1.invincibilityCount = 15;  // Greater than 10
        part2.invincibilityCount = 15;

        // Exercise
        bool result = part1.isHit(&part2);

        // Verify - parts from same origin should not collide
        assertUnit(result == false);
    }

    void testIsHitWithDifferentOrigin()
    {
        // Setup
        Part part1;
        Part part2;
        part1.partOrigin = "Origin1";
        part2.partOrigin = "Origin2";
        part1.invincibilityCount = 15;  // Greater than 10
        part2.invincibilityCount = 15;
        part1.radius = 5;
        part2.radius = 5;
        part2.pos.x = 8.0;  // Close enough to collide

        // Exercise
        bool result = part1.isHit(&part2);

        // Verify - parts from different origins should collide
        assertUnit(result == true);
    }

    void testUpdateInvincibilityCount()
    {
        // Setup
        Part part;
        int initialCount = part.invincibilityCount;

        // Exercise
        part.update(1.0, 0.0, 0.0);

        // Verify
        assertUnit(part.invincibilityCount == initialCount + 1);
    }

    void testUpdatePosition()
    {
        // Setup
        Part part;
        part.pos.x = 100.0;
        part.pos.y = 100.0;
        part.vel.dx = 10.0;
        part.vel.dy = 10.0;

        // Record initial position
        double initialX = part.pos.x;
        double initialY = part.pos.y;

        // Exercise
        part.update(1.0, 0.0, 0.0);

        // Verify - position should change based on velocity
        assertUnit(part.pos.x != initialX);
        assertUnit(part.pos.y != initialY);
    }
};

#endif /* testPart_h */
