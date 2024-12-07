#include "celestialObject.h"
#include "simulator.h"
#include <cmath>
#include "fragment.h"

bool CelestialObject::isHit(CelestialObject* other) {
	// Calculate the distance between the centers of the two circles
	double distance = sqrt(pow(this->pos.getMetersX() - other->pos.getMetersX(), 2) + pow(this->pos.getMetersY() - other->pos.getMetersY(), 2));

	if (distance < (this->getRadius() + other->getRadius()))
		return true; // Collision detected

	return false; // No collision
};

void CelestialObject::breakApart(Simulator* sim, vector<CelestialObject*> subParts)
{
	setHasBeenHit(true);
	setExpired(true);
	for (int i = 0; i < this->numFragments; i++) {
		sim->addObject(new Fragment(this->pos, randomVelocity(this->getVelocity())));
	}
};

void CelestialObject::addObjects(Simulator* sim, vector<CelestialObject*> objs) {
	assert(false);
	vector<Velocity> directions = getSubPartVel(objs.size());
	vector<Position> startingPos = getSubPartPos(directions);
	assert((objs.size() == directions.size()) && (objs.size() == startingPos.size()) && (directions.size() == startingPos.size()));
	vector<Position>::iterator pos = startingPos.begin();
	vector<Velocity>::iterator vel = directions.begin();
	for (vector<CelestialObject*>::iterator part = objs.begin(); part != objs.end(); part++, pos++, vel++)
	{
		CelestialObject* newObj = *part;
		newObj->setPosition(*pos);
		newObj->setVelocity(*vel);
		sim->addObject(newObj);
	}
}

vector<Velocity> CelestialObject::getSubPartVel(int subParts) {
	vector<Velocity> velocities;
	for (int i = 0; i < subParts; i++)
	{
		Velocity newVel = Velocity(this->vel);
		Angle newAngle = Angle(newVel.getAngle().getRadian());
		newAngle += Angle(((i * 2 * 3.142) / (subParts + 1)));
		newVel.addMeters(random(5000.0, 9000.0), newAngle);
		velocities.push_back(newVel);
	}
	return velocities;
}

vector<Position> CelestialObject::getSubPartPos(vector<Velocity> directions) {
	vector<Position> positions;
	for (auto direction : directions)
	{
		Position newPos = Position(this->pos);
		newPos.addPixels(24, direction.getAngle());
		positions.push_back(newPos);
	}
	return positions;
}

Velocity CelestialObject::randomVelocity(Velocity v) {
	return Velocity(
		v.getDx() + ((v.getDx() > 0) ? random(0, 4000) : random(-4000, 0)),
		v.getDy() + ((v.getDy() > 0) ? random(0, 4000) : random(-4000, 0))
	);
}

