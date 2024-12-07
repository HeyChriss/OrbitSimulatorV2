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
#include "fragment.h"
#include <cassert>
#include "unitTest.h"
#include "simulator.h"

/*******************************
 * TEST Fragment
 * A friend class for Fragment which contains the Fragment unit tests
 ********************************/
class TestFragment : public UnitTest
{
public:
    void run()
    {
        testConstructor();
        testUpdate();
        testExpiration();
        testInheritedProperties();

        report("Fragment");
    }

private:
    void testConstructor()
    {
        // Setup & Exercise
        Position pos(100.0, 200.0);
        Velocity vel(50.0, -30.0);
        Angle angle(1.5);
        Fragment fragment(pos, vel, angle);

        // Verify initial state
        assertUnit(fragment.getRadius() == 200000.0);  // 2 * 100000
        assertUnit(fragment.getHasBeenHit() == true);  // Cannot break further
        assertUnit(!fragment.isExpired());  // Should not start expired

        // Verify position and velocity
        assertEquals(fragment.getPosition().getMetersX(), 100.0);
        assertEquals(fragment.getPosition().getMetersY(), 200.0);
        assertEquals(fragment.getVelocity().getDx(), 50.0);
        assertEquals(fragment.getVelocity().getDy(), -30.0);
    }

    void testUpdate()
    {
        // Setup
        Fragment fragment;
        double initialRotation = fragment.getRotation().getRadian();

        // Exercise
        fragment.update(1.0, 0.0, 0.0);

        // Verify rotation changed
        assertUnit(fragment.getRotation().getRadian() != initialRotation);
        assertEquals(fragment.getRotation().getRadian(), initialRotation + 0.005);
    }

    void testExpiration()
    {
        // Test multiple fragments to account for random lifetime
        const int TEST_COUNT = 10;
        int minLifetime = 999;
        int maxLifetime = 0;

        for (int test = 0; test < TEST_COUNT; test++)
        {
            // Setup
            Fragment fragment;
            int updateCount = 0;

            // Exercise - count updates until expiration
            while (!fragment.isExpired() && updateCount < 150)
            {
                updateCount++;
                fragment.update(1.0, 0.0, 0.0);
            }

            // Track min and max lifetimes
            if (updateCount < minLifetime) minLifetime = updateCount;
            if (updateCount > maxLifetime) maxLifetime = updateCount;

            // Verify each fragment expires eventually
            assertUnit(fragment.isExpired());
        }
    }

    void testInheritedProperties()
    {
        // Setup 
        Fragment fragment;

        // Verify CelestialObject properties
        assertUnit(fragment.getNumFragments() == 0);  // Cannot break further
        assertUnit(fragment.getHasBeenHit() == true); // Cannot break further

        // Verify random rotation is within bounds (0 to 2π)
        double rotation = fragment.getRotation().getRadian();
        assertUnit(rotation >= 0.0 && rotation <= 2.0 * 3.141592653589793);

        // Verify radius
        assertUnit(fragment.getRadius() == 200000.0);  // 2 * 100000
    }
};

#endif /* testFragment_h */

