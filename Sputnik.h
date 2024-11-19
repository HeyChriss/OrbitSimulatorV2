#pragma once
#include "satellite.h"
#include "velocity.h"
#include "uiDraw.h"

/*********************************************
 * SPUTNIK
 * The first artificial satellite in space
 *********************************************/
class Sputnik : public Satellite
{
public:
    Sputnik() : Satellite(0, 4.0, 0.1)  // age=0, radius=4.0, angularVelocity=0.1
    {
        // Initial position at 42164000 meters (like in the prototype)
        pos.setMetersX(0.0);
        pos.setMetersY(42164000.0);  // Geostationary orbit altitude

        // Initial velocity for circular orbit (like in the prototype)
        velocity.setDX(3100.0);  // m/s
        velocity.setDY(0.0);      // m/s
    }

    // Draw the Sputnik satellite
    virtual void draw(ogstream& gout) override
    {
        if (!isInvisible() && !isDead())
            gout.drawSputnik(pos, angle.getRadians());
    }


};


#pragma once
#include "satellite.h"
#include "velocity.h"
#include "uiDraw.h"

/*********************************************
 * SPUTNIK
 * The first artificial satellite in space
 *********************************************/
class Sputnik : public Satellite
{
public:
    Sputnik() : Satellite(0, 4.0, 0.1)  // age=0, radius=4.0, angularVelocity=0.1
    {
        // Constants
        const double EARTH_RADIUS = 6378000.0;  // meters
        const double GEO_POSITION = 42164000.0; // meters, like in prototype

        // Initial position - Start at GEO altitude
        pos.setMeters(0.0, GEO_POSITION);  // Place at the equator like prototype

        // Initial velocity for GEO - matching prototype values
        velocity.setDX(-3100.0);  // m/s just like prototype
        velocity.setDY(0.0);      // m/s

        // Time settings (for move() if needed)
        const double HOURS_PER_DAY = 24.0;
        const double MINUTES_PER_HOUR = 60.0;
        timeDilation = HOURS_PER_DAY * MINUTES_PER_HOUR;  // 1440
        timePerFrame = timeDilation / 30.0;  // 30 is the frameRate
    }

    virtual void draw(ogstream& gout) override
    {
        if (!isInvisible() && !isDead())
        {
            // Calculate angle for satellite display like in prototype
            double angleShip = atan2(velocity.getDY(), velocity.getDX());
            gout.drawSputnik(pos, angleShip);
        }
    }

private:
    double timeDilation;
    double timePerFrame;
};



