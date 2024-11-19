/***********************************************************************
 * Source File:
 *    User Interface Draw : put pixels on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This is the code necessary to draw on the screen. We have a collection
 *    of procedural functions here because each draw function does not
 *    retain state. In other words, they are verbs (functions), not nouns
 *    (variables) or a mixture (objects)
 ************************************************************************/

#include <string>     // need you ask?
#include <sstream>    // convert an integer into text
#include <cassert>    // I feel the need... the need for asserts
#include <time.h>     // for clock


#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <openGL/gl.h>    // Main OpenGL library
#include <GLUT/glut.h>    // Second OpenGL library
#endif // __APPLE__

#ifdef __linux__
#include <GL/gl.h>        // Main OpenGL library
#include <GL/glut.h>      // Second OpenGL library
#endif // __linux__

#ifdef _WIN32
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>         // OpenGL library we copied 
#define _USE_MATH_DEFINES
#include <math.h>
#endif // _WIN32

#include "position.h"
#include "uiDraw.h"
#include <iostream>



using namespace std;

// colors ueed in the simulator
const int RGB_WHITE[] = { 255, 255, 255 };
const int RGB_LIGHT_GREY[] = { 196, 196, 196 };
const int RGB_GREY[] = { 128, 128, 128 };
const int RGB_DARK_GREY[] = { 64,   64,  64 };
const int RGB_DEEP_BLUE[] = { 64,   64, 156 };
const int RGB_BLUE[] = { 0,     0, 256 };
const int RGB_RED[] = { 255,   0,   0 };
const int RGB_GOLD[] = { 255, 255,   0 };
const int RGB_TAN[] = { 180, 150, 110 };
const int RGB_GREEN[] = { 0, 150,   0 };

/************************************************************************
 * ROTATE
 * Rotate a given point (point) around a given origin (center) by a given
 * number of degrees (angle).
 *    INPUT  origin   The center point we will rotate around
 *           x,y      Offset from center that we will be rotating, in pixels
 *           rotation Rotation in degrees
 *    OUTPUT point    The new position
 *************************************************************************/
Position rotate(const Position& origin, double x, double y, double rotation)
{
    // because sine and cosine are expensive, we want to call them only once
    double cosA = cos(rotation);
    double sinA = sin(rotation);

    // start with our original point
    Position ptReturn(origin);

    // find the new values
    ptReturn.addPixelsX(x * cosA + y * sinA);
    ptReturn.addPixelsY(y * cosA - x * sinA);

    return ptReturn;
}

/*************************************************************************
 * GL RESET COLOR
 * Just a more convenient way to reset the color
 *************************************************************************/
inline void glResetColor()
{
    glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
}

/************************************************************
 * COLOR RECTANGLE
 * A structure used to conveniently specify a rectangle
 * of a certain color
 ************************************************************/
struct ColorRect
{
    int x0;
    int y0;
    int x1;
    int y1;
    int x2;
    int y2;
    int x3;
    int y3;
    const int* rgb;
};

/************************************************************************
* GL COLOR
* Set the color on the board
*   INPUT  rgb  RGB color in integers (0...255)
*************************************************************************/
void glColor(const int* rgb)
{
    glColor3f((GLfloat)(rgb[0] / 256.0),
        (GLfloat)(rgb[1] / 256.0),
        (GLfloat)(rgb[2] / 256.0));
}

/*************************************************************************
 * GL VERTEXT POINT
 * Just a more convenient format of glVertext2f
 *************************************************************************/
inline void glVertexPoint(const Position& point)
{
    glVertex2f((GLfloat)point.getPixelsX(), (GLfloat)point.getPixelsY());
}

/*************************************************************************
 * GL DRAW RECT
 * Draw a colored rectangle
 *************************************************************************/
void glDrawRect(const Position& center, const Position& offset,
    const ColorRect& rect, double rotation)
{
    glBegin(GL_QUADS);
    glColor(rect.rgb);
    glVertexPoint(rotate(center,
        rect.x0 + offset.getPixelsX(),
        rect.y0 + offset.getPixelsY(),
        rotation));
    glVertexPoint(rotate(center,
        rect.x1 + offset.getPixelsX(),
        rect.y1 + offset.getPixelsY(),
        rotation));
    glVertexPoint(rotate(center,
        rect.x2 + offset.getPixelsX(),
        rect.y2 + offset.getPixelsY(),
        rotation));
    glVertexPoint(rotate(center,
        rect.x3 + offset.getPixelsX(),
        rect.y3 + offset.getPixelsY(),
        rotation));
    glEnd();
}

/*************************************************************************
 * DRAW TEXT
 * Draw text using a simple bitmap font
 *   INPUT  topLeft   The top left corner of the text
 *          text      The text to be displayed
 ************************************************************************/
void drawText(const Position& topLeft, const char* text)
{
    void* pFont = GLUT_BITMAP_HELVETICA_12;  // also try _18

    // prepare to draw the text from the top-left corner
    glRasterPos2f((GLfloat)topLeft.getPixelsX(),
        (GLfloat)topLeft.getPixelsY());

    // loop through the text
    for (const char* p = text; *p; p++)
        glutBitmapCharacter(pFont, *p);
}

/*************************************************************************
 * DISPLAY the results on the screen
 *************************************************************************/
void ogstream::flush()
{
    string sOut;
    string sIn = str();

    // copy everything but the newlines
    for (string::iterator it = sIn.begin(); it != sIn.end(); ++it)
        // newline triggers an buffer flush and a move down
        if (*it == '\n')
        {
            drawText(pt, sOut.c_str());
            sOut.clear();
            pt.addPixelsY(-18);
        }
    // othewise append
        else
            sOut += *it;

    // put the text on the screen
    if (!sOut.empty())
    {
        drawText(pt, sOut.c_str());
        pt.addPixelsY(-18);
    }

    // reset the buffer
    str("");
}

/************************************************************************
 * DRAW PROJECTILE
 * Draw a projectile on the screen at a given point.
 *   INPUT  pt     The location of the projectile
 *************************************************************************/
void ogstream::drawProjectile(const Position& pt)
{
    ColorRect rects[] =
    {
       {1,1, -1,1, -1,-1, 1,-1, RGB_WHITE },
    };

    for (int i = 0; i < sizeof(rects) / sizeof(ColorRect); i++)
        glDrawRect(pt, Position(), rects[i], 0.0);
}

