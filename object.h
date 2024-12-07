
/***********************************************************************
 * Header File:
 *    Object
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about Object
 ************************************************************************/
#pragma once
#include "position.h"
#include "velocity.h"
#include "angle.h"
#include "uiDraw.h"
#include "physics.h"


#ifndef C_ASSERT
#define C_ASSERT
#include <cassert>
#endif      

using namespace std;

class Object
{
public:
    friend class TestHubble;
    friend class TestShip;
    friend class TestObject;
    friend class TestProjectile;

    Object(Position pos = Position(), Velocity vel = Velocity(), Angle rotation = Angle())
    {
        this->pos = pos;
        this->vel = vel;
        this->rotationAngle = rotation;
    };

    virtual void update(double time, double gravity, double planetRadius);
    void setPosition(Position newPos) { this->pos = newPos; };
    Position getPosition()    const { return pos; }
    void setVelocity(Velocity newVel) { this->vel = newVel; };
    Velocity getVelocity()    const { return vel; }
    void addVelocity(Velocity v) { this->vel += v; };
    void addVelocity(double velX, double velY) { this->vel.addMetersX(velX); this->vel.addMetersY(velY); };
    void addRotation(Angle change) { rotationAngle += change; };
    Angle getRotation()     const { return this->rotationAngle; }
    virtual void draw() {};

protected:
    Position pos;
    Velocity vel;
    Angle rotationAngle;
    ogstream ogs;
    Physics physics;
};

