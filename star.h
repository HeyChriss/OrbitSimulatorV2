/***********************************************************************
 * Header File:
 *    Stars
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about Stars
 ************************************************************************/
#pragma once
#include "object.h"
#include "uiDraw.h"

class Star : public Object
{
public:
    Star(Position pos = Position(), Velocity vel = Velocity(), Angle rotation = Angle()) : Object(pos, vel, rotation)
    {
        this->phase = random(0, 250);
    };

    void update(double time) {
        if (phase > 250)
            this->phase = 0;
        else
            this->phase++;
    };

    int getPhase() { return this->phase; };

    void draw() { ogs.drawStar(pos, phase); }


private:
    int phase;
};

