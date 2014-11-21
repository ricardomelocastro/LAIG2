#ifndef SCENE_H
#define SCENE_H

#include "Primitive.h"
#include "CGFscene.h"
#include "Attributes.h"

#include "CGFaxis.h"
#include "CGFapplication.h"
#include "Light.h"

#include "Animation.h"

#include <math.h>

#include "CGFappearance.h"

class Scene : public CGFscene
{
	//Testes
	Plane * plane;
	Patch * patch;
	Vehicle * vehicle;
	Animation * animation;
public:
	Scene();
	void init();
	void display();
	void update(unsigned long t);
	void setCamera(Camera * camera);
	~Scene();
	void addSpotLight(string light_id, bool enabled, bool marker,float * posistion, float * ambient ,float * diffuse, float * speccular,float  angle,float exponent,float * target);
	void addOmniLight(string light_id, bool enabled, bool marker, float * position, float * ambient, float * diffuse, float * specular);
	void applyCamera();
	void chooseCamera();
	void chooseDrawing();
	
	Attributes * getAttributes();
	int cameraId;
	int drawingId;

private:
	Attributes * attributes;
};

#endif