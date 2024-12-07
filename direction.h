/***********************************************************************
 * Header File:
 *    Direction
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about Direction
 ************************************************************************/
#pragma once

#ifndef direction_h
#define direction_h

#include <stdio.h>
#include <iostream>
#include <cmath>

class TestDirection;


using namespace std;
class Direction
{
protected:
    double radians;
    double degrees;
public:

    friend TestDirection;
    Direction();
    Direction(double angD);

    double convertToDegrees(double r);
    double convertToRadians(double d);

    void normalize();

    double getDegrees()const;
    double getRadians()const;
    void setDegrees(double d);
    void setRadians(double r);

    Direction& operator=(const Direction& rhs);
    Direction operator-()const;
    bool operator==(const Direction& rhs)const;
    bool operator!=(const Direction& rhs)const;
    friend ostream& operator<<(ostream& out, const Direction& direction);
    friend istream& operator>>(istream& in, Direction& direction);

    virtual void display();
    virtual Direction& operator++();
    virtual Direction operator++(int);
    virtual Direction& operator--();
    virtual Direction operator--(int);


    const double pi = 2 * asin(1.0);
    const double fullRevolutionRad = 2 * pi;
    const double fullRevolutionDeg = 360.0;
};


#endif /* Direction_h */

