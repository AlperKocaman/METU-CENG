#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <cmath>

#include "Scene.h"
#include "Camera.h"
#include "Color.h"
#include "Model.h"
#include "Rotation.h"
#include "Scaling.h"
#include "Translation.h"
#include "Triangle.h"
#include "Vec3.h"
#include "tinyxml2.h"
#include "Helpers.h"

using namespace tinyxml2;
using namespace std;

/*
	Transformations, clipping, culling, rasterization are done here.
	You can define helper functions inside Scene class implementation.
*/

/*
 * Forward Rendering Pipeline stages:
 *
 * 	Process vertices
		-Modelling transformations:
			->Translation
			->Scaling
			->Rotation
			->Normal transformation

		-Camera Trasformation
			->transform world coordinates of camera coordinates and vectors to local ones(uvw aligns with xyz)
		-Projection Transformation
			if projection is perpective,
				then map perpective to orthographic
				then do Orthographic transformation (in both perspectives do it)(maps viewing volume to canonical vv)
				may need perspective divide
			else
				just do orthographic transformation

	---end of process vertices---

 *	Primitive assembly (do we need, already triangles are assembled?)
 *
 *	Clipping
		-point clipping:straightforward, reject if outside
		-line clipping(choose one of the below):
			->Cohen-Sutherland algorithm
			->Liang-Barsky algorithm
		-polygon clipping
			->Sutherland Hodgeman Algorithm(?)

	---end of clipping---

 * 	Culling
		-don't need to implement frustum culling
		-implement backface only
		-make sure that culling is enabled
		-occlusion culling(don't need?)

	---end of culling---

 * 	Viewport Trasnform
		-transform 3D to 2D screen

	---end of viewport transform---

 *	Rasterization
		-line rasterization
			->midpoint algorithm with interpolation
			->triangle rasterization using barrycentric point

*/
/* TODO: Different modes on solid and wireframe, what the hack are these?? */

/* Modelling Transformations*/

Matrix4 Scene::GetTranslation(int id)
{
	double values[4][4] = {{1, 0, 0, this->translations[id]->tx},
                           {0, 1, 0, this->translations[id]->ty},
                           {0, 0, 1, this->translations[id]->tz},
                           {0, 0, 0, 1}};

    return Matrix4(values);
}

Matrix4 Scene::GetScaling(int id)
{
	//create Scaling matrix with Matrix4
	//apply matrix multiplication

	double values[4][4] = { {this->scalings[id]->sx, 0, 0, 0},
						   {0, this->scalings[id]->sy, 0, 0},
						   {0, 0, this->scalings[id]->sz, 0},
						   {0, 0, 0, 1} };

	return Matrix4(values);
}

Matrix4 Scene::GetRotation(int id) 
{
	// TODO: Implement this function. normalize->rotate->denormalize?
	//create Rotation matrix with Matrix4
	//apply matrix multiplication
	Vec3 rotationPoint = { this->rotations[id]->ux,this->rotations[id]->uy,this->rotations[id]->uz, -1 };

	Vec3 unitU = normalizeVec3(rotationPoint);

	//do it for alpha
	Vec3 UPrime = { 0,unitU.y,unitU.z, -1 };
	float cosAlpha = unitU.z / magnitudeOfVec3(UPrime);// =c/d
	float sinAlpha = unitU.y / magnitudeOfVec3(UPrime);// = b/d
	double values[4][4] = { {1,0,0,0},
							{0,cosAlpha,-sinAlpha,0},
							{0,sinAlpha,cosAlpha,0},
							{0,0,0,1} };
	Matrix4 rxAlpha = Matrix4(values);
	values[1][2] *= -1;//sinAlpha *= -1;
	values[2][1] *= -1;//sinAlpha *= -1;
	Matrix4 rxMinusAlpha = Matrix4(values);
	


	//do it for beta
	float cosBeta = (sqrtf(unitU.y * unitU.y + unitU.z * unitU.z) / magnitudeOfVec3(unitU));
	float sinBeta = unitU.x / magnitudeOfVec3(unitU);
	double betaValues[4][4] = { {cosBeta,0,-sinBeta,0},
								{0,1,0,0},
								{sinBeta,0,cosBeta,0},
								{0,0,0,1} };
	Matrix4 ryBeta = Matrix4(betaValues);
	betaValues[0][2] *= -1;//sinBeta *= -1;
	betaValues[2][0] *= -1;//sinBeta *= -1;
	Matrix4 ryMinusBeta = Matrix4(betaValues);
	
	double cosTheta = cosf(this->rotations[id]->angle*3.14f/180.0);
	double sinTheta = sinf(this->rotations[id]->angle*3.14f/180.0);
	double thetaValues[4][4] = { {cosTheta,-sinTheta,0,0},
								{sinTheta,cosTheta,0,0},
								{0,0,1,0},
								{0,0,0,1} };

	Matrix4 rzTheta = thetaValues;

	return multiplyMatrixWithMatrix(rxMinusAlpha,
		multiplyMatrixWithMatrix(ryBeta,
			multiplyMatrixWithMatrix(rzTheta,
				multiplyMatrixWithMatrix(ryMinusBeta,
					rxAlpha))));
}

