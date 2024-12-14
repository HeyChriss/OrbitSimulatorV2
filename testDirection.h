/***********************************************************************
 * Header File:
 *    Test Direction
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about Testing Direction
 ************************************************************************/
#ifndef testDirection_h
#define testDirection_h

#include <iostream>
#include <cassert>
#include "direction.h"
#include "unitTest.h"
#include "testVelocity.h"

class TestDirection : public UnitTest
{
public:
    void run()
    {
        testDefaultConstructor();
        testNonDefaultConstructor();
        testConvertToDegreesZero();
        testConvertToDegreesQuarterCircle();
        testConvertToDegreesHalfCircle();
        testConvertToDegreesFullCircle();
        testConvertToRadiansZero();
        testConvertToRadiansQuarterCircle();
        testConvertToRadiansHalfCircle();
        testConvertToRadiansFullCircle();
        testNormalizeZero();
        testNormalizePositive();
        testNormalizeNegative();
        testNormalizeMultipleRevolutions();
        testAssignmentOperator();
        testUnaryMinusOperator();
        testEqualityOperator();
        testInequalityOperator();
        testPrefixIncrement();
        testPostfixIncrement();
        testPrefixDecrement();
        testPostfixDecrement();
        testConstants();

        report("Direction");
    }

private:
    void testDefaultConstructor()
    {
        // Setup & Exercise
        Direction d;

        // Verify - direct member access
        assertUnit(d.degrees == 0.0);
        assertUnit(d.radians == 0.0);
    }

    void testNonDefaultConstructor()
    {
        // Setup & Exercise
        Direction d(180.0);

        // Verify - direct member access
        assertUnit(d.degrees == 180.0);
        assertUnit(fabs(d.radians - M_PI) < 0.001);
    }

    void testConvertToDegreesZero()
    {
        // Setup
        Direction d;

        // Exercise
        double result = d.convertToDegrees(0.0);

        // Verify
        assertUnit(result == 0.0);
    }

    void testConvertToDegreesQuarterCircle()
    {
        // Setup
        Direction d;

        // Exercise
        double result = d.convertToDegrees(M_PI / 2);

        // Verify
        assertUnit(fabs(result - 90.0) < 0.001);
    }

    void testConvertToDegreesHalfCircle()
    {
        // Setup
        Direction d;

        // Exercise
        double result = d.convertToDegrees(M_PI);

        // Verify
        assertUnit(fabs(result - 180.0) < 0.001);
    }

    void testConvertToDegreesFullCircle()
    {
        // Setup
        Direction d;

        // Exercise
        double result = d.convertToDegrees(2 * M_PI);

        // Verify
        assertUnit(fabs(result - 360.0) < 0.001);
    }

    void testConvertToRadiansZero()
    {
        // Setup
        Direction d;

        // Exercise
        double result = d.convertToRadians(0.0);

        // Verify
        assertUnit(result == 0.0);
    }

    void testConvertToRadiansQuarterCircle()
    {
        // Setup
        Direction d;

        // Exercise
        double result = d.convertToRadians(90.0);

        // Verify
        assertUnit(fabs(result - M_PI / 2) < 0.001);
    }

    void testConvertToRadiansHalfCircle()
    {
        // Setup
        Direction d;

        // Exercise
        double result = d.convertToRadians(180.0);

        // Verify
        assertUnit(fabs(result - M_PI) < 0.001);
    }

    void testConvertToRadiansFullCircle()
    {
        // Setup
        Direction d;

        // Exercise
        double result = d.convertToRadians(360.0);

        // Verify
        assertUnit(fabs(result - 2 * M_PI) < 0.001);
    }

    void testNormalizeZero()
    {
        // Setup
        Direction d(0.0);

        // Exercise
        d.normalize();

        // Verify - direct member access
        assertUnit(d.degrees == 0.0);
        assertUnit(d.radians == 0.0);
    }

    void testNormalizePositive()
    {
        // Setup
        Direction d(720.0);  // Two full rotations

        // Exercise
        d.normalize();

        // Verify - direct member access
        assertUnit(d.degrees == 0.0);
        assertUnit(fabs(d.radians) < 0.001);
    }

    void testNormalizeNegative()
    {
        // Setup
        Direction d(-180.0);

        // Exercise
        d.normalize();

        // Verify - direct member access
        assertUnit(d.degrees == 180.0);
        assertUnit(fabs(d.radians - M_PI) < 0.001);
    }

    void testNormalizeMultipleRevolutions()
    {
        // Setup
        Direction d(900.0);  // 2.5 rotations

        // Exercise
        d.normalize();

        // Verify - direct member access
        assertUnit(fabs(d.degrees - 180.0) < 0.001);
        assertUnit(fabs(d.radians - M_PI) < 0.001);
    }

    void testAssignmentOperator()
    {
        // Setup
        Direction d1(90.0);
        Direction d2;

        // Exercise
        d2 = d1;

        // Verify - direct member access
        assertUnit(d2.degrees == d1.degrees);
        assertUnit(d2.radians == d1.radians);
    }

    void testUnaryMinusOperator()
    {
        // Setup
        Direction d(90.0);

        // Exercise
        Direction result = -d;

        // Verify - direct member access
        assertUnit(fabs(result.degrees - 270.0) < 0.001);
        assertUnit(fabs(result.radians - (3 * M_PI / 2)) < 0.001);
    }

    void testEqualityOperator()
    {
        // Setup
        Direction d1(90.0);
        Direction d2(90.0);
        Direction d3(180.0);

        // Exercise & Verify
        assertUnit(d1 == d2);
        assertUnit(!(d1 == d3));
    }

    void testInequalityOperator()
    {
        // Setup
        Direction d1(90.0);
        Direction d2(90.0);
        Direction d3(180.0);

        // Exercise & Verify
        assertUnit(!(d1 != d2));
        assertUnit(d1 != d3);
    }

    void testPrefixIncrement()
    {
        // Setup
        Direction d(89.0);

        // Exercise
        ++d;

        // Verify - direct member access
        assertUnit(d.degrees == 90.0);
    }

    void testPostfixIncrement()
    {
        // Setup
        Direction d(89.0);

        // Exercise
        Direction result = d++;

        // Verify - direct member access
        assertUnit(result.degrees == 89.0);
        assertUnit(d.degrees == 90.0);
    }

    void testPrefixDecrement()
    {
        // Setup
        Direction d(90.0);

        // Exercise
        --d;

        // Verify - direct member access
        assertUnit(d.degrees == 89.0);
    }

    void testPostfixDecrement()
    {
        // Setup
        Direction d(90.0);

        // Exercise
        Direction result = d--;

        // Verify - direct member access
        assertUnit(result.degrees == 90.0);
        assertUnit(d.degrees == 89.0);
    }

    void testConstants()
    {
        // Setup
        Direction d;

        // Verify
        assertUnit(fabs(d.pi - M_PI) < 0.001);
        assertUnit(fabs(d.fullRevolutionRad - (2 * M_PI)) < 0.001);
        assertUnit(d.fullRevolutionDeg == 360.0);
    }
};

#endif /* testDirection_h */


