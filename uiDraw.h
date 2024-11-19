/***********************************************************************
 * Header File:
 *    User Interface Draw : put pixels on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This is the code necessary to draw on the screen. We have a collection
 *    of procedural functions here because each draw function does not
 *    retain state. In other words, they are verbs (functions), not nouns
 *    (variables) or a mixture (objects)
 ************************************************************************/

#pragma once

#include <string>     // To display text on the screen
#include <cmath>      // for M_PI, sin() and cos()
#include <algorithm>  // used for min() and max()
#include "position.h" // Where things are drawn
using std::string;
using std::min;
using std::max;

#include <sstream>


#define GL_SILENCE_DEPRECATION

/*************************************************************************
 * GRAPHICS STREAM
 * A graphics stream that behaves much like COUT except on a drawn screen
 *************************************************************************/
class ogstream : public std::ostringstream
{
public:
    ogstream() {}
    ogstream(const Position& pt) : pt(pt) {}
    ~ogstream() { flush(); };

    // This is mostly for the text drawing stuff
    virtual void flush();
    virtual void setPosition(const Position& pt) { flush(); this->pt = pt; }
    virtual ogstream& operator = (const Position& pt)
    {
        setPosition(pt);
        return *this;
    }

    // This is specific to the orbit simulator
    virtual void drawFragment(const Position& center, double rotation);
    virtual void drawProjectile(const Position& pt);

    virtual void drawCrewDragon(const Position& center, double rotation);
    virtual void drawCrewDragonRight(const Position& center, double rotation, const Position& offset = Position());
    virtual void drawCrewDragonLeft(const Position& center, double rotation, const Position& offset = Position());
    virtual void drawCrewDragonCenter(const Position& center, double rotation);

    virtual void drawSputnik(const Position& center, double rotation);

    virtual void drawGPS(const Position& center, double rotation);
    virtual void drawGPSCenter(const Position& center, double rotation);
    virtual void drawGPSRight(const Position& center, double rotation, const Position& offset = Position());
    virtual void drawGPSLeft(const Position& center, double rotation, const Position& offset = Position());

    virtual void drawHubble(const Position& center, double rotation);
    virtual void drawHubbleComputer(const Position& center, double rotation, const Position& offset = Position());
    virtual void drawHubbleTelescope(const Position& center, double rotation, const Position& offset = Position());
    virtual void drawHubbleLeft(const Position& center, double rotation, const Position& offset = Position());
    virtual void drawHubbleRight(const Position& center, double rotation, const Position& offset = Position());

    virtual void drawStarlink(const Position& center, double rotation);
    virtual void drawStarlinkBody(const Position& center, double rotation, const Position& offset = Position());
    virtual void drawStarlinkArray(const Position& center, double rotation, const Position& offset = Position());

    virtual void drawShip(const Position& center, double rotation, bool thrust);

    virtual void drawEarth(const Position& center, double rotation);

    virtual void drawStar(const Position& point, unsigned char phase);

protected:
    Position pt;
};

/*************************************************************************
 * GRAPHICS STREAM DUMMY
 * Better not be called!
 *************************************************************************/
class ogstreamDummy : public ogstream
{
public:
    ogstreamDummy(const Position& pt) {}
    ~ogstreamDummy() {}

    // This is mostly for the text drawing stuff
    void flush();
    void setPosition(const Position& pt);
    ogstreamDummy& operator = (const Position& pt);

    // This is specific to the orbit simulator
    void drawFragment(const Position& center, double rotation);
    void drawProjectile(const Position& pt);

    void drawCrewDragon(const Position& center, double rotation);
    void drawCrewDragonRight(const Position& center, double rotation, const Position& offset = Position());
    void drawCrewDragonLeft(const Position& center, double rotation, const Position& offset = Position());
    void drawCrewDragonCenter(const Position& center, double rotation);

    void drawSputnik(const Position& center, double rotation);

    void drawGPS(const Position& center, double rotation);
    void drawGPSCenter(const Position& center, double rotation);
    void drawGPSRight(const Position& center, double rotation, const Position& offset = Position());
    void drawGPSLeft(const Position& center, double rotation, const Position& offset = Position());

    void drawHubble(const Position& center, double rotation);
    void drawHubbleComputer(const Position& center, double rotation, const Position& offset = Position());
    void drawHubbleTelescope(const Position& center, double rotation, const Position& offset = Position());
    void drawHubbleLeft(const Position& center, double rotation, const Position& offset = Position());
    void drawHubbleRight(const Position& center, double rotation, const Position& offset = Position());

    void drawStarlink(const Position& center, double rotation);
    void drawStarlinkBody(const Position& center, double rotation, const Position& offset = Position());
    void drawStarlinkArray(const Position& center, double rotation, const Position& offset = Position());

    void drawShip(const Position& center, double rotation, bool thrust);

    void drawEarth(const Position& center, double rotation);

    void drawStar(const Position& point, unsigned char phase);
};

/*************************************************************************
 * GRAPHICS STREAM Fake
 * Better not be called!
 *************************************************************************/
class ogstreamFake : public ogstream
{
public:
    ogstreamFake(const Position& pt) {}
    ~ogstreamFake() {}

    // This is mostly for the text drawing stuff
    void flush();
    void setPosition(const Position& pt);
    ogstreamFake& operator = (const Position& pt);

    // This is specific to the orbit simulator
    void drawFragment(const Position& center, double rotation);
    void drawProjectile(const Position& pt);

    void drawCrewDragon(const Position& center, double rotation);
    void drawCrewDragonRight(const Position& center, double rotation, const Position& offset = Position());
    void drawCrewDragonLeft(const Position& center, double rotation, const Position& offset = Position());
    void drawCrewDragonCenter(const Position& center, double rotation);

    void drawSputnik(const Position& center, double rotation);

    void drawGPS(const Position& center, double rotation);
    void drawGPSCenter(const Position& center, double rotation);
    void drawGPSRight(const Position& center, double rotation, const Position& offset = Position());
    void drawGPSLeft(const Position& center, double rotation, const Position& offset = Position());

    void drawHubble(const Position& center, double rotation);
    void drawHubbleComputer(const Position& center, double rotation, const Position& offset = Position());
    void drawHubbleTelescope(const Position& center, double rotation, const Position& offset = Position());
    void drawHubbleLeft(const Position& center, double rotation, const Position& offset = Position());
    void drawHubbleRight(const Position& center, double rotation, const Position& offset = Position());

    void drawStarlink(const Position& center, double rotation);
    void drawStarlinkBody(const Position& center, double rotation, const Position& offset = Position());
    void drawStarlinkArray(const Position& center, double rotation, const Position& offset = Position());

    void drawShip(const Position& center, double rotation, bool thrust);

    void drawEarth(const Position& center, double rotation);

    void drawStar(const Position& point, unsigned char phase);
};

/******************************************************************
 * RANDOM
 * This function generates a random number.  The user specifies
 * The parameters
 *    INPUT:   min, max : The number of values (min <= num <= max)
 *    OUTPUT   <return> : Return the integer/double
 ****************************************************************/
int    random(int    min, int    max);
double random(double min, double max);

