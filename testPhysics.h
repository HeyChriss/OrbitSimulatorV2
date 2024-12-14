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

#include <iostream>
#include <cassert>
#include "unitTest.h"
#include <cmath>
#include "Physics.h"
#include "testVelocity.h"



class TestPhysics : public UnitTest
{
public:
    void run()
    {
        testGravityDirectionQuadrant1();
        testGravityDirectionQuadrant2();
        testGravityDirectionQuadrant3();
        testGravityDirectionQuadrant4();
        testGravityEquationAtSurface();
        testGravityEquationInOrbit();
        testGravityEquationWithZeroRadius();
        testHeightAbovePlanetSurface();
        testHeightAbovePlanetOrbit();
        testComputeDirectionQuadrant1();
        testComputeDirectionQuadrant2();
        testComputeDirectionQuadrant3();
        testComputeDirectionQuadrant4();
        testVerticalAccelerationUp();
        testVerticalAccelerationDown();
        testHorizontalAccelerationRight();
        testHorizontalAccelerationLeft();
        testVelocityConstantAccelerationPositive();
        testVelocityConstantAccelerationNegative();
        testVelocityConstantAccelerationZero();
        testVerticalConstantVelocityUp();
        testVerticalConstantVelocityDown();
        testDistanceFormulaPositive();
        testDistanceFormulaNegative();
        testRadiansFromDegrees();
        testPhysicsConstants();

        report("Physics");
    }

private:
    void testGravityDirectionQuadrant1()
    {
        // Setup
        Physics physics;
        double xs = 1.0;
        double ys = 1.0;

        // Exercise
        double result = physics.gravityDirection(xs, ys);

        // Verify 
        assertUnit(fabs(result - M_PI / 4) < 0.001);
    }

    void testGravityDirectionQuadrant2()
    {
        // Setup
        Physics physics;
        double xs = -1.0;
        double ys = 1.0;

        // Exercise
        double result = physics.gravityDirection(xs, ys);

        // Verify
        assertUnit(fabs(result + M_PI / 4) < 0.001);
    }

    void testGravityDirectionQuadrant3()
    {
        // Setup
        Physics physics;
        double xs = -1.0;
        double ys = -1.0;

        // Exercise
        double result = physics.gravityDirection(xs, ys);

        // Verify
        assertUnit(fabs(result + 3 * M_PI / 4) < 0.001);
    }

    void testGravityDirectionQuadrant4()
    {
        // Setup
        Physics physics;
        double xs = 1.0;
        double ys = -1.0;

        // Exercise
        double result = physics.gravityDirection(xs, ys);

        // Verify
        assertUnit(fabs(result - 3 * M_PI / 4) < 0.001);
    }

    void testGravityEquationAtSurface()
    {
        // Setup
        Physics physics;
        double height = 0.0;
        double radius = 6378000.0;
        double gravity = -9.8067;

        // Exercise
        double result = physics.gravityEquation(height, radius, gravity);

        // Verify
        assertUnit(fabs(result - gravity) < 0.001);
    }

    void testGravityEquationInOrbit()
    {
        // Setup
        Physics physics;
        double height = physics.geoStationaryOrbitHeightMeters - physics.earthRadiusMeters;
        double radius = physics.earthRadiusMeters;
        double gravity = physics.gravityOnEarth;

        // Exercise
        double result = physics.gravityEquation(height, radius, gravity);

        // Verify - gravity should be weaker in orbit
        assertUnit(fabs(result) < fabs(gravity));
    }

    void testGravityEquationWithZeroRadius()
    {
        // Setup
        Physics physics;

        // Exercise
        double result = physics.gravityEquation(0, 0, -9.8067);

        // Verify
        assertUnit(result == 0.0);
    }

    void testHeightAbovePlanetSurface()
    {
        // Setup
        Physics physics;
        double x = 6378000.0;  // Earth radius
        double y = 0.0;
        double radius = 6378000.0;

        // Exercise
        double result = physics.heightAbovePlanet(x, y, radius);

        // Verify
        assertUnit(fabs(result - 0.0) < 0.001);
    }

    void testHeightAbovePlanetOrbit()
    {
        // Setup
        Physics physics;
        double expectedHeight = 35786000.0;  // Geostationary orbit height
        double x = 0.0;
        double y = physics.earthRadiusMeters + expectedHeight;

        // Exercise
        double result = physics.heightAbovePlanet(x, y, physics.earthRadiusMeters);

        // Verify
        assertUnit(fabs(result - expectedHeight) < 0.001);
    }

    void testComputeDirectionQuadrant1()
    {
        // Setup
        Physics physics;
        double x = 1.0;
        double y = 1.0;

        // Exercise
        double result = physics.computeDirection(x, y);

        // Verify
        assertUnit(fabs(result - M_PI / 4) < 0.001);
    }

    void testComputeDirectionQuadrant2()
    {
        // Setup
        Physics physics;
        double x = -1.0;
        double y = 1.0;

        // Exercise
        double result = physics.computeDirection(x, y);

        // Verify
        assertUnit(fabs(result + M_PI / 4) < 0.001);
    }

