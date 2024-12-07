

/***********************************************************************
 * Header File:
 *    Sputnik
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about Sputnik 
 ************************************************************************/
#pragma once
#include "satellite.h"

class Sputnik : public Satellite
{
public:
	friend class TestSputnik;
	Sputnik(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle());
	//   void breakApart(Simulator* sim, vector<CelestialObject*> subParts = {});
	void draw() { ogs.drawSputnik(pos, rotationAngle.getDegree()); }

};

