#include "testShip.h"

void TestShip::testConstructor() {
    // Setup & Exercise
    DummySpaceship ship;

    // Verify
    assertUnit(ship.getRotation().getDegree() == 0.0);
    assertUnit(ship.getPosition().getMetersX() == 0.0);
    assertUnit(ship.getPosition().getMetersY() == 0.0);
}  // Teardown

void TestShip::testThrustUp() {
    // Setup
    DummySpaceship ship;
    ship.thrust = true;

    // Exercise
    ship.update();
    Position p = ship.getPosition();

    // Verify
    assertEquals(p.getMetersX(), 0.0);
    assertUnit(p.getMetersY() > 0.0);

}  // Teardown

void TestShip::testThrustDown() {
    // Setup
    DummySpaceship ship;
    ship.rotationAngle.setDegree(180.0);
    ship.thrust = true;

    // Exercise
    ship.update();
    Position p = ship.getPosition();

    // Verify
    assertUnit(p.getMetersY() < 0.0);

}  // Teardown