/*
Matrix4 Scene::GetNormalTransformation(int id) {
	// TODO: Implement this function. get inverse of all the translations/scaling etc. and apply them all?		
	return NULL;
}
*/

Matrix4 Scene::GetTransformation(char type, int id)
{
	// TODO: Done!
	// transformation can be taken from here and passed to upper funcs in order to ease debugging
	if (type == 't') {
		return GetTranslation(id-1);
	}
	else if (type == 's') {
		return GetScaling(id-1);
	}
	else {
		return GetRotation(id-1);
	}
}


/* Camera Transformations*/
Matrix4 Scene::GetCameraTransformationMatrix(Camera camera) 
{
	//take cam coordinates and uvw
	//apply rotation and transformation to align it xyz
	Matrix4* uvwMatrix = new Matrix4();
	uvwMatrix->val[0][0] = camera.u.x;
	uvwMatrix->val[0][1] = camera.u.y;
	uvwMatrix->val[0][2] = camera.u.z;
	uvwMatrix->val[1][0] = camera.v.x;
	uvwMatrix->val[1][1] = camera.v.y;
	uvwMatrix->val[1][2] = camera.v.z;
	uvwMatrix->val[2][0] = camera.w.x;
	uvwMatrix->val[2][1] = camera.w.y;
	uvwMatrix->val[2][2] = camera.w.z;
	uvwMatrix->val[3][3] = 1;

	Matrix4* originTransformer = new Matrix4(getIdentityMatrix());
	originTransformer->val[0][3] = -camera.pos.x;
	originTransformer->val[1][3] = -camera.pos.y;
	originTransformer->val[2][3] = -camera.pos.z;

	Matrix4* cameraTransformator = new Matrix4();
	*cameraTransformator = multiplyMatrixWithMatrix(*uvwMatrix, *originTransformer);
	return *cameraTransformator;
}

/* Perspective Projections */
Matrix4 Scene::GetOrthographicTransformation(Camera camera) 
{
	//in both cases, this is needed
	Matrix4* orthographicMatrix = new Matrix4();
	orthographicMatrix->val[0][0] = 2 / (camera.right - camera.left);
	orthographicMatrix->val[0][3] = (camera.right + camera.left) / (camera.left - camera.right);//the minus is multiplied with divider
	orthographicMatrix->val[1][1] = 2 / (camera.top - camera.bottom);
	orthographicMatrix->val[1][3] = (camera.top + camera.bottom) / (camera.bottom - camera.top);//the minus is multiplied with divider
	orthographicMatrix->val[2][2] = 2 / (camera.near - camera.far);//the minus is multiplied with divider
	orthographicMatrix->val[2][3] = (camera.far+camera.near) / (camera.near - camera.far);//the minus is multiplied with divider
	orthographicMatrix->val[3][3] = 1;

	return *orthographicMatrix;
}

Matrix4 Scene::GetPerspectiveTransformation(Camera camera) 
{
	//TODO apply perspective divide to points after perspective transformation
	Matrix4* perspectiveMatrix = new Matrix4();
	perspectiveMatrix->val[0][0] = 2*camera.near / (camera.right - camera.left);
	perspectiveMatrix->val[0][2] = (camera.right + camera.left) / (camera.right - camera.left);
	perspectiveMatrix->val[1][1] = 2*camera.near / (camera.top - camera.bottom);
	perspectiveMatrix->val[1][2] = (camera.top + camera.bottom) / (camera.top - camera.bottom);
	perspectiveMatrix->val[2][2] = (camera.far+camera.near) / (camera.near - camera.far);//the minus is multiplied with divider
	perspectiveMatrix->val[2][3] = 2*camera.far * camera.near / (camera.near - camera.far);//the minus is multiplied with divider
	perspectiveMatrix->val[3][2] = -1;
	
	return *perspectiveMatrix;
}


bool Scene::ApplyLiangBarsky(Vec4* entryPoint, Vec4* leavingPoint, Camera camera)
{
	float tE = 0, tL = 1;
	bool visible = false;

    Vec3 entryVec3 = Vec3(entryPoint->x, entryPoint->y, entryPoint->z, entryPoint->colorId);
    Vec3 leavingVec3 = Vec3(leavingPoint->x, leavingPoint->y, leavingPoint->z, leavingPoint->colorId);

	Vec3 direction = subtractVec3(leavingVec3, entryVec3);

	if (Visible(direction.x, camera.left - entryPoint->x, &tE, &tL) && //left
		Visible(-direction.x, entryPoint->x - camera.right, &tE, &tL) && // right
		Visible(direction.y, camera.bottom - entryPoint->y, &tE, &tL) &&//bottom
		Visible(-direction.y, entryPoint->y - camera.top, &tE, &tL) &&//top
		Visible(direction.z, camera.near - entryPoint->z, &tE, &tL) &&//front
		Visible(-direction.z, entryPoint->z - camera.far, &tE, &tL))//back
	{
		visible = true;
		if (tL < 1)
		{
			leavingPoint->x = entryPoint->x + direction.x * tL;
			leavingPoint->y = entryPoint->y + direction.y * tL;
			leavingPoint->z = entryPoint->z + direction.z * tL;
		}
		if (tE > 0)
		{
			entryPoint->x = entryPoint->x + direction.x * tE;
			entryPoint->y = entryPoint->y + direction.y * tE;
			entryPoint->z = entryPoint->z + direction.z * tE;
		}
	}
	return visible;
 }

