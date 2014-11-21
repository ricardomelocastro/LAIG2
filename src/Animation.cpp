#include "Animation.h"

Animation::Animation(string id, float span, string type){
	this->id = id;
	this->span = span;
	this->type = type;
}

string Animation::getId(){

	return this->id;
}

void LinearAnimation::init(unsigned long t){

	if(controlX.size() > 0 && controlY.size() > 0 && controlZ.size() > 0) {
		newX = controlX[0];
		newY = controlY[0];
		newZ = controlZ[0];
	} else {
		newX = newY = newZ = 0;
	}


	this->stime = t;
	this->reset = false;
}

LinearAnimation::LinearAnimation(string id, float span, vector<float>controlX,vector<float>controlY,vector<float>controlZ): Animation(id,span,"linear"){

	this->controlX = controlX;
	this->controlY = controlY;
	this->controlZ = controlZ;
	this->distance = 0;
	for(unsigned int i = 1; i < controlX.size(); i++) {
		this->distance += sqrtf(pow(controlX[i]-controlX[i-1], 2) + pow(controlY[i]-controlY[i-1], 2) + pow(controlZ[i]-controlZ[i-1], 2));
	}
	this->actualPos = 0;
	this->reset = true;
	this->ended = false;

	//this->newX=0;
	//this->newY=0;
	//this->newZ=0;
}

void LinearAnimation::update(unsigned long t){

	if(this->reset){
		this->init(t);
	}

	unsigned long time = t - this->stime;
	this->stime = t;

	if(actualPos < controlX.size()-1  && newX == controlX[actualPos+1] && newY == controlY[actualPos+1] && newZ == controlZ[actualPos+1]) 
	{
		actualPos++;
	}

	if(actualPos == controlX.size()-1){
		ended = true;
		return;
	}

	float direction[3]; //represents the movement vector
	direction[0] = controlX[actualPos+1] - controlX[actualPos];
	direction[1] = controlY[actualPos+1] - controlY[actualPos];
	direction[2] = controlZ[actualPos+1] - controlZ[actualPos];


	float norm = sqrtf(pow(direction[0], 2) + pow(direction[1], 2) + pow(direction[2], 2));

	direction[0] = direction[0]/norm;
	direction[1] = direction[1]/norm;
	direction[2] = direction[2]/norm;

	float velocity = (distance/(span*1000))*time;

	direction[0] = direction[0] * velocity;
	direction[1] = direction[1] * velocity;
	direction[2] = direction[2] * velocity;

	newX += direction[0];
	newY += direction[1];
	newZ += direction[2];

	
	if( (direction[0] > 0 && newX > controlX[actualPos+1]) || (direction[0] < 0 && newX < controlX[actualPos+1]))
		newX = controlX[actualPos+1];

	if( (direction[1] > 0 && newY > controlY[actualPos+1]) || (direction[1] < 0 && newY < controlY[actualPos+1]) )
		newY = controlY[actualPos+1];

	if( (direction[2] > 0 && newZ > controlZ[actualPos+1]) || (direction[2] < 0 && newZ < controlZ[actualPos+1]))
		newZ = controlZ[actualPos+1];
		

}

void LinearAnimation::apply(){
	glTranslatef(this->newX,this->newY,this->newZ);
}

CircularAnimation::CircularAnimation(string id, float span, float * center, float radius,float startang, float rotang): Animation(id,span,"circular"){
	this->center = center;
	this->startang = startang;
	this->rotang = rotang;

	this->rotationvelocity = rotang / (span*1000);
	this->resett = true;
	this->radius = radius;
	this->ended = false;

}

void CircularAnimation::init(unsigned long t){
	this->stime = t;
	resett = false;

}


void CircularAnimation::update(unsigned long t){

	if(resett){
		init(t);
	}
	float dt = (t - stime);

	if(dt<=(span*1000))
		this->rotationangle = rotationvelocity *dt;

	if(dt>=(span*1000))
		this->ended = true;

}

void CircularAnimation::apply(){
	glTranslatef(this->center[0] , this->center[1], this->center[2]);
	glRotatef(rotationangle, 0, 1, 0);
	glTranslatef(-this->center[0], -this->center[1], -this->center[2]);

}


void Animation::applyCompleted(){}

void LinearAnimation::applyCompleted(){
	float totalX = controlX[controlX.size()-1];
	float totalZ = controlZ[controlZ.size()-1];

	glTranslatef(totalX,0,totalZ);

}

void CircularAnimation::applyCompleted(){

	glTranslatef(this->center[0] , this->center[1], this->center[2]);
	glRotatef(this->rotang, 0, 1, 0);
	glTranslatef(-this->center[0], -this->center[1], -this->center[2]);

}


void Animation::apply(){}
void Animation::init(unsigned long t){}
void Animation::update(unsigned long t){}
void Animation::reset(){}
void CircularAnimation::reset(){}


bool LinearAnimation::hasEnded(){

	return ended;
}

bool CircularAnimation::hasEnded(){
	return ended;
}

bool Animation::hasEnded(){
	return 0;
}