#pragma once

#include "gps.h"
#include "unitTest.h"
#include "position.h"
#include "velocity.h"
#include "angle.h"
#include <list>

/*********************************************
 * TEST GPS
 * Unit tests for the GPS class and its components
 *********************************************/
class TestGPS : public UnitTest
{
public:
    void run()
    {
        // Basic satellite tests
        constructor_defaultPosition();
        constructor_specificPosition();
        constructor_initialRotation();
        constructor_defaultAttributes();

        // Initial positions tests
        test_initialPositionsCount();
        test_initialPositionsValues();
        test_initialVelocityValues();

        // State and movement tests
        test_isInvisible();
        test_isDead();
        test_move();
        test_orbit();

        // Destruction tests
        test_destroyMain();
        test_destroyCenter();
        test_destroyLeftArray();
        test_destroyRightArray();

        // Drawing tests
        draw_mainSatellite();
        draw_centerPiece();
        draw_leftArray();
        draw_rightArray();

        report("GPS");
    }

private:
    // Mock ogstream for testing draw calls
    class MockOgstream : public ogstream
    {
    public:
        MockOgstream() : drawMainCalled(false), drawCenterCalled(false),
            drawLeftCalled(false), drawRightCalled(false) {}
        void drawGPS(const Position& pos, double angle) override
        {
            drawMainCalled = true;
        }
        void drawGPSCenter(const Position& pos, double angle) override
        {
            drawCenterCalled = true;
        }
        void drawGPSLeft(const Position& pos, double angle, const Position& offset = Position()) override
        {
            drawLeftCalled = true;
        }

        void drawGPSRight(const Position& pos, double angle, const Position& offset = Position()) override
        {
            drawRightCalled = true;
        }
        bool wasMainDrawCalled() const { return drawMainCalled; }
        bool wasCenterDrawCalled() const { return drawCenterCalled; }
        bool wasLeftDrawCalled() const { return drawLeftCalled; }
        bool wasRightDrawCalled() const { return drawRightCalled; }
    private:
        bool drawMainCalled;
        bool drawCenterCalled;
        bool drawLeftCalled;
        bool drawRightCalled;
    };

    void constructor_defaultPosition()
    {
        // Exercise
        GPS gps;

        // Verify default position (first in the sequence)
        verify(std::abs(gps.getPosition().getMetersX() - 0.0) <= 0.001, __FUNCTION__);
        verify(std::abs(gps.getPosition().getMetersY() - 26560000.0) <= 0.001, __FUNCTION__);
    }

    void constructor_specificPosition()
    {
        // Setup
        Position pos(23001634.72, 13280000.0);
        Velocity vel(-1940.00, 3360.18);

        // Exercise
        GPS gps(pos, vel);

        // Verify
        verify(std::abs(gps.getPosition().getMetersX() - 23001634.72) <= 0.001, __FUNCTION__);
        verify(std::abs(gps.getPosition().getMetersY() - 13280000.0) <= 0.001, __FUNCTION__);
        verify(std::abs(gps.velocity.getDX() - (-1940.00)) <= 0.001, __FUNCTION__);
        verify(std::abs(gps.velocity.getDY() - 3360.18) <= 0.001, __FUNCTION__);
    }

    void constructor_initialRotation()
    {
        // Exercise
        GPS gps;

        // Verify
        verify(std::abs(gps.angularVelocity - 0.001) <= 0.0001, __FUNCTION__);
    }

    void constructor_defaultAttributes()
    {
        // Exercise
        GPS gps;

        // Verify
        verify(gps.getAge() == 0, __FUNCTION__);
        verify(gps.getRadius() == 12.0, __FUNCTION__);  // GPS main body is 12 pixels
        verify(gps.isDead() == false, __FUNCTION__);
    }

    void test_initialPositionsCount()
    {
        // Exercise
        auto positions = GPS::getInitialPositions();

        // Verify
        verify(positions.size() == 6, __FUNCTION__);  // Should be 6 GPS satellites per orbit
    }

    void test_initialPositionsValues()
    {
        // Exercise
        auto positions = GPS::getInitialPositions();

        // Verify first position
        verify(std::abs(positions[0].first.getMetersX() - 0.0) <= 0.001, __FUNCTION__);
        verify(std::abs(positions[0].first.getMetersY() - 26560000.0) <= 0.001, __FUNCTION__);

        // Verify last position
        verify(std::abs(positions[5].first.getMetersX() - (-23001634.72)) <= 0.001, __FUNCTION__);
        verify(std::abs(positions[5].first.getMetersY() - 13280000.0) <= 0.001, __FUNCTION__);
    }

    void test_initialVelocityValues()
    {
        // Exercise
        auto positions = GPS::getInitialPositions();

        // Verify velocities maintain orbital speed of 3.9 km/s
        for (const auto& posVel : positions)
        {
            double speed = sqrt(pow(posVel.second.getDX(), 2) + pow(posVel.second.getDY(), 2));
            verify(std::abs(speed - 3880.0) <= 1.0, __FUNCTION__);  // 3.88 km/s ≈ 3.9 km/s
        }
    }