//used by liang barsky
bool Scene::Visible(float den, float num, float* tE, float* tL)
{
	if (den > 0)//potentially entering
	{
		float t = num / den;
		if (t > *tL)
		{
			return false;
		}
		if (t > *tE)
		{
			*tE = t;
		}
	}
	else if (den < 0)//potentially leaving
	{
		float t = num / den;
		if (t < *tE)
		{
			return false;
		}
		if (t < *tL)
		{
			*tL = t;
		}
	}
	else if (num > 0)//line parallel to edge
	{
		return false;
	}
	return true;
}

/* Culling*/
bool Scene::ApplyBackfaceCulling(Vec4* firstVertex, Vec4* secondVertex, Vec4* thirdVertex, Camera camera) {
	// TODO: Done!
	// returns true if this triangle is culled, false otherwise.
	if (!cullingEnabled) {
		return false;
	}
	Vec3 firstVertexVec3 = Vec3(firstVertex->x, firstVertex->y, firstVertex->z, firstVertex->colorId);
	Vec3 secondVertexVec3 = Vec3(secondVertex->x, secondVertex->y, secondVertex->z, secondVertex->colorId);
	Vec3 thirdVertexVec3 = Vec3(thirdVertex->x, thirdVertex->y, thirdVertex->z, thirdVertex->colorId);

	Vec3 normalVector = normalizeVec3(crossProductVec3(subtractVec3(secondVertexVec3, firstVertexVec3),
		subtractVec3(thirdVertexVec3, firstVertexVec3)));

    Vec3 center = addVec3(firstVertexVec3,addVec3(secondVertexVec3,thirdVertexVec3));
    center = multiplyVec3WithScalar(center,1/3.0);
	Vec3 viewVector = normalizeVec3(subtractVec3(center, camera.pos));
    cout<<"Culling Enabled:"<<(dotProductVec3(normalVector, viewVector))<<endl;
    cout<<"for : "<<" "<<firstVertexVec3<<" "<<secondVertexVec3<<" "<<thirdVertexVec3<<endl;
	return !(dotProductVec3(normalVector, viewVector) > 0);
}

/* Viewport Transform */
Vec4 Scene::GetViewportTransform(Vec4 point, Camera camera) {
	// TODO: Done!
	double values[4][4] = { {camera.horRes / 2.0, 0, 0, (camera.horRes - 1) / 2.0},
						   {0, camera.verRes / 2.0, 0, (camera.verRes - 1) / 2.0},
						   {0, 0, 0.5, 0.5},
						   {0, 0, 0, 1} };
	Matrix4 viewportTransformMatrix = Matrix4(values);
	return multiplyMatrixWithVec4(viewportTransformMatrix, point);
}

/* Rasterization */

