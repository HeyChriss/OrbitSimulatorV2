/***********************************************************************
 * Header File:
 *    TEST SHIP
 * Author:
 *    Chris Mijango & Seth Chen
 * Summary:
 *    The test ship class
 ************************************************************************/

#pragma once
#include "unitTest.h"
#include "Ship.h"

class TestShip : UnitTest
{
public:
    void run()
    {
        // constructor test
        constructor_default();

        // move tests
        move_oneSecond();
        move_tenSeconds();

        // input tests
        input_noInput();
        input_rightOnce();
        input_rightTenTimes();
        input_leftOnce();
        input_leftTenTimes();
        input_downOnce();
        input_downTenTimes();

        // draw tests
        draw_visible();
        draw_invisible();
        draw_dead();
        draw_notDead();

        // getDefunct tests
        getDefunct_dead();
        getDefunct_notDead();

        report("Ship");
    }

private:
    void constructor_default();
    void move_oneSecond();
    void move_tenSeconds();
    void input_noInput();
    void input_rightOnce();
    void input_rightTenTimes();
    void input_leftOnce();
    void input_leftTenTimes();
    void input_downOnce();
    void input_downTenTimes();
    void draw_visible();
    void draw_invisible();
    void draw_dead();
    void draw_notDead();
    void getDefunct_dead();
    void getDefunct_notDead();

    // Mock ogstream for testing draw calls
    class MockOgstream : public ogstream
    {
    public:
        friend TestShip;
        MockOgstream() : drawCalled(false) {}
        void drawShip(const Position& pos, double angle, bool thrust) override
        {
            drawCalled = true;
        }
        bool wasDrawCalled() const { return drawCalled; }
    private:
        bool drawCalled;
    };

};

