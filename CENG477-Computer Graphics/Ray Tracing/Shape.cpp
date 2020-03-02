#include "Shape.h"
#include "Scene.h"
#include <cstdio>
//TODO : added includes
#include <math.h>
#include <cfloat>

Shape::Shape(void)
{
}

Shape::Shape(int id, int matIndex)
    : id(id), matIndex(matIndex)
{
}

Sphere::Sphere(void)
{}

/* Constructor for sphere. You will implement this. */
Sphere::Sphere(int id, int matIndex, int cIndex, float R)
    : Shape(id, matIndex)
{
    this->centerIndex = cIndex;
    this->radius = R;
    this->radiusSquared= R*R;
}

/* Sphere-ray intersection routine. You will implement this. 
Note that ReturnVal structure should hold the information related to the intersection point, e.g., coordinate of that point, normal at that point etc. 
You should to declare the variables in ReturnVal structure you think you will need. It is in defs.h file. */
ReturnVal Sphere::intersect(const Ray & ray) const
{
    Vector3f sphereCenterOffset = {
            ray.origin.x - pScene->vertices[this->centerIndex-1].x,
            ray.origin.y - pScene->vertices[this->centerIndex-1].y,
            ray.origin.z - pScene->vertices[this->centerIndex-1].z
    };

    float leftDiscriminant=ray.direction.x*sphereCenterOffset.x +
            ray.direction.y*sphereCenterOffset.y +
            ray.direction.z*sphereCenterOffset.z;

    float directionSquared = ray.direction.x*ray.direction.x + ray.direction.y*ray.direction.y + ray.direction.z*ray.direction.z;

    float discriminant = leftDiscriminant*leftDiscriminant -
            (directionSquared) *
                    (sphereCenterOffset.x*sphereCenterOffset.x + sphereCenterOffset.y*sphereCenterOffset.y
                     + sphereCenterOffset.z*sphereCenterOffset.z - this->radiusSquared);

    if(discriminant > pScene->intTestEps)//2 t's, take the smaller one(unless t<0)
    {
        //TODO 4 math library
        float discriminantRoot= sqrtf(discriminant);
        float minusB = -(ray.direction.x*sphereCenterOffset.x +
            ray.direction.y*sphereCenterOffset.y+
            ray.direction.z*sphereCenterOffset.z);

        float cachedMinusDiscriminantRoot = minusB - discriminantRoot;
        if(minusB - discriminantRoot > pScene->intTestEps) {
            cachedMinusDiscriminantRoot = minusB - discriminantRoot;
        }
        else if(minusB + discriminantRoot > pScene->intTestEps)
        {
            cachedMinusDiscriminantRoot = minusB + discriminantRoot;
        }
        else
        {
            return {0, 0, 0, FLT_MAX}; // TODO : maybe return 0
        }

        float t = cachedMinusDiscriminantRoot / directionSquared;

        Vector3f intersection = Vector3f{
                ray.origin.x + ray.direction.x*t,
                ray.origin.y + ray.direction.y*t,
                ray.origin.z + ray.direction.z*t};

        Vector3f surfaceNormal = {intersection.x - pScene->vertices[this->centerIndex-1].x,
                                  intersection.y - pScene->vertices[this->centerIndex-1].y,
                                  intersection.z - pScene->vertices[this->centerIndex-1].z};

        float surfaceNormalLength = sqrtf(surfaceNormal.x*surfaceNormal.x +
                                         surfaceNormal.y*surfaceNormal.y +
                                         surfaceNormal.z*surfaceNormal.z) ;

        surfaceNormal.x /= surfaceNormalLength;
        surfaceNormal.y /= surfaceNormalLength;
        surfaceNormal.z /= surfaceNormalLength;

        //TODO 4 return val
        return {
                surfaceNormal.x,
                surfaceNormal.y,
                surfaceNormal.z,
                t};

    }

    return {0, 0, 0, FLT_MAX}; // TODO : maybe return 0
}

Triangle::Triangle(void)
{}

/* Constructor for triangle. You will implement this. */
Triangle::Triangle(int id, int matIndex, int p1Index, int p2Index, int p3Index)
    : Shape(id, matIndex)
{
    this->point1Index = p1Index;
    this->point2Index = p2Index;
    this->point3Index = p3Index;
}

