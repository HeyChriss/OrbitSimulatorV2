/***********************************************************************
 * Header File:
 *    Test Ship
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about Ship
  ************************************************************************/
#ifndef testShip_h
#define testShip_h

#include <iostream>
#include "ship.h"
#include <cassert>
#include "unitTest.h"
#include "simulator.h"

  /*******************************
   * TEST Ship
   * A friend class for Ship which contains the Ship unit tests
   ********************************/
class TestShip : public UnitTest
{
public:
    void run()
    {
        testConstructorRadius();
        testConstructorFragments();
        testConstructorExpired();
        testConstructorHasBeenHit();
        testConstructorDefective();
        testConstructorThrust();
        testConstructorRotation();
        testUpdateWithThrust();
        testUpdateWithoutThrust();
        testIsHitWithProjectile();
        testIsHitWithSatellite();

        report("Ship");
    }

private:
    void testConstructorRadius()
    {
        // Setup & Exercise
        Spaceship ship;

        // Verify - direct member access
        assertUnit(ship.radius == 10);
    }

    void testConstructorFragments()
    {
        // Setup & Exercise
        Spaceship ship;

        // Verify - direct member access
        assertUnit(ship.numFragments == 4);
    }

    void testConstructorExpired()
    {
        // Setup & Exercise
        Spaceship ship;

        // Verify - direct member access
        assertUnit(ship.isExpired == false);
    }

    void testConstructorHasBeenHit()
    {
        // Setup & Exercise
        Spaceship ship;

        // Verify - direct member access
        assertUnit(ship.hasBeenHit == false);
    }

    void testConstructorDefective()
    {
        // Setup & Exercise
        Spaceship ship;

        // Verify - direct member access
        assertUnit(ship.defective == false);
    }

    void testConstructorThrust()
    {
        // Setup & Exercise
        Spaceship ship;

        // Verify - direct member access
        assertUnit(ship.thrust == false);
    }

    void testConstructorRotation()
    {
        // Setup & Exercise
        Spaceship ship;

        // Verify - direct member access
        assertUnit(ship.rotationAngle.radAngle == 0.0);
    }

    void testUpdateWithThrust()
    {
        // Setup
        Spaceship ship;
        ship.thrust = true;
        ship.vel.dx = 0.0;
        ship.vel.dy = 0.0;

        // Exercise
        ship.update(1.0, 0.0, 0.0);

        // Verify - at least one velocity component should have changed
        assertUnit(ship.vel.dx != 0.0 || ship.vel.dy != 0.0);
    }

    void testUpdateWithoutThrust()
    {
        // Setup
        Spaceship ship;
        ship.thrust = false;
        ship.vel.dx = 0.0;
        ship.vel.dy = 0.0;

        // Exercise
        ship.update(1.0, 0.0, 0.0);

        // Verify - velocity should remain unchanged
        assertUnit(ship.vel.dx == 0.0);
        assertUnit(ship.vel.dy == 0.0);
    }

    void testIsHitWithProjectile()
    {
        // Setup
        Spaceship ship;
        Projectile projectile(&ship);

        // Exercise
        bool hit = ship.isHit(&projectile);

        // Verify
        assertUnit(hit == false);  // Ship shouldn't be hit by its own projectile
    }

    void testIsHitWithSatellite()
    {
        // Setup
        Spaceship ship;
        Satellite satellite;
        ship.pos.x = 0.0;
        ship.pos.y = 0.0;
        satellite.pos.x = 5.0;  // Close enough to collide
        satellite.pos.y = 0.0;

        // Exercise
        bool hit = ship.isHit(&satellite);

        // Verify
        assertUnit(hit == true);
    }
};

#endif /* testShip_h */
