#pragma once
#include "satellite.h"
#include "velocity.h"
#include "part.h"
#include "uiDraw.h"
#include <vector>
#include "Fragment.h"

class TestGPS;

/*********************************************
* GPS CENTER
* Center component of a destroyed GPS satellite
*********************************************/
class GPSCenter : public Part
{
public:
    GPSCenter(const Satellite& parent) : Part(7.0, 0.001, parent) {}

    virtual void draw(ogstream& gout) override
    {
        if (!isInvisible() && !isDead())
            gout.drawGPSCenter(pos, angle.getRadians());
    }

    virtual void destroy(std::list<Satellite*>& satellites) override
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
* GPS LEFT ARRAY
* Left solar array of a destroyed GPS satellite
*********************************************/
class GPSLeftArray : public Part
{
public:
    GPSLeftArray(const Satellite& parent) : Part(8.0, 0.001, parent) {}

    virtual void draw(ogstream& gout) override
    {
        if (!isInvisible() && !isDead())
        {
            Position offset;
            offset.setPixelsX(0.0);
            offset.setPixelsY(-12.0);
            gout.drawGPSLeft(pos, angle.getRadians(), offset);
        }
    }

    virtual void destroy(std::list<Satellite*>& satellites) override
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
* GPS RIGHT ARRAY
* Right solar array of a destroyed GPS satellite
*********************************************/
class GPSRightArray : public Part
{
public:
    GPSRightArray(const Satellite& parent) : Part(8.0, 0.001, parent) {}

    virtual void draw(ogstream& gout) override
    {
        if (!isInvisible() && !isDead())
        {
            Position offset;
            offset.setPixelsX(0.0);
            offset.setPixelsY(12.0);
            gout.drawGPSRight(pos, angle.getRadians(), offset);
        }
    }

    virtual void destroy(std::list<Satellite*>& satellites) override
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
* GPS
* GPS satellite in medium Earth orbit
*********************************************/
class GPS : public Satellite
{
public:
    friend TestGPS;

    GPS(const Position& pos, const Velocity& vel) :
        Satellite(0, 12.0, 0.001)
    {
        this->pos = pos;
        this->velocity = vel;
        timeDilation = 48.0;
    }

    GPS() : GPS(
        Position(0.0, 26560000.0),
        Velocity(-3880.0, 0.0)
    ) {}

    static std::vector<std::pair<Position, Velocity>> getInitialPositions()
    {
        return {
            {Position(0.0, 26560000.0), Velocity(-3880.0, 0.0)},
            {Position(23001634.72, 13280000.0), Velocity(-1940.00, 3360.18)},
            {Position(23001634.72, -13280000.0), Velocity(1940.00, 3360.18)},
            {Position(0.0, -26560000.0), Velocity(3880.0, 0.0)},
            {Position(-23001634.72, -13280000.0), Velocity(1940.00, -3360.18)},
            {Position(-23001634.72, 13280000.0), Velocity(-1940.00, -3360.18)}
        };
    }

    virtual void destroy(std::list<Satellite*>& satellites) override
    {
        if (!isInvisible() && !isDead())
        {
            satellites.push_back(new GPSCenter(*this));
            satellites.push_back(new GPSLeftArray(*this));
            satellites.push_back(new GPSRightArray(*this));

            // Create fragments
            for (int i = 0; i < 2; i++)
            {
                Angle fragmentAngle;
                fragmentAngle.setDegrees(random(0.0, 360.0));
                satellites.push_back(new Fragment(*this, fragmentAngle));
            }
            kill();
        }
    }

    virtual void move(double time) override
    {
        Satellite::move(time * timeDilation);
        angle.add(-angularVelocity * (timeDilation - 1.0));
    }

    virtual void draw(ogstream& gout) override
    {
        if (!isInvisible() && !isDead())
            gout.drawGPS(pos, angle.getRadians());
    }

protected:
    void createFragments(std::list<Satellite*>& satellites, int count)
    {
        for (int i = 0; i < count; i++)
        {
            Angle fragmentAngle;
            fragmentAngle.setDegrees(random(0.0, 360.0));
            satellites.push_back(new Satellite(*this, fragmentAngle));
        }
    }

private:
    double timeDilation;
};