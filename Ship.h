/***********************************************************************
 * Header File:
 *    SHIP
 * Author:
 *    Chris Mijango & Seth Chen
 * Summary:
 *    The ship class
 ************************************************************************/


#pragma once
#include "acceleration.h"
#include "Satellite.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include "Projectile.h"

class TestShip;

class Ship : public Satellite
{

private:
    bool isThrusting;  // Track if engines are firing
    std::list<Satellite*>& satellites; // Reference to satellite list for projectiles

public:
    friend TestShip;

    // constructor
    Ship(std::list<Satellite*>& satellites) :
        Satellite(0, 10.0, 0.0),
        isThrusting(false),
        satellites(satellites)
    {
        pos.setPixelsX(-450.0);
        pos.setPixelsY(450.0);
        velocity.setDX(0.0);
        velocity.setDY(-2000.0);
        angle.setDown();
    }

    void draw(ogstream& gout) override
    {
        if (!isInvisible() && !isDead())
            gout.drawShip(pos, angle.getRadians(), isThrusting);
    }

    void input(const Interface& ui) override;
    

    void move(double time) override
    {
        Satellite::move(48.0);

        // Reset angle change to remove time dilation effect on rotation
        angle.add(-angularVelocity * (48.0 - 1.0));
    }

    void destroy(std::list<Satellite*>& satellites) override
    {
        // lab 12
    }

    bool getDefunct() override { return dead; }
};

class FakeShip : public Satellite
{
public:
    FakeShip() : Satellite(0, 10.0, 0.0)
    {
        pos.setPixelsX(-450.0);
        pos.setPixelsY(450.0);
        velocity.setDX(0.0);
        velocity.setDY(-2000.0);
        angle.setDown();
    }

    void input(bool isRight, bool isLeft, bool isDown, bool isSpace)
    {
        if (isRight)
            this->angle.add(0.1);
        if (isLeft)
            this->angle.add(-0.1);

        if (isDown)
        {
            // Calculate thrust effect based on the direction the ship is pointing
            Acceleration thrust;
            for (int i = 0; i < 48; i++)
            {
                thrust.setDDX(2.0 * sin(angle.getRadians()));
                thrust.setDDY(2.0 * cos(angle.getRadians()));

                // udpate velocity
                // velocity.add(thrust, 1.0);
                velocity.addDX(thrust.getDDX() * 1.0);  // v = v0 + at
                velocity.addDY(thrust.getDDY() * 1.0);

                // Update the position using the current velocity
                // pos.add(thrust, velocity, 48.0);
                pos.addMetersX(velocity.getDX() * 1.0);   // x = x0 + vt
                pos.addMetersY(velocity.getDY() * 1.0);
            }
        }
    }
};

