#include <cmath>
#include "angle.h" 

void Angle::normalize()
{
    // Normalize within [-2π, 2π]
    while (radAngle >= fullRevolutionRad) {
        radAngle -= fullRevolutionRad;
    }
    while (radAngle < 0) {
        radAngle += fullRevolutionRad;
    }

    // Ensure exact values at boundaries normalize to 0
    if (fabs(radAngle - fullRevolutionRad) < 1e-9) {
        radAngle = 0.0;
    }
}

void Angle::setDegree(double degree) { this->radAngle = degree * pi / 180.0; normalize(); }
void Angle::addDegree(double degree) { this->radAngle += degree * pi / 180.0; normalize(); };
double Angle::getDegree() const { return radAngle * 180.0 / pi; }

Angle& Angle::operator += (const Angle& twoD) {
    this->radAngle += twoD.radAngle;
    normalize();
    return *this;
}

Angle& Angle::operator-=(const Angle& twoD)
{
    this->radAngle -= twoD.radAngle;
    normalize();
    return *this;
}

Angle& Angle::operator*=(const double scale)
{
    this->radAngle *= scale;
    normalize();
    return *this;
}
