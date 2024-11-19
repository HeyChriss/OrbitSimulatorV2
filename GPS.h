#pragma once
#include "satellite.h"
#include "velocity.h"
#include "uiDraw.h"
#include <vector>

class TestGPS;

/*********************************************
* GPS CENTER
* Center component of a destroyed GPS satellite
*********************************************/
class GPSCenter : public Satellite
{
public:
    GPSCenter(const Satellite& parent) :
        Satellite(0, 7.0, 0.001)
    {
        this->pos = parent.getPosition();
        this->velocity = Velocity();
        this->timeDilation = 48.0;
    }

    virtual void move(double time) override
    {
        Satellite::move(time * timeDilation);
        angle.add(-angularVelocity * (timeDilation - 1.0));
    }

    virtual void draw(ogstream& gout) override
    {
        if (!isInvisible() && !isDead())
            gout.drawGPSCenter(pos, angle.getRadians());
    }

    virtual void destroy(std::list<Satellite*>& satellites) override
    {
        if (!isInvisible() && !isDead())
        {
            createFragments(satellites, 3);
            kill();
        }
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

/*********************************************
* GPS LEFT ARRAY
* Left solar array of a destroyed GPS satellite
*********************************************/
class GPSLeftArray : public Satellite
{
public:
    GPSLeftArray(const Satellite& parent) :
        Satellite(0, 8.0, 0.001)
    {
        this->pos = parent.getPosition();
        this->velocity = Velocity();
        this->timeDilation = 48.0;
    }

    virtual void move(double time) override
    {
        Satellite::move(time * timeDilation);
        angle.add(-angularVelocity * (timeDilation - 1.0));
    }

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
            createFragments(satellites, 3);
            kill();
        }
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

/*********************************************
* GPS RIGHT ARRAY
* Right solar array of a destroyed GPS satellite
*********************************************/
class GPSRightArray : public Satellite
{
public:
    GPSRightArray(const Satellite& parent) :
        Satellite(0, 8.0, 0.001)
    {
        this->pos = parent.getPosition();
        this->velocity = Velocity();
        this->timeDilation = 48.0;
    }

    virtual void move(double time) override
    {
        Satellite::move(time * timeDilation);
        angle.add(-angularVelocity * (timeDilation - 1.0));
    }

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
            createFragments(satellites, 3);
            kill();
        }
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
            createFragments(satellites, 2);
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