#pragma once

#include "starlink.h"
#include "unitTest.h"
#include "position.h"
#include "velocity.h"
#include "angle.h"

/*********************************************
 * TEST STARLINK
 * Unit tests for the Starlink class
 *********************************************/
class TestStarlink : public UnitTest
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

        test_destroyMain();
        test_destroyBody();
        test_destroyArray();

        // Drawing tests
        draw_visible();
        draw_invisible();
        draw_dead();

        // Kill tests
        kill_normalOperation();
        kill_tooYoung();

        report("Starlink");
    }

private:
    // Mock ogstream for testing draw calls
    class MockOgstream : public ogstream
    {
    public:
        MockOgstream() : drawCalled(false) {}
        void drawStarlink(const Position& pos, double angle) override
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
        Starlink s;

        // Verify
        verify(s.getAge() == 0, __FUNCTION__);
        verify(s.getRadius() == 6.0, __FUNCTION__);  // Starlink is smaller
        verify(s.isDead() == false, __FUNCTION__);
        verify(std::abs(s.getAngle().getRadians() - 0.0) <= 0.001, __FUNCTION__);
    }

    void constructor_initialPosition()
    {
        // Exercise
        Starlink s;
        Position pos = s.getPosition();

        // Verify - Starlink's much lower orbit
        verify(std::abs(pos.getMetersX() - 0.0) <= 0.001, __FUNCTION__);
        verify(std::abs(pos.getMetersY() - -13020000.0) <= 0.001, __FUNCTION__);

    }

    void constructor_initialVelocity()
    {
        // Exercise
        Starlink s;

        // Verify - using friend access to test internal velocity
        verify(std::abs(s.velocity.getDX() - (5800.0)) <= 0.001, __FUNCTION__);
        verify(std::abs(s.velocity.getDY() - 0.0) <= 0.001, __FUNCTION__);
    }

    void constructor_initialRotation()
    {
        // Exercise
        Starlink s;

        // Verify - Starlink has small constant rotation
        verify(std::abs(s.angularVelocity - 0.0002) <= 0.0001, __FUNCTION__);
    }

    void constructor_otherAttributes()
    {
        // Exercise
        Starlink s;

        // Verify other attributes
        verify(s.isDead() == false, __FUNCTION__);
        verify(s.isInvisible() == true, __FUNCTION__);
        verify(s.getRadius() == 6.0, __FUNCTION__);
    }

    void test_isInvisible()
    {
        // Setup
        Starlink s;

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
        Starlink s;

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
        Starlink s;
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
        Starlink s;
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
        Starlink s;
        double initialAngle = s.getAngle().getRadians();

        // Exercise
        s.move(1.0);

        // Verify rotation (Starlink has constant rotation)
        verify(s.getAngle().getRadians() != initialAngle, __FUNCTION__);
    }

    void move_timeDilation()
    {
        // Setup
        Starlink s;
        Position pos1 = s.getPosition();

        // Exercise - move with and without time dilation
        Starlink s2;
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

    void test_destroyMain()
    {
        Starlink starlink;
        std::list<Satellite*> satellites;

        for (int i = 0; i < 11; i++)
            starlink.move(1.0);

        starlink.destroy(satellites);

        verify(starlink.isDead() == true, __FUNCTION__);
        verify(satellites.size() == 4, __FUNCTION__);  // 2 pieces + 2 fragments
    }

    void test_destroyBody()
    {
        Starlink parent;
        StarlinkBody body(parent);
        std::list<Satellite*> satellites;

        for (int i = 0; i < 11; i++)
            body.move(1.0);

        body.destroy(satellites);

        verify(body.isDead() == true, __FUNCTION__);
        verify(satellites.size() == 3, __FUNCTION__);  // 3 fragments
    }

    void test_destroyArray()
    {
        Starlink parent;
        StarlinkArray array(parent);
        std::list<Satellite*> satellites;

        for (int i = 0; i < 11; i++)
            array.move(1.0);

        array.destroy(satellites);

        verify(array.isDead() == true, __FUNCTION__);
        verify(satellites.size() == 3, __FUNCTION__);  // 3 fragments
    }
    void draw_visible()
    {
        // Setup
        Starlink s;
        // Make the Starlink visible by aging it
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
        Starlink s;
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
        Starlink s;
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
        Starlink s;
        s.age = 20;  // Make it mature

        // Exercise
        s.kill();

        // Verify
        verify(s.isDead() == true, __FUNCTION__);
    }

    void kill_tooYoung()
    {
        // Setup
        Starlink s;
        s.age = 5;  // Make it young

        // Exercise
        s.kill();

        // Verify
        verify(s.isDead() == false, __FUNCTION__);
    }
};

