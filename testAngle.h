
/***********************************************************************
 * Header File:
 *    TestAngle
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about Testing Angle
 ************************************************************************/
#pragma once
#ifndef testAngle_h
#define testAngle_h

#include <iostream>
#include <cassert>
#include "unitTest.h"
#include "angle.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include "testVelocity.h"


class TestAngle : public UnitTest
{
public:
    void run()
    {
        testDefaultConstructor();
        testNonDefaultConstructor();
        testConstantPi();
        testConstantFullRevolution();
        testAssignmentOperator();
        testAdditionOperator();
        testSubtractionOperator();
        testMultiplicationOperator();
        testEqualityOperator();
        testNormalizeZero();
        testNormalizePositive();
        testNormalizeNegative();
        testNormalizeMultipleRevolutions();
        testNormalizeExactRevolution();
        testSetDegree();
        testAddDegree();
        testSetRadian();
        testAddRadian();

        report("Angle");
    }

private:
    void testDefaultConstructor()
    {
        // Setup & Exercise
        Angle angle;

        // Verify - direct member access
        assertUnit(angle.radAngle == 0.0);
    }

    void testNonDefaultConstructor()
    {
        // Setup & Exercise
        Angle angle(M_PI);

        // Verify - direct member access
        assertUnit(angle.radAngle == M_PI);
    }

    void testConstantPi()
    {
        // Setup & Exercise
        Angle angle;

        // Verify - direct member access
        assertUnit(angle.pi == 2 * asin(1.0));
    }

    void testConstantFullRevolution()
    {
        // Setup & Exercise
        Angle angle;

        // Verify - direct member access
        assertUnit(angle.fullRevolutionRad == 2 * angle.pi);
    }

    void testAssignmentOperator()
    {
        // Setup
        Angle angle1;
        Angle angle2;
        angle1.radAngle = M_PI;

        // Exercise
        angle2 = angle1;

        // Verify - direct member access
        assertUnit(angle2.radAngle == M_PI);
    }

    void testAdditionOperator()
    {
        // Setup
        Angle angle1;
        Angle angle2;
        angle1.radAngle = M_PI / 2;
        angle2.radAngle = M_PI / 2;

        // Exercise
        angle1 += angle2;

        // Verify - direct member access
        assertUnit(angle1.radAngle == M_PI);
    }

    void testSubtractionOperator()
    {
        // Setup
        Angle angle1;
        Angle angle2;
        angle1.radAngle = M_PI;
        angle2.radAngle = M_PI / 2;

        // Exercise
        angle1 -= angle2;

        // Verify - direct member access
        assertUnit(angle1.radAngle == M_PI / 2);
    }

    void testMultiplicationOperator()
    {
        // Setup
        Angle angle;
        angle.radAngle = M_PI / 2;

        // Exercise
        angle *= 2;

        // Verify - direct member access
        assertUnit(angle.radAngle == M_PI);
    }

    void testEqualityOperator()
    {
        // Setup
        Angle angle1;
        Angle angle2;
        angle1.radAngle = M_PI;
        angle2.radAngle = M_PI;

        // Exercise & Verify
        assertUnit(angle1 == angle2);
    }

    void testNormalizeZero()
    {
        // Setup
        Angle angle;
        angle.radAngle = 0.0;

        // Exercise
        angle.normalize();

        // Verify - direct member access
        assertUnit(angle.radAngle == 0.0);
    }

    void testNormalizePositive()
    {
        // Setup
        Angle angle;
        angle.radAngle = 3 * M_PI;

        // Exercise
        angle.normalize();

        // Verify - direct member access
        assertUnit(angle.radAngle == M_PI);
    }

    void testNormalizeNegative()
    {
        // Setup
        Angle angle;
        angle.radAngle = -M_PI;

        // Exercise
        angle.normalize();

        // Verify - direct member access
        assertUnit(angle.radAngle == M_PI);
    }

    void testNormalizeMultipleRevolutions()
    {
        // Setup
        Angle angle;
        angle.radAngle = 5 * M_PI;

        // Exercise
        angle.normalize();

        // Verify - direct member access
        assertUnit(angle.radAngle == M_PI);
    }

    void testNormalizeExactRevolution()
    {
        // Setup
        Angle angle;
        angle.radAngle = 2 * M_PI;

        // Exercise
        angle.normalize();

        // Verify - direct member access
        assertUnit(angle.radAngle == 0.0);
    }

    void testSetDegree()
    {
        // Setup
        Angle angle;

        // Exercise
        angle.setDegree(180.0);

        // Verify - direct member access
        assertUnit(fabs(angle.radAngle - M_PI) < 0.001);
    }

    void testAddDegree()
    {
        // Setup
        Angle angle;
        angle.radAngle = M_PI / 2;

        // Exercise
        angle.addDegree(90.0);

        // Verify - direct member access
        assertUnit(fabs(angle.radAngle - M_PI) < 0.001);
    }

    void testSetRadian()
    {
        // Setup
        Angle angle;

        // Exercise
        angle.setRadian(M_PI);

        // Verify - direct member access
        assertUnit(angle.radAngle == M_PI);
    }

    void testAddRadian()
    {
        // Setup
        Angle angle;
        angle.radAngle = M_PI / 2;

        // Exercise
        angle.addRadian(M_PI / 2);

        // Verify - direct member access
        assertUnit(angle.radAngle == M_PI);
    }
};

#endif /* testAngle_h */