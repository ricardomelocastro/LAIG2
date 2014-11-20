#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>
#include <vector>
#include <iostream>
#include <math.h>
#include <CGFobject.h>
#define PI 3.14159265359

using namespace std;


//Super Animation
class Animation{

protected:
	string id;
	string type;
	float span;

public:
	Animation(string id, float span, string type);
	virtual void apply();
	virtual void update(unsigned long t);
	virtual void reset();
	virtual void init(unsigned long t);
	string getId();
};


//Linear
class LinearAnimation: public Animation{

protected:
	vector<float>controlX;
	vector<float>controlY;
	vector<float>controlZ;
	float distance;
	int actualPos;
	float newX;
	float newY;
	float newZ;
	unsigned long stime;
	bool reset;
public:
	LinearAnimation(string id, float span,vector<float>controlX,vector<float>controlY,vector<float>controlZ);
	void apply();
	void update(unsigned long t);
	void init(unsigned long t);
	

};



//Circular
class CircularAnimation: public Animation{

protected:
	float * center;
	float startang;
	float rotang;
	unsigned long stime;
	float rotationvelocity;
	bool resett;
	float rotationangle;
	float radius;
	

public:
	CircularAnimation(string id, float span, float * center, float radius, float startang, float rotang);
	void apply();
	void update(unsigned long t);
	void init(unsigned long t);
	void reset();

};

#endif