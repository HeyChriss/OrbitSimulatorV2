/***********************************************************************
 * Header File:
 *    Test Hubble 
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about Testing hubble
 ************************************************************************/

#ifndef TestHubble_h
#define TestHubble_h

#include <stdio.h>
#include "unitTest.h"
#include "simulator.h"

/*******************************
 * TEST Hubble
 * A friend class for Hubble which contains the Hubble unit tests
 ********************************/
class TestHubble : public UnitTest
{
public:
    void run()
    {
        testInitialHeight();
        testOneOrbit();
        testHeight();

        report("Hubble");
    }

private:
    void testInitialHeight();
    void testOneOrbit();
    void testHeight();
};


#endif /* testHubble_h */

