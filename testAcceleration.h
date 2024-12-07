
/***********************************************************************
 * Header File:
 *    Test Acceleration
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about Testing acceleration
 ************************************************************************/
#ifndef testAcceleration_h
#define testAcceleration_h

#include <iostream>
#include <cassert>
#include "acceleration.h"
#include "unitTest.h"

using namespace std;

/*******************************
 * TEST Acceleration
 * A friend class for Acceleration which contains the unit tests
 ********************************/
class TestAcceleration : public UnitTest
{
public:
    void run()
    {
        testDefaultConstructor();
        testParameterizedConstructor();
        testGetters();
        testSetters();

        report("Acceleration");
    }

private:
    void testDefaultConstructor()
    {
        // Setup
        Acceleration a;

        // Verify
        assertUnit(a.getDdx() == 0.0);
        assertUnit(a.getDdy() == 0.0);
    }

    void testParameterizedConstructor()
    {
        // Setup
        Acceleration a(3.5f, -2.1f);

        // Verify with precision check
        float epsilon = 1e-6f;
        assertUnit(fabs(a.getDdx() - 3.5f) < epsilon);
        assertUnit(fabs(a.getDdy() - -2.1f) < epsilon);
    }

    void testGetters()
    {
        // Setup
        Acceleration a(1.2f, 2.4f);

        // Verify with precision check
        float epsilon = 1e-6f;
        assertUnit(fabs(a.getDdx() - 1.2f) < epsilon);
        assertUnit(fabs(a.getDdy() - 2.4f) < epsilon);
    }

    void testSetters()
    {
        // Setup
        Acceleration a;
        a.setDdx(4.5f);
        a.setDdy(-3.2f);

        // Verify with precision check
        float epsilon = 1e-6f;
        assertUnit(fabs(a.getDdx() - 4.5f) < epsilon);
        assertUnit(fabs(a.getDdy() - -3.2f) < epsilon);
    }
};

#endif /* testAcceleration_h */