/************************************************************************
 * DRAW FRAGMENT
 * Draw a fragment on the screen.
 *   INPUT  center    The location of the fragment
 *          rotation  Which angle it is pointed
 *************************************************************************/
void ogstream::drawFragment(const Position& center, double rotation)
{
    ColorRect rects[] =
    {
       {-4,1, -4,-1, 4,-1, 4,1, RGB_LIGHT_GREY },
    };

    for (int i = 0; i < sizeof(rects) / sizeof(ColorRect); i++)
        glDrawRect(center, Position(), rects[i], rotation);
}

/************************************************************************
 * DRAW Crew Dragon Center
 * Draw the center part of the Crew Dragon module
 *  INPUT center    The position of the ship
 *        rotation  Which direction it is point
 *************************************************************************/
void ogstream::drawCrewDragonCenter(const Position& center, double rotation)
{
    ColorRect rects[] =
    {
       {-5,5,   3,5,   3,-5,  -5,-5,  RGB_LIGHT_GREY },
       { 3,5,   3,-5, 11,-3,  11,3,   RGB_GREY },
       {12,-3, 12,3,  11,-3,  11,3,   RGB_DARK_GREY },
       { 4,3,   7,2,   7,-2,   4,-3,  RGB_DARK_GREY}
    };

    for (int i = 0; i < sizeof(rects) / sizeof(ColorRect); i++)
        glDrawRect(center, Position(), rects[i], rotation);
}

/************************************************************************
 * DRAW Crew Dragon Right array
 * Draw the right solar array of the crew dragon module
 *  INPUT center    The position of the ship
 *        rotation  Which direction it is point
 *        offset    For pieces of the satellite, this is the relative position of the center
 *                  of rotation when it is connected to the main satellite
 *************************************************************************/
void ogstream::drawCrewDragonRight(const Position& center, double rotation, const Position& offset)
{
    ColorRect rects[] =
    {
       {-4,5,  4,5,  4,1,  -4,1,  RGB_DEEP_BLUE },
       {-4,-1, 4,1,  4,-5, -4,-5, RGB_DEEP_BLUE },
       {0,2,   0,-6, 1,-6,  1,2,  RGB_GREY },
    };

    for (int i = 0; i < sizeof(rects) / sizeof(ColorRect); i++)
        glDrawRect(center, offset, rects[i], rotation);
}

/************************************************************************
 * DRAW Crew Dragon Left array
 * Draw the left solar array of the crew dragon module
 *  INPUT center    The position of the ship
 *        rotation  Which direction it is point
 *        offset    For pieces of the satellite, this is the relative position of the center
 *                  of rotation when it is connected to the main satellite
 *************************************************************************/
void ogstream::drawCrewDragonLeft(const Position& center, double rotation, const Position& offset)
{
    ColorRect rects[] =
    {
       {-4,5,  4,5,  4,1,  -4,1,  RGB_DEEP_BLUE },
       {-4,-1, 4,1,  4,-5, -4,-5, RGB_DEEP_BLUE },
       {0,2,   0,-6, 1,-6,  1,2,  RGB_GREY }
    };

    for (int i = 0; i < sizeof(rects) / sizeof(ColorRect); i++)
        glDrawRect(center, offset, rects[i], rotation);
}


/************************************************************************
 * DRAW Crew Dragon
 * Draw a crew dragon on the screen. It consists of three components
 *  INPUT center    The position of the ship
 *        rotation  Which direction it is point
 *************************************************************************/
void ogstream::drawCrewDragon(const Position& center, double rotation)
{
    drawCrewDragonCenter(center, rotation);

    Position posRight;
    posRight.setPixelsX(-1.0);
    posRight.setPixelsY(11.0);
    drawCrewDragonRight(center, rotation, posRight);

    Position posLeft;
    posLeft.setPixelsX(-1.0);
    posLeft.setPixelsY(-11.0);
    drawCrewDragonLeft(center, rotation, posLeft);
}

/************************************************************************
 * DRAW Sputnik
 * Draw the satellite on the screen
 *  INPUT center    The position of the ship
 *        rotation  Which direction it is point
 *************************************************************************/
void ogstream::drawSputnik(const Position& center, double rotation)
{
    // draw the sphere                                               
    const PT pointsSphere[] =
    {
       {0,0},
       {2,6}, {6,2}, {6,-2}, {2,-6}, {-2,-6}, {-2,-6}, {-6,-2}, {-6,2}, {-2,6}, {2,6}
    };
    glBegin(GL_TRIANGLE_FAN);
    glColor(RGB_GREY);
    for (int i = 0; i < sizeof(pointsSphere) / sizeof(PT); i++)
        glVertexPoint(rotate(center, pointsSphere[i].x, pointsSphere[i].y, rotation));
    glEnd();

    // draw the antenna
    glBegin(GL_LINES);
    glColor(RGB_WHITE);
    glVertexPoint(rotate(center, -6.0, 2.0, rotation));
    glVertexPoint(rotate(center, -10.0, -15.0, rotation));

    glVertexPoint(rotate(center, 0.0, 1.0, rotation));
    glVertexPoint(rotate(center, -2.5, -15.0, rotation));

    glVertexPoint(rotate(center, 2.0, -6.0, rotation));
    glVertexPoint(rotate(center, 2.5, -15.0, rotation));

    glVertexPoint(rotate(center, 6.0, 2.0, rotation));
    glVertexPoint(rotate(center, 10.0, -15.0, rotation));
    glEnd();
}

/************************************************************************
 * DRAW GPS Left
 * Draw a GPS satellite left solar array on the screen
 *  INPUT center    The position of the ship
 *        rotation  Which direction it is point
 *        offset    For pieces of the satellite, this is the relative position of the center
 *                  of rotation when it is connected to the main satellite
 *************************************************************************/
