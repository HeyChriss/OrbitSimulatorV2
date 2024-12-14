/***********************************************************************
 * Header File:
 *    Celestial Object
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about the celestial objects 
 ************************************************************************/
#pragma once
#include <vector>
#include "object.h"



class Simulator;

class CelestialObject : public Object
{
public:
    friend class TestCelestialObject;
    friend class TestHubble;
    friend class TestDragon;
    friend class TestGPS;
    friend class TestShip;
    friend class TestSputnik;
    friend class TestStarlink;
    friend class TestPart;

    CelestialObject(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : Object(pos, vel, angle)
    {
        this->radius = 0;
        this->numFragments = 0;
        this->isExpired = false;
        this->hasBeenHit = false;
    };

    virtual void update(double time, double gravity, double planetRadius) {
        Object::update(time, gravity, planetRadius);
    }

    virtual bool isHit(CelestialObject* other);

    void setExpired(bool expired) { this->isExpired = expired; };
    virtual bool getExpired() { return this->isExpired; };

    void setHasBeenHit(bool hit) { this->hasBeenHit = hit; };
    virtual bool getHasBeenHit() { return this->hasBeenHit; };


    int getNumFragments() const { return this->numFragments; };
    virtual double getRadius() const { return radius * 100000; };

    virtual void breakApart(Simulator* sim, vector<CelestialObject*> subParts = {});
    virtual void draw() {};

protected:
    bool hasBeenHit;
    bool isExpired;
    double radius;
    int numFragments;

    void addObjects(Simulator* sim, vector<CelestialObject*> subParts);
    vector<Velocity> getSubPartVel(int subParts);
    vector<Position> getSubPartPos(vector<Velocity> directions);
    Velocity randomVelocity(Velocity v = Velocity());

};

