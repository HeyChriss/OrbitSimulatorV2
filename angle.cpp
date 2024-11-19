/***********************************************************************
 * Source File:
 *    ANGLE
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#include "angle.h"
#include <math.h>  // for floor()
#include <cassert>
using namespace std;

 /************************************
  * ANGLE : NORMALIZE
  ************************************/
double Angle::normalize(double radians) const
{
	while (radians > 2 * M_PI || radians < 0)
	{
		if (radians > 2 * M_PI)
			radians -= 2 * M_PI;
		if (radians < 0)
			radians += 2 * M_PI;
	}
	return radians;
}



