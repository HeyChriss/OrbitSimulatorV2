/***********************************************************************
 * Header File:
 *    Test Fragments
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about Testing Fragments
 ************************************************************************/

#ifndef testFragment_h
#define testFragment_h

#include <iostream>
#include <cassert>
#include "fragment.h"
#include "unitTest.h"
#include "simulator.h"

class TestFragment : public UnitTest
{
public:
    void run()
    {
        testDefaultConstructorRadius();
        testDefaultConstructorFragments();
        testDefaultConstructorRotation();
        testDefaultConstructorPosition();
        testDefaultConstructorLifetime();
        testDefaultConstructorHasBeenHit();
        testDefaultConstructorNonDefaultPosition();
        testDefaultConstructorNonDefaultVelocity();
        testDefaultConstructorNonDefaultAngle();
        testUpdateRotation();
        testUpdatePosition();
        testIsExpiredFalse();
        testIsExpiredTrue();
        testLifetimeDecrement();

        report("Fragment");
    }

private:
    void testDefaultConstructorRadius()
    {
        // Setup & Exercise
        Fragment fragment;

        // Verify - direct member access
        assertUnit(fragment.radius == 2);
    }

    void testDefaultConstructorFragments()
    {
        // Setup & Exercise
        Fragment fragment;

        // Verify - direct member access
        assertUnit(fragment.numFragments == 0);
    }

    void testDefaultConstructorRotation()
    {
        // Setup & Exercise
        Fragment fragment;

        // Verify - direct member access
        assertUnit(fragment.rotationAngle.radAngle >= 0.0);
        assertUnit(fragment.rotationAngle.radAngle <= 2.0 * 3.141);
    }

    void testDefaultConstructorPosition()
    {
        // Setup & Exercise
        Fragment fragment;

        // Verify - direct member access
        assertUnit(fragment.pos.x == 0.0);
        assertUnit(fragment.pos.y == 0.0);
    }

    void testDefaultConstructorLifetime()
    {
        // Setup & Exercise
        Fragment fragment;

        // Verify - direct member access
        assertUnit(fragment.lifetime >= 50);
        assertUnit(fragment.lifetime <= 100);
    }

    void testDefaultConstructorHasBeenHit()
    {
        // Setup & Exercise
        Fragment fragment;

        // Verify - direct member access
        assertUnit(fragment.hasBeenHit == true);
    }

    void testDefaultConstructorNonDefaultPosition()
    {
        // Setup & Exercise
        Position pos(100.0, 200.0);
        Fragment fragment(pos);

        // Verify - direct member access
        assertUnit(fragment.pos.x == 100.0);
        assertUnit(fragment.pos.y == 200.0);
    }

    void testDefaultConstructorNonDefaultVelocity()
    {
        // Setup & Exercise
        Position pos;
        Velocity vel(10.0, 20.0);
        Fragment fragment(pos, vel);

        // Verify - direct member access
        assertUnit(fragment.vel.dx == 10.0);
        assertUnit(fragment.vel.dy == 20.0);
    }

    void testDefaultConstructorNonDefaultAngle()
    {
        // Setup & Exercise
        Position pos;
        Velocity vel;
        Angle angle;
        angle.radAngle = M_PI / 2;  // 90 degrees
        Fragment fragment(pos, vel, angle);

        // Verify - direct member access
        assertUnit(fragment.rotationAngle.radAngle >= 0.0);
        assertUnit(fragment.rotationAngle.radAngle <= 2.0 * 3.141);
    }

    void testUpdateRotation()
    {
        // Setup
        Fragment fragment;
        double initialRotation = fragment.rotationAngle.radAngle;

        // Exercise
        fragment.update(1.0, 0.0, 0.0);

        // Verify - rotation should change
        assertUnit(fragment.rotationAngle.radAngle != initialRotation);
    }

    void testUpdatePosition()
    {
        // Setup
        Fragment fragment;
        fragment.pos.x = 100.0;
        fragment.pos.y = 100.0;
        fragment.vel.dx = 10.0;
        fragment.vel.dy = 10.0;

        // Record initial position
        double initialX = fragment.pos.x;
        double initialY = fragment.pos.y;

        // Exercise
        fragment.update(1.0, 0.0, 0.0);

        // Verify - position should change based on velocity
        assertUnit(fragment.pos.x != initialX);
        assertUnit(fragment.pos.y != initialY);
    }


    void testIsExpiredFalse()
    {
        // Setup
        Fragment fragment;
        fragment.lifetime = 50;

        // Exercise & Verify
        assertUnit(fragment.isExpired() == false);
    }

    void testIsExpiredTrue()
    {
        // Setup
        Fragment fragment;
        fragment.lifetime = 0;

        // Exercise & Verify
        assertUnit(fragment.isExpired() == true);
    }

    void testLifetimeDecrement()
    {
        // Setup
        Fragment fragment;
        fragment.lifetime = 50;
        int initialLifetime = fragment.lifetime;

        // Exercise
        fragment.isExpired();  // This decrements lifetime

        // Verify
        assertUnit(fragment.lifetime == initialLifetime - 1);
    }
};

#endif /* testFragment_h */
