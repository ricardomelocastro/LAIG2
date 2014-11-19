#include "Light.h"


//omni
Light::Light(unsigned int light_num, string light_id, float* position, bool marker): CGFlight(light_num,position){
	this->light_id = light_id;
	this->marker = marker;
}

//spot
Light::Light(unsigned int light_num, string light_id, float* position, bool marker, float * direction): CGFlight(light_num,position,direction){
	this->light_id = light_id;
	this->marker = marker;

}

Light::~Light(){

}

void Light::draw(){
	if(marker){
		CGFlight::draw();
	}
	else
		CGFlight::update();
}

void Light::setEnabled(bool enabled){
	if(enabled){
		this->enable();
	}
	else{
		this->disable();
	}
}

void Light::toggleEnabled(){
	if(this->enabled)
		this->disable();
	else
		this->enable();
}


void Light::setExponent(float exponent){
	glLightf(this->id,GL_SPOT_EXPONENT,exponent);
}

string Light::getId(){
	return this->light_id;
}

bool Light::isEnabled(){
	return this->enabled;
}

unsigned int Light::getLightNum(){

	return this->id;
}

bool & Light::InterfaceLightValue(){
	return enabled;
}