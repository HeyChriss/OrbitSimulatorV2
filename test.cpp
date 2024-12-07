/***********************************************************************
 * Header File:
 *    test
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about test
 ************************************************************************/

#include "test.h"
#include "testPosition.h"
#include "testPhysics.h"
#include "testHubble.h"
#include "testShip.h"
#include "testAcceleration.h"
#include "TestDirection.h"
#include "TestVelocity.h"
#include "TestCelestialObject.h"
#include "TestSatellite.h"
#include "TestObject.h"
#include "TestDragon.h"
#include "TestGPS.h"
#include "TestSputnik.h"
#include "TestStarlink.h"
#include "TestProjectile.h"
#include "TestFragment.h"
#include "TestPart.h"

 /*****************************************************************
  * TEST RUNNER
  * Runs all the unit tests
  ****************************************************************/
void testRunner()
{
	TestPosition().run();
	TestVelocity().run();
	TestAngle().run();
	TestPhysics().run();
	TestAcceleration().run();
	TestDirection().run();
	TestCelestialObject().run();
	TestObject().run();
	TestSatellite().run();
	TestHubble().run();
	TestDragon().run();
	TestGPS().run();
	TestSputnik().run();
	TestStarlink().run();
	TestShip().run();
	TestProjectile().run();
	TestFragment().run();
	TestPart().run();

}
