#pragma once
#include "satellite.h"
#include "velocity.h"
#include "uiDraw.h"


/*********************************************
* FRAGMENT
* A fragment of a destroyed satellite/part
*********************************************/
class Fragment : public Satellite
{

    friend class TestFragment;
public:
    Fragment(const Satellite& parent, const Angle& direction) :
        Satellite(0, 4.0, 0.001),
        lifetime(random(50, 100)) // Fixed radius and small rotation for all fragments
    {
        // Set position offset from parent
        this->pos = parent.getPosition();
        Position posKick;
        posKick.setPixelsX(4.0 * sin(direction.getRadians()));
        posKick.setPixelsY(4.0 * cos(direction.getRadians()));
        pos.addMetersX(posKick.getMetersX());
        pos.addMetersY(posKick.getMetersY());

        // Set velocity with random kick
        this->velocity = parent.velocity;
        double speed = random(1000.0, 3000.0);
        Velocity kick;
        kick.set(direction, speed);
        velocity.add(kick);

        // Set time dilation
        timeDilation = 48.0;
    }

    virtual void move(double time) override
    {
        lifetime--;
        if (lifetime <= 0)
        {
            kill();
            return;
        } 
        Satellite::move(time * timeDilation);
        angle.add(-angularVelocity * (timeDilation - 1.0));
        
    }

    virtual void draw(ogstream& gout) override
    {
        if (!isInvisible() && !isDead())
            gout.drawFragment(pos, angle.getRadians());
    }

private:
    double timeDilation;
    int lifetime;

};

