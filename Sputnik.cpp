#include "sputnik.h"

Sputnik::Sputnik(Position pos, Velocity vel, Angle angle) : Satellite(pos, vel, angle)
{
	Satellite(pos, vel, angle);
	this->radius = 4;
	this->numFragments = 4;
}
