#include "test.h"
#include "testPosition.h"
#include "testVelocity.h"
#include "testAcceleration.h"
#include "testAngle.h"
#include "testSatellite.h"
#include "testSputnik.h"
#include "testHubble.h"
#include "TestStarlink.h"
#include "TestCrewDragon.h"
#include "TestGPS.h"
#include "TestShip.h"
#include "TestPart.h"
#include "TestFragment.h"
#include "TestProjectile.h"

/*****************************************************************
 * TEST RUNNER
 * Runs all the unit tests
 ****************************************************************/
void testRunner()
{
	TestPosition().run();
	TestVelocity().run();
	TestAcceleration().run();
	TestAngle().run();
	TestSatellite().run();
	TestSputnik().run();
	TestHubble().run();
	TestStarlink().run();
	TestCrewDragon().run();
	TestGPS().run();
	TestShip().run();
	TestPart().run();
	TestFragment().run();
	TestProjectile().run();

}
