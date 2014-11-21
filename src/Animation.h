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

protected:
	string id;
	string type;
	float span;

public:
	Animation(string id, float span, string type);
	virtual void apply();
	virtual void update(unsigned long t);
	virtual void init(unsigned long t);
	string getId();

	virtual void applyCompleted();
	virtual bool hasEnded();
	virtual void defaultValues();
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
	bool ended;

public:
	LinearAnimation(string id, float span,vector<float>controlX,vector<float>controlY,vector<float>controlZ);
	void apply();
	void update(unsigned long t);
	void init(unsigned long t);
	
	void applyCompleted();
	bool hasEnded();
	void defaultValues();

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
	bool ended;
	bool hasEnded();

public:
	CircularAnimation(string id, float span, float * center, float radius, float startang, float rotang);
	void apply();
	void update(unsigned long t);
	void init(unsigned long t);

	void applyCompleted();
	void defaultValues();

};

#endif