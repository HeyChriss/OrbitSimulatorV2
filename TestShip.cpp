/***********************************************************************
 * Source File:
 *    TEST SHIP
 * Author:
 *    Chris Mijango & Seth Chen
 * Summary:
 *    The test ship class
 ************************************************************************/

#include "TestShip.h"
#include "unitTest.h"

 /*********************************************
  * CONSTRUCTOR: default
  * Input:
  * Output:
  *********************************************/
void TestShip::constructor_default()
{
    // setup
    std::list<Satellite*> satellites;
    // exercise
    Ship s(satellites);

    // verify
    assertEquals(s.radius, 10.0);
    assertEquals(s.pos.x, -22500.0);
    assertEquals(s.pos.y, 22500.0);
    assertEquals(s.velocity.dx, 0.0);
    assertEquals(s.velocity.dy, -2000.0);
    assertEquals(s.angle.radians, 3.141592653589);
} // teardown

/*********************************************
 * MOVE: 1 second
 * Input:
 * Output:
 *********************************************/
void TestShip::move_oneSecond()
{
    // setup
    std::list<Satellite*> satellites;
    Ship s(satellites);

    // Exercise
    s.move(1.0);

    // Verify position has changed
    assertEquals(s.pos.x, 641869776.95774639);
    assertEquals(s.pos.y, -641965776.95774639);
    assertEquals(s.age, 1);
}

/*********************************************
 * MOVE: 10 seconds
 * Input:
 * Output:
 *********************************************/
void TestShip::move_tenSeconds()
{
    // setup
    std::list<Satellite*> satellites;
    Ship s(satellites);

    // Exercise
    for (int i = 0; i < 10; i++)
        s.move(1.0);

    // Verify position has changed
    assertEquals(s.pos.x, 6418900259.6663752);
    assertEquals(s.pos.y, -6419860259.6648922);
    assertEquals(s.age, 10);
}

/*********************************************
 * INPUT: right once
 * Input:
 * Output:
 *********************************************/
void TestShip::input_rightOnce()
{
    // setup
    FakeShip s;

    // exercise
    s.input(true, false, false, false);

    // verify
    assertEquals(s.angle.radians, M_PI + 0.1);
}

/*********************************************
 * INPUT: right ten times
 * Input:
 * Output:
 *********************************************/
void TestShip::input_rightTenTimes()
{
    // setup
    FakeShip s;

    // exercise
    for (int i = 0; i < 10; i++)
        s.input(true, false, false, false);

    // verify
    assertEquals(s.angle.radians, M_PI + 1.0);
}

/*********************************************
 * INPUT: left once
 * Input:
 * Output:
 *********************************************/
void TestShip::input_leftOnce()
{
    // setup
    FakeShip s;

    // exercise
    s.input(false, true, false, false);

    // verify
    assertEquals(s.angle.radians, M_PI - 0.1);
}

/*********************************************
 * INPUT: right ten times
 * Input:
 * Output:
 *********************************************/
void TestShip::input_leftTenTimes()
{
    // setup
    FakeShip s;

    // exercise
    for (int i = 0; i < 10; i++)
        s.input(false, true, false, false);

    // verify
    assertEquals(s.angle.radians, M_PI - 1.0);
}

/*********************************************
 * INPUT: no
 * Input:
 * Output:
 *********************************************/
void TestShip::input_noInput()
{
    // Setup
    FakeShip s;

    // Exercise


    // Verify
    assertEquals(s.pos.x, -22500.0);
    assertEquals(s.pos.y, 22500.0);
    assertEquals(s.angle.radians, M_PI);
    assertEquals(s.age, 0);
} // teardown

/*********************************************
 * INPUT: down once
 * Input:
 * Output:
 *********************************************/
void TestShip::input_downOnce()
{
    // Setup
    FakeShip s;

    // Exercise
    s.input(false, false, true, false);

    // Verify
    assertEquals(s.velocity.dx, 0.0);
    assertEquals(s.velocity.dy, -2096.0);
    assertEquals(s.pos.x, -22500.0);
    assertEquals(s.pos.y, -75852.0);
    assertEquals(s.angle.radians, M_PI);
    assertEquals(s.age, 0);
} // teardown

/*********************************************
 * INPUT: down ten times
 * Input:
 * Output:
 *********************************************/
void TestShip::input_downTenTimes()
{
    // Setup
    FakeShip s;

    // Exercise
    for (int i = 0; i < 10; i++)
        s.input(false, false, true, false);

    // Verify
    assertEquals(s.velocity.dx, 0.0);
    assertEquals(s.velocity.dy, -2960.0);
    assertEquals(s.pos.x, -22500.0);
    assertEquals(s.pos.y, -1168380.0);
    assertEquals(s.angle.radians, M_PI);
    assertEquals(s.age, 0);
} // teardown

/*********************************************
 * DRAW: visible
 * Input:
 * Output:
 *********************************************/
void TestShip::draw_visible()
{
    // setup
    std::list<Satellite*> satellites;
    Ship s(satellites);
    s.dead = false;
    MockOgstream gout;

    // Exercise
    s.draw(gout);

    // Verify
    assertEquals(gout.drawCalled, false);
}

/*********************************************
 * DRAW: invisible
 * Input:
 * Output:
 *********************************************/
void TestShip::draw_invisible()
{
    // setup
    std::list<Satellite*> satellites;
    Ship s(satellites);
    s.dead = false;
    s.age = 11;
    MockOgstream gout;

    // Exercise
    s.draw(gout);

    // Verify
    assertEquals(gout.drawCalled, true);
}

/*********************************************
 * DRAW: dead
 * Input:
 * Output:
 *********************************************/
void TestShip::draw_dead()
{
    // setup
    std::list<Satellite*> satellites;
    Ship s(satellites);
    s.dead = true;
    MockOgstream gout;

    // Exercise
    s.draw(gout);

    // Verify
    assertEquals(s.dead, true);
    assertEquals(gout.drawCalled, false);
}

/*********************************************
 * DRAW: not dead
 * Input:
 * Output:
 *********************************************/
void TestShip::draw_notDead()
{
    // setup
    std::list<Satellite*> satellites;
    Ship s(satellites);
    s.dead = false;
    MockOgstream gout;

    // Exercise
    s.draw(gout);

    // Verify
    assertEquals(s.dead, false);
    assertEquals(gout.drawCalled, false);
}

/*********************************************
 * GET DEFUNCT: dead
 * Input:
 * Output:
 *********************************************/
void TestShip::getDefunct_dead()
{
    // setup
    std::list<Satellite*> satellites;
    Ship s(satellites);
    s.dead = false;
    bool defunct;

    // Exercise
    defunct = s.getDefunct();

    // Verify
    assertEquals(s.dead, false);
    assertEquals(defunct, false);
}

/*********************************************
 * GET DEFUNCT: not dead
 * Input:
 * Output:
 *********************************************/
void TestShip::getDefunct_notDead()
{
    // setup
    std::list<Satellite*> satellites;
    Ship s(satellites);
    s.dead = true;
    bool defunct;

    // Exercise
    defunct = s.getDefunct();

    // Verify
    assertEquals(s.dead, true);
    assertEquals(defunct, true);
}
