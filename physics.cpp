#include "physics.h"

double Physics::gravityDirection(double xs, double ys) {
    double d = atan2(xs, ys);
    return d;
}

/*************************************************************************
 * GRAVITY EQUATION
 * This calculates the total acceleration due to earth's gravity
 * Formula: g * ( r / ( r + h ) ) ^ 2 = gh
 * gh = magnitude of acceleration due to gravity at altitude h (m/s^2)
 * g  = gravity at sea level   (m/s^2)
 * r  = radius of earth        (meters)
 * h  = height above earth     (meters)
 *************************************************************************/

double Physics::gravityEquation(double h, double radius, double gravity) {
    if (radius + h == 0) return 0.0;
    double gh = gravity * pow((radius / (radius + h)), 2);
    return gh;
}

/*************************************************************************
 * HEIGHT ABOVE EARTH
 * Finds the height above the earth an object is.
 * Assumes Earth is located at (0, 0)
 * Formula: h = sqrt(x * x + y * y) - r
 * h = distance between the surface of the earth and the object (meters)
 * x = horizontal position of object   (meters)
 * y = vertical position of object     (meters)
 * r = radius of earth                 (meters)
 *************************************************************************/

double Physics::heightAbovePlanet(double x, double y, double radius) {
    double h = sqrt(x * x + y * y) - radius;
    return h;
}

/*************************************************************************
 * GRAVITY DIRECTION
 * Calculates the angle at which an object is pulled by gravity.
 * Assumes Earth is located at (0, 0)
 * Fromula: d = atan( xe - xs, ye - ys )
 * d = direction of the pull of gravity      (radians)
 * xe = horizontal position of the center of the earth : 0m
 * ye = vertical position of the center of the earth : 0m
 * xs = horizontal position of the satellite (meters)
 * ys = vertical position of the satellite   (meters)
 *************************************************************************/

double Physics::computeDirection(double x, double y)
{
    double d = atan2(x, y);
    return d;
}

/*************************************************************************
 * VERTICAL ACCELERATION
 * ddy = a * cos( angle )
 * ddy = vertical component of acceleration        (m/s^2)
 * a = total acceleration                          (m/s^2)
 * angle = angle of the direction of acceleration  (0 degrees is up)
 *************************************************************************/

double Physics::verticalAcceleration(double a, double angle) {
    double ddy = a * cos(angle);
    return ddy;
}

/*************************************************************************
 * HORIZONTAL ACCELERATION
 * ddx = a * sin( angle )
 * ddx = horizontal component of acceleration      (m/s^2)
 * a = total acceleration                          (m/s^2)
 * angle = angle of the direction of acceleration  (0 degrees is up)
 *************************************************************************/

double Physics::horizontalAcceleration(double a, double angle) {
    double ddx = a * sin(angle);
    return ddx;
}


/*************************************************************************
 * VELOCITY CONSTANT ACCELERATION
 * Compute the velocity when given a constant acceleration.
 * Can be used for both horizontal and vertical velocity.
 * Formula: v = vo + a * t
 *    ex. (dx = dxo + ddx * t)
 * v = velocity            (m/s)
 * vo = initial velocity   (m/s)
 * a = acceleration        (m/s^2)
 * t = time                (seconds)
 *************************************************************************/

double Physics::velocityConstantAcceleration(double vo, double a, double t) {
    double v = vo + a * t;
    return v;
}


/*************************************************************************
 * POSITION CONSTANT VELOCITY
 * Compute the distance when given a constant velocity.
 * Can be used for both horizontal and vertical distance.
 * Formula: s = so + v * t
 *     ex. (x = xo + dx * t)
 * s  = distance           (meters)
 * so = initial position   (meters)
 * v  = velocity           (m/s)
 * t  = time               (seconds)
 *************************************************************************/

double Physics::verticalConstantVelocity(double so, double v, double t) {
    double s = so + v * t;
    return s;
}

/*************************************************************************
 * DISTANCE FORMULA
 * This formula is used for calculating the distance something travelled.
 * Can be used for both vertical and horizontal distance.
 * Formula: s = so + (v * t) + (.5 * a * t * t)
 *     ex. (x = xo + (dx * t) + (.5 * ddx * t * t))
 * s = distance            (meters)
 * so = initial distance   (meters)
 * v = velocity            (m/s)
 * t = time                (seconds)
 * a = acceleration        (m/s^2)
 *************************************************************************/
double Physics::distanceFormula(double so, double v, double a, double t) {
    double s = so + (v * t) + (.5 * a * t * t);
    return s;
}


double Physics::radiansFromDegrees(double d)
{
    double pi = 2 * asin(1.0);
    return (d * (2 * pi)) / 360;
}

