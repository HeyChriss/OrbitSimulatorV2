#pragma once

#include "hubble.h"
#include "unitTest.h"
#include "position.h"
#include "velocity.h"
#include "angle.h"

/*********************************************
 * TEST HUBBLE
 * Unit tests for the Hubble class
 *********************************************/
class TestHubble : public UnitTest
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

        // Destruction tests
        test_destroyMain();
        test_destroyTelescope();
        test_destroyComputer();
        test_destroyLeftArray();
        test_destroyRightArray();


        // Drawing tests
        draw_visible();
        draw_invisible();
        draw_dead();

        // Kill tests
        kill_normalOperation();
        kill_tooYoung();

        report("Hubble");
    }

private:
    // Mock ogstream for testing draw calls
    class MockOgstream : public ogstream
    {
    public:
        MockOgstream() : drawCalled(false) {}
        void drawHubble(const Position& pos, double angle) override
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
        Hubble h;

        // Verify
        verify(h.getAge() == 0, __FUNCTION__);
        verify(h.getRadius() == 10.0, __FUNCTION__);  // Hubble has different radius than Sputnik
        verify(h.isDead() == false, __FUNCTION__);
        verify(std::abs(h.getAngle().getRadians() - 0.0) <= 0.001, __FUNCTION__);
    }

    void constructor_initialPosition()
    {
        // Exercise
        Hubble h;
        Position pos = h.getPosition();

        // Verify - Hubble's different orbit height
        verify(std::abs(pos.getMetersX() - 0.0) <= 0.001, __FUNCTION__);
        verify(std::abs(pos.getMetersY() - -42164000.0) <= 0.001, __FUNCTION__);
    }

    void constructor_initialVelocity()
    {
        // Exercise
        Hubble h;

        // Verify - using friend access to test internal velocity
        verify(std::abs(h.velocity.getDX() - (3100.0)) <= 0.001, __FUNCTION__);
        verify(std::abs(h.velocity.getDY() - 0.0) <= 0.001, __FUNCTION__);
    }

    void constructor_initialRotation()
    {
        // Exercise
        Hubble h;

        // Verify - Hubble has no initial rotation
        verify(std::abs(h.angularVelocity - 0.0) <= 0.0001, __FUNCTION__);
    }

    void constructor_otherAttributes()
    {
        // Exercise
        Hubble h;

        // Verify other attributes
        verify(h.isDead() == false, __FUNCTION__);
        verify(h.isInvisible() == true, __FUNCTION__);
        verify(h.getRadius() == 10.0, __FUNCTION__);
    }

    void test_isInvisible()
    {
        // Setup
        Hubble h;

        // Initially should be invisible (age = 0)
        verify(h.isInvisible() == true, __FUNCTION__);

        // Move for 11 seconds
        for (int i = 0; i < 11; i++)
            h.move(1.0);

        // Should now be visible (age > 10)
        verify(h.isInvisible() == false, __FUNCTION__);
    }

    void test_isDead()
    {
        // Setup
        Hubble h;

        // Initially alive
        verify(h.isDead() == false, __FUNCTION__);

        // Move past invisible phase
        for (int i = 0; i < 11; i++)
            h.move(1.0);

        // Kill it
        h.kill();

        // Should now be dead
        verify(h.isDead() == true, __FUNCTION__);
    }

    void move_oneSecond()
    {
        // Setup
        Hubble h;
        Position initialPos = h.getPosition();

        // Exercise
        h.move(1.0);

        // Verify position has changed
        Position newPos = h.getPosition();
        verify(newPos.getMetersX() != initialPos.getMetersX(), __FUNCTION__);
        verify(newPos.getMetersY() != initialPos.getMetersY(), __FUNCTION__);
        verify(h.getAge() == 1, __FUNCTION__);
    }

    void move_tenSeconds()
    {
        // Setup
        Hubble h;
        Position initialPos = h.getPosition();

        // Exercise
        for (int i = 0; i < 10; i++)
            h.move(1.0);

        // Verify significant movement
        Position newPos = h.getPosition();
        verify(newPos.getMetersX() != initialPos.getMetersX(), __FUNCTION__);
        verify(newPos.getMetersY() != initialPos.getMetersY(), __FUNCTION__);
        verify(h.getAge() == 10, __FUNCTION__);
    }

    void move_rotation()
    {
        // Setup
        Hubble h;
        double initialAngle = h.getAngle().getRadians();

        // Exercise
        h.move(1.0);

        // Verify minimal rotation (Hubble should maintain stable orientation)
        verify(std::abs(h.getAngle().getRadians() - initialAngle) < 0.001, __FUNCTION__);
    }

    void move_timeDilation()
    {
        // Setup
        Hubble h;
        Position pos1 = h.getPosition();

        // Exercise - move with and without time dilation
        Hubble h2;
        h2.timeDilation = 1.0;  // No dilation

        h.move(1.0);
        h2.move(1.0);

        // Verify different distances traveled
        Position pos2 = h.getPosition();
        Position pos3 = h2.getPosition();

        double dist1 = sqrt(pow(pos2.getMetersX() - pos1.getMetersX(), 2) +
            pow(pos2.getMetersY() - pos1.getMetersY(), 2));
        double dist2 = sqrt(pow(pos3.getMetersX() - pos1.getMetersX(), 2) +
            pow(pos3.getMetersY() - pos1.getMetersY(), 2));

        verify(dist1 > dist2, __FUNCTION__);
    }

    void test_destroyMain()
    {
        // Setup
        Hubble hubble;
        std::list<Satellite*> satellites;

        // Age to make visible
        for (int i = 0; i < 11; i++)
            hubble.move(1.0);

        // Exercise
        hubble.destroy(satellites);

        // Verify
        verify(hubble.isDead() == true, __FUNCTION__);
        verify(satellites.size() == 4, __FUNCTION__);  // All 4 components
    }

    void test_destroyTelescope()
    {
        // Setup
        Hubble parent;
        HubbleTelescope telescope(parent);
        std::list<Satellite*> satellites;

        // Age to make visible  
        for (int i = 0; i < 11; i++)
            telescope.move(1.0);

        // Exercise
        telescope.destroy(satellites);

        // Verify
        verify(telescope.isDead() == true, __FUNCTION__);
        verify(satellites.size() == 3, __FUNCTION__);  // 3 fragments
    }

    void test_destroyComputer()
    {
        // Setup
        Hubble parent;
        HubbleComputer computer(parent);
        std::list<Satellite*> satellites;

        // Age to make visible
        for (int i = 0; i < 11; i++)
            computer.move(1.0);

        // Exercise
        computer.destroy(satellites);

        // Verify
        verify(computer.isDead() == true, __FUNCTION__);
        verify(satellites.size() == 2, __FUNCTION__);  // 2 fragments
    }

    void test_destroyLeftArray()
    {
        // Setup
        Hubble parent;
        HubbleLeftArray array(parent);
        std::list<Satellite*> satellites;

        // Age to make visible
        for (int i = 0; i < 11; i++)
            array.move(1.0);

        // Exercise
        array.destroy(satellites);

        // Verify
        verify(array.isDead() == true, __FUNCTION__);
        verify(satellites.size() == 2, __FUNCTION__);  // 2 fragments
    }

    void test_destroyRightArray()
    {
        // Setup
        Hubble parent;
        HubbleRightArray array(parent);
        std::list<Satellite*> satellites;

        // Age to make visible
        for (int i = 0; i < 11; i++)
            array.move(1.0);

        // Exercise
        array.destroy(satellites);

        // Verify
        verify(array.isDead() == true, __FUNCTION__);
        verify(satellites.size() == 2, __FUNCTION__);  // 2 fragments
    }


    void draw_visible()
    {
        // Setup
        Hubble h;
        // Make the Hubble visible by aging it
        for (int i = 0; i < 11; i++)
            h.move(1.0);

        MockOgstream gout;

        // Exercise
        h.draw(gout);

        // Verify
        verify(gout.wasDrawCalled() == true, __FUNCTION__);
    }

    void draw_invisible()
    {
        // Setup
        Hubble h;
        h.age = 5;  // Make it young
        MockOgstream gout;

        // Exercise
        h.draw(gout);

        // Verify
        verify(gout.wasDrawCalled() == false, __FUNCTION__);
    }

    void draw_dead()
    {
        // Setup
        Hubble h;
        h.kill();
        MockOgstream gout;

        // Exercise
        h.draw(gout);

        // Verify
        verify(gout.wasDrawCalled() == false, __FUNCTION__);
    }

    void kill_normalOperation()
    {
        // Setup
        Hubble h;
        h.age = 20;  // Make it mature

        // Exercise
        h.kill();

        // Verify
        verify(h.isDead() == true, __FUNCTION__);
    }

    void kill_tooYoung()
    {
        // Setup
        Hubble h;
        h.age = 5;  // Make it young

        // Exercise
        h.kill();

        // Verify
        verify(h.isDead() == false, __FUNCTION__);
    }
};