void Scene::ApplyMidPoint(Vec4* startVec4, Vec4* lastVec4) {
	// TODO: Implement this function.
	int x=0;
    int y=0;
    Pixel startPixel;
    Pixel lastPixel;
    if(startVec4->x < lastVec4->x) {
        startPixel = {(int)startVec4->x, (int)startVec4->y};
        lastPixel = { (int)lastVec4->x, (int)lastVec4->y};
    }
    else{
        startPixel = { (int)lastVec4->x, (int)lastVec4->y};
        lastPixel = { (int)startVec4->x, (int)startVec4->y};
    }
    double slope;
    Color color;
    double colorDerivativeRed;
    double colorDerivativeBlue;
    double colorDerivativeGreen;


	float distance = sqrtf(powf(lastPixel.xCoordinate - startPixel.xCoordinate, 2) + powf(lastPixel.yCoordinate - startPixel.yCoordinate, 2));
    if(lastPixel.xCoordinate != startPixel.xCoordinate) {
        slope = (double) (lastPixel.yCoordinate - startPixel.yCoordinate) /
                (double) (lastPixel.xCoordinate - startPixel.xCoordinate);


        if(slope>=-1 && slope<=1) {
            if (lastVec4->x > startVec4->x) {
                color = *colorsOfVertices[startVec4->colorId - 1];
                colorDerivativeRed =
                        (colorsOfVertices[lastVec4->colorId - 1]->r - colorsOfVertices[startVec4->colorId - 1]->r) /
					distance;
                colorDerivativeBlue =
                        (colorsOfVertices[lastVec4->colorId - 1]->b - colorsOfVertices[startVec4->colorId - 1]->b) /
					distance;
                colorDerivativeGreen =
                        (colorsOfVertices[lastVec4->colorId - 1]->g - colorsOfVertices[startVec4->colorId - 1]->g) /
					distance;
            }
            else{
                color = *colorsOfVertices[lastVec4->colorId - 1];
                colorDerivativeRed =
                        (colorsOfVertices[startVec4->colorId - 1]->r - colorsOfVertices[lastVec4->colorId - 1]->r) /
					distance;
                colorDerivativeBlue =
                        (colorsOfVertices[startVec4->colorId - 1]->b - colorsOfVertices[lastVec4->colorId - 1]->b) /
					distance;
                colorDerivativeGreen =
                        (colorsOfVertices[startVec4->colorId - 1]->g - colorsOfVertices[lastVec4->colorId - 1]->g) /
					distance;
            }
        }
        else{
            if (lastVec4->x > startVec4->x) {
                color = *colorsOfVertices[startVec4->colorId - 1];
                colorDerivativeRed =
                        (colorsOfVertices[lastVec4->colorId - 1]->r - colorsOfVertices[startVec4->colorId - 1]->r) /
					distance;
                colorDerivativeBlue =
                        (colorsOfVertices[lastVec4->colorId - 1]->b - colorsOfVertices[startVec4->colorId - 1]->b) /
					distance;
                colorDerivativeGreen =
                        (colorsOfVertices[lastVec4->colorId - 1]->g - colorsOfVertices[startVec4->colorId - 1]->g) /
					distance;
            }
            else{
                color = *colorsOfVertices[lastVec4->colorId - 1];
                colorDerivativeRed =
                        (colorsOfVertices[startVec4->colorId - 1]->r - colorsOfVertices[lastVec4->colorId - 1]->r) /
					distance;
                colorDerivativeBlue =
                        (colorsOfVertices[startVec4->colorId - 1]->b - colorsOfVertices[lastVec4->colorId - 1]->b) /
					distance;
                colorDerivativeGreen =
                        (colorsOfVertices[startVec4->colorId - 1]->g - colorsOfVertices[lastVec4->colorId - 1]->g) /
					distance;
            }
        }
    }
    else{

        if(lastPixel.yCoordinate <= startPixel.yCoordinate){
            color = *colorsOfVertices[lastVec4->colorId - 1];
            colorDerivativeRed =
                    (colorsOfVertices[startVec4->colorId - 1]->r - colorsOfVertices[lastVec4->colorId - 1]->r) /
				distance;
            colorDerivativeBlue =
                    (colorsOfVertices[startVec4->colorId - 1]->b - colorsOfVertices[lastVec4->colorId - 1]->b) /
				distance;
            colorDerivativeGreen =
                    (colorsOfVertices[startVec4->colorId - 1]->g - colorsOfVertices[lastVec4->colorId - 1]->g) /
				distance;
            for(y=lastPixel.yCoordinate; y<=startPixel.yCoordinate ; ++y){
				SetColor(startPixel.xCoordinate, y, color);
                color.r += colorDerivativeRed;
                color.g += colorDerivativeGreen;
                color.b += colorDerivativeBlue;
            }
        }
        else{
            color = *colorsOfVertices[startVec4->colorId - 1];
            colorDerivativeRed =
                    (colorsOfVertices[lastVec4->colorId - 1]->r - colorsOfVertices[startVec4->colorId - 1]->r) /
				distance;
            colorDerivativeBlue =
                    (colorsOfVertices[lastVec4->colorId - 1]->b - colorsOfVertices[startVec4->colorId - 1]->b) /
				distance;
            colorDerivativeGreen =
                    (colorsOfVertices[lastVec4->colorId - 1]->g - colorsOfVertices[startVec4->colorId - 1]->g) /
				distance;
            for(y=startPixel.yCoordinate; y<=lastPixel.yCoordinate ; ++y){
				SetColor(startPixel.xCoordinate, y, color);
                color.r += colorDerivativeRed;
                color.g += colorDerivativeGreen;
                color.b += colorDerivativeBlue;
            }
        }

		return;
	}

	if (slope >= 0 && slope <= 1) {
		int yVariable = startPixel.yCoordinate;
		//TODO: below should be changed to int by multiplying 2 with each sides after testing
		float derivative =
			startPixel.yCoordinate - lastPixel.yCoordinate + 0.5 * (lastPixel.xCoordinate - startPixel.xCoordinate);
		for (x = startPixel.xCoordinate; x < lastPixel.xCoordinate; ++x) {
			SetColor(x, yVariable, color);
			if (derivative < 0) {
				yVariable += 1;
				derivative += startPixel.yCoordinate - lastPixel.yCoordinate + lastPixel.xCoordinate - startPixel.xCoordinate;
			}
			else {
				derivative += startPixel.yCoordinate - lastPixel.yCoordinate;
			}
			color.r += colorDerivativeRed;
			color.g += colorDerivativeGreen;
			color.b += colorDerivativeBlue;
		}
	}
	else if (slope > 1) {
		int xVariable = startPixel.xCoordinate;
		float derivative =
			startPixel.xCoordinate - lastPixel.xCoordinate + 0.5 * (lastPixel.yCoordinate - startPixel.yCoordinate);
		for (y = startPixel.yCoordinate; y <= lastPixel.yCoordinate; ++y) {
			SetColor(xVariable, y, color);
			if (derivative < 0) {
				xVariable += 1;
				derivative += startPixel.xCoordinate - lastPixel.xCoordinate + lastPixel.yCoordinate - startPixel.yCoordinate;
			}
			else {
				derivative += startPixel.xCoordinate - lastPixel.xCoordinate;
			}
			color.r += colorDerivativeRed;
			color.g += colorDerivativeGreen;
			color.b += colorDerivativeBlue;
		}
	}
	else if (slope < 0 && slope >= -1) {
		int yVariable = startPixel.yCoordinate;
		float derivative =
			startPixel.yCoordinate - lastPixel.yCoordinate + 0.5 * (lastPixel.xCoordinate - startPixel.xCoordinate);
		for (x = startPixel.xCoordinate; x < lastPixel.xCoordinate; ++x) {
			SetColor(x, yVariable, color);
			if (derivative < 0) {
				yVariable -= 1;
				derivative += -startPixel.yCoordinate + lastPixel.yCoordinate + lastPixel.xCoordinate - startPixel.xCoordinate;
			}
			else {
				derivative -= startPixel.yCoordinate - lastPixel.yCoordinate;
			}
			color.r += colorDerivativeRed;
			color.g += colorDerivativeGreen;
			color.b += colorDerivativeBlue;
		}

		//cout<<"finish"<<endl;
	}


	else if (slope < -1) {
		int xVariable = startPixel.xCoordinate;
		float derivative =
			-startPixel.xCoordinate + lastPixel.xCoordinate - 0.5 * (lastPixel.yCoordinate - startPixel.yCoordinate);
		for (y = startPixel.yCoordinate; y >= lastPixel.yCoordinate; --y) {
			SetColor(xVariable, y, color);
			if (derivative < 0) {
				xVariable += 1;
				derivative += startPixel.xCoordinate - lastPixel.xCoordinate - lastPixel.yCoordinate + startPixel.yCoordinate;
			}
			else {
				derivative += startPixel.xCoordinate - lastPixel.xCoordinate;
			}
			color.r += colorDerivativeRed;
			color.g += colorDerivativeGreen;
			color.b += colorDerivativeBlue;
		}
	}

}

