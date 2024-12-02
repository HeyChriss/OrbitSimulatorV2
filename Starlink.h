#pragma once
#include "satellite.h"
#include "velocity.h"
#include "uiDraw.h"
#include "part.h"
#include "Fragment.h"

class TestStarlink;

/*********************************************
* STARLINK BODY
* Body component of a destroyed Starlink satellite
*********************************************/
class StarlinkBody : public Part
{
public:
    StarlinkBody(const Satellite& parent) : Part(2.0, 0.0, parent) {}

    void draw(ogstream& gout) override
    {
        if (!isInvisible() && !isDead())
            gout.drawStarlinkBody(pos, angle.getRadians());
    }

    void destroy(std::list<Satellite*>& satellites) override
    {
        if (!isInvisible() && !isDead())
        {
            // Create 3 fragments
            for (int i = 0; i < 3; i++)
            {
                Angle angle;
                angle.setDegrees(random(0.0, 360.0));
                satellites.push_back(new Fragment(*this, angle));
            }
            kill();
        }
    }
};

/*********************************************
* STARLINK ARRAY
* Solar array component of a destroyed Starlink satellite
*********************************************/
class StarlinkArray : public Part
{
public:
    StarlinkArray(const Satellite& parent) : Part(4.0, 0.0, parent) {}

    void draw(ogstream& gout) override
    {
        if (!isInvisible() && !isDead())
            gout.drawStarlinkArray(pos, angle.getRadians());
    }

    void destroy(std::list<Satellite*>& satellites) override
    {
        if (!isInvisible() && !isDead())
        {
            // Create 3 fragments
            for (int i = 0; i < 3; i++)
            {
                Angle angle;
                angle.setDegrees(random(0.0, 360.0));
                satellites.push_back(new Fragment(*this, angle));
            }
            kill();
        }
    }
};


/*********************************************
 * STARLINK
 * A Starlink satellite in low Earth orbit
 *********************************************/
class Starlink : public Satellite
{
public:
    friend TestStarlink;
    Starlink() : Satellite(0, 6.0, 0.0002)  // age=0, radius=6.0, angularVelocity=0.0002
    {
        // Initial position at lower orbit (low Earth orbit, ~550km altitude)
        pos.setMetersX(0.0);
        pos.setMetersY(-13020000.0);  // Earth radius (6378km) + 550km altitude

        // Initial velocity for circular orbit (faster due to lower orbit)
        velocity.setDX(5800.0);  // m/s
        velocity.setDY(0.0);      // m/s

        timeDilation = 48.0; // Same time dilation as other satellites for consistency
    }

    virtual void move(double time) override
    {
        // Scale time by dilation factor for orbital motion
        Satellite::move(time * timeDilation);

        // Reset angle change to remove time dilation effect on rotation
        angle.add(-angularVelocity * (timeDilation - 1.0));
    }

    void destroy(std::list<Satellite*>& satellites) override {
        if (!isInvisible() && !isDead())
        {
            // Create component parts
            satellites.push_back(new StarlinkBody(*this));
            satellites.push_back(new StarlinkArray(*this));

            // Create fragments
            for (int i = 0; i < 2; i++)
            {
                Angle angle;
                angle.setDegrees(random(0.0, 360.0));
                satellites.push_back(new Fragment(*this, angle));
            }
            kill();
        }
    }

    // Draw the Starlink satellite
    virtual void draw(ogstream& gout) override
    {
        if (!isInvisible() && !isDead())
            gout.drawStarlink(pos, angle.getRadians());
    }

private:
    double timeDilation;  // Time scaling factor for this satellite
};

