/***********************************************************************
 * Header File:
 *    Velocity
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about velocity
 ************************************************************************/
#pragma once
#include "angle.h"
class Velocity
{
private:
	double dx;
	double dy;

public:

	friend class TestVelocity;
	friend class TestCelestialObject;
	friend class TestObject;
	friend class TestHubble;
	friend class TestDragon;
	friend class TestGPS;
	friend class TestShip;
	friend class TestSputnik;
	friend class TestStarlink;
	friend class TestSatellite;
	friend class TestProjectile;
	friend class TestFragment;
	friend class TestPart;

	Velocity();
	Velocity(double dx, double dy);

	Velocity& operator += (const Velocity& twoD) {
		this->dx += twoD.dx;
		this->dy += twoD.dy;
		return *this;
	}

	double getDx();
	double getDy();
	double getSpeed() const;
	Angle getAngle();
	void setDx(double dx);
	void setDy(double dy);
	void addMeters(double change, Angle angle);
	void addMetersX(double dxMeters) { setMetersX(getMetersX() + dxMeters); }
	void addMetersY(double dyMeters) { setMetersY(getMetersY() + dyMeters); }
	void addPixels(double change, Angle angle);
	void addPixelsX(double dxPixels) { setPixelsX(getPixelsX() + dxPixels); }
	void addPixelsY(double dyPixels) { setPixelsY(getPixelsY() + dyPixels); }
	double getMetersX()       const { return dx; }
	double getMetersY()       const { return dy; }
	double getPixelsX()       const { return dx / metersFromPixels; }
	double getPixelsY()       const { return dy / metersFromPixels; }
	void setMeters(double xMeters, double yMeters) { dx = xMeters; dy = yMeters; }
	void setMetersX(double xMeters) { dx = xMeters; }
	void setMetersY(double yMeters) { dy = yMeters; }
	void setPixelsX(double xPixels) { dx = xPixels * metersFromPixels; }
	void setPixelsY(double yPixels) { dy = yPixels * metersFromPixels; }
protected:
	static double metersFromPixels;
};



#include <cassert>
/*********************************************
 * VelocityDummy
 * A Dummy double for velocity. This does nothing but assert.
 * Stubs will be derived from this for the purpose of making
 * isolated unit tests.
 *********************************************/
class VelocityDummy : public Velocity
{
public:
	// getters
	double    getDX()    const { assert(false); return 0.0; }
	double    getDY()    const { assert(false); return 0.0; }
	double    getSpeed() const { assert(false); return 0.0; }
	Angle     getAngle() const;

	// setters
	void setDX(double dx) { assert(false); }
	void setDY(double dy) { assert(false); }
	void setDxDy(double dx, double dy) { assert(false); }
	void setDirection(const Angle& direction) { assert(false); }
	void setSpeed(double speed) { assert(false); }
	void set(const Angle& angle, double magnitude) { assert(false); }
	void addDX(double dx) { assert(false); }
	void addDY(double dy) { assert(false); }
	void add(const Velocity& v) { assert(false); }
	void reverse() { assert(false); }
};
