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
#include <cmath>

const double M_PI = std::acos(-1.0);

using namespace std;

/*******************************
 * TEST Velocity
 * A friend class for Velocity which contains the unit tests
 ********************************/
class TestVelocity : public UnitTest
{
public:
    void run()
    {
        testDefaultConstructor();
        testParameterizedConstructor();
        testSettersAndGetters();
        testGetSpeed();
        testGetAngle();
        testAddMeters();
        testAddPixels();
        testAdditionOperator();

        report("Velocity");
    }

private:
    void testDefaultConstructor()
    {
        // Setup
        Velocity v;

        // Verify
        assertUnit(v.getDx() == 0.0f);
        assertUnit(v.getDy() == 0.0f);
    }

    void testParameterizedConstructor()
    {
        // Setup
        Velocity v(3.5f, -2.1f);

        // Verify
        float epsilon = 1e-6f;
        assertUnit(fabs(v.getDx() - 3.5f) < epsilon);
        assertUnit(fabs(v.getDy() - -2.1f) < epsilon);
    }

    void testSettersAndGetters()
    {
        // Setup
        Velocity v;
        v.setDx(4.5f);
        v.setDy(-3.2f);

        // Verify
        float epsilon = 1e-6f;
        assertUnit(fabs(v.getDx() - 4.5f) < epsilon);
        assertUnit(fabs(v.getDy() - -3.2f) < epsilon);
    }

    void testGetSpeed()
    {
        // Setup
        Velocity v(3.0f, 4.0f); // Speed = sqrt(3^2 + 4^2) = 5.0

        // Verify
        assertUnit(v.getSpeed() == 5.0f);
    }

    void testGetAngle()
    {
        // Setup
        Velocity v(1.0f, 1.0f);
        Angle angle = v.getAngle();

        // Verify
        float epsilon = 1e-6f;
        assertUnit(fabs(angle.getRadian() - atan2(1.0, 1.0)) < epsilon);
    }

    void testAddMeters()
    {
        // Setup
        Velocity v;
        Angle angle(45.0); // 45 degrees = pi/4 radians

        // Exercise
        v.addMeters(10.0, angle); // Adds 10 meters at 45 degrees

        // Verify
        float epsilon = 1e-6f;
        assertUnit(fabs(v.getDx() - (10.0 * sin(angle.getDegree()))) < epsilon);
        assertUnit(fabs(v.getDy() - (10.0 * cos(angle.getDegree()))) < epsilon);
    }

    void testAddPixels()
    {
        // Setup
        Velocity v;
        Angle angle;
        angle.setDegree(90.0); // Set angle to 90 degrees (π/2 radians)

        // Exercise
        v.addPixels(20.0, angle); // Adds 20 pixels at 90 degrees

        // Verify
        double dx = v.getDx(); // Raw `dx` value in meters
        double dy = v.getDy();

        // Expected values
        double expectedDx = 20.0 * Velocity::metersFromPixels; // Scaled by `metersFromPixels`
        double expectedDy = 0.0; // Since cos(90°) = 0

        assertUnit(dx > expectedDx - 0.1 && dx < expectedDx + 0.1); // Account for floating-point errors
        assertUnit(dy > expectedDy - 0.1 && dy < expectedDy + 0.1);
    }

    void testAdditionOperator()
    {
        // Setup
        Velocity v1(3.0f, 4.0f);
        Velocity v2(1.0f, 2.0f);

        // Exercise
        v1 += v2;

        // Verify
        assertUnit(v1.getDx() == 4.0f);
        assertUnit(v1.getDy() == 6.0f);
    }

};

#endif /* testVelocity_h */


