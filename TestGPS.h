/***********************************************************************
 * Header File:
 *    Test GPS
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about Testing GPS
 ************************************************************************/
#ifndef testGPS_h
#define testGPS_h

#include <iostream>
#include "gps.h"
#include <cassert>
#include "unitTest.h"
#include "simulator.h"

 /*******************************
  * TEST GPS
  * A friend class for GPS which contains the GPS unit tests
  ********************************/
class TestGPS : public UnitTest
{
public:
    void run()
    {
        testGPSConstructorRadius();
        testGPSConstructorFragments();
        testGPSConstructorExpired();
        testGPSConstructorHasBeenHit();
        testGPSBreakApart();
        testGPSCenterRadius();
        testGPSCenterFragments();
        testGPSCenterOrigin();
        testGPSLeftRadius();
        testGPSLeftFragments();
        testGPSLeftOrigin();
        testGPSRightRadius();
        testGPSRightFragments();
        testGPSRightOrigin();

        report("GPS");
    }

private:
    void testGPSConstructorRadius()
    {
        // Setup & Exercise
        GPS::GPS gps;

        // Verify - direct member access
        assertUnit(gps.radius == 7);
    }

    void testGPSConstructorFragments()
    {
        // Setup & Exercise
        GPS::GPS gps;

        // Verify - direct member access
        assertUnit(gps.numFragments == 2);
    }

    void testGPSConstructorExpired()
    {
        // Setup & Exercise
        GPS::GPS gps;

        // Verify - direct member access
        assertUnit(gps.isExpired == false);
    }

    void testGPSConstructorHasBeenHit()
    {
        // Setup & Exercise
        GPS::GPS gps;

        // Verify - direct member access
        assertUnit(gps.hasBeenHit == false);
    }

    void testGPSBreakApart()
    {
        // Setup
        DummySimulator sim("GPS");
        GPS::GPS gps;
        gps.pos.x = 100;
        gps.pos.y = 100;
        gps.vel.dx = 50;
        gps.vel.dy = 50;

        // Exercise
        gps.breakApart(&sim);

        // Verify - direct member access
        assertUnit(gps.isExpired == true);
    }

    void testGPSCenterRadius()
    {
        // Setup & Exercise
        GPS::GPSCenter center;

        // Verify - direct member access
        assertUnit(center.radius == 7);
    }

    void testGPSCenterFragments()
    {
        // Setup & Exercise
        GPS::GPSCenter center;

        // Verify - direct member access
        assertUnit(center.numFragments == 3);
    }

    void testGPSCenterOrigin()
    {
        // Setup & Exercise
        GPS::GPSCenter center;

        // Verify - direct member access
        assertUnit(center.partOrigin == "GPS");
    }

    void testGPSLeftRadius()
    {
        // Setup & Exercise
        GPS::GPSLeft left;

        // Verify - direct member access
        assertUnit(left.radius == 8);
    }

    void testGPSLeftFragments()
    {
        // Setup & Exercise
        GPS::GPSLeft left;

        // Verify - direct member access
        assertUnit(left.numFragments == 3);
    }

    void testGPSLeftOrigin()
    {
        // Setup & Exercise
        GPS::GPSLeft left;

        // Verify - direct member access
        assertUnit(left.partOrigin == "GPS");
    }

    void testGPSRightRadius()
    {
        // Setup & Exercise
        GPS::GPSRight right;

        // Verify - direct member access
        assertUnit(right.radius == 8);
    }

    void testGPSRightFragments()
    {
        // Setup & Exercise
        GPS::GPSRight right;

        // Verify - direct member access
        assertUnit(right.numFragments == 3);
    }

    void testGPSRightOrigin()
    {
        // Setup & Exercise
        GPS::GPSRight right;

        // Verify - direct member access
        assertUnit(right.partOrigin == "GPS");
    }
};

#endif /* testGPS_h */

