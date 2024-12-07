/***********************************************************************
 * Header File:
 *    Simulator Class
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about Simulator class 
 ************************************************************************/
#pragma once
#include "uiInteract.h" 
#include "star.h"
#include "earth.h"
#include "ship.h"
#include "projectile.h"
#include "hubble.h"
#include "starlink.h"
#include "sputnik.h"
#include "gps.h"
#include "dragon.h"
#include <list> 

const double TIME = (24 * 60.0 / 30);

class TestHubble;
class TestDragon;

class Simulator {
public:
    friend TestHubble;
    friend TestDragon;

    Simulator(bool dummyConstructor) {}

    Simulator();
    ~Simulator();

    void addObjects();
    //    void removeObject(CelestialObject* objectToDelete);
    void createStars(int numStars);
    void addObject(CelestialObject* newObj) { this->celestialObjects.push_back(newObj); };

    void getInput(const Interface* pUI);
    void update();
    void display();

protected:
    list<CelestialObject*> celestialObjects;
    Spaceship* ship;
    Earth* planet;
    Physics physics;
    list<Star*> stars;
    double timeDilatation;
};


class DummySimulator : public Simulator {
public:

    DummySimulator() : Simulator(true) {
        Simulator::addObjects();
        this->timeDilatation = TIME;
    }

    DummySimulator(string satellite = "") : Simulator(true) {
        addObjects(satellite);
        this->timeDilatation = TIME;
    }

    ~DummySimulator()
    {
        while (!celestialObjects.empty()) {
            delete celestialObjects.front();
            celestialObjects.pop_front();
        }
    }

    void createStars(int numStars) { assert(false); }

    void addObjects(string satellite);

    void update() {
        for (CelestialObject* obj : celestialObjects)
            obj->update(this->timeDilatation, this->planet->getGravity(), this->planet->getRadius());
    }

    void display() { assert(false); }
};

