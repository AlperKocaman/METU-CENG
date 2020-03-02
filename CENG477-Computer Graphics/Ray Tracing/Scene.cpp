#include <cfloat>
#include <map>
#include <cmath>
#include "Scene.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include "Shape.h"
#include "tinyxml2.h"
#include "Image.h"
#include <math.h>

using namespace tinyxml2;

/* 
 * Must render the scene from each camera's viewpoint and create an image.
 * You can use the methods of the Image class to save the image as a PPM file. 
 */
void Scene::renderScene(void)
{
    //TODO 1 might forgetten u unit vector

    Shape *shape;
    Shape *selectedShape = nullptr;
    ReturnVal *returnVal = new ReturnVal;
    ReturnVal *returnValOverall = new ReturnVal;

    for (int c = pScene->cameras.size() -1 ; c >= 0 ; --c)
    {
        Camera *camera = pScene->cameras[c];
        Image *image = new Image(camera->imgPlane.nx, camera->imgPlane.ny);

        for (int i = camera->imgPlane.nx -1 ; i >= 0 ; --i)
        {
            for (int j = camera->imgPlane.ny -1 ; j >= 0 ; --j)
            {
                Ray primaryRay = camera->getPrimaryRay(i,j);

                selectedShape = nullptr;
                returnValOverall->time = FLT_MAX;

                for (int o = pScene->objects.size()-1 ; o >= 0 ; --o)
                {
                    shape = pScene->objects[o];
                    *returnVal = shape->intersect(primaryRay);

                    if(returnVal->time < returnValOverall->time)//if it intersects
                    {
                        returnValOverall->time = returnVal->time;
                        returnValOverall->surfaceNormalX = returnVal->surfaceNormalX;
                        returnValOverall->surfaceNormalY = returnVal->surfaceNormalY;
                        returnValOverall->surfaceNormalZ = returnVal->surfaceNormalZ;
                        selectedShape = objects[o];
                    }

                }

                if(returnValOverall->time < FLT_MAX)
                {
                    Vector3f intersection = primaryRay.getPoint(returnValOverall->time);

                    Vector3f ambientColor = {
                            pScene->ambientLight.x* pScene->materials[selectedShape->matIndex -1]->ambientRef.x,
                            pScene->ambientLight.y* pScene->materials[selectedShape->matIndex -1]->ambientRef.y,
                            pScene->ambientLight.z* pScene->materials[selectedShape->matIndex -1]->ambientRef.z,
                    };

                    //point light diffuse and specular calculations
                    for (int l = pScene->lights.size() -1; l >= 0 ; --l)
                    {
                        Vector3f lightRay = {
                                pScene->lights[l]->position.x - intersection.x,
                                pScene->lights[l]->position.y - intersection.y,
                                pScene->lights[l]->position.z - intersection.z
                        };

                        float lightRayLength = sqrtf(lightRay.x*lightRay.x +
                                               lightRay.y*lightRay.y +
                                               lightRay.z*lightRay.z) ;

                        lightRay.x /= lightRayLength;
                        lightRay.y /= lightRayLength;
                        lightRay.z /= lightRayLength;

                        Ray shadowRay = {
                                Vector3f{
                                    intersection.x + shadowRayEps*lightRay.x,
                                    intersection.y + shadowRayEps*lightRay.y,
                                    intersection.z + shadowRayEps*lightRay.z},
                                Vector3f{
                                        lightRay.x,
                                        lightRay.y,
                                        lightRay.z}};

                        bool inShadow = false;

                        for (int o = 0; o < objects.size() ; ++o)
                        {
                            ReturnVal shadowReturnVal = objects[o]->intersect(shadowRay);
                            if(shadowReturnVal.time < FLT_MAX )
                            {
                                //we are in shadow by this light
                                if(lightRayLength > shadowReturnVal.time)//normally you would check their time or their lengths seperately but they are the same in this case
                                {
                                    inShadow = true;
                                    break;
                                }
                            }
                        }

                        bool isMirror = materials[selectedShape->matIndex -1]->mirrorRef.x != 0 ||
                                materials[selectedShape->matIndex -1]->mirrorRef.y != 0 ||
                                materials[selectedShape->matIndex -1]->mirrorRef.z != 0;

                        /*if(inShadow && !isMirror)
                        {
                            continue;
                        }*/

                        if(!inShadow)
                        {
                            Vector3f lightContribution = lights[l]->computeLightContribution(intersection);
                            float lightAngleToNormal = fmax(0.0f,
                                                            lightRay.x*returnValOverall->surfaceNormalX +
                                                            lightRay.y*returnValOverall->surfaceNormalY +
                                                            lightRay.z*returnValOverall->surfaceNormalZ );

                            ambientColor.x += pScene->materials[selectedShape->matIndex -1]->diffuseRef.x * lightContribution.x * lightAngleToNormal;
                            ambientColor.y += pScene->materials[selectedShape->matIndex -1]->diffuseRef.y * lightContribution.y * lightAngleToNormal;
                            ambientColor.z += pScene->materials[selectedShape->matIndex -1]->diffuseRef.z * lightContribution.z * lightAngleToNormal;

                            Vector3f halfVector = {
                                    lightRay.x - primaryRay.direction.x,
                                    lightRay.y - primaryRay.direction.y,
                                    lightRay.z - primaryRay.direction.z};

                            float halfVectorLength = sqrtf(halfVector.x*halfVector.x +
                                                          halfVector.y*halfVector.y +
                                                          halfVector.z*halfVector.z) ;

                            halfVector.x /= halfVectorLength;
                            halfVector.y /= halfVectorLength;
                            halfVector.z /= halfVectorLength;

                            float phongMultiplier = powf(fmax(0.0f,
                                                              returnValOverall->surfaceNormalX*halfVector.x +
                                                              returnValOverall->surfaceNormalY*halfVector.y +
                                                              returnValOverall->surfaceNormalZ*halfVector.z),
                                                         materials[selectedShape->matIndex -1]->phongExp);

                            ambientColor.x += pScene->materials[selectedShape->matIndex -1]->specularRef.x * lightContribution.x *phongMultiplier;
                            ambientColor.y += pScene->materials[selectedShape->matIndex -1]->specularRef.y * lightContribution.y *phongMultiplier;
                            ambientColor.z += pScene->materials[selectedShape->matIndex -1]->specularRef.z * lightContribution.z *phongMultiplier;                            
                        }

                        if(isMirror)
                        {
                            float mirrorDotProduct = -returnValOverall->surfaceNormalX*primaryRay.direction.x -
                                                     returnValOverall->surfaceNormalY*primaryRay.direction.y -
                                                     returnValOverall->surfaceNormalZ*primaryRay.direction.z;

                            Vector3f reflectedRay = {
                                    2 * returnValOverall->surfaceNormalX * mirrorDotProduct + primaryRay.direction.x,
                                    2 * returnValOverall->surfaceNormalY * mirrorDotProduct + primaryRay.direction.y,
                                    2 * returnValOverall->surfaceNormalZ * mirrorDotProduct + primaryRay.direction.z};

                            float reflectedRayLength = sqrtf(reflectedRay.x*reflectedRay.x + 
                                reflectedRay.y*reflectedRay.y + 
                                reflectedRay.z*reflectedRay.z);

                            reflectedRay.x /= reflectedRayLength;
                            reflectedRay.y /= reflectedRayLength;
                            reflectedRay.z /= reflectedRayLength;

                            Vector3f reflectedSurfaceColors = calculateMirroredRay(Ray{
                                Vector3f{
                                    intersection.x + shadowRayEps*reflectedRay.x,
                                    intersection.y + shadowRayEps*reflectedRay.y,
                                    intersection.z + shadowRayEps*reflectedRay.z},reflectedRay}, 0);
                            
                            ambientColor.x += reflectedSurfaceColors.x * materials[selectedShape->matIndex -1]->mirrorRef.x;
                            ambientColor.y += reflectedSurfaceColors.y * materials[selectedShape->matIndex -1]->mirrorRef.y;
                            ambientColor.z += reflectedSurfaceColors.z * materials[selectedShape->matIndex -1]->mirrorRef.z;
                        }
                        
                    }


                    Color finalColor = {
                            (unsigned char) fmin(255.0f,ambientColor.x),
                            (unsigned char) fmin(255.0f,ambientColor.y),
                            (unsigned char) fmin(255.0f,ambientColor.z)
                    };

                    image->setPixelValue(i, j, finalColor);
                }
                else
                {
                	image->setPixelValue(i, j, {
                            (unsigned char) backgroundColor.r,
                            (unsigned char) backgroundColor.g,
                            (unsigned char) backgroundColor.b
                    } );
                }

            }
        }

		image->saveImage(camera->imageName);
    }
}

