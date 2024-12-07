/***********************************************************************
 * Header File:
 *    Projectile
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about Projectile
 ************************************************************************/
#ifndef projectile_h
#define projectile_h

#include "object.h"
#include "fragment.h"
#include "ship.h"

#include <stdio.h>

class Projectile : public Fragment {
public:
    friend class TestProjectile; 
    Projectile(Spaceship* ship);

    void draw() { if (!getExpired()) ogs.drawProjectile(pos); }
    void update(double time, double gravity, double planetRadius);

protected:
    Angle angle;
};

#endif /* projectile_h */

