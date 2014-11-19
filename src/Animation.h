#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>
#include <vector>
#include <iostream>
#include <math.h>
#include <CGFobject.h>

using namespace std;


//Super Animation
class Animation{

private:
	string id;
	string type;
	

public:
	Animation(string id, float span, string type);
	virtual void apply();
	virtual void update(unsigned long t);
	virtual void reset();
	float span;
};


//Linear
class LinearAnimation: public Animation{

private:
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

private:
	float * center;
	float startang;
	float rotang;
	

public:
	CircularAnimation(string id, float span, float * center, float startang, float rotang);
	void apply();
	void update(unsigned long t);
	void reset();

};

#endif