void ogstream::drawGPSLeft(const Position& center, double rotation, const Position& offset)
{
    ColorRect rects[] =
    {
       {-6,5,  6,5,  6,1,  -6,1,  RGB_WHITE},
       {-6,0,  6,0,  6,-4, -6,-4, RGB_WHITE},
       {-5,4,  5,4,  5,2,  -5,2,  RGB_DEEP_BLUE },
       {-5,-1, 5,-1, 5,-3, -5,-3, RGB_DEEP_BLUE }
    };

    for (int i = 0; i < sizeof(rects) / sizeof(ColorRect); i++)
        glDrawRect(center, offset, rects[i], rotation);

    // draw the line connecting the solar array to the rest of the ship
    glBegin(GL_LINE_STRIP);
    glColor(RGB_WHITE);
    glVertexPoint(rotate(center,
        3.0 + offset.getPixelsX(),
        4.0 + offset.getPixelsY(),
        rotation));
    glVertexPoint(rotate(center,
        0.0 + offset.getPixelsX(),
        8.0 + offset.getPixelsY(),
        rotation));
    glVertexPoint(rotate(center,
        -3.0 + offset.getPixelsX(),
        4.0 + offset.getPixelsY(),
        rotation));
    glEnd();
}

/************************************************************************
 * DRAW GPS Right
 * Draw a GPS satellite right solar array on the screen
 *  INPUT center    The position of the ship
 *        rotation  Which direction it is point
 *        offset    For pieces of the satellite, this is the relative position of the center
 *                  of rotation when it is connected to the main satellite
 *************************************************************************/
void ogstream::drawGPSRight(const Position& center, double rotation, const Position& offset)
{
    ColorRect rects[] =
    {
       {-6,-5, 6,-5, 6,-1, -6,-1,  RGB_WHITE},
       {-6,0,  6,0,  6,4,  -6,4,   RGB_WHITE},
       {-5,-4, 5,-4, 5,-2, -5,-2,  RGB_DEEP_BLUE },
       {-5,1,  5,1,  5,3,  -5,3,   RGB_DEEP_BLUE }
    };

    for (int i = 0; i < sizeof(rects) / sizeof(ColorRect); i++)
        glDrawRect(center, offset, rects[i], rotation);

    // draw the line connecting the solar array to the rest of the ship
    glBegin(GL_LINE_STRIP);
    glColor(RGB_WHITE);
    glVertexPoint(rotate(center,
        3.0 + offset.getPixelsX(),
        -4.0 + offset.getPixelsY(),
        rotation));
    glVertexPoint(rotate(center,
        0.0 + offset.getPixelsX(),
        -8.0 + offset.getPixelsY(),
        rotation));
    glVertexPoint(rotate(center,
        -3.0 + offset.getPixelsX(),
        -4.0 + offset.getPixelsY(),
        rotation));
    glEnd();

}

/************************************************************************
 * DRAW GPS Center
 * Draw the main part of the GPS satellite
 *  INPUT center    The position of the ship
 *        rotation  Which direction it is point
 *************************************************************************/
void ogstream::drawGPSCenter(const Position& center, double rotation)
{
    ColorRect rects[4] =
    {
       {-3,4,  4,4,  4,-4, -3,-4, RGB_GOLD  },
       {4,4,  -3,4, -3,-4, -4,-4, RGB_WHITE },
       {4,3,   7,3,   7,1,   4,1, RGB_GREY  },
       {4,-3, 7,-3,  7,-1,  4,-1, RGB_GREY  }
    };

    for (int i = 0; i < sizeof(rects) / sizeof(ColorRect); i++)
        glDrawRect(center, Position(), rects[i], rotation);
}

/************************************************************************
 * DRAW GPS
 * Draw a GPS satellite on the screen. It consists of three parts
 *  INPUT center    The position of the ship
 *        rotation  Which direction it is point
 *************************************************************************/
void ogstream::drawGPS(const Position& center, double rotation)
{
    drawGPSCenter(center, rotation);

    Position posRight;
    posRight.setPixelsX(0.0);
    posRight.setPixelsY(12.0);
    drawGPSRight(center, rotation, posRight);

    Position posLeft;
    posLeft.setPixelsX(0.0);
    posLeft.setPixelsY(-12.0);
    drawGPSLeft(center, rotation, posLeft);
}

/************************************************************************
 * DRAW Hubble Telescope
 * Draw a the telescope part of the hubble
 *  INPUT center    The position of the ship
 *        rotation  Which direction it is point
 *        offset    For pieces of the satellite, this is the relative position of the center
 *                  of rotation when it is connected to the main satellite
 *************************************************************************/
void ogstream::drawHubbleTelescope(const Position& center, double rotation, const Position& offset)
{
    ColorRect rects[] =
    {
       {-9,3,  11,3,  11,-3, -9,-3,  RGB_LIGHT_GREY},
       {11,3,  15,6,  16,5,  12,2,   RGB_GREY},
       {-9,-2, 11,-2, 11,-3, -9,-3,  RGB_GREY}
    };

    for (int i = 0; i < sizeof(rects) / sizeof(ColorRect); i++)
        glDrawRect(center, offset, rects[i], rotation);
}

/************************************************************************
 * DRAW Hubble Computer
 * Draw a the computer part of the hubble space telescope
 *  INPUT center    The position of the ship
 *        rotation  Which direction it is point
 *        offset    For pieces of the satellite, this is the relative position of the center
 *                  of rotation when it is connected to the main satellite
 *************************************************************************/
void ogstream::drawHubbleComputer(const Position& center, double rotation, const Position& offset)
{
    ColorRect rects[] =
    {
       {-5,5,   0,5,  0,-3, -5,-3,  RGB_GREY},
       {-5,-5,  0,-5, 0,-3, -5,-3,  RGB_DARK_GREY},
       { 0,4,   3,4,  3,-2,  0,-2,  RGB_GREY},
       { 0,-4,  3,-4, 3,-2,  0,-2,  RGB_DARK_GREY},
    };

    for (int i = 0; i < sizeof(rects) / sizeof(ColorRect); i++)
        glDrawRect(center, offset, rects[i], rotation);
}

/************************************************************************
 * DRAW Hubble Left
 * Draw left solar array of the hubble space telescope on the screen
 *  INPUT center    The position of the ship
 *        rotation  Which direction it is point
 *        offset    For pieces of the satellite, this is the relative position of the center
 *                  of rotation when it is connected to the main satellite
 *************************************************************************/
