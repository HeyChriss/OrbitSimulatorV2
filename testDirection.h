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

using namespace std;

/*******************************
 * TEST Direction
 * A friend class for Direction which contains the unit tests
 ********************************/
class TestDirection : public UnitTest
{
public:
    void run()
    {
        testDefaultConstructor();
        testParameterizedConstructor();
        testConvertToRadians();
        testConvertToDegrees();
        testSettersAndGetters();
        testNormalization();
        testEqualityOperators();
        testUnaryMinusOperator();
        testIncrementDecrementOperators();

        report("Direction");
    }

private:
    void testDefaultConstructor()
    {
        // Setup
        Direction d;

        // Verify
        assertUnit(d.getDegrees() == 0.0);
        assertUnit(d.getRadians() == 0.0);
    }

    void testParameterizedConstructor()
    {
        // Setup
        Direction d(180.0);

        // Verify
        float epsilon = 1e-6;
        assertUnit(fabs(d.getDegrees() - 180.0) < epsilon);
        assertUnit(fabs(d.getRadians() - Direction().pi) < epsilon);
    }

    void testConvertToRadians()
    {
        // Setup
        Direction d;

        // Verify
        assertUnit(d.convertToRadians(180.0) == Direction().pi);
    }

    void testConvertToDegrees()
    {
        // Setup
        Direction d;

        // Verify
        assertUnit(d.convertToDegrees(Direction().pi) == 180.0);
    }

    void testSettersAndGetters()
    {
        // Setup
        Direction d;
        d.setDegrees(90.0);
        d.setRadians(Direction().pi / 2);

        // Verify
        float epsilon = 1e-6;
        assertUnit(fabs(d.getDegrees() - 90.0) < epsilon);
        assertUnit(fabs(d.getRadians() - (Direction().pi / 2)) < epsilon);
    }

    void testNormalization()
    {
        // Setup
        Direction d(450.0); // 450 degrees -> 90 degrees after normalization

        // Exercise
        d.normalize();

        // Verify
        assertUnit(d.getDegrees() == 90.0);
    }

    void testEqualityOperators()
    {
        // Setup
        Direction d1(90.0);
        Direction d2(450.0); // Equivalent to 90 degrees after normalization
        d2.normalize();

        // Verify
        assertUnit(d1 == d2);
        assertUnit(!(d1 != d2));
    }

    void testUnaryMinusOperator()
    {
        // Setup
        Direction d(90.0);

        // Exercise
        Direction negD = -d;

        // Verify
        assertUnit(negD.getDegrees() == 270.0); // 360 - 90 = 270
    }

    void testIncrementDecrementOperators()
    {
        // Setup
        Direction d(90.0);

        // Exercise
        ++d; // Prefix increment
        d++; // Postfix increment
        --d; // Prefix decrement
        d--; // Postfix decrement

        // Verify
        assertUnit(d.getDegrees() == 90.0); // Should return to original value
    }

};

#endif /* testDirection_h */


