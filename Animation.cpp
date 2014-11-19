#include "Animation.h"

Animation::Animation(string id, float span, string type){
	this->id = id;
	this->span = span;
	this->type = type;
}



LinearAnimation::LinearAnimation(string id, float span, vector<float>controlX,vector<float>controlY,vector<float>controlZ): Animation(id,span,"linear"){

	this->controlX = controlX;
	this->controlY = controlY;
	this->controlZ = controlZ;

}

CircularAnimation::CircularAnimation(string id, float span, float * center, float startang, float rotang): Animation(id,span,"circular"){
	
	this->center = center;
	this->startang = startang;
	this->rotang = rotang;

}