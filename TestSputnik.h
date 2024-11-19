#pragma once

#include "sputnik.h"
#include "unitTest.h"
#include "position.h"
#include "velocity.h"
#include "angle.h"

/*********************************************
 * TEST SPUTNIK
 * Unit tests for the Sputnik class
 *********************************************/
class TestSputnik : public UnitTest
{
public:
    void run()
    {
        // Constructor tests
        constructor_default();
        constructor_initialPosition();
        constructor_initialVelocity();
        constructor_initialRotation();
        constructor_otherAttributes();

        // State tests
        test_isInvisible();
        test_isDead();

        // Movement tests
        move_oneSecond();
        move_tenSeconds();
        move_rotation();
        move_timeDilation();

        // Drawing tests
        draw_visible();
        draw_invisible();
        draw_dead();

        // Kill tests
        kill_normalOperation();
        kill_tooYoung();

        report("Sputnik");
    }

private:
    // Mock ogstream for testing draw calls
    class MockOgstream : public ogstream
    {
    public:
        MockOgstream() : drawCalled(false) {}
        void drawSputnik(const Position& pos, double angle) override
        {
            drawCalled = true;
        }
        bool wasDrawCalled() const { return drawCalled; }
    private:
        bool drawCalled;
    };

    void constructor_default()
    {
        // Exercise
        Sputnik s;

        // Verify
        verify(s.getAge() == 0, __FUNCTION__);
        verify(s.getRadius() == 4.0, __FUNCTION__);
        verify(s.isDead() == false, __FUNCTION__);
        verify(std::abs(s.getAngle().getRadians() - 0.0) <= 0.001, __FUNCTION__);
    }

    void constructor_initialPosition()
    {
        // Exercise
        Sputnik s;
        Position pos = s.getPosition();

        // Verify
        verify(std::abs(pos.getMetersX() - -36515095.13) <= 0.001, __FUNCTION__);
        verify(std::abs(pos.getMetersY() - 21082000.0) <= 0.001, __FUNCTION__);
    }

    void constructor_initialVelocity()
    {
        // Exercise
        Sputnik s;

        // Verify - using friend access to test internal velocity
        verify(std::abs(s.velocity.getDX() - (2050.0)) <= 0.001, __FUNCTION__);
        verify(std::abs(s.velocity.getDY() - 2684.68) <= 0.001, __FUNCTION__);
    }

    void constructor_initialRotation()
    {
        // Exercise
        Sputnik s;

        // Verify
        verify(std::abs(s.angularVelocity - 0.001) <= 0.0001, __FUNCTION__);
    }

    void constructor_otherAttributes()
    {
        // Exercise
        Sputnik s;

        // Verify other attributes
        verify(s.isDead() == false, __FUNCTION__);
        verify(s.isInvisible() == true, __FUNCTION__);
        verify(s.getRadius() == 4.0, __FUNCTION__);
    }

    void test_isInvisible()
    {
        // Setup
        Sputnik s;

        // Initially should be invisible (age = 0)
        verify(s.isInvisible() == true, __FUNCTION__);

        // Move for 11 seconds
        for (int i = 0; i < 11; i++)
            s.move(1.0);

        // Should now be visible (age > 10)
        verify(s.isInvisible() == false, __FUNCTION__);
    }

    void test_isDead()
    {
        // Setup
        Sputnik s;

        // Initially alive
        verify(s.isDead() == false, __FUNCTION__);

        // Move past invisible phase
        for (int i = 0; i < 11; i++)
            s.move(1.0);

        // Kill it
        s.kill();

        // Should now be dead
        verify(s.isDead() == true, __FUNCTION__);
    }

    void move_oneSecond()
    {
        // Setup
        Sputnik s;
        Position initialPos = s.getPosition();

        // Exercise
        s.move(1.0);

        // Verify position has changed
        Position newPos = s.getPosition();
        verify(newPos.getMetersX() != initialPos.getMetersX(), __FUNCTION__);
        verify(newPos.getMetersY() != initialPos.getMetersY(), __FUNCTION__);
        verify(s.getAge() == 1, __FUNCTION__);
    }

    void move_tenSeconds()
    {
        // Setup
        Sputnik s;
        Position initialPos = s.getPosition();

        // Exercise
        for (int i = 0; i < 10; i++)
            s.move(1.0);

        // Verify significant movement
        Position newPos = s.getPosition();
        verify(newPos.getMetersX() != initialPos.getMetersX(), __FUNCTION__);
        verify(newPos.getMetersY() != initialPos.getMetersY(), __FUNCTION__);
        verify(s.getAge() == 10, __FUNCTION__);
    }

    void move_rotation()
    {
        // Setup
        Sputnik s;
        double initialAngle = s.getAngle().getRadians();

        // Exercise
        s.move(1.0);

        // Verify rotation
        verify(s.getAngle().getRadians() != initialAngle, __FUNCTION__);
    }

    void move_timeDilation()
    {
        // Setup
        Sputnik s;
        Position pos1 = s.getPosition();

        // Exercise - move with and without time dilation
        Sputnik s2;
        s2.timeDilation = 1.0;  // No dilation

        s.move(1.0);
        s2.move(1.0);

        // Verify different distances traveled
        Position pos2 = s.getPosition();
        Position pos3 = s2.getPosition();

        double dist1 = sqrt(pow(pos2.getMetersX() - pos1.getMetersX(), 2) +
            pow(pos2.getMetersY() - pos1.getMetersY(), 2));
        double dist2 = sqrt(pow(pos3.getMetersX() - pos1.getMetersX(), 2) +
            pow(pos3.getMetersY() - pos1.getMetersY(), 2));

        verify(dist1 > dist2, __FUNCTION__);
    }

    void draw_visible()
    {
        // Setup
        Sputnik s;
        // Make the Sputnik visible by aging it
        for (int i = 0; i < 11; i++)
            s.move(1.0);

        MockOgstream gout;

        // Exercise
        s.draw(gout);

        // Verify
        verify(gout.wasDrawCalled() == true, __FUNCTION__);
    }

    void draw_invisible()
    {
        // Setup
        Sputnik s;
        s.age = 5;  // Make it young
        MockOgstream gout;

        // Exercise
        s.draw(gout);

        // Verify
        verify(gout.wasDrawCalled() == false, __FUNCTION__);
    }

    void draw_dead()
    {
        // Setup
        Sputnik s;
        s.kill();
        MockOgstream gout;

        // Exercise
        s.draw(gout);

        // Verify
        verify(gout.wasDrawCalled() == false, __FUNCTION__);
    }

    void kill_normalOperation()
    {
        // Setup
        Sputnik s;
        s.age = 20;  // Make it mature

        // Exercise
        s.kill();

        // Verify
        verify(s.isDead() == true, __FUNCTION__);
    }

    void kill_tooYoung()
    {
        // Setup
        Sputnik s;
        s.age = 5;  // Make it young

        // Exercise
        s.kill();

        // Verify
        verify(s.isDead() == false, __FUNCTION__);
    }
};