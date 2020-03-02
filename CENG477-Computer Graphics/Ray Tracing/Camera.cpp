#include "Camera.h"
#include <math.h>
#include <stdio.h>
#include <iostream>

Camera::Camera(int id,                      // Id of the camera
               const char* imageName,       // Name of the output PPM file 
               const Vector3f& pos,         // Camera position
               const Vector3f& gaze,        // Camera gaze direction
               const Vector3f& up,          // Camera up direction
               const ImagePlane& imgPlane) :pos(pos),gaze(gaze), up(up) // Image plane parameters

{
    this->id = id;
    this->imgPlane = imgPlane;

    for (int i = 0; i<32 ; ++i)
    {
        this->imageName[i] = imageName[i];
    }

}

/* Takes coordinate of an image pixel as row and col, and
 * returns the ray going through that pixel. 
 */
Ray Camera::getPrimaryRay(int col, int row) const
{
    float distance = this->imgPlane.distance;
    Vector3f gaze = this->gaze;
    Vector3f position = this->pos;

    Vector3f unitU = {gaze.y*up.z - gaze.z*up.y,
                      gaze.z*up.x - gaze.x*up.z,
                      gaze.x*up.y - gaze.y*up.x};

    float u = this->imgPlane.left + (this->imgPlane.right - this->imgPlane.left)/this->imgPlane.nx * (col+0.5);
    float v = this->imgPlane.top - (this->imgPlane.top - this->imgPlane.bottom)/this->imgPlane.ny * (row+0.5);

    Vector3f direction = {
            distance*gaze.x + unitU.x*u + up.x*v,
            distance*gaze.y + unitU.y*u + up.y*v,
            distance*gaze.z + unitU.z*u + up.z*v
    };

    float primaryRayLength = sqrtf(direction.x*direction.x + 
      direction.y*direction.y + 
      direction.z*direction.z);

    direction.x /= primaryRayLength;
    direction.y /= primaryRayLength;
    direction.z /= primaryRayLength;


    return {
            position,
            direction
    };

}