void Scene::SetColor(int x, int y, const Color& color)
{
	if (this->image.size() > x && x >= 0
		&& this->image.at(0).size() > y && y >= 0)
	{

	this->image[x][y] = color;
	}
}

double Scene::f_function(double x, double y, Vec4* firstVertex, Vec4* secondVertex){
	return x*(firstVertex->y-secondVertex->y) + y*(secondVertex->x - firstVertex->x) +
			 firstVertex->x*secondVertex->y - firstVertex->y*secondVertex->x;
}

void Scene::ApplyTriangleRasterization(Vec4* firstVertex, Vec4* secondVertex, Vec4* thirdVertex, Camera camera) {
	// TODO: Implement this function.
	//find xMax
	int xMax = firstVertex->x;
	if(xMax<secondVertex->x){
		xMax = secondVertex->x;
	}
	if(xMax<thirdVertex->x){
		xMax = thirdVertex->x;
	}
	// find xMin
	int xMin = firstVertex->x;
	if(xMin>secondVertex->x){
		xMin = secondVertex->x;
	}
	if(xMin>thirdVertex->x){
		xMin = thirdVertex->x;
	}
	//find yMax
	int yMax = firstVertex->y;
	if(yMax<secondVertex->y){
		yMax = secondVertex->y;
	}
	if(yMax<thirdVertex->y){
		yMax = thirdVertex->y;
	}
	//find yMin
	int yMin = firstVertex->y;
	if(yMin>secondVertex->y){
		yMin = secondVertex->y;
	}
	if(yMin>thirdVertex->y){
		yMin = thirdVertex->y;
	}

	double  alpha = 0;
	double  beta = 0;
	double  gamma = 0;
	Color color;

	for(int y=yMin; y<=yMax ; ++y){

		for(int x=xMin; x<=xMax ; ++x){

			alpha = f_function(x,y, secondVertex, thirdVertex)/f_function(firstVertex->x, firstVertex->y, secondVertex, thirdVertex);
			beta = f_function(x,y, firstVertex, thirdVertex)/f_function(secondVertex->x, secondVertex->y, firstVertex, thirdVertex);
			gamma = f_function(x,y, firstVertex, secondVertex)/f_function(thirdVertex->x, thirdVertex->y, firstVertex, secondVertex);

			if((alpha>=0) && (beta>=0) && (gamma>=0)){

				color.r = alpha*colorsOfVertices[firstVertex->colorId-1]->r +
						beta*colorsOfVertices[secondVertex->colorId-1]->r +
						gamma*colorsOfVertices[thirdVertex->colorId-1]->r ;

				color.g = alpha*colorsOfVertices[firstVertex->colorId-1]->g +
						  beta*colorsOfVertices[secondVertex->colorId-1]->g +
						  gamma*colorsOfVertices[thirdVertex->colorId-1]->g ;

				color.b = alpha*colorsOfVertices[firstVertex->colorId-1]->b +
						  beta*colorsOfVertices[secondVertex->colorId-1]->b +
						  gamma*colorsOfVertices[thirdVertex->colorId-1]->b ;
                if(x>=0 && x<=camera.horRes && y>=0 && y<=camera.verRes){
				    SetColor(x,y,color);
                }
			}
		}
	}

}