void ogstream::drawHubbleLeft(const Position& center, double rotation, const Position& offset)
{
    ColorRect rects[] =
    {
       {-8,3, -1,3, -1,-1, -8,-1,  RGB_LIGHT_GREY},
       { 8,3,  1,3,  1,-1,  8,-1,  RGB_LIGHT_GREY},
       {-7,2, -1,2, -2,0,  -7,0,   RGB_DARK_GREY},
       { 7,2,  1,2,  2,0,   7,0,   RGB_DARK_GREY}
    };

    for (int i = 0; i < sizeof(rects) / sizeof(ColorRect); i++)
        glDrawRect(center, offset, rects[i], rotation);

    glBegin(GL_LINE_STRIP);
    glColor(RGB_WHITE);
    glVertexPoint(rotate(center,
        0.0 + offset.getPixelsX(),
        3.0 + offset.getPixelsY(),
        rotation));
    glVertexPoint(rotate(center,
        0.0 + offset.getPixelsX(),
        -5.0 + offset.getPixelsY(),
        rotation));
    glEnd();
}


/************************************************************************
 * DRAW Hubble Right
 * Draw right solar array of the hubble space telescope on the screen
 *  INPUT center    The position of the ship
 *        rotation  Which direction it is point
 *        offset    For pieces of the satellite, this is the relative position of the center
 *                  of rotation when it is connected to the main satellite
 *************************************************************************/
void ogstream::drawHubbleRight(const Position& center, double rotation, const Position& offset)
{
    ColorRect rects[] =
    {
       {-8,-3, -1,-3, -1,1,  -8,1,  RGB_LIGHT_GREY},
       { 8,-3,  1,-3,  1,1,   8,1,  RGB_LIGHT_GREY},
       {-7,-2, -1,-2, -2,0,  -7,0,  RGB_DARK_GREY},
       { 7,-2,  1,-2,  2,0,   7,0,  RGB_DARK_GREY}
    };

    for (int i = 0; i < sizeof(rects) / sizeof(ColorRect); i++)
        glDrawRect(center, offset, rects[i], rotation);

    glBegin(GL_LINE_STRIP);
    glColor(RGB_WHITE);
    glVertexPoint(rotate(center,
        0.0 + offset.getPixelsX(),
        -3.0 + offset.getPixelsY(),
        rotation));
    glVertexPoint(rotate(center,
        0.0 + offset.getPixelsX(),
        5.0 + offset.getPixelsY(),
        rotation));
    glEnd();
}

/************************************************************************
 * DRAW Hubble
 * Draw a Hubble satellite on the screen. It consists of 4 parts
 *  INPUT center    The position of the ship
 *        rotation  Which direction it is point
 *************************************************************************/
void ogstream::drawHubble(const Position& center, double rotation)
{
    Position posTelescope;
    posTelescope.setPixelsX(2.0);
    posTelescope.setPixelsY(0.0);
    drawHubbleTelescope(center, rotation, posTelescope);

    Position posComputer;
    posComputer.setPixelsX(-10.0);
    posComputer.setPixelsY(0.0);
    drawHubbleComputer(center, rotation, posComputer);

    Position posRight;
    posRight.setPixelsX(1.0);
    posRight.setPixelsY(-8.0);
    drawHubbleRight(center, rotation, posRight);

    Position posLeft;
    posLeft.setPixelsX(1.0);
    posLeft.setPixelsY(8.0);
    drawHubbleLeft(center, rotation, posLeft);
}

/************************************************************************
 * DRAW Starlink Body
 * Draw the body of the Starlink satellite on the screen
 *  INPUT center    The position of the ship
 *        rotation  Which direction it is point
 *        offset    For pieces of the satellite, this is the relative position of the center
 *                  of rotation when it is connected to the main satellite
 *************************************************************************/
void ogstream::drawStarlinkBody(const Position& center, double rotation, const Position& offset)
{
    ColorRect rects[] =
    {
       {1,5,    1,-3, -1,-5, -1,3,  RGB_LIGHT_GREY},
       {-4,-5, -1,-5, -1,3,  -4,3,  RGB_GREY},
       {-4,3,  -2,3,   1,5,  -1,3,  RGB_WHITE}
    };

    for (int i = 0; i < sizeof(rects) / sizeof(ColorRect); i++)
        glDrawRect(center, offset, rects[i], rotation);
}

/************************************************************************
 * DRAW Starlink Array
 * Draw the solar array of the Starlink satellite on the screen
 *  INPUT center    The position of the ship
 *        rotation  Which direction it is point
 *        offset    For pieces of the satellite, this is the relative position of the center
 *                  of rotation when it is connected to the main satellite
 *************************************************************************/
void ogstream::drawStarlinkArray(const Position& center, double rotation, const Position& offset)
{
    ColorRect rects[] =
    {
       {-7,7, 8,2, 8,-6, -7,-1,  RGB_GREY},
       {-6,6, 7,1, 7,-5, -6,0,   RGB_DEEP_BLUE}
    };

    for (int i = 0; i < sizeof(rects) / sizeof(ColorRect); i++)
        glDrawRect(center, offset, rects[i], rotation);
}

/************************************************************************
 * DRAW Starlink
 * Draw a Starlink satellite on the screen. It consists of 2 components
 *  INPUT center    The position of the ship
 *        rotation  Which direction it is point
 *************************************************************************/
void ogstream::drawStarlink(const Position& center, double rotation)
{
    Position posBody;
    posBody.setPixelsX(-1.0);
    posBody.setPixelsY(0.0);
    drawStarlinkBody(center, rotation, posBody);

    Position posArray;
    posArray.setPixelsX(8.0);
    posArray.setPixelsY(-2.0);
    drawStarlinkArray(center, rotation, posArray);
}

/************************************************************************
 * DRAW Ship
 * Draw a spaceship on the screen
 *  INPUT center    The position of the ship
 *        rotation  Which direction it is point
 *        offset    For pieces of the satellite, this is the relative position of the center
 *                  of rotation when it is connected to the main satellite
 *        thrust    Whether the thrusters are on
 *************************************************************************/
