#include "Light.h"

/* Constructor. Implemented for you. */
PointLight::PointLight(const Vector3f & position, const Vector3f & intensity)
    : position(position), intensity(intensity)
{
}

// Compute the contribution of light at point p using the
// inverse square law formula
Vector3f PointLight::computeLightContribution(const Vector3f& p)
{
    Vector3f lightPosition = this->position;

    float distanceX = lightPosition.x - p.x;
    float distanceY = lightPosition.y - p.y;
    float distanceZ = lightPosition.z - p.z;

    float distanceSquared = distanceX*distanceX + distanceY*distanceY + distanceZ*distanceZ;

    // TODO 4 ask if we need to check distanceSquare is 0
    return {
            intensity.x/distanceSquared,
            intensity.y/distanceSquared,
            intensity.z/distanceSquared
    };
}
