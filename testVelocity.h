/***********************************************************************
 * Header File:
 *    TEST VELOCITY
 * Author:
 *    <your name here>
 * Summary:
 *    Unit tests for the Velocity class.
 ************************************************************************/

#pragma once

#include "unitTest.h"
#include "velocity.h"
#include <cmath>
#define M_PI 3.14159265358979323846 // Define pi
#define M_PI_2 (M_PI / 2)           // Define pi/2

/*********************************************
 * TEST VELOCITY
 * Unit tests for Velocity
 *********************************************/
class TestVelocity : public UnitTest
{
public:
   void run()
   {
      // Ticket 5: From before
      constructor_default();
      constructor_nonDefault();
      getDX();
      getDY();
      getSpeed_up();
      getSpeed_down();
      getSpeed_left();
      getSpeed_right();
      getSpeed_diagonal();
      setDX();
      setDY();
      set_up();
      set_down();
      set_left();
      set_right();
      set_diagonal();
      addDX_zero();
      addDX_value();
      addDY_zero();
      addDY_value();
      add_stationary();
      add_noTime();
      add_moving4Seconds();
      add_moving1Second();

      // Ticket 6: Reverse and add
      reverse_stationary();
      reverse_up();
      reverse_down();
      reverse_left();
      reverse_right();
      reverse_diagonal();
      addV_stationary();
      addV_nothing();
      addV_moving();

      report("Velocity");
   }

private:

   /*****************************************************************
    *****************************************************************
    * CONSTRUCTOR
    *****************************************************************
    *****************************************************************/
   
   
   /*********************************************
    * name:    DEFAULT CONSTRUCTOR
    * input:   nothing
    * output:  zero
    *********************************************/
   void constructor_default()
   {  // setup
      // exercise
      Velocity v;

      // verify
      assertEquals(v.dx, 0.0);
      assertEquals(v.dy, 0.0);
   }  // teardown
      
   /*********************************************
    * name:    NON DEFAULT CONSTRUCTOR
    * input:   2.3, 4.5
    * output:  (2.3, 4.5)
    *********************************************/
   void constructor_nonDefault()
   {  // setup
      double dx = 2.3;
      double dy = 4.5;
      
      // exercise
      Velocity v(dx, dy);

      // verify
      assertEquals(v.dx, 2.3);
      assertEquals(v.dy, 4.5);
      assertEquals(dx, 2.3);
      assertEquals(dy, 4.5);
   }  // teardown

   /*****************************************************************
    *****************************************************************
    * GETTERS
    *****************************************************************
    *****************************************************************/

   /*********************************************
    * name:    GET DX
    * input:   (2.3, 4.5)
    * output:  2.3
    *********************************************/
   void getDX()
   {  // setup
      Velocity v;
      v.dx = 2.3;
      v.dy = 4.5;
      double dx = 99.9;

      // exercise
      dx = v.getDX();

      // verify
      assertEquals(v.dx, 2.3);
      assertEquals(v.dy, 4.5);
      assertEquals(dx, 2.3);
   }  // teardown

   /*********************************************
    * name:    GET DY
    * input:   (2.3, 4.5)
    * output:  4.5
    *********************************************/
   void getDY()
   {  // setup
      Velocity v;
      v.dx = 2.3;
      v.dy = 4.5;
      double dy = 99.9;

      // exercise
      dy = v.getDY();

      // verify
      assertEquals(v.dx, 2.3);
      assertEquals(v.dy, 4.5);
      assertEquals(dy, 4.5);
   }  // teardown
   
   /*********************************************
    * name:    GET SPEED ZERO
    * input:   (0.0, 0.0)
    * output:  0.0
    *********************************************/
   void getSpeed_zero()
   {  // setup
      Velocity v;
      v.dx = 0.0;
      v.dy = 0.0;
      double s = 99.9;

      // exercise
      s = v.getSpeed();

      // verify
      assertEquals(v.dx, 0.0);
      assertEquals(v.dy, 0.0);
      assertEquals(s, 0.0);
   }  // teardown
   
