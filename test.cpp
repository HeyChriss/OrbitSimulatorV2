#include "test.h"
#include "testPosition.h"
#include "testVelocity.h"
#include "testAcceleration.h"
#include "testAngle.h"
#include "testSatellite.h"
//#include "testDirection.h"
//#include "TestSimulationObject.h"
//#include "TestSatellite.h"
//#include "TestSputnik.h"

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
	//TestDirection().run();
	//TestSimulationObject().run();
	//TestSatellite().run();
	//TestSputnik().run();


}
