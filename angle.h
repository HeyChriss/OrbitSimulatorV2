/***********************************************************************
 * Header File:
 *    Angle
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about Angle
 ************************************************************************/

#pragma once
#include <cmath>


class Angle
{
public:
    friend class TestAngle;
    friend class TestShip;
    friend class TestCelestialObject;
    friend class TestVelocity;
    friend class TestSatellite;
    friend class TestProjectile;
    friend class TestFragment;
    friend class TestPart;

    Angle() : radAngle(0.0) {}
    Angle(double radAngle) : radAngle(radAngle) { this->normalize(); }

    const double pi = 2 * asin(1.0);
    const double fullRevolutionRad = 2 * pi;

    Angle& operator *= (const double scale);
    Angle& operator += (const Angle& twoD);
    Angle& operator -= (const Angle& twoD);
    bool operator == (const Angle& twoD) {
        return this->radAngle == twoD.radAngle;
    }
    Angle& operator = (const Angle& twoD) {
        this->radAngle = twoD.radAngle;
        return *this;
    };

    void setRadian(double radians) { this->radAngle = radians; normalize(); };
    void addRadian(double radians) { this->radAngle += radians; normalize(); };
    double getRadian() const { return radAngle; }

    void setDegree(double degrees);
    void addDegree(double degrees);
    double getDegree() const;

private:
    double radAngle;
    void normalize();
};