void Scene::forwardRenderingPipeline(Camera* camera)
{   /*
	for (auto rotation : this->rotations)
	{
		rotation->angle *= 3.14 / 180;
	}
    */
	// TODO: Implement this function.
	// TODO probably need interpolating attributes @rasterization for colors etc.

	// cameraTransformation matrix is obtained
	Matrix4 cameraTransformationMatrix = GetCameraTransformationMatrix(*camera);
	// projection matrix is obtained
	// orthogonal matrix is needed in both cases
	Matrix4 projectionMatrix;
	if(this->projectionType == 0){
		//orthographic transformation
		projectionMatrix = GetOrthographicTransformation(*camera);
	}
	else if(this->projectionType == 1){
		//perspective projection
		projectionMatrix = GetPerspectiveTransformation(*camera);
	}

	// process model
	for(Model *model : models){
		//get tranformation matrix that will be applied to vertices
		Matrix4 cumulativeTransformationMatrix = getIdentityMatrix();
		for(int i=0 ; i<model->numberOfTransformations ; ++i){
			Matrix4 tranformationMatrix = GetTransformation(model->transformationTypes[i], model->transformationIds[i]);
			//cout<<"tranformationMatrix "<<i<<" :"<<endl;
			//cout<<tranformationMatrix<<endl;
			cumulativeTransformationMatrix = multiplyMatrixWithMatrix(tranformationMatrix, cumulativeTransformationMatrix);
		}
		//cout<<"projection Matrix "<<" :"<<endl;
		//cout<<projectionMatrix<<endl;
		// at this stage, total transformation matrix should be obtained
		// these matrices are seperated in order to see their content
		//Matrix4 totalMatrix = multiplyMatrixWithMatrix(projectionMatrix,
		//											   multiplyMatrixWithMatrix(cameraTransformationMatrix, cumulativeTransformationMatrix));

		Matrix4 totalMatrix = multiplyMatrixWithMatrix(cameraTransformationMatrix, cumulativeTransformationMatrix);
		//TODO: apply total matrix to all vertices in model's triangles
        vector< Vec4 > modelVertices;

		for(Triangle triangle: model->triangles){

            int firstVertexId = triangle.getFirstVertexId();
            int secondVertexId = triangle.getSecondVertexId();
            int thirdVertexId = triangle.getThirdVertexId();

            Vec3 firstVertex   = *vertices[firstVertexId-1];
            Vec3 secondVertex = *vertices[secondVertexId-1];
            Vec3 thirdVertex  = *vertices[thirdVertexId-1];

            Vec4 firstVector4 = Vec4(firstVertex.getElementAt(0),
                                     firstVertex.getElementAt(1),
                                     firstVertex.getElementAt(2),
                                     1,
                                     firstVertexId);

            Vec4 secondVector4 = Vec4(secondVertex.getElementAt(0),
                                      secondVertex.getElementAt(1),
                                      secondVertex.getElementAt(2),
                                      1,
                                      secondVertexId);

            Vec4 thirdVector4 = Vec4(thirdVertex.getElementAt(0),
                                     thirdVertex.getElementAt(1),
                                     thirdVertex.getElementAt(2),
                                     1,
                                     thirdVertexId);

            firstVector4 = multiplyMatrixWithVec4(totalMatrix, firstVector4);
            secondVector4 = multiplyMatrixWithVec4(totalMatrix, secondVector4);
            thirdVector4 = multiplyMatrixWithVec4(totalMatrix, thirdVector4);

			firstVector4 = multiplyMatrixWithVec4(projectionMatrix, firstVector4);
			secondVector4 = multiplyMatrixWithVec4(projectionMatrix, secondVector4);
			thirdVector4 = multiplyMatrixWithVec4(projectionMatrix, thirdVector4);

            modelVertices.push_back(firstVector4);
            modelVertices.push_back(secondVector4);
            modelVertices.push_back(thirdVector4);
		}

		if(model->type == 0){
			// TODO: wireframe mode, do clipping
<<<<<<< HEAD
            for(int i=99999; i<modelVertices.size() ; i+=3){
=======
            for(int i=9999; i<modelVertices.size() ; i+=3){
>>>>>>> 163c0b53cd4b62fd536fe6988895fa6034e92001
				if (!ApplyLiangBarsky(&modelVertices[i], &modelVertices[i + 1], *camera) &&
					!ApplyLiangBarsky(&modelVertices[i], &modelVertices[i + 2], *camera) &&
					!ApplyLiangBarsky(&modelVertices[i + 1], &modelVertices[i + 2], *camera))
				{
					/*modelVertices.erase(modelVertices.begin() + i + 2);
					modelVertices.erase(modelVertices.begin() + i + 1);
					modelVertices.erase(modelVertices.begin() + i);*/
				}
				else
				{
					//i -= 3;
				}
            }
		}

        if(this->cullingEnabled){
            // TODO: do culling
            int i=0;
            while(i<modelVertices.size()) {
                bool isCulled = ApplyBackfaceCulling(&modelVertices[i], &modelVertices[i+1], &modelVertices[i+2], *camera);
                if(isCulled){
                    modelVertices.erase(modelVertices.begin()+i+2);
                    modelVertices.erase(modelVertices.begin()+i+1);
                    modelVertices.erase(modelVertices.begin()+i);
                }
                else{
                    i+=3;
                }
            }
        }
        //TODO: do perspective divide
        for(int i=0; i<modelVertices.size(); ++i){
            Vec4 modelVertice = modelVertices[i];
            if(modelVertice.t != 0 && modelVertice.t != 1){
                modelVertice.x /= modelVertice.t;
                modelVertice.y /= modelVertice.t;
                modelVertice.z /= modelVertice.t;
                modelVertice.t = 1;
                modelVertices[i] = modelVertice;
            }
        }
        //viewport transformation
        for(int i=0; i<modelVertices.size() ; ++i){
            //TODO: make below function to take reference
            //cout<<"point before viewport"<<modelVertices[i]<<endl;
            modelVertices[i] = GetViewportTransform(modelVertices[i], *camera);
            //cout<<"point after viewport"<<modelVertices[i]<<endl;
        }

        if(model->type == 0){
            // wireframe mode, use midpoint algorithm
            for(int i=0; i<modelVertices.size() ; i+=3){
                ApplyMidPoint(&modelVertices[i], &modelVertices[i+1]);
                ApplyMidPoint(&modelVertices[i], &modelVertices[i+2]);
                ApplyMidPoint(&modelVertices[i+1], &modelVertices[i+2]);
            }

        }
        else{
            for(int i=0; i<modelVertices.size(); i+=3){
                ApplyTriangleRasterization(&modelVertices[i], &modelVertices[i+1], &modelVertices[i+2], *camera);
            }
        }
	}



	//writeImageToPPMFile(camera) done in the main
	//TODO: if windows used, make argument 1 in the function convertPPMToPNG to 2.
 	//convertPPMToPNG(camera->outputFileName, 1) done in the main

}

/*
	Parses XML file
*/
Scene::Scene(const char* xmlPath)
{
	const char* str;
	XMLDocument xmlDoc;
	XMLElement* pElement;

	xmlDoc.LoadFile(xmlPath);

	XMLNode* pRoot = xmlDoc.FirstChild();

	// read background color
	pElement = pRoot->FirstChildElement("BackgroundColor");
	str = pElement->GetText();
	sscanf(str, "%lf %lf %lf", &backgroundColor.r, &backgroundColor.g, &backgroundColor.b);

	// read culling
	pElement = pRoot->FirstChildElement("Culling");
	if (pElement != NULL)
		pElement->QueryBoolText(&cullingEnabled);

	// read projection type
	pElement = pRoot->FirstChildElement("ProjectionType");
	if (pElement != NULL)
		pElement->QueryIntText(&projectionType);

	// read cameras
	pElement = pRoot->FirstChildElement("Cameras");
	XMLElement* pCamera = pElement->FirstChildElement("Camera");
	XMLElement* camElement;
	while (pCamera != NULL)
	{
		Camera* cam = new Camera();

		pCamera->QueryIntAttribute("id", &cam->cameraId);

		camElement = pCamera->FirstChildElement("Position");
		str = camElement->GetText();
		sscanf(str, "%lf %lf %lf", &cam->pos.x, &cam->pos.y, &cam->pos.z);

		camElement = pCamera->FirstChildElement("Gaze");
		str = camElement->GetText();
		sscanf(str, "%lf %lf %lf", &cam->gaze.x, &cam->gaze.y, &cam->gaze.z);

		camElement = pCamera->FirstChildElement("Up");
		str = camElement->GetText();
		sscanf(str, "%lf %lf %lf", &cam->v.x, &cam->v.y, &cam->v.z);

		cam->gaze = normalizeVec3(cam->gaze);
		cam->u = crossProductVec3(cam->gaze, cam->v);
		cam->u = normalizeVec3(cam->u);

		cam->w = inverseVec3(cam->gaze);
		cam->v = crossProductVec3(cam->u, cam->gaze);
		cam->v = normalizeVec3(cam->v);

		camElement = pCamera->FirstChildElement("ImagePlane");
		str = camElement->GetText();
		sscanf(str, "%lf %lf %lf %lf %lf %lf %d %d",
			&cam->left, &cam->right, &cam->bottom, &cam->top,
			&cam->near, &cam->far, &cam->horRes, &cam->verRes);

		camElement = pCamera->FirstChildElement("OutputName");
		str = camElement->GetText();
		cam->outputFileName = string(str);

		cameras.push_back(cam);

		pCamera = pCamera->NextSiblingElement("Camera");
	}

	// read vertices
	pElement = pRoot->FirstChildElement("Vertices");
	XMLElement* pVertex = pElement->FirstChildElement("Vertex");
	int vertexId = 1;

	while (pVertex != NULL)
	{
		Vec3* vertex = new Vec3();
		Color* color = new Color();

		vertex->colorId = vertexId;

		str = pVertex->Attribute("position");
		sscanf(str, "%lf %lf %lf", &vertex->x, &vertex->y, &vertex->z);

		str = pVertex->Attribute("color");
		sscanf(str, "%lf %lf %lf", &color->r, &color->g, &color->b);

		vertices.push_back(vertex);
		colorsOfVertices.push_back(color);

		pVertex = pVertex->NextSiblingElement("Vertex");

		vertexId++;
	}

	// read translations
	pElement = pRoot->FirstChildElement("Translations");
	XMLElement* pTranslation = pElement->FirstChildElement("Translation");
	while (pTranslation != NULL)
	{
		Translation* translation = new Translation();

		pTranslation->QueryIntAttribute("id", &translation->translationId);

		str = pTranslation->Attribute("value");
		sscanf(str, "%lf %lf %lf", &translation->tx, &translation->ty, &translation->tz);

		translations.push_back(translation);

		pTranslation = pTranslation->NextSiblingElement("Translation");
	}

	// read scalings
	pElement = pRoot->FirstChildElement("Scalings");
	XMLElement* pScaling = pElement->FirstChildElement("Scaling");
	while (pScaling != NULL)
	{
		Scaling* scaling = new Scaling();

		pScaling->QueryIntAttribute("id", &scaling->scalingId);
		str = pScaling->Attribute("value");
		sscanf(str, "%lf %lf %lf", &scaling->sx, &scaling->sy, &scaling->sz);

		scalings.push_back(scaling);

		pScaling = pScaling->NextSiblingElement("Scaling");
	}

	// read rotations
	pElement = pRoot->FirstChildElement("Rotations");
	XMLElement* pRotation = pElement->FirstChildElement("Rotation");
	while (pRotation != NULL)
	{
		Rotation* rotation = new Rotation();

		pRotation->QueryIntAttribute("id", &rotation->rotationId);
		str = pRotation->Attribute("value");
		sscanf(str, "%lf %lf %lf %lf", &rotation->angle, &rotation->ux, &rotation->uy, &rotation->uz);

		rotations.push_back(rotation);

		pRotation = pRotation->NextSiblingElement("Rotation");
	}

	// read models
	pElement = pRoot->FirstChildElement("Models");

	XMLElement* pModel = pElement->FirstChildElement("Model");
	XMLElement* modelElement;
	while (pModel != NULL)
	{
		Model* model = new Model();

		pModel->QueryIntAttribute("id", &model->modelId);
		pModel->QueryIntAttribute("type", &model->type);

		// read model transformations
		XMLElement* pTransformations = pModel->FirstChildElement("Transformations");
		XMLElement* pTransformation = pTransformations->FirstChildElement("Transformation");

		pTransformations->QueryIntAttribute("count", &model->numberOfTransformations);

		while (pTransformation != NULL)
		{
			char transformationType;
			int transformationId;

			str = pTransformation->GetText();
			sscanf(str, "%c %d", &transformationType, &transformationId);

			model->transformationTypes.push_back(transformationType);
			model->transformationIds.push_back(transformationId);

			pTransformation = pTransformation->NextSiblingElement("Transformation");
		}

		// read model triangles
		XMLElement* pTriangles = pModel->FirstChildElement("Triangles");
		XMLElement* pTriangle = pTriangles->FirstChildElement("Triangle");

		pTriangles->QueryIntAttribute("count", &model->numberOfTriangles);

		while (pTriangle != NULL)
		{
			int v1, v2, v3;

			str = pTriangle->GetText();
			sscanf(str, "%d %d %d", &v1, &v2, &v3);

			model->triangles.push_back(Triangle(v1, v2, v3));

			pTriangle = pTriangle->NextSiblingElement("Triangle");
		}

		models.push_back(model);

		pModel = pModel->NextSiblingElement("Model");
	}
}

/*
	Initializes image with background color
*/
void Scene::initializeImage(Camera* camera)
{
	if (this->image.empty())
	{
		for (int i = 0; i < camera->horRes; i++)
		{
			vector<Color> rowOfColors;

			for (int j = 0; j <camera->verRes; j++)
			{
				rowOfColors.push_back(this->backgroundColor);
			}

			this->image.push_back(rowOfColors);
		}
	}
	// if image is filled before, just change color rgb values with the background color
	else
	{
		for (int i = 0; i < camera->horRes; i++)
		{
			for (int j = 0; j < camera->verRes; j++)
			{
				this->image[i][j].r = this->backgroundColor.r;
				this->image[i][j].g = this->backgroundColor.g;
				this->image[i][j].b = this->backgroundColor.b;
			}
		}
	}
}

/*
	If given value is less than 0, converts value to 0.
	If given value is more than 255, converts value to 255.
	Otherwise returns value itself.
*/
int Scene::makeBetweenZeroAnd255(double value)
{
	if (value >= 255.0)
		return 255;
	if (value <= 0.0)
		return 0;
	return (int)(value);
}

/*
	Writes contents of image (Color**) into a PPM file.
*/
void Scene::writeImageToPPMFile(Camera* camera)
{
	ofstream fout;

	fout.open(camera->outputFileName.c_str());

	fout << "P3" << endl;
	fout << "# " << camera->outputFileName << endl;
	fout << camera->horRes << " " << camera->verRes << endl;
	fout << "255" << endl;

	for (int j = camera->verRes - 1; j >= 0; j--)
	{
		for (int i = 0; i < camera->horRes; i++)
		{
			fout << makeBetweenZeroAnd255(this->image[i][j].r) << " "
				<< makeBetweenZeroAnd255(this->image[i][j].g) << " "
				<< makeBetweenZeroAnd255(this->image[i][j].b) << " ";
		}
		fout << endl;
	}
	fout.close();
}

/*
	Converts PPM image in given path to PNG file, by calling ImageMagick's 'convert' command.
	os_type == 1 		-> Ubuntu
	os_type == 2 		-> Windows
	os_type == other	-> No conversion
*/
void Scene::convertPPMToPNG(string ppmFileName, int osType)
{
	string command;

	// call command on Ubuntu
	if (osType == 1)
	{
		command = "convert " + ppmFileName + " " + ppmFileName + ".png";
		system(command.c_str());
	}

	// call command on Windows
	else if (osType == 2)
	{
		command = "magick convert " + ppmFileName + " " + ppmFileName + ".png";
		system(command.c_str());
	}

	// default action - don't do conversion
	else
	{
	}
}