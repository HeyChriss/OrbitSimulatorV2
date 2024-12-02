#pragma once

#include "part.h"
#include "unitTest.h"
#include "position.h"
#include "velocity.h"
#include "angle.h"

/*********************************************
 * TEST PART
 * Unit tests for the Part base class
 *********************************************/
class TestPart : public UnitTest
{
public:
    void run()
    {
        // Constructor tests
        constructor_fromParent();
        constructor_initialPosition();
        constructor_initialVelocity();
        constructor_radius();
        constructor_rotation();
        constructor_timeDilation();

        // State tests
        test_isInvisible();
        test_isDead();

        // Movement tests
        move_oneSecond();
        move_tenSeconds();
        move_rotation();

        // Fragment tests
        test_createFragments();
        test_createMultipleFragments();

        // Drawing tests
        draw_visible();
        draw_invisible();
        draw_dead();

        report("Part");
    }

private:
    // Forward declare TestPartImpl
    class TestPartImpl;

    // Mock ogstream for testing draw calls
    class MockOgstream : public ogstream
    {
        friend class TestPartImpl;  // Allow TestPartImpl to access private members
    public:
        MockOgstream() : drawCalled(false) {}
        bool wasDrawCalled() const { return drawCalled; }
    private:
        bool drawCalled;
    };

    // Test Part implementation of abstract class for testing
    class TestPartImpl : public Part
    {
    public:
        TestPartImpl(const Satellite& parent) : Part(5.0, 0.1, parent) {}

        void draw(ogstream& gout) override
        {
            if (!isInvisible() && !isDead())
                static_cast<MockOgstream&>(gout).drawCalled = true;  // Now works because of friend declaration
        }

        // Make createFragments public for testing
        void publicCreateFragments(std::list<Satellite*>& satellites, int count)
        {
            createFragments(satellites, count);
        }
    };

    void constructor_fromParent()
    {
        // Setup parent satellite
        Satellite parent;
        parent.pos.setMetersX(100.0);
        parent.pos.setMetersY(200.0);
        parent.velocity.setDX(10.0);
        parent.velocity.setDY(20.0);

        // Exercise
        TestPartImpl part(parent);

        // Verify
        assertEquals(part.getPosition().getMetersX(), 100.0);
        assertEquals(part.getPosition().getMetersY(), 200.0);
        assertEquals(part.velocity.getDX(), 0.0); // Parts start with zero velocity
        assertEquals(part.velocity.getDY(), 0.0);
        assertEquals(part.getRadius(), 5.0);
        assertEquals(part.angularVelocity, 0.1);
    }

    void constructor_initialPosition()
    {
        // Setup
        Satellite parent;
        parent.pos.setMetersX(150.0);
        parent.pos.setMetersY(-250.0);

        // Exercise
        TestPartImpl part(parent);

        // Verify position inherited from parent
        assertEquals(part.getPosition().getMetersX(), 150.0);
        assertEquals(part.getPosition().getMetersY(), -250.0);
    }

    void constructor_initialVelocity()
    {
        // Setup
        Satellite parent;
        parent.velocity.setDX(30.0);
        parent.velocity.setDY(-40.0);

        // Exercise
        TestPartImpl part(parent);

        // Verify initial velocity is zero regardless of parent
        assertEquals(part.velocity.getDX(), 0.0);
        assertEquals(part.velocity.getDY(), 0.0);
    }

    void constructor_radius()
    {
        // Setup
        Satellite parent;

        // Exercise
        TestPartImpl part(parent);

        // Verify
        assertEquals(part.getRadius(), 5.0); // Test implementation uses radius 5.0
    }

    void constructor_rotation()
    {
        // Setup
        Satellite parent;

        // Exercise
        TestPartImpl part(parent);

        // Verify
        assertEquals(part.angularVelocity, 0.1); // Test implementation uses 0.1
        assertEquals(part.getAngle().getRadians(), 0.0);
    }

    void constructor_timeDilation()
    {
        // Setup
        Satellite parent;

        // Exercise
        TestPartImpl part(parent);

        // Verify
        assertEquals(part.timeDilation, 48.0);
    }

