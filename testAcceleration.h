
/***********************************************************************
 * Header File:
 *    Test Acceleration
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about Testing acceleration
 ************************************************************************/


/*******************************
 * TEST Acceleration
 * A friend class for Acceleration which contains the unit tests
 ********************************/
#ifndef testAcceleration_h
#define testAcceleration_h

#include <iostream>
#include <cassert>
#include "acceleration.h"
#include "unitTest.h"

class TestAcceleration : public UnitTest
{
public:
    void run()
    {
        testDefaultConstructorDdx();
        testDefaultConstructorDdy();
        testNonDefaultConstructorDdx();
        testNonDefaultConstructorDdy();
        testSetDdx();
        testSetDdy();
        report("Acceleration");
    }

private:
    void testDefaultConstructorDdx()
    {
        // Setup & Exercise
        Acceleration a;

        // Verify - direct member access
        assertUnit(a.ddx == 0.0);
    }

    void testDefaultConstructorDdy()
    {
        // Setup & Exercise
        Acceleration a;

        // Verify - direct member access
        assertUnit(a.ddy == 0.0);
    }

    void testNonDefaultConstructorDdx()
    {
        // Setup & Exercise
        Acceleration a(3.5, -2.1);

        // Verify - direct member access
        assertUnit(a.ddx == 3.5);
    }

    void testNonDefaultConstructorDdy()
    {
        // Setup & Exercise
        Acceleration a(3.5, -2.1);

        // Verify - direct member access
        assertUnit(a.ddy == -2.1);
    }

    void testSetDdx()
    {
        // Setup
        Acceleration a;

        // Exercise
        a.setDdx(4.5);

        // Verify - direct member access
        assertUnit(a.ddx == 4.5);
    }

    void testSetDdy()
    {
        // Setup
        Acceleration a;

        // Exercise
        a.setDdy(-3.2);

        // Verify - direct member access
        assertUnit(a.ddy == -3.2);
    }

    // Testing AccelerationDummy methods
    void testDummyGetDDX()
    {
        // Setup
        AccelerationDummy a;

        // Exercise & Verify
        assertUnit(a.getDDX() == 99.9);
    }
};

#endif /* testAcceleration_h */
