#pragma once
#include "satellite.h"
#include "velocity.h"
#include "uiDraw.h"
#include "part.h"
#include "Fragment.h"

class TestHubble;

/*********************************************
* HUBBLE TELESCOPE
* Telescope component of a destroyed Hubble satellite
*********************************************/
class HubbleTelescope : public Part
{
public:
    HubbleTelescope(const Satellite& parent) : Part(10.0, 0.0, parent) {}

    virtual void draw(ogstream& gout) override {
        if (!isInvisible() && !isDead())
            gout.drawHubbleTelescope(pos, angle.getRadians());
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
* HUBBLE COMPUTER
* Computer component of a destroyed Hubble satellite
*********************************************/
class HubbleComputer : public Part
{
public:
    HubbleComputer(const Satellite& parent) : Part(7.0, 0.0, parent) {}

    virtual void draw(ogstream& gout) override {
        if (!isInvisible() && !isDead())
            gout.drawHubbleComputer(pos, angle.getRadians());
    }

    virtual void destroy(std::list<Satellite*>& satellites) override
    {
        if (!isInvisible() && !isDead())
        {
            // Create 2 fragments
            for (int i = 0; i < 2; i++)
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
* HUBBLE LEFT ARRAY
* Left solar array of a destroyed Hubble satellite
*********************************************/
class HubbleLeftArray : public Part
{
public:
    HubbleLeftArray(const Satellite& parent) : Part(8.0, 0.0, parent) {}

    virtual void draw(ogstream& gout) override {
        if (!isInvisible() && !isDead())
            gout.drawHubbleLeft(pos, angle.getRadians());
    }

    virtual void destroy(std::list<Satellite*>& satellites) override
    {
        if (!isInvisible() && !isDead())
        {
            // Create 2 fragments
            for (int i = 0; i < 2; i++)
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
* HUBBLE RIGHT ARRAY
* Right solar array of a destroyed Hubble satellite
*********************************************/
class HubbleRightArray : public Part
{
public:
    HubbleRightArray(const Satellite& parent) : Part(8.0, 0.0, parent) {}

    virtual void draw(ogstream& gout) override {
        if (!isInvisible() && !isDead())
            gout.drawHubbleRight(pos, angle.getRadians());
    }

    virtual void destroy(std::list<Satellite*>& satellites) override
    {
        if (!isInvisible() && !isDead())
        {
            // Create 2 fragments
            for (int i = 0; i < 2; i++)
            {
                Angle angle;
                angle.setDegrees(random(0.0, 360.0));
                satellites.push_back(new Fragment(*this, angle));
            }
            kill();
        }
    }

};

class Hubble : public Satellite {
public:
    friend TestHubble;

    Hubble() : Satellite(0, 10.0, 0.0) {
        pos.setMetersX(0.0);
        pos.setMetersY(-42164000.0);
        velocity.setDX(3100.0);
        velocity.setDY(0.0);
        timeDilation = 48.0;
    }

    virtual void destroy(std::list<Satellite*>& satellites) override {
        if (!isInvisible() && !isDead())
        {
            // Create component parts
            satellites.push_back(new HubbleTelescope(*this));
            satellites.push_back(new HubbleComputer(*this));
            satellites.push_back(new HubbleLeftArray(*this));
            satellites.push_back(new HubbleRightArray(*this));

            // Create fragments
            //for (int i = 0; i < 3; i++)
            //{
            //    Angle angle;
            //    angle.setDegrees(random(0.0, 360.0));
            //    satellites.push_back(new Fragment(*this, angle));
            //}
            kill();
        }
    }

    virtual void move(double time) override {
        Satellite::move(time * timeDilation);
        angle.add(-angularVelocity * (timeDilation - 1.0));
    }

    virtual void draw(ogstream& gout) override {
        if (!isInvisible() && !isDead())
            gout.drawHubble(pos, angle.getRadians());
    }

private:
    double timeDilation;
};