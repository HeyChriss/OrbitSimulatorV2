#pragma once
#include "satellite.h"
#include "velocity.h"
#include "Fragment.h"
#include "angle.h"

/*********************************************
* PART
* Base class for satellite parts that break off during collision
*********************************************/
class Part : public Satellite
{
    friend TestPart;
public:
    Part(double radius, double angularVelocity, const Satellite& parent) :
        Satellite(0, radius, angularVelocity)
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

protected:
    void createFragments(std::list<Satellite*>& satellites, int count)
    {
        for (int i = 0; i < count; i++)
        {
            Angle fragmentAngle;
            fragmentAngle.setDegrees(random(0.0, 360.0));
            satellites.push_back(new Fragment(*this, fragmentAngle));
        }
    }

    double timeDilation;
};