   /*********************************************
    * name:    GET SPEED RIGHT
    * input:   (2.3, 0.0)
    * output:  2.3
    *********************************************/
   void getSpeed_right()
   {  // setup
      Velocity v;
      v.dx = 2.3;
      v.dy = 0.0;
      double s = 99.9;

      // exercise
      s = v.getSpeed();

      // verify
      assertEquals(v.dx, 2.3);
      assertEquals(v.dy, 0.0);
      assertEquals(s, 2.3);
   }  // teardown

   /*********************************************
    * name:    GET SPEED UP
    * input:   (0.0, 4.5)
    * output:  4.5
    *********************************************/
   void getSpeed_up()
   {  // setup
      Velocity v;
      v.dx = 0.0;
      v.dy = 4.5;
      double s = 99.9;

      // exercise
      s = v.getSpeed();

      // verify
      assertEquals(v.dx, 0.0);
      assertEquals(v.dy, 4.5);
      assertEquals(s, 4.5);
   }  // teardown
   
   /*********************************************
    * name:    GET SPEED LEFT
    * input:   (-2.3, 0.0)
    * output:  2.3
    *********************************************/
   void getSpeed_left()
   {  // setup
      Velocity v;
      v.dx = -2.3;
      v.dy = 0.0;
      double s = 99.9;

      // exercise
      s = v.getSpeed();

      // verify
      assertEquals(v.dx, -2.3);
      assertEquals(v.dy, 0.0);
      assertEquals(s, 2.3);
   }  // teardown

   /*********************************************
    * name:    GET SPEED DOWN
    * input:   (0.0, -4.5)
    * output:  4.5
    *********************************************/
   void getSpeed_down()
   {  // setup
      Velocity v;
      v.dx = 0.0;
      v.dy = -4.5;
      double s = 99.9;

      // exercise
      s = v.getSpeed();

      // verify
      assertEquals(v.dx, 0.0);
      assertEquals(v.dy, -4.5);
      assertEquals(s, 4.5);
   }  // teardown
   
   /*********************************************
    * name:    GET SPEED DIAGONAL
    * input:   (3.0, -4.0)
    * output:  5.0
    *********************************************/
   void getSpeed_diagonal()
   {  // setup
      Velocity v;
      v.dx = 3.0;
      v.dy = -4.0;
      double s = 99.9;

      // exercise
      s = v.getSpeed();

      // verify
      assertEquals(v.dx, 3.0);
      assertEquals(v.dy, -4.0);
      assertEquals(s, 5.0);
   }  // teardown
   
   /*****************************************************************
    *****************************************************************
    * SETTERS
    *****************************************************************
    *****************************************************************/
   
   /*********************************************
    * name:    SET DX
    * input:   (99.9, 88.8) -1.1
    * output:  (-1.1, 88.8)
    *********************************************/
   void setDX()
   {  // setup
      Velocity v;
      v.dx = 99.9;
      v.dy = 88.8;
      double dx = -1.1;

      // exercise
      v.setDX(dx);

      // verify
      assertEquals(v.dx, -1.1);
      assertEquals(v.dy, 88.8);
      assertEquals(dx, -1.1);
   }  // teardown

   /*********************************************
    * name:    SET DY
    * input:   (99.9, 88.8) -1.1
    * output:  (99.9, -1.1)
    *********************************************/
   void setDY()
   {  // setup
      Velocity v;
      v.dx = 99.9;
      v.dy = 88.8;
      double dy = -1.1;

      // exercise
      v.setDY(dy);

      // verify
      assertEquals(v.dx, 99.9);
      assertEquals(v.dy, -1.1);
      assertEquals(dy, -1.1);
   }  // teardown
   
