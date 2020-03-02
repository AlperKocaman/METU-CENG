#ifndef _SCENE_H_
#define _SCENE_H_

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "Camera.h"
#include "Color.h"
#include "Model.h"
#include "Rotation.h"
#include "Scaling.h"
#include "Translation.h"
#include "Triangle.h"
#include "Vec3.h"
#include "Vec4.h"
//TODO : added include, check again
#include "Helpers.h"


using namespace std;

class Scene
{
public:
	Color backgroundColor;
	bool cullingEnabled;
	int projectionType;

	vector< vector<Color> > image;
	vector< Camera* > cameras;
	vector< Vec3* > vertices;
	vector< Color* > colorsOfVertices;
	vector< Scaling* > scalings;
	vector< Rotation* > rotations;
	vector< Translation* > translations;
	vector< Model* > models;

	Scene(const char* xmlPath);

	void initializeImage(Camera* camera);
	void forwardRenderingPipeline(Camera* camera);
	int makeBetweenZeroAnd255(double value);
	void writeImageToPPMFile(Camera* camera);
	void convertPPMToPNG(string ppmFileName, int osType);

	typedef struct Pixel {
		int xCoordinate;
		int yCoordinate;
	};

	Vec4 GetViewportTransform(Vec4 point, Camera camera);
	Matrix4 GetTranslation(int id);
	Matrix4 GetScaling(int id);
	Matrix4 GetRotation(int id);
	Matrix4 GetTransformation(char type, int id);
	Matrix4 GetCameraTransformationMatrix(Camera camera);
	Matrix4 GetOrthographicTransformation(Camera camera);
	Matrix4 GetPerspectiveTransformation(Camera camera);
    bool ApplyLiangBarsky(Vec4 *entryPoint, Vec4 *leavingPoint, Camera camera);
	bool Visible(float den, float num, float* tE, float* tL);
    bool ApplyBackfaceCulling(Vec4 *firstVertex, Vec4 *secondVertex, Vec4 *thirdVertex, Camera camera);
    void ApplyMidPoint(Vec4 *startVec4, Vec4 *lastVec4);
	void SetColor(int x, int y, const Color& color);
	double f_function(double x, double y, Vec4 *firstVertex, Vec4 *secondVertex);
    void ApplyTriangleRasterization(Vec4 *firstVertex, Vec4 *secondVertex, Vec4 *thirdVertex, Camera camera);
};

#endif
