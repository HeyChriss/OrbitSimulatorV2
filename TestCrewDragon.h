#pragma once

#include "crewDragon.h"
#include "unitTest.h"
#include "position.h"
#include "velocity.h"
#include "angle.h"

/*********************************************
 * TEST CREW DRAGON
 * Unit tests for the CrewDragon class
 *********************************************/
class TestCrewDragon : public UnitTest
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
        move_noRotation();
        move_timeDilation();

        // Destruction tests
        test_destroyMain();
        test_destroyCenter();
        test_destroyLeft();
        test_destroyRight();


        // Drawing tests
        draw_visible();
        draw_invisible();
        draw_dead();

        // Kill tests
        kill_normalOperation();
        kill_tooYoung();

        report("CrewDragon");
    }

private:
    // Mock ogstream for testing draw calls
    class MockOgstream : public ogstream
    {
    public:
        MockOgstream() : drawCalled(false) {}
        void drawCrewDragon(const Position& pos, double angle) override
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
        CrewDragon cd;

        // Verify
        verify(cd.getAge() == 0, __FUNCTION__);
        verify(cd.getRadius() == 7.0, __FUNCTION__);  // Crew Dragon is larger
        verify(cd.isDead() == false, __FUNCTION__);
        verify(std::abs(cd.getAngle().getRadians() - 0.0) <= 0.001, __FUNCTION__);
    }

    void constructor_initialPosition()
    {
        // Exercise
        CrewDragon cd;
        Position pos = cd.getPosition();

        // Verify - ISS orbit altitude
        verify(std::abs(pos.getMetersX() - 0.0) <= 0.001, __FUNCTION__);
        verify(std::abs(pos.getMetersY() - 8000000.0) <= 0.001, __FUNCTION__);
    }

    void constructor_initialVelocity()
    {
        // Exercise
        CrewDragon cd;

        // Verify - using friend access to test internal velocity
        verify(std::abs(cd.velocity.getDX() - (-7900.0)) <= 0.001, __FUNCTION__);
        verify(std::abs(cd.velocity.getDY() - 0.0) <= 0.001, __FUNCTION__);
    }

    void constructor_initialRotation()
    {
        // Exercise
        CrewDragon cd;

        // Verify - Crew Dragon has no rotation
        verify(std::abs(cd.angularVelocity - 0.0) <= 0.0001, __FUNCTION__);
    }

    void constructor_otherAttributes()
    {
        // Exercise
        CrewDragon cd;

        // Verify other attributes
        verify(cd.isDead() == false, __FUNCTION__);
        verify(cd.isInvisible() == true, __FUNCTION__);
        verify(cd.getRadius() == 7.0, __FUNCTION__);
    }

    void test_isInvisible()
    {
        // Setup
        CrewDragon cd;

        // Initially should be invisible (age = 0)
        verify(cd.isInvisible() == true, __FUNCTION__);

        // Move for 11 seconds
        for (int i = 0; i < 11; i++)
            cd.move(1.0);

        // Should now be visible (age > 10)
        verify(cd.isInvisible() == false, __FUNCTION__);
    }

    void test_isDead()
    {
        // Setup
        CrewDragon cd;

        // Initially alive
        verify(cd.isDead() == false, __FUNCTION__);

        // Move past invisible phase
        for (int i = 0; i < 11; i++)
            cd.move(1.0);

        // Kill it
        cd.kill();

        // Should now be dead
        verify(cd.isDead() == true, __FUNCTION__);
    }

    void move_oneSecond()
    {
        // Setup
        CrewDragon cd;
        Position initialPos = cd.getPosition();

        // Exercise
        cd.move(1.0);

        // Verify position has changed
        Position newPos = cd.getPosition();
        verify(newPos.getMetersX() != initialPos.getMetersX(), __FUNCTION__);
        verify(newPos.getMetersY() != initialPos.getMetersY(), __FUNCTION__);
        verify(cd.getAge() == 1, __FUNCTION__);
    }

    void move_tenSeconds()
    {
        // Setup
        CrewDragon cd;
        Position initialPos = cd.getPosition();

        // Exercise
        for (int i = 0; i < 10; i++)
            cd.move(1.0);

        // Verify significant movement
        Position newPos = cd.getPosition();
        verify(newPos.getMetersX() != initialPos.getMetersX(), __FUNCTION__);
        verify(newPos.getMetersY() != initialPos.getMetersY(), __FUNCTION__);
        verify(cd.getAge() == 10, __FUNCTION__);
    }

    void move_noRotation()
    {
        // Setup
        CrewDragon cd;
        double initialAngle = cd.getAngle().getRadians();

        // Exercise
        cd.move(1.0);

        // Verify no rotation
        verify(std::abs(cd.getAngle().getRadians() - initialAngle) < 0.001, __FUNCTION__);
    }

    void move_timeDilation()
    {
        // Setup
        CrewDragon cd;
        Position pos1 = cd.getPosition();

        // Exercise - move with and without time dilation
        CrewDragon cd2;
        cd2.timeDilation = 1.0;  // No dilation

        cd.move(1.0);
        cd2.move(1.0);

        // Verify different distances traveled
        Position pos2 = cd.getPosition();
        Position pos3 = cd2.getPosition();

        double dist1 = sqrt(pow(pos2.getMetersX() - pos1.getMetersX(), 2) +
            pow(pos2.getMetersY() - pos1.getMetersY(), 2));
        double dist2 = sqrt(pow(pos3.getMetersX() - pos1.getMetersX(), 2) +
            pow(pos3.getMetersY() - pos1.getMetersY(), 2));

        verify(dist1 > dist2, __FUNCTION__);
    }

    void test_destroyMain()
    {
        CrewDragon dragon;
        std::list<Satellite*> satellites;

        for (int i = 0; i < 11; i++)
            dragon.move(1.0);

        dragon.destroy(satellites);

        verify(dragon.isDead() == true, __FUNCTION__);
        verify(satellites.size() == 5, __FUNCTION__);  // 3 pieces + 2 fragments
    }

    void test_destroyCenter()
    {
        CrewDragon parent;
        CrewDragonCenter center(parent);
        std::list<Satellite*> satellites;

        for (int i = 0; i < 11; i++)
            center.move(1.0);

        center.destroy(satellites);

        verify(center.isDead() == true, __FUNCTION__);
        verify(satellites.size() == 4, __FUNCTION__);  // 4 fragments
    }

    void test_destroyLeft()
    {
        CrewDragon parent;
        CrewDragonLeft array(parent);
        std::list<Satellite*> satellites;

        for (int i = 0; i < 11; i++)
            array.move(1.0);

        array.destroy(satellites);

        verify(array.isDead() == true, __FUNCTION__);
        verify(satellites.size() == 2, __FUNCTION__);  // 2 fragments
    }

    void test_destroyRight()
    {
        CrewDragon parent;
        CrewDragonRight array(parent);
        std::list<Satellite*> satellites;

        for (int i = 0; i < 11; i++)
            array.move(1.0);

        array.destroy(satellites);

        verify(array.isDead() == true, __FUNCTION__);
        verify(satellites.size() == 2, __FUNCTION__);  // 2 fragments
    }


    void draw_visible()
    {
        // Setup
        CrewDragon cd;
        // Make the Crew Dragon visible by aging it
        for (int i = 0; i < 11; i++)
            cd.move(1.0);

        MockOgstream gout;

        // Exercise
        cd.draw(gout);

        // Verify
        verify(gout.wasDrawCalled() == true, __FUNCTION__);
    }

    void draw_invisible()
    {
        // Setup
        CrewDragon cd;
        cd.age = 5;  // Make it young
        MockOgstream gout;

        // Exercise
        cd.draw(gout);

        // Verify
        verify(gout.wasDrawCalled() == false, __FUNCTION__);
    }

    void draw_dead()
    {
        // Setup
        CrewDragon cd;
        cd.kill();
        MockOgstream gout;

        // Exercise
        cd.draw(gout);

        // Verify
        verify(gout.wasDrawCalled() == false, __FUNCTION__);
    }

    void kill_normalOperation()
    {
        // Setup
        CrewDragon cd;
        cd.age = 20;  // Make it mature

        // Exercise
        cd.kill();

        // Verify
        verify(cd.isDead() == true, __FUNCTION__);
    }

    void kill_tooYoung()
    {
        // Setup
        CrewDragon cd;
        cd.age = 5;  // Make it young

        // Exercise
        cd.kill();

        // Verify
        verify(cd.isDead() == false, __FUNCTION__);
    }
};