void ogstream::drawShip(const Position& center, double rotation, bool thrust)
{
    // draw the white part of the ship                                               
    const PT pointsShipWhite[] =
    {
       {0,0},
       {-3,-9}, {-12,-12}, {-14,-12}, {-13,-7}, {-8,-2}, {-6,3}, {-4,11}, {-4,14}, {-3,16}, {-1,18},
       {1,18}, {3,16}, {4,14}, {4,11}, {6,3}, {8,-2}, {13,-7}, {14,-12}, {12,-12}, {3,-9}, {-3,-9}
    };

    glBegin(GL_TRIANGLE_FAN);
    glColor(RGB_LIGHT_GREY);
    for (int i = 0; i < sizeof(pointsShipWhite) / sizeof(PT); i++)
        glVertexPoint(rotate(center, pointsShipWhite[i].x, pointsShipWhite[i].y, rotation));
    glEnd();

    // draw the flame if necessary
    if (thrust)
    {
        glBegin(GL_TRIANGLES);
        glColor(RGB_RED);
        glVertexPoint(rotate(center, -3.0, -9.0, rotation));
        glVertexPoint(rotate(center, random(-5.0, 5.0), random(-25.0, -13.0), rotation));
        glVertexPoint(rotate(center, 3.0, -9.0, rotation));
        glVertexPoint(rotate(center, -3.0, -9.0, rotation));
        glVertexPoint(rotate(center, random(-5.0, 5.0), random(-25.0, -13.0), rotation));
        glVertexPoint(rotate(center, 3.0, -9.0, rotation));
        glResetColor();
        glEnd();
    }

    // draw the dark part of the ship                                               
    const PT pointsShipBlack[][4] =
    {
       {{-5,-8},  {-12,-11},{-11,-7},{-5,-2}}, // left wing
       {{ 5,-8},  { 12,-11},{ 11,-7},{ 5,-2}}, // right wing
       {{ 0,-13}, {-3,11},  {-1,15}, {1,15}},  // left canopy
       {{ 0,-13}, { 3,11},  { 1,15}, {-1,15}}  // right canopy
    };
    glBegin(GL_QUADS);
    glColor(RGB_DEEP_BLUE);
    for (int iRectangle = 0; iRectangle < 4; iRectangle++)
        for (int iVertex = 0; iVertex < 4; iVertex++)
            glVertexPoint(rotate(center, pointsShipBlack[iRectangle][iVertex].x,
                pointsShipBlack[iRectangle][iVertex].y, rotation));
    glResetColor();
    glEnd();
}

/************************************************************************
 * DRAW Earth
 * Draw Earth
 *  INPUT center    The position of the ship
 *        rotation  Which direction it is point
 *************************************************************************/
