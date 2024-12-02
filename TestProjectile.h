#pragma once
#include "Projectile.h"
#include "unitTest.h"
#include "position.h"
#include "velocity.h"
#include "angle.h"
#include "Ship.h"
#include "Satellite.h"

class TestProjectile : public UnitTest
{
public:
    void run()
    {
        // Constructor tests
        test_construct();
        test_constructWithRotation();
        test_offset();
        test_velocity();

        // Lifetime tests
        test_lifetime();
        test_expireAfter70Frames();
        test_notExpiredBefore70Frames();

        // Movement tests
        test_moveWithTimeDilation();

        // State tests
        test_initiallyInvisible();
        test_visibleAfter10Frames();
        test_deadWhenKilled();

        // Drawing tests
        test_draw();
        test_noDraw_whenInvisible();
        test_noDraw_whenDead();

        report("Projectile");
    }

private:
    // Mock ogstream for testing draw calls
    class MockOgstream : public ogstream
    {
    public:
        MockOgstream() : drawCalled(false) {}
        void drawProjectile(const Position& pos) override {
            drawCalled = true;
            lastDrawPosition = pos;
        }
        bool wasDrawCalled() const { return drawCalled; }
        Position getLastDrawPosition() const { return lastDrawPosition; }
    private:
        bool drawCalled;
        Position lastDrawPosition;
    };

    void test_construct()
    {
        // Setup
        std::list<Satellite*> satellites;
        Ship parent(satellites);

        // Exercise
        Projectile projectile(parent, 0.0);

        // Verify
        assertEquals(projectile.getRadius(), 1.0);
        assertEquals(projectile.lifetime, 70);
        assertUnit(!projectile.isDead());
    }

    void test_constructWithRotation()
    {
        // Setup
        std::list<Satellite*> satellites;
        Ship parent(satellites);
        double rotation = M_PI_2;

        // Exercise
        Projectile projectile(parent, rotation);

        // Verify projectile position is offset to the right
        Position pos = projectile.getPosition();
        Position parentPos = parent.getPosition();
        double dx = pos.getMetersX() - parentPos.getMetersX();
        double dy = pos.getMetersY() - parentPos.getMetersY();

        // Should be offset 19 pixels right
        assertUnit(dx > 0);
        assertEquals(dy, 0.0);
    }

    void test_offset()
    {
        // Setup
        std::list<Satellite*> satellites;
        Ship parent(satellites);
        double rotation = 0.0;

        // Exercise
        Projectile projectile(parent, rotation);

        // Verify offset is 19 pixels forward
        Position pos = projectile.getPosition();
        Position parentPos = parent.getPosition();
        double dy = pos.getMetersY() - parentPos.getMetersY();
        assertEquals(dy, 19.0 * pos.getZoom());  // Convert pixels to meters
    }

    void test_velocity()
    {
        // Setup
        std::list<Satellite*> satellites;
        Ship parent(satellites);
        parent.velocity.dx = 0.0;
        parent.velocity.dy = 0.0;  // Zero out parent velocity for clean test
        double rotation = 0.0;  // pointing up

        // Exercise
        Projectile projectile(parent, rotation);

        // Verify velocity is 9000 m/s upward
        assertEquals(projectile.velocity.getDX(), 0.0);
        assertEquals(projectile.velocity.getDY(), 9000.0);
    }

    void test_lifetime()
    {
        // Setup
        std::list<Satellite*> satellites;
        Ship parent(satellites);
        Projectile projectile(parent, 0.0);

        // Verify initial lifetime
        assertEquals(projectile.lifetime, 70);
    }

    void test_expireAfter70Frames()
    {
        // Setup
        std::list<Satellite*> satellites;
        Ship parent(satellites);
        Projectile projectile(parent, 0.0);

        // Exercise - move for full lifetime
        for (int i = 0; i <= 70; i++)
            projectile.move(1.0);

        // Verify
        assertUnit(projectile.isDead());
    }

    void test_notExpiredBefore70Frames()
    {
        // Setup
        std::list<Satellite*> satellites;
        Ship parent(satellites);
        Projectile projectile(parent, 0.0);

        // Exercise - move for 69 frames
        for (int i = 0; i < 69; i++)
            projectile.move(1.0);

        // Verify still alive
        assertUnit(!projectile.isDead());
    }

    void test_moveWithTimeDilation()
    {
        // Setup
        std::list<Satellite*> satellites;
        Ship parent(satellites);
        Projectile projectile(parent, 0.0);
        Position pos1 = projectile.getPosition();

        // Exercise
        projectile.move(1.0);

        // Verify movement scaled by time dilation
        Position pos2 = projectile.getPosition();
        double distance = sqrt(pow(pos2.getMetersX() - pos1.getMetersX(), 2) +
            pow(pos2.getMetersY() - pos1.getMetersY(), 2));
        assertUnit(distance > 9000.0);  // Should move more than base speed due to time dilation
    }

    void test_initiallyInvisible()
    {
        // Setup
        std::list<Satellite*> satellites;
        Ship parent(satellites);
        Projectile projectile(parent, 0.0);

        // Verify
        assertUnit(projectile.isInvisible());
    }

    void test_visibleAfter10Frames()
    {
        // Setup
        std::list<Satellite*> satellites;
        Ship parent(satellites);
        Projectile projectile(parent, 0.0);

        // Move for 11 frames
        for (int i = 0; i < 11; i++)
            projectile.move(1.0);

        // Verify
        assertUnit(!projectile.isInvisible());
    }

    void test_deadWhenKilled()
    {
        // Setup
        std::list<Satellite*> satellites;
        Ship parent(satellites);
        Projectile projectile(parent, 0.0);
        projectile.age = 10; // Make the object visible (bypass invisibility)

        // Exercise
        projectile.kill();

        // Verify
        assertUnit(projectile.isDead());
    }

    void test_draw()
    {
        // Setup
        std::list<Satellite*> satellites;
        Ship parent(satellites);
        Projectile projectile(parent, 0.0);
        MockOgstream gout;

        // Age past invisible phase
        for (int i = 0; i < 11; i++)
            projectile.move(1.0);

        // Exercise
        projectile.draw(gout);

        // Verify
        assertUnit(gout.wasDrawCalled());
    }

    void test_noDraw_whenInvisible()
    {
        // Setup
        std::list<Satellite*> satellites;
        Ship parent(satellites);
        Projectile projectile(parent, 0.0);
        MockOgstream gout;

        // Exercise - draw while still invisible
        projectile.draw(gout);

        // Verify
        assertUnit(!gout.wasDrawCalled());
    }

    void test_noDraw_whenDead()
    {
        // Setup
        std::list<Satellite*> satellites;
        Ship parent(satellites);
        Projectile projectile(parent, 0.0);
        MockOgstream gout;

        projectile.kill();

        // Exercise
        projectile.draw(gout);

        // Verify
        assertUnit(!gout.wasDrawCalled());
    }
};