    void test_isInvisible()
    {
        // Setup
        Satellite parent;
        TestPartImpl part(parent);

        // Initially invisible
        verify(part.isInvisible() == true, __FUNCTION__);

        // Move for 11 seconds
        for (int i = 0; i < 11; i++)
            part.move(1.0);

        // Should now be visible
        verify(part.isInvisible() == false, __FUNCTION__);
    }

    void test_isDead()
    {
        // Setup
        Satellite parent;
        TestPartImpl part(parent);

        // Initially alive
        verify(part.isDead() == false, __FUNCTION__);

        // Age past invisible phase
        for (int i = 0; i < 11; i++)
            part.move(1.0);

        // Kill it
        part.kill();

        // Should now be dead
        verify(part.isDead() == true, __FUNCTION__);
    }

    void move_oneSecond()
    {
        // Setup
        Satellite parent;  // Create the parent satellite first
        TestPartImpl part(parent);  // Pass the parent to constructor
        part.pos.x = 0.0;
        part.pos.y = 6378000.0 + 100000.0;
        Position initialPos = part.pos;

        // Exercise
        part.move(1.0);

        // Verify - direct attribute access
        double dx = part.pos.x - initialPos.x;
        double dy = part.pos.y - initialPos.y;
        double dist = sqrt(dx * dx + dy * dy);
        verify(dist > 0.1, __FUNCTION__);
        assertEquals(part.age, 1);
    }

    void move_tenSeconds()
    {
        // Setup
        Satellite parent;
        TestPartImpl part(parent);
        part.pos.x = 0.0;
        part.pos.y = 6378000.0 + 100000.0;
        Position initialPos = part.pos;

        // Exercise - single line loop since it's testing one method
        for (int i = 0; i < 10; i++) part.move(1.0);

        // Verify - direct attribute access
        double dx = part.pos.x - initialPos.x;
        double dy = part.pos.y - initialPos.y;
        double dist = sqrt(dx * dx + dy * dy);
        verify(dist > 1.0, __FUNCTION__);
        assertEquals(part.age, 10);
    }

    void move_rotation()
    {
        // Setup
        Satellite parent;
        TestPartImpl part(parent);
        double initialAngle = part.getAngle().getRadians();

        // Exercise
        part.move(1.0);

        // Verify rotation
        verify(part.getAngle().getRadians() != initialAngle, __FUNCTION__);
    }


    void test_createFragments()
    {
        // Setup
        Satellite parent;
        TestPartImpl part(parent);
        std::list<Satellite*> satellites;

        // Exercise
        part.publicCreateFragments(satellites, 1);

        // Verify
        verify(satellites.size() == 1, __FUNCTION__);
    }

    void test_createMultipleFragments()
    {
        // Setup
        Satellite parent;
        TestPartImpl part(parent);
        std::list<Satellite*> satellites;

        // Exercise
        part.publicCreateFragments(satellites, 3);

        // Verify
        verify(satellites.size() == 3, __FUNCTION__);

        // Cleanup - prevent memory leaks
        for (auto sat : satellites)
            delete sat;
    }

    void draw_visible()
    {
        // Setup
        Satellite parent;
        TestPartImpl part(parent);
        // Make it visible by aging it
        for (int i = 0; i < 11; i++)
            part.move(1.0);

        MockOgstream gout;

        // Exercise
        part.draw(gout);

        // Verify
        verify(gout.wasDrawCalled() == true, __FUNCTION__);
    }

    void draw_invisible()
    {
        // Setup
        Satellite parent;
        TestPartImpl part(parent);
        part.age = 5;  // Make it young
        MockOgstream gout;

        // Exercise
        part.draw(gout);

        // Verify
        verify(gout.wasDrawCalled() == false, __FUNCTION__);
    }

    void draw_dead()
    {
        // Setup
        Satellite parent;
        TestPartImpl part(parent);
        part.kill();
        MockOgstream gout;

        // Exercise
        part.draw(gout);

        // Verify
        verify(gout.wasDrawCalled() == false, __FUNCTION__);
    }
};

