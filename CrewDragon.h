#pragma once
#include "satellite.h"
#include "velocity.h"
#include "uiDraw.h"

class TestCrewDragon;

// Components
class CrewDragonCenter : public Satellite {
public:
    CrewDragonCenter(const Satellite& parent) : Satellite(0, 6.0, 0.0) {
        pos = parent.getPosition();
        velocity = Velocity();
        timeDilation = 48.0;
    }

    void destroy(std::list<Satellite*>& satellites) override {
        if (!isInvisible() && !isDead()) {
            for (int i = 0; i < 4; i++) {
                Angle angle;
                angle.setDegrees(random(0.0, 360.0));
                satellites.push_back(new Satellite(*this, angle));
            }
            kill();
        }
    }

    void draw(ogstream& gout) override {
        if (!isInvisible() && !isDead())
            gout.drawCrewDragonCenter(pos, angle.getRadians());
    }

private:
    double timeDilation;
};

class CrewDragonLeft : public Satellite {
public:
    CrewDragonLeft(const Satellite& parent) : Satellite(0, 6.0, 0.0) {
        pos = parent.getPosition();
        velocity = Velocity();
        timeDilation = 48.0;
    }

    void destroy(std::list<Satellite*>& satellites) override {
        if (!isInvisible() && !isDead()) {
            for (int i = 0; i < 2; i++) {
                Angle angle;
                angle.setDegrees(random(0.0, 360.0));
                satellites.push_back(new Satellite(*this, angle));
            }
            kill();
        }
    }

    void draw(ogstream& gout) override {
        if (!isInvisible() && !isDead())
            gout.drawCrewDragonLeft(pos, angle.getRadians());
    }

private:
    double timeDilation;
};

class CrewDragonRight : public Satellite {
public:
    CrewDragonRight(const Satellite& parent) : Satellite(0, 6.0, 0.0) {
        pos = parent.getPosition();
        velocity = Velocity();
        timeDilation = 48.0;
    }

    void destroy(std::list<Satellite*>& satellites) override {
        if (!isInvisible() && !isDead()) {
            for (int i = 0; i < 2; i++) {
                Angle angle;
                angle.setDegrees(random(0.0, 360.0));
                satellites.push_back(new Satellite(*this, angle));
            }
            kill();
        }
    }

    void draw(ogstream& gout) override {
        if (!isInvisible() && !isDead())
            gout.drawCrewDragonRight(pos, angle.getRadians());
    }

private:
    double timeDilation;
};



/*********************************************
 * CREW DRAGON
 * SpaceX Crew Dragon spacecraft in low Earth orbit
 *********************************************/
class CrewDragon : public Satellite
{
public:
    friend TestCrewDragon;
    CrewDragon() : Satellite(0, 7.0, 0.0)  // age=0, radius=8.0 (larger than other satellites), no rotation
    {
        // Initial position at ISS-like orbit (~400km altitude)
        pos.setMetersX(0.0);
        pos.setMetersY(8000000.0);  // 

        // Initial velocity for circular orbit at ISS altitude
        velocity.setDX(-7900.0);  // m/s - slightly faster than Starlink due to lower orbit
        velocity.setDY(0.0);      // m/s

        timeDilation = 48.0; // Same time dilation as other satellites
    }

    virtual void move(double time) override
    {
        // Scale time by dilation factor for orbital motion
        Satellite::move(time * timeDilation);

        // Reset angle change to remove time dilation effect on rotation
        angle.add(-angularVelocity * (timeDilation - 1.0));
    }

    void destroy(std::list<Satellite*>& satellites) override {
        if (!isInvisible() && !isDead()) {
            satellites.push_back(new CrewDragonCenter(*this));
            satellites.push_back(new CrewDragonLeft(*this));
            satellites.push_back(new CrewDragonRight(*this));

            // Add 2 fragments
            for (int i = 0; i < 2; i++) {
                Angle angle;
                angle.setDegrees(random(0.0, 360.0));
                satellites.push_back(new Satellite(*this, angle));
            }
            kill();
        }
    }

    // Draw the Crew Dragon spacecraft
    virtual void draw(ogstream& gout) override
    {
        if (!isInvisible() && !isDead())
            gout.drawCrewDragon(pos, angle.getRadians());
    }

private:
    double timeDilation;  // Time scaling factor for this satellite
};