Vector3f Scene::calculateMirroredRay(Ray ray, int bounceCount)
{
    //TODO 1 recheck bounceCount if we bounce again before returning
    ReturnVal returnVal;
    ReturnVal returnValOverall;
    Shape *selectedShape;
    for (int i = 0; i < objects.size(); ++i)
    {
        returnVal = objects[i]->intersect(ray);
        if(returnVal.time < FLT_MAX)
        {
            if(returnValOverall.time > returnVal.time)
            {
                returnValOverall = returnVal;
                selectedShape = objects[i];
            }
        }
    }

    if(returnValOverall.time == FLT_MAX)
    {
        return backgroundColor;
    }
    else
    {
        //normalize the surface normal
        float normalLength = sqrtf(returnValOverall.surfaceNormalX*returnValOverall.surfaceNormalX +
                                  returnValOverall.surfaceNormalY*returnValOverall.surfaceNormalY +
                                  returnValOverall.surfaceNormalZ*returnValOverall.surfaceNormalZ) ;

        returnValOverall.surfaceNormalX /= normalLength;
        returnValOverall.surfaceNormalY /= normalLength;
        returnValOverall.surfaceNormalZ /= normalLength;

        Vector3f intersection = {
                ray.origin.x + ray.direction.x*returnValOverall.time,
                ray.origin.y + ray.direction.y*returnValOverall.time,
                ray.origin.z + ray.direction.z*returnValOverall.time};

        Vector3f ambientColor = {
                pScene->ambientLight.x* pScene->materials[selectedShape->matIndex -1]->ambientRef.x,
                pScene->ambientLight.y* pScene->materials[selectedShape->matIndex -1]->ambientRef.y,
                pScene->ambientLight.z* pScene->materials[selectedShape->matIndex -1]->ambientRef.z};

        //point light diffuse and specular calculations
        for (int l = 0; l < pScene->lights.size(); ++l)
        {
            Vector3f lightRay = {
                    lights[l]->position.x - intersection.x,
                    lights[l]->position.y - intersection.y,
                    lights[l]->position.z - intersection.z};

            float lightRayLength = sqrt(lightRay.x*lightRay.x +
                                   lightRay.y*lightRay.y +
                                   lightRay.z*lightRay.z) ;

            lightRay.x /= lightRayLength;
            lightRay.y /= lightRayLength;
            lightRay.z /= lightRayLength;

            Ray shadowRay = {
                    Vector3f{
                        intersection.x + shadowRayEps*lightRay.x,
                        intersection.y + shadowRayEps*lightRay.y,
                        intersection.z + shadowRayEps*lightRay.z},
                    Vector3f{
                        lightRay.x,
                        lightRay.y,
                        lightRay.z}};

            bool inShadow = false;

            for (int o = 0; o < objects.size() ; ++o)
            {
                ReturnVal shadowReturnVal = objects[o]->intersect(shadowRay);
                if(shadowReturnVal.time < FLT_MAX )
                {
                    //we are in shadow by this light
                    if(lightRayLength > shadowReturnVal.time)//normally you would check their time or their lengths seperately but they are the same in this case
                    {
                        inShadow = true;
                        break;
                    }
                }
            }

            bool isMirror = materials[selectedShape->matIndex -1]->mirrorRef.x != 0 ||
                materials[selectedShape->matIndex -1]->mirrorRef.y != 0 ||
                materials[selectedShape->matIndex -1]->mirrorRef.z != 0;


            if(!inShadow)
            {
                Vector3f lightContribution = lights[l]->computeLightContribution(intersection);
                float lightAngleToNormal = fmax(0.0f,
                                                lightRay.x*returnValOverall.surfaceNormalX +
                                                lightRay.y*returnValOverall.surfaceNormalY +
                                                lightRay.z*returnValOverall.surfaceNormalZ );

                ambientColor.x += pScene->materials[selectedShape->matIndex -1]->diffuseRef.x * lightContribution.x * lightAngleToNormal;
                ambientColor.y += pScene->materials[selectedShape->matIndex -1]->diffuseRef.y * lightContribution.y * lightAngleToNormal;
                ambientColor.z += pScene->materials[selectedShape->matIndex -1]->diffuseRef.z * lightContribution.z * lightAngleToNormal;

                Vector3f halfVector = {
                        lightRay.x - ray.direction.x,
                        lightRay.y - ray.direction.y,
                        lightRay.z - ray.direction.z};

                float halfVectorLength = sqrtf(halfVector.x*halfVector.x +
                                              halfVector.y*halfVector.y +
                                              halfVector.z*halfVector.z) ;

                halfVector.x /= halfVectorLength;
                halfVector.y /= halfVectorLength;
                halfVector.z /= halfVectorLength;

                float phongMultiplier = powf(fmax(0.0f,
                                                  returnValOverall.surfaceNormalX*halfVector.x +
                                                  returnValOverall.surfaceNormalY*halfVector.y +
                                                  returnValOverall.surfaceNormalZ*halfVector.z),
                                             materials[selectedShape->matIndex -1]->phongExp);

                ambientColor.x += pScene->materials[selectedShape->matIndex -1]->specularRef.x * lightContribution.x *phongMultiplier;
                ambientColor.y += pScene->materials[selectedShape->matIndex -1]->specularRef.y * lightContribution.y *phongMultiplier;
                ambientColor.z += pScene->materials[selectedShape->matIndex -1]->specularRef.z * lightContribution.z *phongMultiplier;                            
            }
            
            if(isMirror && bounceCount < maxRecursionDepth)
            {
                float mirrorDotProduct = -returnValOverall.surfaceNormalX*ray.direction.x - 
                    returnValOverall.surfaceNormalY*ray.direction.y - 
                    returnValOverall.surfaceNormalZ*ray.direction.z;

                Vector3f reflectedRay = {
                    2 * returnValOverall.surfaceNormalX * mirrorDotProduct + ray.direction.x,
                    2 * returnValOverall.surfaceNormalY * mirrorDotProduct + ray.direction.y,
                    2 * returnValOverall.surfaceNormalZ * mirrorDotProduct + ray.direction.z};

                float reflectedRayLength = sqrtf(reflectedRay.x*reflectedRay.x + 
                    reflectedRay.y*reflectedRay.y + 
                    reflectedRay.z*reflectedRay.z);

                reflectedRay.x /= reflectedRayLength;
                reflectedRay.y /= reflectedRayLength;
                reflectedRay.z /= reflectedRayLength;

                Vector3f reflectedSurfaceColors = calculateMirroredRay(Ray{
                    Vector3f{
                        intersection.x + shadowRayEps*reflectedRay.x,
                        intersection.y + shadowRayEps*reflectedRay.y,
                        intersection.z + shadowRayEps*reflectedRay.z},reflectedRay}, bounceCount + 1);
                
                ambientColor.x += reflectedSurfaceColors.x * materials[selectedShape->matIndex -1]->mirrorRef.x;
                ambientColor.y += reflectedSurfaceColors.y * materials[selectedShape->matIndex -1]->mirrorRef.y;
                ambientColor.z += reflectedSurfaceColors.z * materials[selectedShape->matIndex -1]->mirrorRef.z;
            }
        }
        return ambientColor;
    }
}

