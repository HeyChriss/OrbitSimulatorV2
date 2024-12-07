
/***********************************************************************
 * Header File:
 *    TestAngle
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about Testing Angle
 ************************************************************************/

#ifndef testAngle_h
#define testAngle_h

#include <stdio.h>
#pragma once

#include <iostream>
#include "angle.h"
#include <cassert>
#include "unitTest.h"

using namespace std;

/*******************************
 * TEST Angle
 * A friend class for Angle which contains the Angle unit tests
 ********************************/
class TestAngle : public UnitTest
{
public:
    void run()
    {
        testNormalize();
        testConstructor();
        testNormalizeEdgeCases();
        testDegreeConversion();
        testAdditionOperator();
        testMultiplicationOperator();
        testEqualityOperator();
        testChainedOperations();
        report("Angle");
    }

private:
    void testNormalize();
    void testConstructor();
    void testNormalizeEdgeCases();
    void testDegreeConversion();
    void testAdditionOperator();
    void testMultiplicationOperator();
    void testEqualityOperator();
    void testChainedOperations();
};

#endif /* testAngle_h */