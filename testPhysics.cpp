#include "testPhysics.h"

constexpr double M_PI = 3.141592653589793;


void TestPhysics::testComputeDirection() {
    // Setup
    double x = 0.5;
    double y = 0.5;

    // Exercise
    double a = Physics().computeDirection(x, y);

    // Verify
    assertEquals(a, 0.78539816);
} // Teardown


void TestPhysics::testHeightAboveEarth() {

    // Setup
    double expectedHeight = 3211711.57022;
    double earthHeight = Physics().earthRadiusMeters;

    // Exercise
    double height = Physics().heightAbovePlanet(6578000, 6978000, earthHeight);

    // Verify
    assertEquals(height, expectedHeight);
} // Teardown


void TestPhysics::testComputeGravity() {
    Physics p;
    double gravity = p.gravityEquation(35786000, p.earthRadiusMeters, p.gravityOnEarth);

    assertEquals(gravity, -0.2244);
}


void TestPhysics::testHorizontalComponent() {
    // Setup
    double angle = 30.0 * M_PI / 180.0;

    // Exercise
    double hC = Physics().horizontalAcceleration(100.0, angle);

    // Verify
    assertEquals(hC, 50.0);
}


void TestPhysics::testVerticalComponent() {
    // Setup
    double angle = 30.0 * M_PI / 180.0;

    // Exercise
    double vC = Physics().verticalAcceleration(100.0, angle);

    // Verify
    assertEquals(vC, 86.6025);
}


void TestPhysics::testComputeDistance() {
    double s = 20.0;
    double v = 8.0;
    double a = 3.2;
    double t = 4.0;
    double distance = Physics().distanceFormula(s, v, a, t);
    assertEquals(distance, 77.6);
}


void TestPhysics::testVelocity() {
    double v = -5.0;
    double a = -1.2;
    double t = 2.0;
    double velocity = Physics().velocityConstantAcceleration(v, a, t);
    assertEquals(velocity, -7.4);
}

