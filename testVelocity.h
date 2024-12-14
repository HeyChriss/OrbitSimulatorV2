/***********************************************************************
 * Header File:
 *    Test Velocity
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about testing velocity
 ************************************************************************/
#ifndef testVelocity_h
#define testVelocity_h

#include <iostream>
#include <cassert>
#include "velocity.h"
#include "unitTest.h"
#include "angle.h"

constexpr double M_PI = 3.141592653589793;

class TestVelocity : public UnitTest
{
public:
    void run()
    {
        // Constructor tests
        testDefaultConstructor();
        testNonDefaultConstructor();

        // Method tests
        testAdditionOperator();
        testMetersFromPixels();
        testAddMetersX();
        testAddMetersY();
        testSetMetersX();
        testSetMetersY();
        testSetPixelsX();
        testSetPixelsY();
        testAddPixelsWithAngle();

        // Getter method tests - only test these methods directly
        testGetDx();
        testGetDy();
        testGetSpeed();
        testGetAngle();

        report("Velocity");
    }

private:
    void testDefaultConstructor()
    {
        // Setup & Exercise
        Velocity vel;

        // Verify - direct member access
        assertUnit(vel.dx == 0.0);
        assertUnit(vel.dy == 0.0);
    }

    void testNonDefaultConstructor()
    {
        // Setup & Exercise
        Velocity vel(3.0, 4.0);

        // Verify - direct member access
        assertUnit(vel.dx == 3.0);
        assertUnit(vel.dy == 4.0);
    }

    void testAdditionOperator()
    {
        // Setup
        Velocity vel1(3.0, 4.0);
        Velocity vel2(2.0, 1.0);

        // Exercise
        vel1 += vel2;

        // Verify - direct member access
        assertUnit(vel1.dx == 5.0);
        assertUnit(vel1.dy == 5.0);
    }

    void testMetersFromPixels()
    {
        // Setup
        Velocity vel;
        vel.metersFromPixels = 50.0;

        // Verify - direct member access
        assertUnit(vel.metersFromPixels == 50.0);
    }

    void testAddMetersX()
    {
        // Setup
        Velocity vel(10.0, 20.0);

        // Exercise
        vel.addMetersX(5.0);

        // Verify - direct member access
        assertUnit(vel.dx == 15.0);
        assertUnit(vel.dy == 20.0);
    }

    void testAddMetersY()
    {
        // Setup
        Velocity vel(10.0, 20.0);

        // Exercise
        vel.addMetersY(5.0);

        // Verify - direct member access
        assertUnit(vel.dx == 10.0);
        assertUnit(vel.dy == 25.0);
    }

    void testSetMetersX()
    {
        // Setup
        Velocity vel(10.0, 20.0);

        // Exercise
        vel.setMetersX(15.0);

        // Verify - direct member access
        assertUnit(vel.dx == 15.0);
    }

    void testSetMetersY()
    {
        // Setup
        Velocity vel(10.0, 20.0);

        // Exercise
        vel.setMetersY(25.0);

        // Verify - direct member access
        assertUnit(vel.dy == 25.0);
    }

    void testSetPixelsX()
    {
        // Setup
        Velocity vel;
        vel.metersFromPixels = 2.0;

        // Exercise
        vel.setPixelsX(10.0);

        // Verify - direct member access
        assertUnit(vel.dx == 20.0);  // 10 pixels * 2 meters/pixel
    }

    void testSetPixelsY()
    {
        // Setup
        Velocity vel;
        vel.metersFromPixels = 2.0;

        // Exercise
        vel.setPixelsY(10.0);

        // Verify - direct member access
        assertUnit(vel.dy == 20.0);  // 10 pixels * 2 meters/pixel
    }



    void testAddPixelsWithAngle()
    {
        // Setup
        Velocity vel;
        vel.metersFromPixels = 2.0;
        Angle angle;
        angle.radAngle = M_PI / 2.0;  // 90 degrees

        // Exercise
        vel.addPixels(10.0, angle);

        // Verify - direct member access
        assertUnit(fabs(vel.dx - 20.0) < 0.001);  // Should be approximately 20 (10 pixels * 2 meters/pixel)
        assertUnit(fabs(vel.dy) < 0.001);         // Should be approximately 0
    }

    // Getter method tests - these specifically test the getter methods
    void testGetDx()
    {
        // Setup
        Velocity vel;
        vel.dx = 5.0;

        // Exercise & Verify
        assertUnit(vel.getDx() == 5.0);
    }

    void testGetDy()
    {
        // Setup
        Velocity vel;
        vel.dy = 5.0;

        // Exercise & Verify
        assertUnit(vel.getDy() == 5.0);
    }

    void testGetSpeed()
    {
        // Setup
        Velocity vel(3.0, 4.0);

        // Exercise & Verify
        assertUnit(vel.getSpeed() == 5.0);
    }

    void testGetAngle()
    {
        // Setup
        Velocity vel(1.0, 1.0);

        // Exercise
        Angle angle = vel.getAngle();

        // Verify - should be 45 degrees (π/4 radians)
        assertUnit(fabs(angle.radAngle - M_PI / 4) < 0.001);
    }
};

#endif /* testVelocity_h */


