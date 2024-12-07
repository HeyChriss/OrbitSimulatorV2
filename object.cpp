#pragma once
#include "object.h"
#include "ship.h"

void Object::update(double time, double gravity, double planetRadius)
{
    double x = this->pos.getMetersX();
    double y = this->pos.getMetersY();
    double dx = this->vel.getMetersX();
    double dy = this->vel.getMetersY();

    double angle = physics.computeDirection(x, y);
    double height = physics.heightAbovePlanet(x, y, planetRadius);
    double gh = physics.gravityEquation(height, planetRadius, gravity);

    double ddx = physics.horizontalAcceleration(gh, angle);
    double ddy = physics.verticalAcceleration(gh, angle);

    double newDx = physics.velocityConstantAcceleration(dx, ddx, time);
    double newDy = physics.velocityConstantAcceleration(dy, ddy, time);
    this->setVelocity(Velocity(newDx, newDy));

    double newX = physics.distanceFormula(x, newDx, ddx, time);
    double newY = physics.distanceFormula(y, newDy, ddy, time);
    this->pos.setMeters(newX, newY);
}
