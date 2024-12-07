/***********************************************************************
 * Header File:
 *    Prijectile
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about Projectile
 ************************************************************************/
#ifndef testProjectile_h
#define testProjectile_h

#include <iostream>
#include "projectile.h"
#include "ship.h"
#include <cassert>
#include "unitTest.h"

/*******************************
 * TEST Projectile
 * A friend class for Projectile which contains the Projectile unit tests
 ********************************/
class TestProjectile : public UnitTest
{
public:
    void run()
    {
        testConstructorFromShip();
        testUpdate();
        testExpiration();

        report("Projectile");
    }

private:
    // Test helper to create a ship at a specific position and rotation
    Spaceship* createShipAtPosition(double x, double y, double rotation)
    {
        Position pos;
        pos.setMeters(x, y);
        Velocity vel(0.0, 0.0);
        Spaceship* ship = new Spaceship(pos, vel);
        Angle angle;
        angle.setDegree(rotation);
        ship->addRotation(angle);
        return ship;
    }

    void testConstructorFromShip()
    {
        // Setup - create ship at position with 45 degree rotation
        Spaceship* ship = createShipAtPosition(1000.0, 2000.0, 45.0);
        Physics physics;

        // Exercise
        Projectile projectile(ship);

        // Verify - projectile should be at ship's position
        assertEquals(projectile.getPosition().getMetersX(), 1000.0);
        assertEquals(projectile.getPosition().getMetersY(), 2000.0);

        // Get expected velocities using the same physics calculations used in Projectile constructor
        double speed = 10000.0;
        double rotation = ship->getRotation().getDegree();
        double expectedVx = physics.horizontalAcceleration(speed, rotation);
        double expectedVy = physics.verticalAcceleration(speed, rotation);

        // Verify velocities
        assertEquals(projectile.getVelocity().getDx(), expectedVx);

        // Cleanup
        delete ship;
    }

    void testUpdate()
    {
        // Setup - create ship pointing straight up
        Spaceship* ship = createShipAtPosition(0.0, 0.0, 0.0);
        Projectile projectile(ship);

        double time = 1.0;
        double gravity = 0.0;
        double radius = 0.0;

        // Exercise - update for one second
        projectile.update(time, gravity, radius);

        // Verify - with initial velocity of 10000 m/s straight up
        assertEquals(projectile.getPosition().getMetersY(), 10000.0);  // Moved up 10000m
        assertEquals(projectile.getPosition().getMetersX(), 0.0);      // No horizontal movement

        // Cleanup
        delete ship;
    }

    void testExpiration()
    {
        // Setup
        Spaceship* ship = createShipAtPosition(0.0, 0.0, 0.0);
        Projectile projectile(ship);

        // Exercise & Verify - projectile should expire after enough updates
        bool hasExpired = false;
        int updateCount = 0;
        while (!hasExpired && updateCount < 100)
        {
            projectile.update(1.0, 0.0, 0.0);
            hasExpired = projectile.isExpired();
            updateCount++;
        }

        assertUnit(hasExpired == true);  // Should expire eventually
        assertUnit(updateCount > 0 && updateCount < 100);  // Should expire within reasonable time

        // Cleanup
        delete ship;
    }
};

#endif /* testProjectile_h */