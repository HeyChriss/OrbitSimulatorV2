#pragma once
#include "satellite.h"
#include "velocity.h"
#include "uiDraw.h"

class TestProjectile;

/*********************************************
* PROJECTILE
* A bullet fired from the Dream Chaser that expires after 2 seconds
*********************************************/
class Projectile : public Satellite
{
    friend TestProjectile;

public:
    Projectile(const Satellite& parent, const double rotation) :
        Satellite(0, 1.0, 0.0),
        lifetime(70)
    {
        // Set position with offset
        this->pos = parent.getPosition();
        Position posKick;
        posKick.setPixelsX(19.0 * sin(rotation));
        posKick.setPixelsY(19.0 * cos(rotation));
        pos.addMetersX(posKick.getMetersX());
        pos.addMetersY(posKick.getMetersY());

        // Set velocity to 9000 m/s in firing direction plus parent velocity
        this->velocity = parent.velocity;
        Angle direction;
        direction.setRadians(rotation);
        Velocity kick;
        kick.set(direction, 9000.0);
        velocity.add(kick);

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


    virtual void draw(ogstream& gout) override {
        if (!isInvisible() && !isDead())
            gout.drawProjectile(pos);
    }


private:
    int lifetime;
    double timeDilation;
};
