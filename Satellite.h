/***********************************************************************
 * Header File:
 *    SATELLITE
 * Author:
 *    <your name here>
 * Summary:
 *    Base class for all satellites in orbit
 ************************************************************************/


#pragma once

#include "position.h"
#include "velocity.h"
#include "angle.h"
#include "uiDraw.h"
#include <list>

class TestSatellite;
class Interface;
class TestSatellite;


/*********************************************
 * SATELLITE
 * Base class for all the satellites in our simulation
 *********************************************/
class Satellite
{
public:
    friend TestSatellite;


    // constructors
    Satellite(int age = 0, double radius = 0.0, double angularVelocity = 0.0)
        : angularVelocity(angularVelocity), dead(false), age(age), radius(radius)
    {
#ifdef NDEBUG
        useRandom = true;
#endif
    }

    // Used to create parts and fragments
    Satellite(const Satellite& parent, const Angle& direction);

    // Used to create projectiles. They have specific speeds
    Satellite(const Satellite& parent, const Position& offset, const Velocity& kick);

    // Getters
    double getRadius() const { return radius; }
    bool isDead() const { return dead; }
    bool isInvisible() const { return age < 10; }
    const Angle& getAngle() const { return angle; }
    const Position& getPosition() const { return pos; }

    // Setters
    virtual void kill() { if (!isInvisible()) dead = true; }

    // Stuff to be overridden
    virtual bool getDefunct() { return false; }
    virtual void draw(ogstream& gout) {}
    virtual void destroy(std::list<Satellite*>& satellites) {}
    virtual void move(double time);
    virtual void input(const Interface& ui, std::list<Satellite*>& satellites) {}

protected:
    Velocity velocity;        // speed and direction
    Position pos;            // position in meters
    Angle angle;            // angle satellite is pointed
    double angularVelocity; // spin
    bool dead;              // whether it is dead - to be cleaned
    double radius;          // radius in meters
    int age;               // how long have we been alive?
    Acceleration getGravity(const Position& pos) const;
#ifdef NDEBUG
    bool useRandom;
#endif // DEBUG
};

