#pragma once
#include "satellite.h"
#include "velocity.h"
#include "uiDraw.h"

class TestHubble;

// Base component class for Hubble pieces
class HubbleComponent : public Satellite {
public:
    HubbleComponent(const Satellite& parent, double radius, int fragments) :
        Satellite(0, radius, 0.0), numFragments(fragments)
    {
        pos = parent.getPosition();
        velocity = Velocity();
        timeDilation = 48.0;
    }

    virtual void destroy(std::list<Satellite*>& satellites) override {
        if (!isInvisible() && !isDead()) {
            for (int i = 0; i < numFragments; i++) {
                Angle angle;
                angle.setDegrees(random(0.0, 360.0));
                satellites.push_back(new Satellite(*this, angle));
            }
            kill();
        }
    }

    virtual void move(double time) override {
        Satellite::move(time * timeDilation);
        angle.add(-angularVelocity * (timeDilation - 1.0));
    }

protected:
    int numFragments;
    double timeDilation;
};

class HubbleTelescope : public HubbleComponent {
public:
    HubbleTelescope(const Satellite& parent) : HubbleComponent(parent, 10.0, 3) {}
    virtual void draw(ogstream& gout) override {
        if (!isInvisible() && !isDead())
            gout.drawHubbleTelescope(pos, angle.getRadians());
    }
};

class HubbleComputer : public HubbleComponent {
public:
    HubbleComputer(const Satellite& parent) : HubbleComponent(parent, 7.0, 2) {}
    virtual void draw(ogstream& gout) override {
        if (!isInvisible() && !isDead())
            gout.drawHubbleComputer(pos, angle.getRadians());
    }
};

class HubbleLeftArray : public HubbleComponent {
public:
    HubbleLeftArray(const Satellite& parent) : HubbleComponent(parent, 8.0, 2) {}
    virtual void draw(ogstream& gout) override {
        if (!isInvisible() && !isDead())
            gout.drawHubbleLeft(pos, angle.getRadians());
    }
};

class HubbleRightArray : public HubbleComponent {
public:
    HubbleRightArray(const Satellite& parent) : HubbleComponent(parent, 8.0, 2) {}
    virtual void draw(ogstream& gout) override {
        if (!isInvisible() && !isDead())
            gout.drawHubbleRight(pos, angle.getRadians());
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
        if (!isInvisible() && !isDead()) {
            satellites.push_back(new HubbleTelescope(*this));
            satellites.push_back(new HubbleComputer(*this));
            satellites.push_back(new HubbleLeftArray(*this));
            satellites.push_back(new HubbleRightArray(*this));
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