   /*********************************************
    * name:    SET UP
    * input:   (-99.9, -88.8) 0 degreess, 3.3
    * output:  (0.0, 3.3)
    *********************************************/
   void set_up()
   {  // setup
      Velocity v;
      v.dx = -99.9;
      v.dy = -88.8;
      Angle angle;
      angle.radians = 0.0; // up
      double magnitude = 3.3;

      // exercise
      v.set(angle, magnitude);

      // verify
      assertEquals(v.dx, 0.0);
      assertEquals(v.dy, 3.3);
      assertEquals(angle.radians, 0.0);
      assertEquals(magnitude, 3.3);
   }
   
   /*********************************************
    * name:    SET DOWN
    * input:   (-99.9, -88.8) 180 degreess, 3.3
    * output:  (0.0, -3.3)
    *********************************************/
   void set_down()
   {  // setup
      Velocity v;
      v.dx = -99.9;
      v.dy = -88.8;
      Angle angle;
      angle.radians = M_PI; // DOWN
      double magnitude = 3.3;

      // exercise
      v.set(angle, magnitude);

      // verify
      assertEquals(v.dx, 0.0);
      assertEquals(v.dy, -3.3);
      assertEquals(angle.radians, M_PI);
      assertEquals(magnitude, 3.3);
   }

   /*********************************************
    * name:    SET RIGHT
    * input:   (-99.9, -88.8) 90 degreess, 3.3
    * output:  (3.3, 0.0)
    *********************************************/
   void set_right()
   {  // setup
      Velocity v;
      v.dx = -99.9;
      v.dy = -88.8;
      Angle angle;
      angle.radians = M_PI_2; // RIGHT
      double magnitude = 3.3;

      // exercise
      v.set(angle, magnitude);

      // verify
      assertEquals(v.dx, 3.3);
      assertEquals(v.dy, 0.0);
      assertEquals(angle.radians, M_PI_2);
      assertEquals(magnitude, 3.3);
   }
   
   /*********************************************
    * name:    SET LEFT
    * input:   (-99.9, -88.8) 270 degreess, 3.3
    * output:  (-3.3, 0.0)
    *********************************************/
   void set_left()
   {  // setup
      Velocity v;
      v.dx = -99.9;
      v.dy = -88.8;
      Angle angle;
      angle.radians = M_PI_2 + M_PI; // LEFT
      double magnitude = 3.3;

      // exercise
      v.set(angle, magnitude);

      // verify
      assertEquals(v.dx, -3.3);
      assertEquals(v.dy, 0.0);
      assertEquals(angle.radians, M_PI_2 + M_PI);
      assertEquals(magnitude, 3.3);
   }
   
   /*********************************************
    * name:    SET DIAGONAL
    * input:   (-99.9, -88.8) ~57 degreess, 1.0
    * output:  (0.84, 0.54)
    *********************************************/
   void set_diagonal()
   {  // setup
      Velocity v;
      v.dx = -99.9;
      v.dy = -88.8;
      Angle angle;
      angle.radians = 1.0; // up and right somewhat
      double magnitude = 1.0;

      // exercise
      v.set(angle, magnitude);

      // verify
      assertEquals(v.dx, 0.8414);
      assertEquals(v.dy, 0.5403);
      assertEquals(angle.radians, 1.0);
      assertEquals(magnitude, 1.0);
   }
   
   /*********************************************
    * name:    REVERSE STATIONARY
    * input:   (0, 0)
    * output:  (0, 0)
    *********************************************/
   void reverse_stationary()
   {
       Velocity v(0,0);
       v.reverse();
       assertEquals(v.getDX(), 0);
       assertEquals(v.getDY(), 0);
   }

   /*********************************************
    * name:    REVERSE UP
    * input:   (0,  10)
    * output:  (0, -10)
    *********************************************/
   void reverse_up()
   {
       Velocity v(0, 10);
       v.reverse();
       assertEquals(v.getDX(), 0);
       assertEquals(v.getDY(), -10);
   }

   /*********************************************
    * name:    REVERSE DOWN
    * input:   (0, -12.34)
    * output:  (0,  12.34)
    *********************************************/
   void reverse_down()
   {
       Velocity v(0, -12.34);
       v.reverse();
       assertEquals(v.getDX(), 0);
       assertEquals(v.getDY(), 12.34);
   }

