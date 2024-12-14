/***********************************************************************
 * Header File:
 *    Ship
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about Ship
 ************************************************************************/
#pragma once
#include "satellite.h"
class Spaceship : public Satellite
{
	friend class TestShip;
	friend class TestProjectile;
public:
	Spaceship(Position pos = Position(), Velocity vel = Velocity(), Angle angle =
		Angle()) : Satellite(pos, vel, angle) {
		this->defective = false;
		this->thrust = false;
		this->radius = 10;
		this->numFragments = 4;
		this->rotationAngle.setDegree(0);
	};
	bool isHit(CelestialObject* other);
	void update(double time, double gravity, double planetRadius);
	void setThrust(bool t) { this->thrust = t; }
	bool getThrust() { return this->thrust; };
	void draw() { ogs.drawShip(pos, rotationAngle.getDegree(), getThrust()); }
private:
	bool thrust;
};
class DummySpaceship : Spaceship {
	friend class TestShip;
public:
	DummySpaceship() : Spaceship() {}
	void update(double time = 1, double gravity = 0.0, double planetRadius = 0.0)
		override;
	void draw() override { assert(false); }
};


