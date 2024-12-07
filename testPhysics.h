/***********************************************************************
 * Header File:
 *    Testing Physics
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about Testing Physics
 ************************************************************************/

#ifndef testPhysics_h
#define testPhysics_h

#include <stdio.h>

#pragma once

#include <iostream>
#include "physics.h"
#include "direction.h"
#include <cassert>
#include "unitTest.h"

using namespace std;

/*******************************
 * TEST Physics
 * A friend class for Physics which contains the Physics unit tests
 ********************************/
class TestPhysics : public UnitTest
{
public:
    void run()
    {
        testComputeDirection();
        testHeightAboveEarth();
        testComputeGravity();
        testHorizontalComponent();
        testVerticalComponent();
        testComputeDistance();
        testVelocity();

        report("Physics");
    }

private:
    void testComputeDirection();
    void testHeightAboveEarth();
    void testComputeGravity();
    void testHorizontalComponent();
    void testVerticalComponent();
    void testComputeDistance();
    void testVelocity();
};


#endif /* testPhysics_h */
