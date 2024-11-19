/***********************************************************************
 * Source File:
 *    SATELLITE
 * Author:
 *    <your name here>
 * Summary:
 *    Implementation of the Satellite class
 ************************************************************************/

#include "satellite.h"
#include "acceleration.h"

 // Constants
const double EARTH_RADIUS = 6378000.0;    // meters
const double G = 9.80665;                 // m/s^2
const double TIME_DILATION = 1440.0;      // 24 hours * 60 minutes
const double FRAME_RATE = 30.0;           // frames per second
const double TIME_PER_FRAME = TIME_DILATION / FRAME_RATE;

 /*********************************************
  * SATELLITE : GET GRAVITY
  * Get the acceleration due to gravity at a given position
  *********************************************/
Acceleration Satellite::getGravity(const Position& pos) const
{
    // Get current position relative to Earth's center
    double dx = pos.getMetersX();
    double dy = pos.getMetersY();

    // Calculate distance from Earth's center
    double distance = sqrt(dx * dx + dy * dy);

    // No gravity at center of Earth
    if (distance == 0.0)
        return Acceleration(0.0, 0.0);

    // Calculate acceleration magnitude using inverse square law
    double magnitude = G * pow(EARTH_RADIUS / distance, 2.0);

    // Calculate acceleration components (negative because gravity pulls toward center)
    Acceleration gravity;
    gravity.setDDX(-magnitude * dx / distance);
    gravity.setDDY(-magnitude * dy / distance);

    return gravity;
}



 /*********************************************
  * SATELLITE : CONSTRUCTOR with Parent and Direction
  * Create a Satellite (called by the derived classes)
  *********************************************/
Satellite::Satellite(const Satellite& parent, const Angle& direction) :
    velocity(parent.velocity),
    pos(parent.pos),
    angle(parent.angle),
    angularVelocity(parent.angularVelocity),
    radius(0.0),
    age(0),
#ifdef NDEBUG
    useRandom(parent.useRandom),
#endif
    dead(false)
{
    // compute the kick
    double speed = random(1000.0, 3000.0);
#ifdef NDEBUG
    if (parent.useRandom == false)
        speed = 3000.0;
#endif // DEBUG
    Velocity kick;
    kick.set(direction, speed);
    velocity.add(kick);

    // compute the offset
    Position posKick;
    posKick.setPixelsX(4.0 * sin(direction.getRadians()));
    posKick.setPixelsY(4.0 * cos(direction.getRadians()));
    pos.addMetersX(posKick.getMetersX());
    pos.addMetersY(posKick.getMetersY());
}

/*********************************************
 * SATELLITE : CONSTRUCTOR with Parent, Offset and Kick
 * Used to create projectiles with specific speeds
 *********************************************/
Satellite::Satellite(const Satellite& parent, const Position& offset, const Velocity& kick) :
    velocity(parent.velocity),
    pos(parent.pos),
    angle(parent.angle),
    angularVelocity(parent.angularVelocity),
    radius(0.0),
    age(0),
#ifdef NDEBUG
    useRandom(parent.useRandom),
#endif
    dead(false)
{
    // new velocity is the velocity of your parent plus the direction of the "kick"
    velocity.add(kick);

    // advance by one time unit so we do not hit our parent
    pos.addMetersX(offset.getMetersX());
    pos.addMetersY(offset.getMetersY());
}

/*********************************************
 * SATELLITE : MOVE
 * Inertia and gravity using proper time dilation
 *********************************************/
void Satellite::move(double time)
{
    // Get gravity acceleration at current position
    Acceleration aGravity = getGravity(pos);

    // Update velocity first with gravity
    velocity.addDX(aGravity.getDDX() * time);  // v = v0 + at
    velocity.addDY(aGravity.getDDY() * time);

    // Update position with current velocity
    pos.addMetersX(velocity.getDX() * time);   // x = x0 + vt
    pos.addMetersY(velocity.getDY() * time);

    // Update rotation
    angle.add(angularVelocity);

    // Update age
    age++;
}
