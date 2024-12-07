#include "simulator.h"
#include "fragment.h"

Simulator::Simulator() {
    addObjects();
    createStars(500);
    this->timeDilatation = TIME;
}

Simulator::~Simulator() {
    while (!celestialObjects.empty()) {
        delete celestialObjects.front();
        celestialObjects.pop_front();
    }
    while (!stars.empty()) {
        delete stars.front();
        stars.pop_front();
    }
}

void Simulator::addObjects()
{
    addObject(new Sputnik(Position(-36515095.13, 21082000.0), Velocity(2050.0, 2684.68)));


    addObject(new GPS::GPS(Position(0.0, 26560000.0), Velocity(-3880.0, 0.0)));
    addObject(new GPS::GPS(Position(23001634.72, 13280000.0), Velocity(-1940.00, 3360.18)));
    addObject(new GPS::GPS(Position(23001634.72, -13280000.0), Velocity(1940.00, 3360.18)));
    addObject(new GPS::GPS(Position(0.0, -26560000.0), Velocity(3880.0, 0.0)));
    addObject(new GPS::GPS(Position(-23001634.72, -13280000.0), Velocity(1940.00, -3360.18)));
    addObject(new GPS::GPS(Position(-23001634.72, 13280000.0), Velocity(-1940.00, -3360.18)));

    addObject(new Hubble::Hubble(Position(0.0, -physics.geoStationaryOrbitHeightMeters), Velocity(3100.0, 0.0)));

    addObject(new Dragon::Dragon(Position(0.0, 8800000.0), Velocity(-7900.0, 0.0)));

    addObject(new Starlink::Starlink(Position(0.0, -14020000.0), Velocity(5800.0, 0.0)));

    Position shipPos = Position();

    shipPos.setPixelsX(-450);
    shipPos.setPixelsY(450);
    this->ship = new Spaceship(shipPos, Velocity(0.0, -2000.0));
    addObject(ship);

    this->planet = new Earth();
    addObject(planet);
}

void DummySimulator::addObjects(string satellite)
{
    this->planet = new Earth();
    if (satellite == "Hubble" || satellite == "") {
        addObject(new Hubble::Hubble(Position(0.0, -physics.geoStationaryOrbitHeightMeters), Velocity(physics.geoStationarySpeed, 0.0)));
    }
    else if (satellite == "Dragon") {
        addObject(new Dragon::Dragon(Position(0.0, 8000000.0), Velocity(-7900.0, 0.0)));
    }
    else if (satellite == "GPS") {
        addObject(new GPS::GPS(Position(0.0, 26560000.0), Velocity(-3880.0, 0.0)));
    }
    else if (satellite == "Sputnik") {
        addObject(new Sputnik(Position(-36515095.13, 21082000.0), Velocity(2050.0, 2684.68)));
    }
    else if (satellite == "Starlink") {
        addObject(new Starlink::Starlink(Position(0.0, -13020000.0), Velocity(5800.0, 0.0)));
    }


}

void Simulator::createStars(int numStars)
{
    for (int i = 0; i < numStars; i++)
    {
        Position initial;
        initial.setPixelsX(random(-500, 500));
        initial.setPixelsY(random(-500, 500));
        this->stars.push_back(new Star(initial));
    }
};


void Simulator::getInput(const Interface* pUI)
{
    if (this->ship != NULL)
    {
        Angle shipRotation;
        if (pUI->isLeft())
            shipRotation.setDegree(-0.1);
        if (pUI->isRight())
            shipRotation.setDegree(0.1);
        ship->addRotation(shipRotation);
        if (pUI->isDown())
            ship->setThrust(true);
        else
            ship->setThrust(false);

        if (pUI->isSpace() && !this->ship->getExpired())
        {
            this->addObject(new Projectile(this->ship));
        }
    }
}

void Simulator::update()
{
    list<CelestialObject*> hitObjects;
    for (CelestialObject* obj : celestialObjects)
    {
        obj->update(this->timeDilatation, this->planet->getGravity(), this->planet->getRadius());
    }
    for (CelestialObject* obj : celestialObjects)
    {
        for (CelestialObject* collisionObject : celestialObjects)
        {
            if (collisionObject == obj) continue;  // You can't hit yourself
            if (obj->isHit(collisionObject)) {
                if (dynamic_cast<Earth*>(obj) != nullptr) continue; // Earth cannot break apart
                if (dynamic_cast<Earth*>(collisionObject) != nullptr) {
                    // Falls into earth
                    obj->setExpired(true);
                }
                else if (!obj->getHasBeenHit()) {
                    hitObjects.push_back(obj);
                }
            }
        }
    }

    for (CelestialObject* obj : hitObjects) {
        obj->breakApart(this);
    }

    // Remove defunct objects
    for (auto it = celestialObjects.begin(); it != celestialObjects.end();) {
        if ((*it)->getExpired()) {
            it = celestialObjects.erase(it);
        }
        else {
            ++it;
        }
    }

    for (Star* star : stars)
        star->update(this->timeDilatation);
}

void Simulator::display() {
    for (auto star : stars)
        star->draw();
    for (auto obj : celestialObjects)
        obj->draw();
}

