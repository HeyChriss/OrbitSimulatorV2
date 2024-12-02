#pragma once
#include "fragment.h"
#include "unitTest.h"
#include <set>

class TestFragment : public UnitTest
{
public:
    void run()
    {
        constructor_withParent();
        test_movement();
        test_drawing();
        test_lifespan();    
        test_expiration();  
        test_angle_initialization();
        test_angle_rotation();
        test_random_angle();


        report("Fragment");
    }

private:
    // Mock ogstream for testing draw calls
    class MockOgstream : public ogstream
    {
        friend class TestFragment;
    public:
        MockOgstream() : drawCalled(false) {}
        void drawFragment(const Position& pos, double rotation) override
        {
            drawCalled = true;
        }
        bool wasDrawCalled() const { return drawCalled; }
    private:
        bool drawCalled;
    };

    void constructor_withParent()
    {
        // Setup
        Satellite parent;
        parent.pos.x = 100.0;
        parent.pos.y = 200.0;
        Angle direction;
        direction.setDegrees(45.0);

        // Exercise
        Fragment fragment(parent, direction);

        // Verify
        verify(fragment.pos.x != parent.pos.x, __FUNCTION__); // Position should be offset
        verify(fragment.pos.y != parent.pos.y, __FUNCTION__);
        assertEquals(fragment.age, 0);
        assertEquals(fragment.radius, 4.0);  // All fragments have same radius
    }

    void test_movement()
    {
        // Setup
        Satellite parent;
        parent.pos.x = 0.0;
        parent.pos.y = 6378000.0 + 100000.0;
        Angle direction;
        direction.setDegrees(45.0);
        Fragment fragment(parent, direction);
        Position initialPos = fragment.pos;

        // Exercise
        fragment.move(1.0);

        // Verify
        double dx = fragment.pos.x - initialPos.x;
        double dy = fragment.pos.y - initialPos.y;
        double dist = sqrt(dx * dx + dy * dy);
        verify(dist > 0.1, __FUNCTION__);
        assertEquals(fragment.age, 1);
    }

    void test_drawing()
    {
        // Setup
        Satellite parent;
        Angle direction;
        Fragment fragment(parent, direction);

        // Age it past invisible phase
        for (int i = 0; i < 11; i++)
            fragment.move(1.0);

        MockOgstream gout;

        // Exercise
        fragment.draw(gout);

        // Verify
        verify(gout.wasDrawCalled(), __FUNCTION__);
    }

void test_lifespan()
{
    // Setup
    Satellite parent;
    Angle direction;
    Fragment fragment(parent, direction);

    // Verify initial lifespan is in range
    verify(fragment.lifetime >= 50 && fragment.lifetime <= 100, __FUNCTION__);

    // Age the fragment and check that lifespan decreases correctly
    int initialLifetime = fragment.lifetime;
    fragment.move(1.0);
    verify(fragment.lifetime == initialLifetime - 1, __FUNCTION__);
}

void test_expiration()
{
    // Setup
    Satellite parent;
    Angle direction;
    Fragment fragment(parent, direction);

    // Capture initial lifetime for debugging
    int lifespan = fragment.lifetime;

    // Simulate lifetime expiration
    for (int i = 0; i <= lifespan; i++) // Run for lifetime + 1 to ensure expiration
    {
        fragment.move(1.0);
    }

    // Verify fragment is marked as dead after expiration
    verify(fragment.isDead(), __FUNCTION__);
}

void test_angle_initialization()
{
    // Setup
    Satellite parent;
    parent.angle.setDegrees(0); // Parent starts with an angle of 0 degrees
    Angle direction;
    direction.setDegrees(45); // Fragment is created at a 45-degree angle

    // Exercise
    Fragment fragment(parent, direction);

    // Verify
    verify(fragment.getAngle().getDegrees() == 0, __FUNCTION__); // Fragment's angle matches parent's angle
}

void test_angle_rotation()
{
    // Setup
    Satellite parent;
    Angle direction;
    direction.setDegrees(0); // Fragment starts with an angle of 0 degrees
    Fragment fragment(parent, direction);

    // Simulate multiple movements
    double initialAngle = fragment.getAngle().getDegrees();
    for (int i = 0; i < 10; i++)
    {
        fragment.move(1.0); // Move the fragment
    }

    // Verify that the angle has changed due to angular velocity
    double finalAngle = fragment.getAngle().getDegrees();
    verify(finalAngle != initialAngle, __FUNCTION__); // Angle should have changed
}

void test_random_angle()
{
    // Setup
    Satellite parent;
    Angle randomAngles[10]; // Store angles to check randomness
    Fragment* fragments[10];

    // Create multiple fragments with unique angles
    std::set<double> uniqueAngles;
    for (int i = 0; i < 10; i++)
    {
        double angle;
        do
        {
            angle = random(0.0, 360.0);
        } while (uniqueAngles.find(angle) != uniqueAngles.end());
        uniqueAngles.insert(angle);

        randomAngles[i].setDegrees(angle);
        fragments[i] = new Fragment(parent, randomAngles[i]);
    }

    // Verify that all angles are unique
    verify(uniqueAngles.size() == 10, __FUNCTION__);

    // Cleanup
    for (int i = 0; i < 10; i++)
    {
        delete fragments[i];
    }
}


};

