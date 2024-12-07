/***********************************************************************
 * Header File:
 *    Test Ship
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about Ship
 ************************************************************************/

#ifndef testShip_h
#define testShip_h


#include <iostream>
#include "ship.h"
#include <cassert>
#include "unitTest.h"

#include <stdio.h>

/*******************************
 * TEST Hubble
 * A friend class for Hubble which contains the Hubble unit tests
 ********************************/
class TestShip : public UnitTest
{
public:
    void run()
    {
        testConstructor();
        testThrustUp();
        testThrustDown();

        report("Ship");
    }

private:
    void testConstructor();
    void testThrustUp();
    void testThrustDown();
};


#endif /* testShip_h */

