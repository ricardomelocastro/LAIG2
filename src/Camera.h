#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <stdio.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "CGFcamera.h"
#include "CGFscene.h"


using namespace std;

class Camera: public CGFcamera {

protected:
	bool enabled;
	string camera_id;
	float near;
	float far;


public:
	Camera(string camera_id, float near, float far);

	bool getEnabled();
	void setEnabled(bool enable);
	virtual int getCameraType();
	string getId();
	virtual void applyView();
	virtual void updateProjectionMatrix(int width, int height);


	
};

class Perspective: public Camera {

protected:
	float angle;

public:

	Perspective(string camera_id, float near, float far, float * pos, float * target);
	int getCameraType();
	void changeView();
	void applyView();
	void updateProjectionMatrix(int width, int height);
	
};


class Ortho: public Camera{

protected:
	float left;
	float right;
	float top;
	float bottom;
	string direction;

public:

	Ortho(string camera_id, string direction, float near, float far, float left, float right, float top, float bottom);
	int getCameraType();
	void changeView();
	void applyView();
	void updateProjectionMatrix(int width, int height);

};
#endif