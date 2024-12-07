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
        testConstructor();
        testBreakApart();
        testGPSParts();

        report("GPS");
    }

private:
    void testConstructor()
    {
        // Setup & Exercise
        GPS::GPS gps;

        // Verify initial state
        assertUnit(gps.getRadius() == 700000.0);  // 7 * 100000
        assertUnit(gps.getNumFragments() == 2);
        assertUnit(!gps.getExpired());
        assertUnit(!gps.getHasBeenHit());
    }

    void testBreakApart()
    {
        // Setup
        Position pos(100, 100);
        Velocity vel(50, 50);
        DummySimulator* sim = new DummySimulator("GPS");  // Specify GPS type
        GPS::GPS* gps = new GPS::GPS(pos, vel);
        sim->addObject(gps);  // Add GPS to simulator

        // Exercise
        gps->breakApart(sim);

        // Verify
        assertUnit(gps->getExpired() == true);

        // Cleanup
        delete sim;
    }

    void testGPSParts()
    {
        // Test GPSCenter 
        GPS::GPSCenter center;
        assertUnit(center.getRadius() == 700000.0);  // 7 * 100000
        assertUnit(center.getNumFragments() == 3);
        assertUnit(center.partOrigin == "GPS");

        // Test GPSLeft
        GPS::GPSLeft left;
        assertUnit(left.getRadius() == 800000.0);    // 8 * 100000
        assertUnit(left.getNumFragments() == 3);
        assertUnit(left.partOrigin == "GPS");

        // Test GPSRight
        GPS::GPSRight right;
        assertUnit(right.getRadius() == 800000.0);   // 8 * 100000
        assertUnit(right.getNumFragments() == 3);
        assertUnit(right.partOrigin == "GPS");
    }
};

#endif /* testGPS_h */