    void test_isInvisible()
    {
        // Setup
        GPS gps;

        // Initially invisible
        verify(gps.isInvisible() == true, __FUNCTION__);

        // Age it
        for (int i = 0; i < 11; i++)
            gps.move(1.0);

        // Should now be visible
        verify(gps.isInvisible() == false, __FUNCTION__);
    }

    void test_isDead()
    {
        // Setup
        GPS gps;

        // Age to make it visible
        for (int i = 0; i < 11; i++)
            gps.move(1.0); 

        // Initially alive
        verify(gps.isDead() == false, __FUNCTION__);

        // Kill it
        gps.kill();

        // Should be dead
        verify(gps.isDead() == true, __FUNCTION__);
    }

    void test_move()
    {
        // Setup
        GPS gps;
        Position initialPos = gps.getPosition();

        // Exercise
        gps.move(1.0);

        // Verify movement
        Position newPos = gps.getPosition();
        verify(newPos.getMetersX() != initialPos.getMetersX(), __FUNCTION__);
        verify(newPos.getMetersY() != initialPos.getMetersY(), __FUNCTION__);
    }

    void test_orbit()
    {
        // Setup
        GPS gps;
        Position initialPos = gps.getPosition();

        // Move for a significant time
        for (int i = 0; i < 60; i++)
            gps.move(1.0);

        // Verify still in orbit (distance from Earth center relatively constant)
        Position finalPos = gps.getPosition();
        double initialRadius = sqrt(pow(initialPos.getMetersX(), 2) + pow(initialPos.getMetersY(), 2));
        double finalRadius = sqrt(pow(finalPos.getMetersX(), 2) + pow(finalPos.getMetersY(), 2));
        verify(std::abs(finalRadius - initialRadius) < initialRadius * 0.01, __FUNCTION__);
    }

    void test_destroyMain()
    {
        // Setup
        GPS gps;
        std::list<Satellite*> satellites;

        // Age the center piece to make it visible
        for (int i = 0; i < 11; i++)
            gps.move(1.0);

        // Exercise
        gps.destroy(satellites);

        // Verify
        verify(gps.isDead() == true, __FUNCTION__);
        verify(satellites.size() == 5, __FUNCTION__);  // 3 pieces + 2 fragments
    }

    void test_destroyCenter()
    {
        // Setup
        GPS parent;
        GPSCenter center(parent);
        std::list<Satellite*> satellites;

        // Age the center piece to make it visible
        for (int i = 0; i < 11; i++)
            center.move(1.0);

        // Exercise
        center.destroy(satellites);

        // Verify
        verify(center.isDead() == true, __FUNCTION__);
        verify(satellites.size() == 3, __FUNCTION__);  // 3 fragments
    }

    void test_destroyLeftArray()
    {
        // Setup
        GPS parent;
        GPSLeftArray array(parent);
        std::list<Satellite*> satellites;

        // Age the center piece to make it visible
        for (int i = 0; i < 11; i++)
            array.move(1.0);

        // Exercise
        array.destroy(satellites);

        // Verify
        verify(array.isDead() == true, __FUNCTION__);
        verify(satellites.size() == 3, __FUNCTION__);  // 3 fragments
    }

    void test_destroyRightArray()
    {
        // Setup
        GPS parent;
        GPSRightArray array(parent);
        std::list<Satellite*> satellites;

        // Age the center piece to make it visible
        for (int i = 0; i < 11; i++)
            array.move(1.0);

        // Exercise
        array.destroy(satellites);

        // Verify
        verify(array.isDead() == true, __FUNCTION__);
        verify(satellites.size() == 3, __FUNCTION__);  // 3 fragments
    }

    void draw_mainSatellite()
    {
        // Setup
        GPS gps;
        // Age it to make it visible
        for (int i = 0; i < 11; i++)
            gps.move(1.0);
        MockOgstream gout;

        // Exercise
        gps.draw(gout);

        // Verify
        verify(gout.wasMainDrawCalled() == true, __FUNCTION__);
    }

    void draw_centerPiece()
    {
        // Setup
        GPS parent;
        GPSCenter center(parent);
        // Age it to make it visible
        for (int i = 0; i < 11; i++)
            center.move(1.0);
        MockOgstream gout;

        // Exercise
        center.draw(gout);

        // Verify
        verify(gout.wasCenterDrawCalled() == true, __FUNCTION__);
    }

    void draw_leftArray()
    {
        // Setup
        GPS parent;
        GPSLeftArray array(parent);
        // Age it to make it visible
        for (int i = 0; i < 11; i++)
            array.move(1.0);
        MockOgstream gout;

        // Exercise
        array.draw(gout);

        // Verify
        verify(gout.wasLeftDrawCalled() == true, __FUNCTION__);
    }

    void draw_rightArray()
    {
        // Setup
        GPS parent;
        GPSRightArray array(parent);
        // Age it to make it visible
        for (int i = 0; i < 11; i++)
            array.move(1.0);
        MockOgstream gout;

        // Exercise
        array.draw(gout);

        // Verify
        verify(gout.wasRightDrawCalled() == true, __FUNCTION__);
    }
};