void ogstream::drawEarth(const Position& center, double rotation)
{
    const int* colors[5] =
    {
       RGB_GREY,  // 0
       RGB_BLUE,  // 1
       RGB_GREEN, // 2
       RGB_TAN,   // 3
       RGB_WHITE  // 4
    };

    int earth[50][50] =
    {
    {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 1,1,1,1,1, 1,1,1,1,1, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,},
    {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1,3,3, 3,2,2,1,1, 1,1,2,2,2, 3,1,1,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,},
    {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 1,1,1,2,2, 2,2,2,2,3, 3,3,3,3,3, 3,3,1,1,1, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,},
    {0,0,0,0,0, 0,0,0,0,0, 0,0,2,1,1, 1,2,2,2,2, 2,2,2,2,2, 2,2,2,2,3, 3,3,3,1,1, 1,1,1,0,0, 0,0,0,0,0, 0,0,0,0,0,},
    {0,0,0,0,0, 0,0,0,0,0, 0,2,2,1,1, 2,2,2,2,2, 3,3,3,3,3, 3,3,3,3,3, 2,2,2,2,1, 1,1,1,1,1, 0,0,0,0,0, 0,0,0,0,0,},

    {0,0,0,0,0, 0,0,0,0,2, 1,1,1,2,2, 3,3,3,3,3, 3,3,3,3,3, 3,3,3,3,4, 3,3,3,3,3, 3,1,3,3,1, 1,0,0,0,0, 0,0,0,0,0,},
    {0,0,0,0,0, 0,0,0,1,1, 1,1,1,1,3, 3,3,3,3,3, 3,3,3,3,3, 3,3,3,3,3, 4,3,3,3,3, 3,3,2,3,3, 1,1,0,0,0, 0,0,0,0,0,},
    {0,0,0,0,0, 0,0,1,1,1, 1,1,1,1,1, 3,3,3,3,3, 3,3,3,3,3, 3,3,3,3,3, 3,3,3,3,3, 3,3,3,1,3, 3,2,2,0,0, 0,0,0,0,0,},
    {0,0,0,0,0, 0,1,1,1,1, 1,1,1,1,1, 2,3,3,3,3, 3,3,3,3,3, 3,3,3,3,2, 3,3,3,3,3, 3,3,3,3,3, 3,3,2,3,0, 0,0,0,0,0,},
    {0,0,0,0,0, 0,1,1,1,1, 2,2,2,2,2, 3,3,3,3,3, 3,3,3,3,3, 2,3,3,3,3, 3,3,3,2,3, 3,2,2,3,2, 3,3,3,3,0, 0,0,0,0,0,},

    {0,0,0,0,0, 1,1,1,1,1, 2,1,1,2,3, 3,3,3,3,2, 2,2,2,3,3, 3,2,3,3,3, 3,3,3,3,3, 3,1,3,3,3, 3,3,3,2,3, 0,0,0,0,0,},
    {0,0,0,0,1, 1,1,1,1,1, 2,1,1,3,3, 3,3,3,3,3, 3,2,2,3,2, 2,3,3,3,3, 3,3,3,3,3, 1,1,3,3,3, 3,3,3,3,3, 3,0,0,0,0,},
    {0,0,0,0,1, 1,1,1,1,2, 1,1,3,2,2, 3,2,3,3,3, 2,3,2,2,2, 2,2,2,3,3, 3,3,3,3,3, 3,3,3,3,3, 3,3,3,3,3, 3,3,0,0,0,},
    {0,0,0,1,1, 1,1,1,1,1, 1,1,2,2,3, 3,3,3,3,3, 2,3,3,3,3, 2,3,3,3,3, 2,2,3,3,3, 3,2,3,2,1, 3,1,1,3,3, 3,3,0,0,0,},
    {0,0,0,1,1, 1,1,1,1,1, 2,2,2,2,3, 3,3,2,2,2, 3,3,3,3,3, 3,3,3,3,2, 2,2,3,2,3, 3,3,3,2,1, 3,3,1,2,3, 3,3,0,0,0,},

    {0,0,1,1,1, 1,1,1,1,1, 1,1,2,2,1, 2,2,2,3,2, 3,3,3,3,3, 3,3,3,3,3, 2,2,2,2,2, 3,3,3,3,2, 1,3,1,1,3, 3,3,3,0,0,},
    {0,0,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 3,2,2,3,3, 3,3,3,3,3, 3,3,4,3,3, 3,2,2,2,2, 3,3,3,3,3, 1,1,3,3,1, 3,3,3,0,0,},
    {0,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 3,3,3,3,3, 3,3,3,3,3, 3,3,3,1,1, 1,2,2,2,2, 2,2,3,3,3, 2,3,2,1,2, 3,3,3,2,0,},
    {0,1,1,1,1, 1,1,1,1,1, 2,1,1,1,3, 3,3,3,3,3, 3,3,4,4,3, 1,1,1,1,4, 1,2,2,2,2, 2,2,3,3,3, 3,3,2,1,1, 3,3,3,3,0,},
    {0,1,1,1,1, 1,1,1,1,1, 1,3,2,2,3, 3,3,3,3,1, 1,1,1,4,1, 1,1,1,4,1, 1,1,3,2,2, 2,2,3,3,3, 3,3,1,2,1, 3,3,3,3,0,},

    {0,1,1,1,1, 1,1,1,1,1, 1,2,2,1,3, 3,3,3,3,4, 1,1,1,1,4, 1,1,1,1,1, 1,1,2,2,2, 2,2,1,2,3, 3,2,1,1,1, 3,3,3,3,0,},
    {1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,3, 3,3,3,1,4, 1,1,1,1,1, 1,1,1,1,1, 1,1,2,2,2, 2,2,2,2,3, 3,3,3,1,2, 3,3,3,3,3,},
    {1,1,1,1,1, 1,1,1,1,1, 1,1,1,3,3, 3,3,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,3, 3,2,2,2,3, 3,3,2,2,2, 3,3,3,2,2,},
    {1,1,1,1,1, 1,1,1,1,1, 1,1,1,3,3, 3,4,1,1,1, 1,1,1,1,1, 1,1,1,4,4, 4,1,1,1,1, 1,3,3,1,1, 3,3,3,2,1, 3,3,3,3,2,},
    {1,1,1,1,1, 1,1,1,1,1, 1,1,1,2,3, 3,1,1,1,1, 1,1,1,1,1, 1,1,4,4,4, 4,4,4,1,1, 1,1,1,1,1, 1,3,3,3,1, 3,3,3,3,2,},

    {1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 3,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,2,3, 3,3,1,3,3, 3,3,3,3,2,},
    {1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,4,4,1, 1,1,1,1,1, 1,1,1,1,2, 1,1,1,3,3, 3,3,3,3,2,},
    {1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,4,1,1,1, 1,1,1,1,1, 1,1,4,4,4, 4,1,1,1,1, 1,1,1,1,2, 1,1,1,3,2, 3,3,3,3,2,},
    {1,1,1,1,1, 1,1,1,1,1, 1,1,1,3,2, 2,2,2,1,1, 1,1,1,1,4, 4,4,4,4,4, 4,4,4,1,4, 1,1,1,1,1, 1,1,1,1,1, 1,3,3,3,3,},
    {0,1,1,1,1, 1,1,1,1,1, 1,1,1,2,2, 2,3,3,1,1, 1,1,1,4,4, 4,1,4,4,4, 4,4,4,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,3,3,3,0,},

    {0,1,1,1,1, 1,1,1,1,1, 1,1,1,3,2, 2,2,3,1,1, 1,1,4,1,1, 4,1,1,4,4, 4,4,4,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,2,3,3,0,},
    {0,1,1,1,1, 1,1,1,1,1, 1,1,1,1,3, 2,2,2,2,4, 1,4,1,1,4, 4,1,1,1,1, 4,4,4,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,2,1,0,},
    {0,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 3,2,2,2,2, 2,2,4,4,4, 2,4,4,1,1, 4,4,4,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,0,},
    {0,0,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 2,2,2,3,2, 3,2,2,1,4, 2,4,4,4,1, 1,1,4,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,0,0,},
    {0,0,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 3,3,3,3,3, 3,3,3,3,3, 2,2,2,4,4, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,0,0,},

    {0,0,0,1,1, 1,1,1,1,1, 1,1,1,1,1, 2,3,2,2,2, 3,3,3,2,2, 2,1,2,2,2, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,0,0,0,},
    {0,0,0,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,2,2,2,2, 3,1,3,2,2, 1,1,2,3,2, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,0,0,0,},
    {0,0,0,0,1, 1,1,1,1,1, 1,1,1,1,1, 2,2,2,2,2, 3,3,3,3,2, 1,1,1,3,2, 2,3,2,2,1, 1,1,1,1,1, 1,1,1,1,1, 1,0,0,0,0,},
    {0,0,0,0,1, 1,1,1,1,1, 1,1,1,1,1, 1,3,2,2,3, 3,3,3,3,3, 1,1,2,2,2, 2,2,2,2,3, 1,1,1,1,1, 1,1,1,1,1, 1,0,0,0,0,},
    {0,0,0,0,0, 1,1,1,1,1, 1,1,1,1,1, 2,3,2,3,3, 3,3,3,3,3, 2,2,1,2,2, 2,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 0,0,0,0,0,},

    {0,0,0,0,0, 0,1,1,1,1, 1,1,1,1,2, 3,2,2,3,3, 3,3,3,2,2, 2,2,2,2,2, 1,2,2,1,1, 1,1,1,1,1, 1,1,1,1,0, 0,0,0,0,0,},
    {0,0,0,0,0, 0,0,1,1,1, 1,1,1,1,2, 3,3,3,3,3, 3,1,3,2,2, 1,2,2,2,2, 2,2,1,1,1, 1,1,1,1,1, 1,1,1,0,0, 0,0,0,0,0,},
    {0,0,0,0,0, 0,0,0,1,1, 1,1,1,1,1, 3,3,3,3,3, 3,3,3,3,2, 2,2,2,2,2, 2,1,1,1,1, 1,1,1,1,1, 1,1,0,0,0, 0,0,0,0,0,},
    {0,0,0,0,0, 0,0,0,0,1, 1,1,1,1,1, 2,3,3,3,3, 3,3,3,3,3, 3,3,3,2,2, 1,1,1,1,1, 1,1,1,1,1, 1,0,0,0,0, 0,0,0,0,0,},
    {0,0,0,0,0, 0,0,0,0,0, 1,1,1,1,1, 1,1,3,3,3, 3,3,3,3,3, 3,3,2,2,2, 1,1,1,1,1, 1,1,1,1,1, 0,0,0,0,0, 0,0,0,0,0,},

    {0,0,0,0,0, 0,0,0,0,0, 0,1,1,1,1, 1,2,3,3,3, 3,3,3,2,3, 2,2,2,2,1, 1,1,1,1,1, 1,1,1,1,0, 0,0,0,0,0, 0,0,0,0,0,},
    {0,0,0,0,0, 0,0,0,0,0, 0,0,0,1,1, 1,1,1,3,3, 3,3,3,2,1, 1,1,2,2,2, 1,1,1,1,2, 1,2,0,0,0, 0,0,0,0,0, 0,0,0,0,0,},
    {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 1,1,1,1,3, 3,3,1,1,1, 1,1,1,2,2, 2,2,1,1,3, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,},
    {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1,1,1, 1,2,2,2,2, 1,1,1,1,1, 1,2,3,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,},
    {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,1,1,1,1, 1,1,1,1,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,},
    };

    const double SCALE = 2.0;

    for (int y = 0; y < 50; y++)
        for (int x = 0; x < 50; x++)
            if (earth[y][x])
            {
                assert(earth[y][x] > 0 && earth[y][x] <= 4);
                ColorRect rect =
                {
                   static_cast<int>(x * SCALE),
                   static_cast<int>(y * SCALE),

                   static_cast<int>(x * SCALE),
                   static_cast<int>(y * SCALE + SCALE),

                   static_cast<int>(x * SCALE + SCALE),
                   static_cast<int>(y * SCALE + SCALE),

                   static_cast<int>(x * SCALE + SCALE),
                   static_cast<int>(y * SCALE), colors[earth[y][x]] };
                Position pos;
                pos.setPixelsX(-25.0 * SCALE);
                pos.setPixelsY(-25.0 * SCALE);
                glDrawRect(center, pos, rect, rotation);
            }

    return;
}

