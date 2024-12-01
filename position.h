/***********************************************************************
 * Header File:
 *    POSITION
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a location on the screen.
 ************************************************************************/


#pragma once

#include <iostream> 
#include <cmath>

class TestPosition;
class Acceleration;
class Velocity;
class TestSatellite;
class TestSputnik;
class TestHubble;
class TestStarlink;
class TestCrewDragon;
class TestGPS;
class TestShip;


/*********************************************
 * Position
 * A single position on the field in Meters  
 *********************************************/
class Position
{
public:
   friend ::TestPosition;
   friend ::TestSatellite;
   friend :: TestSputnik;
   friend ::TestHubble;
   friend ::TestStarlink;
   friend ::TestCrewDragon;
   friend ::TestGPS;
   friend ::TestShip;

   
   // constructors
   Position()            : x(0.0), y(0.0)  {}
   Position(double x, double y);
   Position(const Position & pt) : x(pt.getMetersX()), y(pt.getMetersY()) {}
   Position& operator = (const Position& pt);

   // getters
   double getMetersX()       const { return x; }
   double getMetersY()       const { return y; }
   double getPixelsX()       const { return x / metersFromPixels; }
   double getPixelsY()       const { return y / metersFromPixels; }
   double getZoom()          const { return metersFromPixels; }

   // setters
   void setZoom(double z) { metersFromPixels = z; }
   void setMeters(double xMeters, double yMeters) { }
   void setMetersX(double xMeters) { this->x = xMeters; }
   void setMetersY(double yMeters) { this->y = yMeters; }
   void setPixelsX(double xPixels) { this->x = xPixels * metersFromPixels; }
   void setPixelsY(double yPixels) { this->y = yPixels * metersFromPixels; }
   void addMetersX(double dxMeters) { setMetersX(getMetersX() + dxMeters); }
   void addMetersY(double dyMeters) { setMetersY(getMetersY() + dyMeters); }
   void addPixelsX(double dxPixels) { setPixelsX(getPixelsX() + dxPixels); }
   void addPixelsY(double dyPixels) { setPixelsY(getPixelsY() + dyPixels); }
   void add(const Acceleration& a, const Velocity& v, double t);
   void reverse() {  }


private:
   double x;                 // horizontal position
   double y;                 // vertical position
   static double metersFromPixels;
};



// stream I/O useful for debugging
std::ostream & operator << (std::ostream & out, const Position& pt);
std::istream & operator >> (std::istream & in,        Position& pt);


/*********************************************
 * PT
 * Trivial point
 *********************************************/
struct PT
{
   double x;
   double y;
};


