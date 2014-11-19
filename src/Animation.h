#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;


//Super Animation
class Animation{

private:
	string id;
	float span;
	string type;
	

public:
	Animation(string id, float span, string type);
	virtual void apply();
	virtual void update(unsigned long t);
	virtual void reset();

};


//Linear
class LinearAnimation: public Animation{

private:
	vector<float>controlX;
	vector<float>controlY;
	vector<float>controlZ;
	

public:
	LinearAnimation(string id, float span,vector<float>controlX,vector<float>controlY,vector<float>controlZ);
	void apply();
	void update(unsigned long t);
	void reset();
	

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