   /*********************************************
    * name:    REVERSE LEFT
    * input:   (-300, 0)
    * output:  ( 300, 0)
    *********************************************/
   void reverse_left()
   {
       Velocity v(-300, 0);
       v.reverse();
       assertEquals(v.getDX(), 300);
       assertEquals(v.getDY(), 0);
   }

   /*********************************************
    * name:    REVERSE RIGHT
    * input:   ( 0.0123, 0)
    * output:  (-0.0123, 0)
    *********************************************/
   void reverse_right()
   {
       Velocity v(0.0123, 0);
       v.reverse();
       assertEquals(v.getDX(), -0.0123);
       assertEquals(v.getDY(), 0);
   }

   /*********************************************
    * name:    REVERSE DIAGONAL
    * input:   ( 123.456, -7.89)
    * output:  (-123.456,  7.89)
    *********************************************/
   void reverse_diagonal()
   {
       Velocity v(123.456, -7.89);
       v.reverse();
       assertEquals(v.getDX(), -123.456);
       assertEquals(v.getDY(), 7.89);
   }

   /*****************************************************************
    *****************************************************************
    * ADD
    *****************************************************************
    *****************************************************************/
   
   /*********************************************
    * name:    ADD DX  zero
    * input:   (2.3, 4.5) 0.0
    * output:  (2.3, 4.5)
    *********************************************/
   void addDX_zero()
   {  // setup
      Velocity v;
      v.dx = 2.3;
      v.dy = 4.5;
      double dx = 0.0;

      // exercise
      v.addDX(dx);

      // verify
      assertEquals(v.dx, 2.3);
      assertEquals(v.dy, 4.5);
      assertEquals(dx, 0.0);
   }  // teardown

   /*********************************************
    * name:    ADD DX  VALUE
    * input:   (2.3, 4.5) 4.1
    * output:  (6.4, 4.5)
    *********************************************/
   void addDX_value()
   {  // setup
      Velocity v;
      v.dx = 2.3;
      v.dy = 4.5;
      double dx = 4.1;

      // exercise
      v.addDX(dx);

      // verify
      assertEquals(v.dx, 6.4);
      assertEquals(v.dy, 4.5);
      assertEquals(dx,  4.1);
   }  // teardown

   /*********************************************
    * name:    ADD DY  zero
    * input:   (2.3, 4.5) 0.0
    * output:  (2.3, 4.5)
    *********************************************/
   void addDY_zero()
   {  // setup
      Velocity v;
      v.dx = 2.3;
      v.dy = 4.5;
      double dy = 0.0;

      // exercise
      v.addDY(dy);

      // verify
      assertEquals(v.dx, 2.3);
      assertEquals(v.dy, 4.5);
      assertEquals(dy, 0.0);
   }  // teardown

   /*********************************************
    * name:    ADD DY  VALUE
    * input:   (2.3, 4.5) 4.1
    * output:  (2.3, 8.6)
    *********************************************/
   void addDY_value()
   {  // setup
      Velocity v;
      v.dx = 2.3;
      v.dy = 4.5;
      double dy = 4.1;

      // exercise
      v.addDY(dy);

      // verify
      assertEquals(v.dx, 2.3);
      assertEquals(v.dy, 8.6);
      assertEquals(dy, 4.1);
   }  // teardown

   /*********************************************
    * name:    ADD  STATIONARY
    * input:   v=(2.3, 4.5) a=(0.0, 0.0) t=0.0
    * output:  (2.3, 4.5)
    *********************************************/
   void add_stationary()
   {  // setup
      Velocity v;
      v.dx = 2.3;
      v.dy = 4.5;
      Acceleration a;
      a.ddx = 0.0;
      a.ddy = 0.0;
      double t = 0.0;

      // exercise
      v.add(a, t);

      // verify
      assertEquals(v.dx, 2.3);
      assertEquals(v.dy, 4.5);
      assertEquals(a.ddx, 0.0);
      assertEquals(a.ddy, 0.0);
      assertEquals(t, 0.0);
   }  // teardown

