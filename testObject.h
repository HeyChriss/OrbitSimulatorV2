/***********************************************************************
 * Header File:
 *    Testing Object
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about Testing object
 ************************************************************************/
#ifndef testObject_h
#define testObject_h

#include <iostream>
#include <cassert>
#include "object.h"
#include "unitTest.h"
#include "physics.h"
#include "angle.h"

/*******************************
 * TEST Object
 * A friend class for Object which contains the unit tests
 ********************************/
class TestObject : public UnitTest
{
public:
    void run()
    {
        constructor_default();
        constructor_nonDefault();
        getPosition_default();
        setPosition_basic();
        getVelocity_default();
        setVelocity_basic();
        getRotation_default();
        addRotation_basic();
        addVelocity_velocity();
        addVelocity_components();

        report("Object");
    }

private:
    // Test the default constructor
    void constructor_default()
    {
        // Setup & Exercise
        Object obj;

        // Verify
        assertEquals(obj.pos.getMetersX(), 0.0);
        assertEquals(obj.pos.getMetersY(), 0.0);
        assertEquals(obj.vel.getMetersX(), 0.0);
        assertEquals(obj.vel.getMetersY(), 0.0);
        assertEquals(obj.rotationAngle.getRadian(), 0.0);
    }

    // Test the non-default constructor
    void constructor_nonDefault()
    {
        // Setup
        Position pos(100.0, 200.0);
        Velocity vel(10.0, 20.0);
        Angle angle;
        angle.setDegree(45.0);

        // Exercise
        Object obj(pos, vel, angle);

        // Verify
        assertEquals(obj.getPosition().getMetersX(), 100.0);
        assertEquals(obj.getPosition().getMetersY(), 200.0);
        assertEquals(obj.getVelocity().getMetersX(), 10.0);
        assertEquals(obj.getVelocity().getMetersY(), 20.0);
        assertEquals(obj.getRotation().getDegree(), 45.0);
    }

    // Test getting position for default object
    void getPosition_default()
    {
        // Setup
        Object obj;

        // Exercise
        Position pos = obj.getPosition();

        // Verify
        assertEquals(pos.getMetersX(), 0.0);
        assertEquals(pos.getMetersY(), 0.0);
    }

    // Test setting position
    void setPosition_basic()
    {
        // Setup
        Object obj;
        Position newPos(150.0, -275.0);

        // Exercise
        obj.setPosition(newPos);

        // Verify
        assertEquals(obj.getPosition().getMetersX(), 150.0);
        assertEquals(obj.getPosition().getMetersY(), -275.0);
    }

    // Test getting velocity for default object
    void getVelocity_default()
    {
        // Setup
        Object obj;

        // Exercise
        Velocity vel = obj.getVelocity();

        // Verify
        assertEquals(vel.getMetersX(), 0.0);
        assertEquals(vel.getMetersY(), 0.0);
    }

    // Test setting velocity
    void setVelocity_basic()
    {
        // Setup
        Object obj;
        Velocity newVel(33.0, -44.0);

        // Exercise
        obj.setVelocity(newVel);

        // Verify
        assertEquals(obj.getVelocity().getMetersX(), 33.0);
        assertEquals(obj.getVelocity().getMetersY(), -44.0);
    }

    // Test getting rotation for default object
    void getRotation_default()
    {
        // Setup
        Object obj;

        // Exercise
        Angle rotation = obj.getRotation();

        // Verify
        assertEquals(rotation.getDegree(), 0.0);
    }

    // Test adding rotation
    void addRotation_basic()
    {
        // Setup
        Object obj;
        Angle change;
        change.setDegree(90.0);

        // Exercise
        obj.addRotation(change);

        // Verify
        assertEquals(obj.getRotation().getDegree(), 90.0);
    }

    // Test adding velocity using Velocity object
    void addVelocity_velocity()
    {
        // Setup
        Object obj;
        Velocity v1(10.0, 20.0);
        Velocity v2(5.0, -8.0);

        // Exercise
        obj.addVelocity(v1);
        obj.addVelocity(v2);

        // Verify
        assertEquals(obj.getVelocity().getMetersX(), 15.0);
        assertEquals(obj.getVelocity().getMetersY(), 12.0);
    }

    // Test adding velocity using components
    void addVelocity_components()
    {
        // Setup
        Object obj;

        // Exercise
        obj.addVelocity(3.0, 4.0);
        obj.addVelocity(-1.0, 2.0);

        // Verify
        assertEquals(obj.getVelocity().getMetersX(), 2.0);
        assertEquals(obj.getVelocity().getMetersY(), 6.0);
    }
};

#endif /* testObject_h */

