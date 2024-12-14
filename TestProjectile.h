/***********************************************************************
 * Header File:
 *    Projectile
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about Projectile
 ************************************************************************/
#ifndef testProjectile_h
#define testProjectile_h

#include <iostream>
#include <cassert>
#include "projectile.h"
#include "unitTest.h"
#include "ship.h"

class TestProjectile : public UnitTest
{
public:
    void run()
    {
        testConstructorFromShipPosition();
        testConstructorFromShipVelocityAngleZero();
        testUpdatePositionNoExpiry();
        testUpdatePositionWithExpiry();
        testUpdateVelocity();
        testLifetime();

        report("Projectile");
    }

private:
    void testConstructorFromShipPosition()
    {
        // Setup
        Spaceship ship;
        ship.pos.x = 100.0;
        ship.pos.y = 200.0;

        // Exercise
        Projectile projectile(&ship);

        // Verify - direct member access
        assertUnit(projectile.pos.x == 100.0);
        assertUnit(projectile.pos.y == 200.0);
    }

    void testConstructorFromShipVelocityAngleZero()
    {
        // Setup
        Spaceship ship;
        ship.rotationAngle.radAngle = 0.0;  // Pointing up

        // Exercise
        Projectile projectile(&ship);

        // Verify - direct member access
        assertUnit(projectile.vel.dy > 0.0);  // Should have upward velocity
        assertUnit(fabs(projectile.vel.dx) < 0.001);  // Should have minimal horizontal velocity
    }

    void testUpdatePositionNoExpiry()
    {
        // Setup
        Spaceship ship;
        Projectile projectile(&ship);
        projectile.pos.x = 100.0;
        projectile.pos.y = 100.0;
        projectile.vel.dx = 10.0;
        projectile.vel.dy = 10.0;
        projectile.lifetime = 50;  // Not expired

        // Record initial position
        double initialX = projectile.pos.x;
        double initialY = projectile.pos.y;

        // Exercise
        projectile.update(1.0, 0.0, 0.0);

        // Verify - position should change
        assertUnit(projectile.pos.x != initialX);
        assertUnit(projectile.pos.y != initialY);
    }

    void testUpdatePositionWithExpiry()
    {
        // Setup
        Spaceship ship;
        Projectile projectile(&ship);
        projectile.pos.x = 100.0;
        projectile.pos.y = 100.0;
        projectile.vel.dx = 10.0;
        projectile.vel.dy = 10.0;
        projectile.lifetime = 0;  // Expired

        // Record initial position
        double initialX = projectile.pos.x;
        double initialY = projectile.pos.y;

        // Exercise
        projectile.update(1.0, 0.0, 0.0);

        // Verify - position should not change due to expiry
        assertUnit(projectile.isExpired() == true);
    }

    void testUpdateVelocity()
    {
        // Setup
        Spaceship ship;
        Projectile projectile(&ship);
        projectile.vel.dx = 10.0;
        projectile.vel.dy = 10.0;

        // Record initial velocity
        double initialDx = projectile.vel.dx;
        double initialDy = projectile.vel.dy;

        // Exercise
        projectile.update(1.0, 0.0, 0.0);

        // Verify - velocity should remain constant (no gravity effect)
        assertUnit(projectile.vel.dx == initialDx);
        assertUnit(projectile.vel.dy == initialDy);
    }

    void testLifetime()
    {
        // Setup
        Spaceship ship;
        Projectile projectile(&ship);
        projectile.lifetime = 1;

        // Verify initial state
        assertUnit(projectile.isExpired() == false);

        // Exercise - update until expired
        projectile.update(1.0, 0.0, 0.0);
        projectile.update(1.0, 0.0, 0.0);

        // Verify - should be expired
        assertUnit(projectile.isExpired() == true);
    }
};

#endif /* testProjectile_h */