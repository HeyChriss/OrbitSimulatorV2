/***********************************************************************
 * Header File:
 *    Testing Satellite
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about testing satellites and collisions 
 ************************************************************************/
#ifndef testSatellite_h
#define testSatellite_h

#include <iostream>
#include <cassert>
#include "satellite.h"
#include "gps.h"
#include "dragon.h"
#include "starlink.h"
#include "hubble.h"
#include "simulator.h"
#include "unitTest.h"

using namespace std;

/*******************************
 * TEST Satellite
 * A friend class for Satellite which contains the unit tests
 ********************************/
class TestSatellite : public UnitTest
{
public:
    void run()
    {
        testDefaultConstructor();
        testBreakApart();
        testCollisionBehavior();
        testSatelliteInitialStates();
        testSatelliteVelocityCollisions();
        testSatelliteTypesCollisions();
        testBoundaryCollisions();

        report("Satellite and collision");
    }

private:
    void testDefaultConstructor()
    {
        // Setup
        Satellite sat;

        // Verify
        assertUnit(sat.getRadius() == 10.0 * 100000); // Adjusted for scaling
        assertUnit(sat.getNumFragments() == 2); // Satellite fragments
        assertUnit(sat.getExpired() == false);
        assertUnit(sat.getHasBeenHit() == false);
    }

    void testBreakApart()
    {
        // Setup
        DummySimulator sim("");  // Pass empty string for default
        Satellite sat(Position(100, 100), Velocity(50, 50));
        sat.numFragments = 3; // Set number of fragments

        // Exercise
        sat.breakApart(&sim);

        // Verify
        assertUnit(sat.getExpired() == true);
        assertUnit(sat.getHasBeenHit() == true);
    }

    void testCollisionBehavior()
    {
        // Setup - Create two satellites in collision course
        Position pos1(0, 0);
        Position pos2(15, 0);  // Close enough to collide based on radii
        Velocity vel(0, 0);

        Satellite sat1(pos1, vel);
        Satellite sat2(pos2, vel);

        // Test collision detection
        assertUnit(sat1.isHit(&sat2));
        assertUnit(sat2.isHit(&sat1));

        // Test collision between different satellite types
        GPS::GPS gps(pos1, vel);
        Dragon::Dragon dragon(pos2, vel);

        assertUnit(gps.isHit(&dragon));
        assertUnit(dragon.isHit(&gps));
    }

    void testSatelliteInitialStates()
    {
        // Test GPS initial state
        GPS::GPS gps;
        assertUnit(gps.getRadius() == 7.0 * 100000);
        assertUnit(gps.getNumFragments() == 2);

        // Test Dragon initial state
        Dragon::Dragon dragon;
        assertUnit(dragon.getRadius() == 7.0 * 100000);
        assertUnit(dragon.getNumFragments() == 2);

        // Test Starlink initial state
        Starlink::Starlink starlink;
        assertUnit(starlink.getRadius() == 7.0 * 100000);
        assertUnit(starlink.getNumFragments() == 2);

        // Test Hubble initial state
        Hubble::Hubble hubble;
        assertUnit(hubble.getRadius() == 7.0 * 100000);
        assertUnit(hubble.getNumFragments() == 2);
    }

    void testSatelliteVelocityCollisions()
    {
        // Test collisions with different velocities
        Position pos1(0, 0);
        Position pos2(15, 0);

        // Test head-on collision
        Velocity vel1(50, 0);
        Velocity vel2(-50, 0);
        Satellite sat1(pos1, vel1);
        Satellite sat2(pos2, vel2);
        assertUnit(sat1.isHit(&sat2));

        // Test perpendicular paths
        Velocity vel3(0, 50);
        Satellite sat3(pos1, vel1);
        Satellite sat4(pos2, vel3);
        assertUnit(sat3.isHit(&sat4));

        // Test parallel paths
        Velocity vel5(50, 0);
        Velocity vel6(50, 0);
        Satellite sat5(pos1, vel5);
        Satellite sat6(pos2, vel6);
        assertUnit(sat5.isHit(&sat6));
    }

    void testSatelliteTypesCollisions()
    {
        Position pos1(0, 0);
        Position pos2(15, 0);
        Velocity vel(0, 0);

        // Test GPS with all other types
        GPS::GPS gps(pos1, vel);
        Dragon::Dragon dragon(pos2, vel);
        Starlink::Starlink starlink(pos2, vel);
        Hubble::Hubble hubble(pos2, vel);
        Sputnik sputnik(pos2, vel);

        assertUnit(gps.isHit(&dragon));
        assertUnit(gps.isHit(&starlink));
        assertUnit(gps.isHit(&hubble));
        assertUnit(gps.isHit(&sputnik));

        // Test Dragon with all other types
        Dragon::Dragon dragon2(pos1, vel);
        assertUnit(dragon2.isHit(&starlink));
        assertUnit(dragon2.isHit(&hubble));
        assertUnit(dragon2.isHit(&sputnik));

        // Test Starlink with remaining types
        Starlink::Starlink starlink2(pos1, vel);
        assertUnit(starlink2.isHit(&hubble));
        assertUnit(starlink2.isHit(&sputnik));
    }

    void testBoundaryCollisions()
    {
        Position pos1(0, 0);
        Velocity vel(0, 0);
        Satellite sat1(pos1, vel);

        // Test exact boundary collision
        double exactDistance = (sat1.getRadius() + sat1.getRadius()) / 100000.0;
        Position boundaryPos(exactDistance, 0);
        Satellite sat2(boundaryPos, vel);
        assertUnit(sat1.isHit(&sat2));

        // Test just inside boundary
        Position insidePos(exactDistance - 1, 0);
        Satellite sat4(insidePos, vel);
        assertUnit(sat1.isHit(&sat4));
    }


};

#endif /* testSatellite_h */
