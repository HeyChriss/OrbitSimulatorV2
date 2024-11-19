/***********************************************************************
 * Header File:
 *    TEST SATELLITE
 * Author:
 *    <your name here>
 * Summary:
 *    A friend class for Satellite which contains the Satellite unit tests
 ************************************************************************/

#pragma once

#include "satellite.h"
#include "unitTest.h"
#define TEST

using namespace std;

 /***************************************************
  * TEST SATELLITE
  * A friend class for Satellite which contains the Satellite unit tests
  ***************************************************/
class TestSatellite : public UnitTest
{
public:
    void run()
    {
        defaultConstructor();
        constructor_stationaryNorth();
        constructor_stationarySouth();
        constructor_stationaryEast();
        constructor_stationaryWest();
        constructor_upNorth();
        constructor_upEast();
        constructor_rightNorth();

        move_stationaryNorth();
        move_stationaryNorthSpin();
        move_stationaryEast();
        move_upNorth();
        move_upEast();
        move_rightNorth();

        report("Satellite");
    }

private:

    // Helper Macros
    #define assertEqualsTolerance(value, test, tol) \
        assertUnitParameters((std::abs((value) - (test)) <= (tol)), #test, __LINE__, __FUNCTION__)

    #define assertInRange(value, min, max) \
        assertUnitParameters(((value) >= (min) && (value) <= (max)), #value " out of range", __LINE__, __FUNCTION__)

    #define assertGreaterThan(value, threshold) \
    assertUnitParameters((value) > (threshold), #value " is not greater than " #threshold, __LINE__, __FUNCTION__)


    // Helper Function
    bool isCloseEnough(double value, double test, double tolerance) const
    {
        return std::abs(value - test) <= tolerance;
    }

    // default constructor
    void defaultConstructor()
    {  // Setup
       // Exercise
        Satellite s;
        // Verify
        assertEquals(s.velocity.dx, 0.0);
        assertEquals(s.velocity.dy, 0.0);
        assertEquals(s.pos.x, 0.0);
        assertEquals(s.pos.y, 0.0);
        assertEquals(s.angle.radians, 0.0);
        assertEquals(s.angularVelocity, 0.0);
        assertEquals(s.dead, false);
        assertEquals(s.radius, 0.0);
        assertEquals(s.age, 0);
    }  // Teardown

// initially not moving but receive a kick in the northern direction
    void constructor_stationaryNorth()
    {  // Setup
        Satellite sParent;
        sParent.pos.x = 51200000.0;   // 4000 px
        sParent.pos.y = 64000000.0;   // 5000 px
        sParent.velocity.dx = 0.0;    // stationary
        sParent.velocity.dy = 0.0;
        Angle direction;
        direction.setDegrees(0.0);  // Up = 0 degrees
        // Exercise
        Satellite s(sParent, direction);
        // Verify
        assertEqualsTolerance(0.0, s.velocity.dx, 250.0);    // small deviation 250
        assertEqualsTolerance(2000.0, s.velocity.dy, 1200.0); // 1,000 <= v <= 3,000
        assertEqualsTolerance(51200000.0, s.pos.x, 51200.0); // 4x128000.0 51200.0
        assertEqualsTolerance(64000000.0, s.pos.y, 51200.0); // 512000.0
        assertEquals(s.angle.radians, 0.0);
        assertEquals(s.angularVelocity, 0.0);
        assertEquals(s.dead, false);
        assertEquals(s.radius, 0.0);
        assertEquals(s.age, 0);
    }

    // initially not moving but receive a kick in the south direction
    void constructor_stationarySouth()
    {  // Setup
        Satellite sParent;
        sParent.pos.x = 51200000.0;   // 4000 px
        sParent.pos.y = 64000000.0;   // 5000 px
        sParent.velocity.dx = 0.0;     // stationary
        sParent.velocity.dy = 0.0;
        Angle direction;
        direction.setDegrees(180.0);  // Down = 180 degrees
        // Exercise
        Satellite s(sParent, direction);
        // Verify
        assertEqualsTolerance(0.0, s.velocity.dx, 250.0);     // small deviation
        assertEqualsTolerance(-2000.0, s.velocity.dy, 1200.0); // -3,000 <= v <= -1,000
        assertEqualsTolerance(51200000.0, s.pos.x, 51200.0);
        assertEqualsTolerance(64000000.0, s.pos.y, 51200.0);
        assertEquals(s.angle.radians, 0.0);
        assertEquals(s.angularVelocity, 0.0);
        assertEquals(s.dead, false);
        assertEquals(s.radius, 0.0);
        assertEquals(s.age, 0);
    }

    // initially not moving but receive a kick in the east direction
    void constructor_stationaryEast()
    {  // Setup
        Satellite sParent;
        sParent.pos.x = 51200000.0;   // 4000 px
        sParent.pos.y = 64000000.0;   // 5000 px
        sParent.velocity.dx = 0.0;     // stationary
        sParent.velocity.dy = 0.0;
        Angle direction;
        direction.setDegrees(90.0);   // West = 270 degrees
        // Exercise
        Satellite s(sParent, direction);
        // Verify
        assertEqualsTolerance(2000.0, s.velocity.dx, 1200.0); // 1,000 <= v <= 3,000
        assertEqualsTolerance(0.0, s.velocity.dy, 250.0);    // small deviation
        assertEqualsTolerance(51200000.0, s.pos.x, 51200.0); // 4x128000.0
        assertEqualsTolerance(64000000.0, s.pos.y, 51200.0);
        assertEquals(s.angle.radians, 0.0);
        assertEquals(s.angularVelocity, 0.0);
        assertEquals(s.dead, false);
        assertEquals(s.radius, 0.0);
        assertEquals(s.age, 0);
    }  // Teardown

    void constructor_stationaryWest()
    {  // Setup
        Satellite sParent;
        sParent.pos.x = 51200000.0;   // 4000 px
        sParent.pos.y = 64000000.0;   // 5000 px
        sParent.velocity.dx = 0.0;     // stationary
        sParent.velocity.dy = 0.0;
        Angle direction;
        direction.setDegrees(270.0);   // West = 270 degrees
        // Exercise
        Satellite s(sParent, direction);
        // Verify
        assertEqualsTolerance(-2000.0, s.velocity.dx, 1200.0); // -3,000 <= v <= -1,000
        assertEqualsTolerance(0.0, s.velocity.dy, 250.0);      // small deviation
        assertEqualsTolerance(51200000.0, s.pos.x, 51200.0);  // 4x128000.0
        assertEqualsTolerance(64000000.0, s.pos.y, 51200.0);
        assertEquals(s.angle.radians, 0.0);
        assertEquals(s.angularVelocity, 0.0);
        assertEquals(s.dead, false);
        assertEquals(s.radius, 0.0);
        assertEquals(s.age, 0);
    }

    // Constructor tests for satellites receiving kicks
    void constructor_upNorth()
    {  // Setup
        Satellite sParent;
        sParent.pos.x = 512000000.0;       // 4000 px
        sParent.pos.y = 640000000.0;       // 5000 px
        sParent.velocity.dx = 0.0;
        sParent.velocity.dy = 10000.0;     // moving up
        Angle direction;
        direction.setDegrees(0.0);   
        // Exercise
        Satellite s(sParent, direction);
        // Verify
        assertEqualsTolerance(0.0, s.velocity.dx, 250.0);         // small deviation
        assertEqualsTolerance(12000.0, s.velocity.dy, 1200.0);    // 11,000 <= v <= 13,000
        assertEqualsTolerance(512000000.0, s.pos.x, 512000.0);    // 4x128000.0
        assertEqualsTolerance(640000000.0, s.pos.y, 512000.0);
        assertEquals(s.angle.radians, 0.0);
        assertEquals(s.angularVelocity, 0.0);
        assertEquals(s.dead, false);
        assertEquals(s.radius, 0.0);
        assertEquals(s.age, 0);
    }

    void constructor_upEast()
    {  // Setup
        Satellite sParent;
        sParent.pos.x = 512000000.0;       // 4000 px
        sParent.pos.y = 640000000.0;       // 5000 px
        sParent.velocity.dx = 0.0;
        sParent.velocity.dy = 10000.0;     // moving up
        Angle direction;
        direction.setDegrees(90.0);
        // Exercise
        Satellite s(sParent, direction);
        // Verify
        assertEqualsTolerance(2000.0, s.velocity.dx, 1200.0);     // 1,000 <= v <= 3,000
        assertEqualsTolerance(10000.0, s.velocity.dy, 250.0);     // small deviation
        assertEqualsTolerance(512000000.0, s.pos.x, 512000.0);    // 4x128000.0
        assertEqualsTolerance(640000000.0, s.pos.y, 512000.0);
        assertEquals(s.angle.radians, 0.0);
        assertEquals(s.angularVelocity, 0.0);
        assertEquals(s.dead, false);
        assertEquals(s.radius, 0.0);
        assertEquals(s.age, 0);
    }

    void constructor_rightNorth()
    {  // Setup
        Satellite sParent;
        sParent.pos.x = 512000000.0;       // 4000 px
        sParent.pos.y = 640000000.0;       // 5000 px
        sParent.velocity.dx = 10000.0;     // moving right
        sParent.velocity.dy = 0.0;
        Angle direction;
        direction.setDegrees(0.0);
        // Exercise
        Satellite s(sParent, direction);
        // Verify
        assertEqualsTolerance(10000.0, s.velocity.dx, 250.0);     // small kick
        assertEqualsTolerance(2000.0, s.velocity.dy, 1200.0);     // 1,000 <= v <= 3,000
        assertEqualsTolerance(512000000.0, s.pos.x, 512000.0);    // 4x128000.0
        assertEqualsTolerance(640000000.0, s.pos.y, 512000.0);
        assertEquals(s.angle.radians, 0.0);
        assertEquals(s.angularVelocity, 0.0);
        assertEquals(s.dead, false);
        assertEquals(s.radius, 0.0);
        assertEquals(s.age, 0);
    }

    void move_stationaryNorth()
    {  // Setup
        Satellite s;
        s.pos.x = 0.0;
        s.pos.y = 6378000.0;       // radius of the earth
        s.velocity.dx = 0.0;
        s.velocity.dy = 0.0;
        s.angle.radians = 1.234;
        s.angularVelocity = 0.0;
        s.dead = false;
        s.radius = 0.0;
        s.age = 100;
        // Exercise
        s.move(1.0);
        // Verify
        assertEqualsTolerance(0.0, s.velocity.dx, 0.01);           // no horizontal movement
        assertEqualsTolerance(-9.806, s.velocity.dy, 0.01);        // should fall towards earth
        assertEqualsTolerance(0.0, s.pos.x, 0.01);                 // no horizontal movement
        assertEqualsTolerance(6378000.0 - 9.806, s.pos.y, 0.01);   // should fall towards earth
        assertEquals(s.angle.radians, 1.234);                       // no rotation
        assertEquals(s.age, 101);                                   // aged by 1 second
        assertEquals(s.angularVelocity, 0.0);
        assertEquals(s.dead, false);
        assertEquals(s.radius, 0.0);
    }

    // Initially stationary and above the earth but with a spin
    void move_stationaryNorthSpin()
    {  // Setup
        Satellite s;
        s.pos.x = 0.0;
        s.pos.y = 6378000.0;       // radius of the earth
        s.velocity.dx = 0.0;
        s.velocity.dy = 0.0;
        s.angle.radians = 1.234;
        s.angularVelocity = 0.5;    // huge rotation
        s.dead = false;
        s.radius = 0.0;
        s.age = 100;
        // Exercise
        s.move(1.0);
        // Verify
        assertEqualsTolerance(0.0, s.velocity.dx, 0.01);           // no horizontal movement
        assertEqualsTolerance(-9.806, s.velocity.dy, 0.01);        // should fall towards earth
        assertEqualsTolerance(0.0, s.pos.x, 0.01);                 // no horizontal movement
        assertEqualsTolerance(6378000.0 - 9.806, s.pos.y, 0.01);   // should fall towards earth
        assertEquals(s.angle.radians, 1.734);                       // rotate by .5 radians
        assertEquals(s.age, 101);                                   // aged by 1 second
        assertEquals(s.angularVelocity, 0.5);
        assertEquals(s.dead, false);
        assertEquals(s.radius, 0.0);
    }

    // Initially stationary and to the right of the earth
    void move_stationaryEast()
    {  // Setup
        Satellite s;
        s.pos.x = 6378000.0;       // radius of the earth
        s.pos.y = 0.0;
        s.velocity.dx = 0.0;
        s.velocity.dy = 0.0;
        s.angle.radians = 1.234;
        s.angularVelocity = 0.0;
        s.dead = false;
        s.radius = 0.0;
        s.age = 100;
        // Exercise
        s.move(1.0);
        // Verify
        assertEqualsTolerance(-9.806, s.velocity.dx, 0.01);        // should fall towards earth
        assertEqualsTolerance(0.0, s.velocity.dy, 0.01);           // no vertical movement
        assertEqualsTolerance(6378000.0 - 9.806, s.pos.x, 0.01);   // should fall towards earth
        assertEqualsTolerance(0.0, s.pos.y, 0.01);                 // no vertical movement
        assertEquals(s.angle.radians, 1.234);                       // no rotation
        assertEquals(s.age, 101);                                   // aged by 1 second
    }

    // Moving up (north) when to the north (above) the earth
    void move_upNorth()
    {  // Setup
        Satellite s;
        s.pos.x = 0.0;
        s.pos.y = 6378000.0;       // to the north radius of the earth
        s.velocity.dx = 0.0;
        s.velocity.dy = 100.0;      // moving up
        s.angle.radians = 1.234;
        s.angularVelocity = 0.0;
        s.dead = false;
        s.radius = 0.0;
        s.age = 100;
        // Exercise
        s.move(1.0);
        // Verify
        assertEqualsTolerance(0.0, s.velocity.dx, 0.01);                      // no horizontal movement
        assertEqualsTolerance(100.0 - 9.806, s.velocity.dy, 0.01);           // should slow down due to gravity
        assertEqualsTolerance(0.0, s.pos.x, 0.01);                           // no horizontal movement
        assertEqualsTolerance(6378000.00 + 100.0 - 9.806, s.pos.y, 0.01);   // should move up less due to gravity
        assertEquals(s.angle.radians, 1.234);                                 // no rotation
        assertEquals(s.age, 101);                                             // aged by 1 second
        assertEquals(s.angularVelocity, 0.0);
        assertEquals(s.dead, false);
        assertEquals(s.radius, 0.0);
    }

    // Moving up (north) when to the east (right) the earth
    void move_upEast()
    {  // Setup
        Satellite s;
        s.pos.x = 6378000.00;      // to the east radius of the earth
        s.pos.y = 0.0;
        s.velocity.dx = 0.0;
        s.velocity.dy = 100.0;      // moving up
        s.angle.radians = 1.234;
        s.angularVelocity = 0.0;
        s.dead = false;
        s.radius = 0.0;
        s.age = 100;
        // Exercise
        s.move(1.0);
        // Verify
        assertEqualsTolerance(-9.806, s.velocity.dx, 0.01);        // should fall towards earth
        assertEqualsTolerance(100.0, s.velocity.dy, 0.01);         // move vertically due to thrust
        assertEqualsTolerance(6378000.0 - 9.806, s.pos.x, 0.01);   // fell a tiny bit due to gravity
        assertEqualsTolerance(100.0, s.pos.y, 0.01);               // moved quite a bit due to thrust
        assertEquals(s.angle.radians, 1.234);                       // no rotation
        assertEquals(s.age, 101);                                   // aged by 1 second
        assertEquals(s.angularVelocity, 0.0);
        assertEquals(s.dead, false);
        assertEquals(s.radius, 0.0);
    }

    void move_rightNorth()
    {  // Setup
        Satellite s;
        s.pos.x = 0.0;
        s.pos.y = 6378000.0;       // to the north radius of the earth
        s.velocity.dx = 100.0;      // moving to the east
        s.velocity.dy = 0.0;
        s.angle.radians = 1.234;
        s.angularVelocity = 0.0;
        s.dead = false;
        s.radius = 0.0;
        s.age = 100;
        // Exercise
        s.move(1.0);
        // Verify
        assertEqualsTolerance(100.0, s.velocity.dx, 0.01);         // move horizontally
        assertEqualsTolerance(-9.806, s.velocity.dy, 0.01);        // should fall towards earth
        assertEqualsTolerance(100.0, s.pos.x, 0.01);              // moved quite a bit horizontally
        assertEqualsTolerance(6378000.0 - 9.806, s.pos.y, 0.01);  // fell a tiny bit due to gravity
        assertEquals(s.angle.radians, 1.234);                      // no rotation
        assertEquals(s.age, 101);                                  // aged by 1 second
        assertEquals(s.angularVelocity, 0.0);
        assertEquals(s.dead, false);
        assertEquals(s.radius, 0.0);
    }
};

