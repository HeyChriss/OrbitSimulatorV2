#include "velocity.h"
#include "angle.h"
#include <cmath>

#include <cmath>

const double M_PI = std::acos(-1.0);


Velocity::Velocity()
{
	dx = 0;
	dy = 0;
}

Velocity::Velocity(float dx, float dy)
{
	this->dx = dx;
	this->dy = dy;
}

float Velocity::getDx()
{
	return dx;
}

float Velocity::getDy()
{
	return dy;
}

float Velocity::getSpeed() const
{
	return sqrt((dx * dx) + (dy * dy));
}

void Velocity::setDx(float dx)
{
	this->dx = dx;
}

void Velocity::setDy(float dy)
{
	this->dy = dy;
}

Angle Velocity::getAngle() {
	if (dx == 0 && dy == 0)
		return Angle(0);
	return Angle(atan2(this->dx, this->dy));
}


void Velocity::addMeters(double totalMeters, Angle angle) {
	double xMeters = totalMeters * sin(angle.getDegree());
	double yMeters = totalMeters * cos(angle.getDegree());

	this->addMetersX(xMeters);
	this->addMetersY(yMeters);
};

void Velocity::addPixels(double totalPixels, Angle angle) {
	// Convert degrees to radians
	double radians = angle.getDegree() * M_PI / 180.0;

	double xPixels = totalPixels * sin(radians); // Use radians
	double yPixels = totalPixels * cos(radians); // Use radians

	this->addPixelsX(xPixels);
	this->addPixelsY(yPixels);
}

double Velocity::metersFromPixels = 40;


Angle VelocityDummy::getAngle() const
{
	assert(false);
	return Angle();
}