/************************************************************************
 * DRAW STAR
 * Draw a star that twinkles
 *   INPUT  POINT     The position of the beginning of the star
 *          PHASE     The phase of the twinkling
 *************************************************************************/
void ogstream::drawStar(const Position& point, unsigned char phase)
{
    // Get ready...
    glBegin(GL_POINTS);

    // most of the time, it is just a pale yellow dot
    if (phase < 128)
    {
        glColor3f((GLfloat)0.5 /* red % */, (GLfloat)0.5 /* green % */, (GLfloat)0.0 /* blue % */);
        glVertex2f((GLfloat)(point.getPixelsX() + 0.0), (GLfloat)(point.getPixelsY() + 0.0));
    }
    // transitions to a bright yellow dot
    else if (phase < 160 || phase > 224)
    {
        glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)0.0 /* blue % */);
        glVertex2f((GLfloat)(point.getPixelsX() + 0.0), (GLfloat)(point.getPixelsY() + 0.0));
    }
    // transitions to a bright yellow dot with pale yellow corners
    else if (phase < 176 || phase > 208)
    {
        glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)0.0 /* blue % */);
        glVertex2f((GLfloat)(point.getPixelsX() + 0.0), (GLfloat)(point.getPixelsY() + 0.0));
        glColor3f((GLfloat)0.5 /* red % */, (GLfloat)0.5 /* green % */, (GLfloat)0.0 /* blue % */);
        glVertex2f((GLfloat)(point.getPixelsX() + 1.0), (GLfloat)(point.getPixelsY() + 0.0));
        glVertex2f((GLfloat)(point.getPixelsX() - 1.0), (GLfloat)(point.getPixelsY() + 0.0));
        glVertex2f((GLfloat)(point.getPixelsX() + 0.0), (GLfloat)(point.getPixelsY() + 1.0));
        glVertex2f((GLfloat)(point.getPixelsX() + 0.0), (GLfloat)(point.getPixelsY() - 1.0));
    }
    // the biggest yet
    else
    {
        glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)0.0 /* blue % */);
        glVertex2f((GLfloat)(point.getPixelsX() + 0.0), (GLfloat)(point.getPixelsY() + 0.0));
        glColor3f((GLfloat)0.7 /* red % */, (GLfloat)0.7 /* green % */, (GLfloat)0.0 /* blue % */);
        glVertex2f((GLfloat)(point.getPixelsX() + 1.0), (GLfloat)(point.getPixelsY() + 0.0));
        glVertex2f((GLfloat)(point.getPixelsX() - 1.0), (GLfloat)(point.getPixelsY() + 0.0));
        glVertex2f((GLfloat)(point.getPixelsX() + 0.0), (GLfloat)(point.getPixelsY() + 1.0));
        glVertex2f((GLfloat)(point.getPixelsX() + 0.0), (GLfloat)(point.getPixelsY() - 1.0));
        glColor3f((GLfloat)0.5 /* red % */, (GLfloat)0.5 /* green % */, (GLfloat)0.0 /* blue % */);
        glVertex2f((GLfloat)(point.getPixelsX() + 2.0), (GLfloat)(point.getPixelsY() + 0.0));
        glVertex2f((GLfloat)(point.getPixelsX() - 2.0), (GLfloat)(point.getPixelsY() + 0.0));
        glVertex2f((GLfloat)(point.getPixelsX() + 0.0), (GLfloat)(point.getPixelsY() + 2.0));
        glVertex2f((GLfloat)(point.getPixelsX() + 0.0), (GLfloat)(point.getPixelsY() - 2.0));
    }

    // Complete drawing
    glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
    glEnd();
}

/******************************************************************
 * DUMMY
 ****************************************************************/
