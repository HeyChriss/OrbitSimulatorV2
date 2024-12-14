/***********************************************************************
 * Header File:
 *    Physics
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about Physics
 ************************************************************************/
#pragma once

#ifndef physics_h
#define physics_h

#include <math.h>

#include <iostream>
#include <cmath>
#include <string>

using namespace std;

#include <stdio.h>
#include "direction.h"
#include "position.h"


class Physics {
public:

    double gravityDirection(double xs, double ys);
    double gravityEquation(double h, double radius, double gravity);
    double heightAbovePlanet(double x, double y, double radius);
    double computeDirection(double x, double y);
    double verticalAcceleration(double a, double angle);
    double horizontalAcceleration(double a, double angle);
    double velocityConstantAcceleration(double vo, double a, double t);
    double verticalConstantVelocity(double so, double v, double t);
    double distanceFormula(double so, double v, double a, double t);
    double radiansFromDegrees(double d);


    const int geoStationarySpeed = 3100; // Meters per second
    const double earthRadiusMeters = 6378000.0;
    const int geoStationaryOrbitHeightMeters = 42164000;
    const double gravityOnEarth = -9.8067; // Meters per second squared
    const double secondsPerFrame = 48;  // time dilation
};


#endif /* physics_h */
