#include "Ray.h"

Ray::Ray()
{
}

Ray::Ray(const Vector3f& origin, const Vector3f& direction)
    : origin(origin), direction(direction)
{
}

/* Takes a parameter t and returns the point accoring to t. t is the parametric variable in the ray equation o+t*d.*/
Vector3f Ray::getPoint(float t) const 
{
    return  {this->origin.x + this->direction.x*t,
                     this->origin.y + this->direction.y*t,
                     this->origin.z + this->direction.z*t};
}

/* Takes a point p and returns the parameter t according to p such that p = o+t*d. */
float Ray::gett(const Vector3f & p) const
{
    if (this->direction.x != 0)
    {
        return (p.x - this->origin.x) / this->direction.x;
    }
    else if (this->direction.y != 0)
    {
        return (p.y-this->origin.y)/this->direction.y;
    }
    else if(this->direction.z != 0)
    {
        return (p.z-this->origin.z)/this->direction.z;
    }
    else
    {
        return 0;
    }
}