// Parses XML file. 
Scene::Scene(const char *xmlPath)
{
	const char *str;
	XMLDocument xmlDoc;
	XMLError eResult;
	XMLElement *pElement;

	maxRecursionDepth = 1;
	shadowRayEps = 0.001;

	eResult = xmlDoc.LoadFile(xmlPath);

	XMLNode *pRoot = xmlDoc.FirstChild();

	pElement = pRoot->FirstChildElement("MaxRecursionDepth");
	if(pElement != nullptr)
		pElement->QueryIntText(&maxRecursionDepth);

	pElement = pRoot->FirstChildElement("BackgroundColor");
	str = pElement->GetText();
	sscanf(str, "%f %f %f", &backgroundColor.r, &backgroundColor.g, &backgroundColor.b);

	pElement = pRoot->FirstChildElement("ShadowRayEpsilon");
	if(pElement != nullptr)
		pElement->QueryFloatText(&shadowRayEps);

	pElement = pRoot->FirstChildElement("IntersectionTestEpsilon");
	if(pElement != nullptr)
		eResult = pElement->QueryFloatText(&intTestEps);

	// Parse cameras
	pElement = pRoot->FirstChildElement("Cameras");
	XMLElement *pCamera = pElement->FirstChildElement("Camera");
	XMLElement *camElement;
	while(pCamera != nullptr)
	{
        int id;
        char imageName[64];
        Vector3f pos, gaze, up;
        ImagePlane imgPlane;

		eResult = pCamera->QueryIntAttribute("id", &id);
		camElement = pCamera->FirstChildElement("Position");
		str = camElement->GetText();
		sscanf(str, "%f %f %f", &pos.x, &pos.y, &pos.z);
		camElement = pCamera->FirstChildElement("Gaze");
		str = camElement->GetText();
		sscanf(str, "%f %f %f", &gaze.x, &gaze.y, &gaze.z);
		camElement = pCamera->FirstChildElement("Up");
		str = camElement->GetText();
		sscanf(str, "%f %f %f", &up.x, &up.y, &up.z);
		camElement = pCamera->FirstChildElement("NearPlane");
		str = camElement->GetText();
		sscanf(str, "%f %f %f %f", &imgPlane.left, &imgPlane.right, &imgPlane.bottom, &imgPlane.top);
		camElement = pCamera->FirstChildElement("NearDistance");
		eResult = camElement->QueryFloatText(&imgPlane.distance);
		camElement = pCamera->FirstChildElement("ImageResolution");	
		str = camElement->GetText();
		sscanf(str, "%d %d", &imgPlane.nx, &imgPlane.ny);
		camElement = pCamera->FirstChildElement("ImageName");
		str = camElement->GetText();
		strcpy(imageName, str);


		cameras.push_back(new Camera(id, imageName, pos, gaze, up, imgPlane));

		pCamera = pCamera->NextSiblingElement("Camera");
	}

    // Parse materals
	pElement = pRoot->FirstChildElement("Materials");
	XMLElement *pMaterial = pElement->FirstChildElement("Material");
	XMLElement *materialElement;
	while(pMaterial != nullptr)
	{
		materials.push_back(new Material());

		int curr = materials.size() - 1;
	
		eResult = pMaterial->QueryIntAttribute("id", &materials[curr]->id);
		materialElement = pMaterial->FirstChildElement("AmbientReflectance");
		str = materialElement->GetText();
		sscanf(str, "%f %f %f", &materials[curr]->ambientRef.r, &materials[curr]->ambientRef.g, &materials[curr]->ambientRef.b);
		materialElement = pMaterial->FirstChildElement("DiffuseReflectance");
		str = materialElement->GetText();
		sscanf(str, "%f %f %f", &materials[curr]->diffuseRef.r, &materials[curr]->diffuseRef.g, &materials[curr]->diffuseRef.b);
		materialElement = pMaterial->FirstChildElement("SpecularReflectance");
		str = materialElement->GetText();
		sscanf(str, "%f %f %f", &materials[curr]->specularRef.r, &materials[curr]->specularRef.g, &materials[curr]->specularRef.b);
		materialElement = pMaterial->FirstChildElement("MirrorReflectance");
		if(materialElement != nullptr)
		{
			str = materialElement->GetText();
			sscanf(str, "%f %f %f", &materials[curr]->mirrorRef.r, &materials[curr]->mirrorRef.g, &materials[curr]->mirrorRef.b);
		}
				else
		{
			materials[curr]->mirrorRef.r = 0.0;
			materials[curr]->mirrorRef.g = 0.0;
			materials[curr]->mirrorRef.b = 0.0;
		}
		materialElement = pMaterial->FirstChildElement("PhongExponent");
		if(materialElement != nullptr)
			materialElement->QueryIntText(&materials[curr]->phongExp);

		pMaterial = pMaterial->NextSiblingElement("Material");
	}

	// Parse vertex data
	pElement = pRoot->FirstChildElement("VertexData");
	int cursor = 0;
	Vector3f tmpPoint;
	str = pElement->GetText();
	while(str[cursor] == ' ' || str[cursor] == '\t' || str[cursor] == '\n')
		cursor++;
	while(str[cursor] != '\0')
	{
		for(int cnt = 0 ; cnt < 3 ; cnt++)
		{
			if(cnt == 0)
				tmpPoint.x = atof(str + cursor);
			else if(cnt == 1)
				tmpPoint.y = atof(str + cursor);
			else
				tmpPoint.z = atof(str + cursor);
			while(str[cursor] != ' ' && str[cursor] != '\t' && str[cursor] != '\n')
				cursor++; 
			while(str[cursor] == ' ' || str[cursor] == '\t' || str[cursor] == '\n')
				cursor++;
		}
		vertices.push_back(tmpPoint);
	}

	// Parse objects
	pElement = pRoot->FirstChildElement("Objects");
	
	// Parse spheres
	XMLElement *pObject = pElement->FirstChildElement("Sphere");
	XMLElement *objElement;
	while(pObject != nullptr)
	{
		int id;
		int matIndex;
		int cIndex;
		float R;

		eResult = pObject->QueryIntAttribute("id", &id);
		objElement = pObject->FirstChildElement("Material");
		eResult = objElement->QueryIntText(&matIndex);
		objElement = pObject->FirstChildElement("Center");
		eResult = objElement->QueryIntText(&cIndex);
		objElement = pObject->FirstChildElement("Radius");
		eResult = objElement->QueryFloatText(&R);

		objects.push_back(new Sphere(id, matIndex, cIndex, R));

		pObject = pObject->NextSiblingElement("Sphere");
	}

	// Parse triangles
	pObject = pElement->FirstChildElement("Triangle");
	while(pObject != nullptr)
	{
		int id;
		int matIndex;
		int p1Index;
		int p2Index;
		int p3Index;

		eResult = pObject->QueryIntAttribute("id", &id);
		objElement = pObject->FirstChildElement("Material");
		eResult = objElement->QueryIntText(&matIndex);
		objElement = pObject->FirstChildElement("Indices");
		str = objElement->GetText();
		sscanf(str, "%d %d %d", &p1Index, &p2Index, &p3Index);

		objects.push_back(new Triangle(id, matIndex, p1Index, p2Index, p3Index));

		pObject = pObject->NextSiblingElement("Triangle");
	}

	// Parse meshes
	pObject = pElement->FirstChildElement("Mesh");
	while(pObject != nullptr)
	{
		int id;
		int matIndex;
		int p1Index;
		int p2Index;
		int p3Index;
		int cursor = 0;
		int vertexOffset = 0;
		vector<Triangle> faces;

		eResult = pObject->QueryIntAttribute("id", &id);
		objElement = pObject->FirstChildElement("Material");
		eResult = objElement->QueryIntText(&matIndex);
		objElement = pObject->FirstChildElement("Faces");
		objElement->QueryIntAttribute("vertexOffset", &vertexOffset);
		str = objElement->GetText();
		while(str[cursor] == ' ' || str[cursor] == '\t' || str[cursor] == '\n')
			cursor++;
		while(str[cursor] != '\0')
		{
			for(int cnt = 0 ; cnt < 3 ; cnt++)
			{
				if(cnt == 0)
					p1Index = atoi(str + cursor) + vertexOffset;
				else if(cnt == 1)
					p2Index = atoi(str + cursor) + vertexOffset;
				else
					p3Index = atoi(str + cursor) + vertexOffset;
				while(str[cursor] != ' ' && str[cursor] != '\t' && str[cursor] != '\n')
					cursor++; 
				while(str[cursor] == ' ' || str[cursor] == '\t' || str[cursor] == '\n')
					cursor++;
			}
			faces.push_back(*(new Triangle(-1, matIndex, p1Index, p2Index, p3Index)));
		}

		objects.push_back(new Mesh(id, matIndex, faces));

		pObject = pObject->NextSiblingElement("Mesh");
	}

	// Parse lights
	int id;
	Vector3f position;
	Vector3f intensity;
	pElement = pRoot->FirstChildElement("Lights");

	XMLElement *pLight = pElement->FirstChildElement("AmbientLight");
	XMLElement *lightElement;
	str = pLight->GetText();
	sscanf(str, "%f %f %f", &ambientLight.r, &ambientLight.g, &ambientLight.b);

	pLight = pElement->FirstChildElement("PointLight");
	while(pLight != nullptr)
	{
		eResult = pLight->QueryIntAttribute("id", &id);
		lightElement = pLight->FirstChildElement("Position");
		str = lightElement->GetText();
		sscanf(str, "%f %f %f", &position.x, &position.y, &position.z);
		lightElement = pLight->FirstChildElement("Intensity");
		str = lightElement->GetText();
		sscanf(str, "%f %f %f", &intensity.r, &intensity.g, &intensity.b);

		lights.push_back(new PointLight(position, intensity));

		pLight = pLight->NextSiblingElement("PointLight");
	}
}