    void testComputeDirectionQuadrant3()
    {
        // Setup
        Physics physics;
        double x = -1.0;
        double y = -1.0;

        // Exercise
        double result = physics.computeDirection(x, y);

        // Verify
        assertUnit(fabs(result + 3 * M_PI / 4) < 0.001);
    }

    void testComputeDirectionQuadrant4()
    {
        // Setup
        Physics physics;
        double x = 1.0;
        double y = -1.0;

        // Exercise
        double result = physics.computeDirection(x, y);

        // Verify
        assertUnit(fabs(result - 3 * M_PI / 4) < 0.001);
    }

    void testVerticalAccelerationUp()
    {
        // Setup
        Physics physics;
        double acceleration = 10.0;
        double angle = 0.0;  // Straight up

        // Exercise
        double result = physics.verticalAcceleration(acceleration, angle);

        // Verify
        assertUnit(fabs(result - 10.0) < 0.001);
    }

    void testVerticalAccelerationDown()
    {
        // Setup
        Physics physics;
        double acceleration = 10.0;
        double angle = M_PI;  // Straight down

        // Exercise
        double result = physics.verticalAcceleration(acceleration, angle);

        // Verify
        assertUnit(fabs(result + 10.0) < 0.001);
    }

    void testHorizontalAccelerationRight()
    {
        // Setup
        Physics physics;
        double acceleration = 10.0;
        double angle = M_PI / 2;  // Right

        // Exercise
        double result = physics.horizontalAcceleration(acceleration, angle);

        // Verify
        assertUnit(fabs(result - 10.0) < 0.001);
    }

    void testHorizontalAccelerationLeft()
    {
        // Setup
        Physics physics;
        double acceleration = 10.0;
        double angle = 3 * M_PI / 2;  // Left

        // Exercise
        double result = physics.horizontalAcceleration(acceleration, angle);

        // Verify
        assertUnit(fabs(result + 10.0) < 0.001);
    }

    void testVelocityConstantAccelerationPositive()
    {
        // Setup
        Physics physics;
        double initialVelocity = 5.0;
        double acceleration = 2.0;
        double time = 3.0;

        // Exercise
        double result = physics.velocityConstantAcceleration(initialVelocity, acceleration, time);

        // Verify
        assertUnit(fabs(result - 11.0) < 0.001);  // v = v0 + at
    }

    void testVelocityConstantAccelerationNegative()
    {
        // Setup
        Physics physics;
        double initialVelocity = 5.0;
        double acceleration = -2.0;
        double time = 3.0;

        // Exercise
        double result = physics.velocityConstantAcceleration(initialVelocity, acceleration, time);

        // Verify
        assertUnit(fabs(result - (-1.0)) < 0.001);
    }

    void testVelocityConstantAccelerationZero()
    {
        // Setup
        Physics physics;
        double initialVelocity = 5.0;
        double acceleration = 0.0;
        double time = 3.0;

        // Exercise
        double result = physics.velocityConstantAcceleration(initialVelocity, acceleration, time);

        // Verify
        assertUnit(fabs(result - 5.0) < 0.001);
    }

    void testVerticalConstantVelocityUp()
    {
        // Setup
        Physics physics;
        double initialPosition = 0.0;
        double velocity = 5.0;
        double time = 2.0;

        // Exercise
        double result = physics.verticalConstantVelocity(initialPosition, velocity, time);

        // Verify
        assertUnit(fabs(result - 10.0) < 0.001);
    }

    void testVerticalConstantVelocityDown()
    {
        // Setup
        Physics physics;
        double initialPosition = 10.0;
        double velocity = -5.0;
        double time = 2.0;

        // Exercise
        double result = physics.verticalConstantVelocity(initialPosition, velocity, time);

        // Verify
        assertUnit(fabs(result - 0.0) < 0.001);
    }

    void testDistanceFormulaPositive()
    {
        // Setup
        Physics physics;
        double initialPosition = 0.0;
        double velocity = 5.0;
        double acceleration = 2.0;
        double time = 2.0;

        // Exercise
        double result = physics.distanceFormula(initialPosition, velocity, acceleration, time);

        // Verify
        assertUnit(fabs(result - 14.0) < 0.001);  // s = s0 + vt + (1/2)at^2
    }

    void testDistanceFormulaNegative()
    {
        // Setup
        Physics physics;
        double initialPosition = 20.0;
        double velocity = -5.0;
        double acceleration = -2.0;
        double time = 2.0;

        // Exercise
        double result = physics.distanceFormula(initialPosition, velocity, acceleration, time);

        // Verify
        assertUnit(fabs(result - 6.0) < 0.001);
    }

    void testRadiansFromDegrees()
    {
        // Setup
        Physics physics;
        double degrees = 180.0;

        // Exercise
        double result = physics.radiansFromDegrees(degrees);

        // Verify
        assertUnit(fabs(result - M_PI) < 0.001);
    }

    void testPhysicsConstants()
    {
        // Setup
        Physics physics;

        // Verify all constants
        assertUnit(physics.geoStationarySpeed == 3100);
        assertUnit(physics.earthRadiusMeters == 6378000.0);
        assertUnit(physics.geoStationaryOrbitHeightMeters == 42164000);
        assertUnit(physics.gravityOnEarth == -9.8067);
        assertUnit(physics.secondsPerFrame == 48);
    }
};

#endif /* testPhysics_h */