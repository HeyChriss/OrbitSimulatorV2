/***********************************************************************
 * SourceFile:
 *    SHIP
 * Author:
 *    Chris Mijango & Seth Chen
 * Summary:
 *    The ship class
 ************************************************************************/


#include "Ship.h"

void Ship::input(const Interface& ui)
{
    // Rotate 0.1 radians left or right based on input
    if (ui.isRight())
        this->angle.add(0.1);
    if (ui.isLeft())
        this->angle.add(-0.1);

    // Track thrust state for drawing
    isThrusting = ui.isDown();

    if (isThrusting)
    {
        // Calculate thrust effect based on the direction the ship is pointing
        Acceleration thrust;

        // Apply 2.0 m/s² thrust in the ship's current direction
        thrust.setDDX(2.0 * sin(angle.getRadians()));
        thrust.setDDY(2.0 * cos(angle.getRadians()));

        // Apply single velocity update with 48 second time dilation
        velocity.addDX(thrust.getDDX() * 48.0);
        velocity.addDY(thrust.getDDY() * 48.0);

        // Update position with new velocity
        pos.addMetersX(velocity.getDX());
        pos.addMetersY(velocity.getDY());
    }

    // Fire projectile when space is pressed
    if (ui.isSpace() && !isDead() && !isInvisible())
    {

        Projectile* projectile = new Projectile(*this, angle.getRadians());
        satellites.push_back(projectile);

        // Debug log
        std::cout << "Projectile fired! Current satellite count: " << satellites.size() << std::endl;

    }

}