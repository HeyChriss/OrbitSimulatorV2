
/***********************************************************************
 * Header File:
 *    Acceleration
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about acceleration
 ************************************************************************/
#pragma once

class TestVelocity;
class TestPosition;
class TestAcceleration;

class Acceleration
{

    friend TestPosition;
    friend TestVelocity;
    friend TestAcceleration;

private:
    float ddx;
    float ddy;

public:

    // Constructors
    Acceleration() : ddx(0.0), ddy(0.0) {}
    Acceleration(float ddx, float ddy) : ddx(ddx), ddy(ddy) {}

    float getDdx()const { return ddx; }
    float getDdy()const { return ddy; }
    void setDdx(float rhsDdx) { ddx = rhsDdx; }
    void setDdy(float rhsDdy) { ddy = rhsDdy; }
};


/*********************************************
 * AccelerationDummy
 * A Dummy double for acceleration. This does nothing but assert.
 * Stubs will be derived from this for the purpose of making
 * isolated unit tests.
 *********************************************/
class AccelerationDummy : public Acceleration
{
public:
    // getters
    virtual double getDDX()   const { assert(false); return 99.9; }
    virtual double getDDY()   const { assert(false); return 99.9; }

    // setters                        
    virtual void setDDX(double ddx) { assert(false); }
    virtual void setDDY(double ddy) { assert(false); }
    virtual void set(const Angle& a, double magnitude);
    virtual void addDDX(double ddx) { assert(false); }
    virtual void addDDY(double ddy) { assert(false); }
    virtual void add(const Acceleration& rhs) { assert(false); }
};