   /*********************************************
    * name:    ADD  TIME IS ZERO
    * input:   v=(2.3, 4.5) a=(6.0, 7.0) t=0.0
    * output:  (2.3, 4.5)
    *********************************************/
   void add_noTime()
   {  // setup
      Velocity v;
      v.dx = 2.3;
      v.dy = 4.5;
      Acceleration a;
      a.ddx = 6.0;
      a.ddy = 7.0;
      double t = 0.0;

      // exercise
      v.add(a, t);

      // verify
      assertEquals(v.dx, 2.3);
      assertEquals(v.dy, 4.5);
      assertEquals(a.ddx, 6.0);
      assertEquals(a.ddy, 7.0);
      assertEquals(t, 0.0);
   }  // teardown

   /*********************************************
    * name:    ADD  ONE SECOND
    * input:   v=(2.3, 4.5) a=(6.0, 7.0) t=1.0
    * output:  (8.3, 11.5)
    *********************************************/
   void add_moving1Second()
   {  // setup
      Velocity v;
      v.dx = 2.3;
      v.dy = 4.5;
      Acceleration a;
      a.ddx = 6.0;
      a.ddy = 7.0;
      double t = 1.0;

      // exercise
      v.add(a, t);

      // verify
      assertEquals(v.dx, 8.3);  // 2.3 + 6.0*1
      assertEquals(v.dy, 11.5); // 4.5 + 7.0*1
      assertEquals(a.ddx, 6.0);
      assertEquals(a.ddy, 7.0);
      assertEquals(t, 1.0);
   }  // teardown

   /*********************************************
    * name:    ADD  FOUR SECONDS
    * input:   v=(2.3, 4.5) a=(6.0, 7.0) t=4.0
    * output:  (14.3, 24.5)
    *********************************************/
   void add_moving4Seconds()
   {  // setup
      Velocity v;
      v.dx = 2.3;
      v.dy = 4.5;
      Acceleration a;
      a.ddx = 3.0;
      a.ddy = 5.0;
      double t = 4.0;

      // exercise
      v.add(a, t);

      // verify
      assertEquals(v.dx, 14.3); // 2.3 + 3.0*4
      assertEquals(v.dy, 24.5); // 4.5 + 5.0*4
      assertEquals(a.ddx, 3.0);
      assertEquals(a.ddy, 5.0);
      assertEquals(t, 4.0);
   }  // teardown

   /*********************************************
    * name:    ADD  STATIONARY
    * input:   vLHS=(0, 0) vRHS=(2.3, 4.5)
    * output:  vLHS=(2.3, 4.5)
    *********************************************/
   void addV_stationary()
   {
       Velocity LHS(0, 0);
       Velocity RHS(2.3, 4.5);
       LHS.add(RHS);
       assertEquals(LHS.getDX(), 2.3);
       assertEquals(LHS.getDY(), 4.5);
   }

   /*********************************************
    * name:    ADD  NOTHING
    * input:   vLHS=(2.3, 4.5) vRHS=(0, 0)
    * output:  vLHS=(2.3, 4.5)
    *********************************************/
   void addV_nothing()
   {
       Velocity LHS(2.3, 4.5);
       Velocity RHS(0, 0);
       LHS.add(RHS);
       assertEquals(LHS.getDX(), 2.3);
       assertEquals(LHS.getDY(), 4.5);
   }

   /*********************************************
    * name:    ADD  MOVING
    * input:   vLHS=(2.3, 4.5) vRHS=(100, 200)
    * output:  vLHS=(102.3, 204.5)
    *********************************************/
   void addV_moving()
   {
       Velocity LHS(2.3, 4.5);
       Velocity RHS(100, 200);
       LHS.add(RHS);
       assertEquals(LHS.getDX(), 102.3);
       assertEquals(LHS.getDY(), 204.5);
   }

};
