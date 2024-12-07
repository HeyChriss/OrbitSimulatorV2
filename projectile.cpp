#include "projectile.h"

Projectile::Projectile(Spaceship* ship) {
    double speed = 10000.0;
    Position shipPosition = ship->getPosition();

    double shipRotation = ship->getRotation().getDegree();

    this->pos.setMeters(shipPosition.getMetersX(), shipPosition.getMetersY());
    this->setVelocity(Velocity(physics.horizontalAcceleration(speed, shipRotation), physics.verticalAcceleration(speed, shipRotation)));
}


void Projectile::update(double time, double gravity, double planetRadius) {
    if (isExpired())
        setExpired(true);
    else
    {
        double x = this->pos.getMetersX();
        double y = this->pos.getMetersY();
        double dx = this->vel.getMetersX();
        double dy = this->vel.getMetersY();

        double newX = physics.distanceFormula(x, dx, 0.0, time);
        double newY = physics.distanceFormula(y, dy, 0.0, time);
        this->pos.setMeters(newX, newY);
    }
}