/* Triangle-ray intersection routine. You will implement this. 
Note that ReturnVal structure should hold the information related to the intersection point, e.g., coordinate of that point, normal at that point etc. 
You should to declare the variables in ReturnVal structure you think you will need. It is in defs.h file. */
ReturnVal Triangle::intersect(const Ray & ray) const
{
    //TODO 7 save vertices on the triangle itself(?) or here
    float abX=pScene->vertices[this->point1Index -1].x-pScene->vertices[this->point2Index -1].x;
    float acX=pScene->vertices[this->point1Index -1].x-pScene->vertices[this->point3Index -1].x;
    float abY=pScene->vertices[this->point1Index -1].y-pScene->vertices[this->point2Index -1].y;
    float acY=pScene->vertices[this->point1Index -1].y-pScene->vertices[this->point3Index -1].y;
    float abZ=pScene->vertices[this->point1Index -1].z-pScene->vertices[this->point2Index -1].z;
    float acZ=pScene->vertices[this->point1Index -1].z-pScene->vertices[this->point3Index -1].z;

    float aoX=pScene->vertices[this->point1Index -1].x-ray.origin.x;
    float aoY=pScene->vertices[this->point1Index -1].y-ray.origin.y;
    float aoZ=pScene->vertices[this->point1Index -1].z-ray.origin.z;

    float firstMiniDeterminant = abY*acZ-acY*abZ;
    float secondMiniDeterminant = acX*abZ - abX*acZ;//negatived
    float thirdMiniDeterminant = abX*acY-acX*abY;

    float lowerDeterminant=ray.direction.x*firstMiniDeterminant+
                           ray.direction.y*secondMiniDeterminant +
                           ray.direction.z*thirdMiniDeterminant;

    //TODO 9 check if we need to check lowerDeterminant = 0 or not
    if(lowerDeterminant > pScene->intTestEps || lowerDeterminant < (-1)*(pScene->intTestEps))
    {
        float beta = (ray.direction.x*(aoY*acZ-acY*aoZ) +
                      ray.direction.y*(acX*aoZ-aoX*acZ) +
                      ray.direction.z*(aoX*acY-acX*aoY)) / lowerDeterminant;

        if(beta>=0)
        {
            float gamma = (ray.direction.x*(abY*aoZ-aoY*abZ)+
                           ray.direction.y*(aoX*abZ-abX*aoZ)+
                           ray.direction.z*(abX*aoY-aoX*abY)) / lowerDeterminant;
            if(gamma>=0 && beta+gamma<=1 )
            {
                float upperDeterminant = aoX * firstMiniDeterminant +
                                         aoY * secondMiniDeterminant +
                                         aoZ * thirdMiniDeterminant;

                float t = upperDeterminant / lowerDeterminant;

                //TODO 6 single comparison between check
                //TODO 1 tmin tmax
                if (pScene->intTestEps <=t)
                {
                    // u and v are calculated for surface normal
                    Vector3f u = {
                            pScene->vertices[this->point2Index-1].x - pScene->vertices[this->point1Index-1].x,
                            pScene->vertices[this->point2Index-1].y - pScene->vertices[this->point1Index-1].y,
                            pScene->vertices[this->point2Index-1].z - pScene->vertices[this->point1Index-1].z
                    };

                    Vector3f v = {
                            pScene->vertices[this->point3Index-1].x - pScene->vertices[this->point1Index-1].x,
                            pScene->vertices[this->point3Index-1].y - pScene->vertices[this->point1Index-1].y,
                            pScene->vertices[this->point3Index-1].z - pScene->vertices[this->point1Index-1].z
                    };

                    Vector3f normalVector = {
                            u.y*v.z - u.z*v.y,
                            u.z*v.x - u.x*v.z,
                            u.x*v.y - u.y*v.x
                    };

                    float normalVectorLength = sqrtf(
                            normalVector.x*normalVector.x +
                            normalVector.y*normalVector.y +
                            normalVector.z*normalVector.z);

                    normalVector.x /= normalVectorLength;
                    normalVector.y /= normalVectorLength;
                    normalVector.z /= normalVectorLength;

                    return {
                            normalVector.x,
                            normalVector.y,
                            normalVector.z,
                            t
                    };
                }
            }

        }
    }

    return  {0, 0, 0, FLT_MAX};
}

Mesh::Mesh()
{
}

/* Constructor for mesh. You will implement this. */
Mesh::Mesh(int id, int matIndex, const vector<Triangle>& faces)
    : Shape(id, matIndex), faces(faces)
{
}

/* Mesh-ray intersection routine. You will implement this. 
Note that ReturnVal structure should hold the information related to the intersection point, e.g., coordinate of that point, normal at that point etc. 
You should to declare the variables in ReturnVal structure you think you will need. It is in defs.h file. */
ReturnVal Mesh::intersect(const Ray & ray) const
{
    ReturnVal triangularReturn;
    ReturnVal meshReturn;
    for(int i = 0 ; i < faces.size() ; i++)
    {
        //TODO 2 complete if and return
        triangularReturn = faces[i].intersect(ray);
        // TODO 9 struct null check
        if(triangularReturn.time != FLT_MAX )
        {
            if(triangularReturn.time < meshReturn.time)
            {
                meshReturn = triangularReturn;
            }
        }
    }

    //TODO 9 set default time value to flt max so you wont need to check if meshreturn != null
    return meshReturn;
}
