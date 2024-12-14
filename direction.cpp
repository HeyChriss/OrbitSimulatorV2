#include "direction.h"
#include <iostream>
#include <cmath>
using namespace std;

Direction::Direction() : degrees(0.0), radians(0.0) {}

Direction::Direction(double angD) {
    this->degrees = angD;
    this->radians = convertToRadians(angD);
}

double Direction::convertToDegrees(double r)
{
    return r * 180 / pi;
}

double Direction::convertToRadians(double d)
{
    return d * pi / 180;
}

void Direction::normalize()
{
    // Normalize degrees
    while (degrees < 0) {
        degrees += fullRevolutionDeg; // Add 360° to bring it into [0, 360)
    }
    while (degrees >= fullRevolutionDeg) {
        degrees -= fullRevolutionDeg; // Subtract 360° to bring it into [0, 360)
    }

    // Normalize radians
    while (radians < 0) {
        radians += fullRevolutionRad; // Add 2π to bring it into [0, 2π)
    }
    while (radians >= fullRevolutionRad) {
        radians -= fullRevolutionRad; // Subtract 2π to bring it into [0, 2π)
    }
}

// getters
double Direction::getDegrees()const
{
    return degrees;
}
double Direction::getRadians()const
{
    return radians;
}

// setters
void Direction::setDegrees(double d)
{
    degrees = d;
}
void Direction::setRadians(double r)
{
    radians = r;
}

Direction& Direction::operator=(const Direction& rhs) {
    if (this == &rhs)
        return *this;
    degrees = rhs.degrees;
    radians = rhs.radians;
    return *this;
}

Direction Direction::operator-()const {
    double inverseDegrees = 360.0 - degrees;
    return Direction(inverseDegrees);
}

bool Direction::operator==(const Direction& rhs)const {
    return degrees == rhs.degrees;
}

bool Direction::operator!=(const Direction& rhs)const {
    return degrees != rhs.degrees;
}


ostream& operator<<(ostream& out, const Direction& direction)
{
    out << direction.getDegrees() << endl;
    return out;
}

istream& operator>>(istream& in, Direction& direction)
{
    double value;
    in >> value;
    direction.setDegrees(value);
    return in;
}

// virtuals

void Direction::display()
{
    cout.setf(ios::fixed);
    cout.precision(1);

    cout << "Radians: " << getRadians() << endl;
    cout << "Degrees: " << getDegrees() << endl;
}

// Prefix
Direction& Direction::operator++()
{
    degrees += 1.0;
    return *this;
}

// Postfix
Direction Direction::operator++(int postfix)
{
    Direction directionToReturn(*this);
    degrees += 1.0;
    return directionToReturn;
}

// Prefix
Direction& Direction::operator--()
{
    degrees -= 1.0;
    return *this;
}

// Postfix
Direction Direction::operator--(int postfix)
{
    Direction directionToReturn(*this);
    degrees -= 1.0;
    return directionToReturn;
}