void ogstreamDummy::flush() { assert(false); }
void ogstreamDummy::setPosition(const Position& pt) { assert(false); }
ogstreamDummy& ogstreamDummy::operator = (const Position& pt) { assert(false); return *this; }
void ogstreamDummy::drawFragment(const Position& center, double rotation) { assert(false); }
void ogstreamDummy::drawProjectile(const Position& pt) { assert(false); }
void ogstreamDummy::drawCrewDragon(const Position& center, double rotation) { assert(false); }
void ogstreamDummy::drawCrewDragonRight(const Position& center, double rotation, const Position& offset) { assert(false); }
void ogstreamDummy::drawCrewDragonLeft(const Position& center, double rotation, const Position& offset) { assert(false); }
void ogstreamDummy::drawCrewDragonCenter(const Position& center, double rotation) { assert(false); }
void ogstreamDummy::drawSputnik(const Position& center, double rotation) { assert(false); }
void ogstreamDummy::drawGPS(const Position& center, double rotation) { assert(false); }
void ogstreamDummy::drawGPSCenter(const Position& center, double rotation) { assert(false); }
void ogstreamDummy::drawGPSRight(const Position& center, double rotation, const Position& offset) { assert(false); }
void ogstreamDummy::drawGPSLeft(const Position& center, double rotation, const Position& offset) { assert(false); }
void ogstreamDummy::drawHubble(const Position& center, double rotation) { assert(false); }
void ogstreamDummy::drawHubbleComputer(const Position& center, double rotation, const Position& offset) { assert(false); }
void ogstreamDummy::drawHubbleTelescope(const Position& center, double rotation, const Position& offset) { assert(false); }
void ogstreamDummy::drawHubbleLeft(const Position& center, double rotation, const Position& offset) { assert(false); }
void ogstreamDummy::drawHubbleRight(const Position& center, double rotation, const Position& offset) { assert(false); }
void ogstreamDummy::drawStarlink(const Position& center, double rotation) { assert(false); }
void ogstreamDummy::drawStarlinkBody(const Position& center, double rotation, const Position& offset) { assert(false); }
void ogstreamDummy::drawStarlinkArray(const Position& center, double rotation, const Position& offset) { assert(false); }
void ogstreamDummy::drawShip(const Position& center, double rotation, bool thrust) { assert(false); }
void ogstreamDummy::drawEarth(const Position& center, double rotation) { assert(false); }
void ogstreamDummy::drawStar(const Position& point, unsigned char phase) { assert(false); }


/******************************************************************
 * FAKE
 ****************************************************************/
 // void ogstreamFake::flush() { assert(false); }
 // void ogstreamFake::setPosition(const Position& pt) { assert(false); }
 // ogstreamFake& ogstreamFake::operator = (const Position& pt) { assert(false); return *this; }
 // void ogstreamFake::drawFragment(const Position& center, double rotation) { *this << "Fragment" << center << rotation << "\n"; }
 // void ogstreamFake::drawProjectile(const Position& center) { *this << "Projectile" << center << "\n"; }
 // void ogstreamFake::drawCrewDragon(const Position& center, double rotation) { *this << "CrewDragon" << center << rotation << "\n"; }
 // void ogstreamFake::drawCrewDragonRight(const Position& center, double rotation, const Position& offset) { *this << "CrewDragonRight" << center << rotation << "\n"; }
 // void ogstreamFake::drawCrewDragonLeft(const Position& center, double rotation, const Position& offset) { *this << "CrewDragonLeft " << center << rotation << "\n"; }
 // void ogstreamFake::drawCrewDragonCenter(const Position& center, double rotation) { *this << "CrewDragonCenter" << center << rotation << "\n"; }
 // void ogstreamFake::drawSputnik(const Position& center, double rotation) { *this << "Sputnik" << center << rotation << "\n"; }
 // void ogstreamFake::drawGPS(const Position& center, double rotation) { *this << "GPS" << center << rotation << "\n"; }
 // void ogstreamFake::drawGPSCenter(const Position& center, double rotation) { *this << "GPSCenter" << center << rotation << "\n"; }
 // void ogstreamFake::drawGPSRight(const Position& center, double rotation, const Position& offset) { *this << "GPSRight" << center << rotation << "\n"; }
 // void ogstreamFake::drawGPSLeft(const Position& center, double rotation, const Position& offset) { *this << "GPSLeft" << center << rotation << "\n"; }
 // void ogstreamFake::drawHubble(const Position& center, double rotation) { *this << "Hubble" << center << rotation << "\n"; }
 // void ogstreamFake::drawHubbleComputer(const Position& center, double rotation, const Position& offset) { *this << "HubbleComputer" << center << rotation << "\n"; }
 // void ogstreamFake::drawHubbleTelescope(const Position& center, double rotation, const Position& offset) { *this << "HubbleTelescope" << center << rotation << "\n"; }
 // void ogstreamFake::drawHubbleLeft(const Position& center, double rotation, const Position& offset) { *this << "HubbleLeft" << center << rotation << "\n"; }
 // void ogstreamFake::drawHubbleRight(const Position& center, double rotation, const Position& offset) { *this << "HubbleRight" << center << rotation << "\n"; }
 // void ogstreamFake::drawStarlink(const Position& center, double rotation) { *this << "Starlink" << center << rotation << "\n"; }
 // void ogstreamFake::drawStarlinkBody(const Position& center, double rotation, const Position& offset) { *this << "StarlinkBody" << center << rotation << "\n"; }
 // void ogstreamFake::drawStarlinkArray(const Position& center, double rotation, const Position& offset) { *this << "StarlinkArray" << center << rotation << "\n"; }
 // void ogstreamFake::drawShip(const Position& center, double rotation, bool thrust) { *this << "Ship" << center << rotation << "\n"; }
 // void ogstreamFake::drawEarth(const Position& center, double rotation) { *this << "Earth" << center << rotation << "\n"; }
 // void ogstreamFake::drawStar(const Position& center, unsigned char phase) { *this << "Star" << center << phase << "\n"; }

 /******************************************************************
  * RANDOM
  * This function generates a random number.
  *
  *    INPUT:   min, max : The number of values (min <= num <= max)
  *    OUTPUT   <return> : Return the integer
  ****************************************************************/
int random(int min, int max)
{
    assert(min < max);
    int num = (rand() % (max - min)) + min;
    assert(min <= num && num <= max);

    return num;
}

/******************************************************************
 * RANDOM
 * This function generates a random number.
 *
 *    INPUT:   min, max : The number of values (min <= num <= max)
 *    OUTPUT   <return> : Return the double
 ****************************************************************/
double random(double min, double max)
{
    assert(min <= max);
    double num = min + ((double)rand() / (double)RAND_MAX * (max - min));

    assert(min <= num && num <= max);

    return num;
}
