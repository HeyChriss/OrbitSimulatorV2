#pragma once
#include "satellite.h"
#include "velocity.h"
#include "uiDraw.h"

class TestSputnik;

/*********************************************
 * SPUTNIK
 * The first artificial satellite in space
 *********************************************/
class Sputnik : public Satellite
{
public:
    friend TestSputnik;
    Sputnik() : Satellite(0, 4.0, 0.001)  // age=0, radius=4.0, angularVelocity=0.1
    {
        // Initial position and velocity for retrograde orbit
        pos.setMetersX(-36515095.13);
        pos.setMetersY(21082000.0);

        velocity.setDX(2050.0);  // m/s
        velocity.setDY(2684.68); // m/s

        timeDilation = 48.0; // Slowed down from 1440 for better visualization
    }

    virtual void move(double time) override
    {
        // Scale time by dilation factor for orbital motion
        Satellite::move(time * timeDilation);

        // Reset angle change to remove time dilation effect on rotation
        angle.add(-angularVelocity * (timeDilation - 1.0));  // Counteract the extra rotation
    }


    // Draw the Sputnik satellite
    virtual void draw(ogstream& gout) override
    {
        if (!isInvisible() && !isDead())
            gout.drawSputnik(pos, angle.getRadians());
    }

    // Draw the Sputnik satellite
    virtual void destroy(std::list<Satellite*>& satellites) override
    {
        if (!isInvisible() && !isDead())
        {
            // Create 4 fragments
            for (int i = 0; i < 4; i++)
            {
                Angle fragmentAngle;
                fragmentAngle.setDegrees(random(0.0, 360.0));
                satellites.push_back(new Satellite(*this, fragmentAngle));
            }
            kill();
        }
    }


private:
    double timeDilation;  // Time scaling factor for this satellite
};






