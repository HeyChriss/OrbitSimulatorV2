#include "testAngle.h"

void TestAngle::testNormalize()
{
    // Setup
    double pi = Angle().pi;
    Angle a(Angle().fullRevolutionRad * 34 + pi);

    // Exercise
    a.normalize();


    // Verify
    assertEquals(a.getRadian(), pi);
} // Teardown


void TestAngle::testConstructor()
{
    // Setup
    Angle a = Angle();

    // Exercise
    double degrees = a.getDegree();
    double radians = a.getRadian();

    // Verify
    assertUnit(degrees == 0.0);
    assertUnit(radians == 0.0);
} // Teardown



void TestAngle::testNormalizeEdgeCases()
{
    // Setup
    double fullRevolution = Angle().fullRevolutionRad;
    Angle a1(fullRevolution);
    Angle a2(-fullRevolution);
    Angle a3(0);

    // Exercise
    a1.normalize();
    a2.normalize();
    a3.normalize();

    // Verify
    assertEquals(a1.getRadian(), 0.0);
    assertEquals(a2.getRadian(), 0.0);
    assertEquals(a3.getRadian(), 0.0);
}


void TestAngle::testDegreeConversion()
{
    // Setup
    Angle a;

    // Exercise
    a.setDegree(180);
    double rad = a.getRadian();
    double deg = a.getDegree();

    // Verify
    assertEquals(rad, Angle().pi);
    assertEquals(deg, 180.0);
}


void TestAngle::testAdditionOperator()
{
    // Setup
    Angle a(Angle().pi / 2); // 90 degrees
    Angle b(Angle().pi);     // 180 degrees

    // Exercise
    a += b;

    // Verify
    assertEquals(a.getDegree(), 270.0);
}

void TestAngle::testMultiplicationOperator()
{
    // Setup
    Angle a(Angle().pi); // 180 degrees

    // Exercise
    a *= 0.5;

    // Verify
    assertEquals(a.getDegree(), 90.0);
}

void TestAngle::testEqualityOperator()
{
    // Setup
    Angle a(Angle().pi); // 180 degrees
    Angle b(3 * Angle().pi); // 540 degrees, normalized to 180 degrees

    // Exercise and Verify
    assertUnit(a == b);
}


void TestAngle::testChainedOperations()
{
    // Setup
    Angle a(Angle().pi / 2); // 90 degrees

    // Exercise
    a += Angle(Angle().pi); // Add 180 degrees
    a *= 2;                 // Scale by 2

    // Verify
    assertEquals(a.getDegree(), 180.0); // Normalized value
}





