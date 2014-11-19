#include "Animation.h"

Animation::Animation(string id, float span, string type){
	this->id = id;
	this->span = span;
	this->type = type;
}

void LinearAnimation::init(unsigned long t){
	this->stime = t;
	newX = controlX[0];
	newY = controlY[0];
	newZ = controlZ[0];
}

LinearAnimation::LinearAnimation(string id, float span, vector<float>controlX,vector<float>controlY,vector<float>controlZ): Animation(id,span,"linear"){

	this->controlX = controlX;
	this->controlY = controlY;
	this->controlZ = controlZ;
	
	for(unsigned int i = 1; i < controlX.size(); i++) {
		this->distance += sqrtf(pow(controlX[i]-controlX[i-1], 2) + pow(controlY[i]-controlY[i-1], 2) + pow(controlZ[i]-controlZ[i-1], 2));
	}
	this->actualPos = 0;
	//this->newX=0;
	//this->newY=0;
	//this->newZ=0;
}

void LinearAnimation::update(unsigned long t){

	unsigned long time = t - this->stime;
	this->stime = t;

	float direction[3]; //represents the movement vector
	direction[0] = controlX[actualPos++] - controlX[actualPos];
	direction[1] = controlY[actualPos++] - controlY[actualPos];
	direction[2] = controlZ[actualPos++] - controlZ[actualPos];

	float norm = sqrtf(pow(direction[0], 2) + pow(direction[1], 2) + pow(direction[2], 2));

	direction[0] = direction[0]/norm;
	direction[1] = direction[1]/norm;
	direction[2] = direction[2]/norm;

	float velocity = (distance/span);

	direction[0] = direction[0] * velocity;
	direction[1] = direction[1] * velocity;
	direction[2] = direction[2] * velocity;

	newX += direction[0];
	newY += direction[1];
	newZ += direction[2];

	/*
	// Verificar se não passou o ponto de controlo seguinte
	if( (v[0] > 0 && xTrans > controlX[previousPoint+1])
		|| (v[0] < 0 && xTrans < controlX[previousPoint+1]))
		xTrans = controlX[previousPoint+1];

	if( (v[1] > 0 && yTrans > controlY[previousPoint+1])
		|| (v[1] < 0 && yTrans < controlY[previousPoint+1]) )
		yTrans = controlY[previousPoint+1];

	if( (v[2] > 0 && zTrans > controlZ[previousPoint+1])
		|| (v[2] < 0 && zTrans < controlZ[previousPoint+1]))
		zTrans = controlZ[previousPoint+1];
		
	
	// Declarando vetores para calcular o ângulo
	float v1[2]; // vetor do segmento de recta a ser actualmente percorrido
	float v2[2]; // vector do segmento de recta unitário no eixo dos zz

	if(previousPoint + 1 < controlX.size()){
		v1[0] = controlX[previousPoint + 1] - controlX[previousPoint];
		v1[1] =	controlZ[previousPoint + 1] - controlZ[previousPoint];
		v2[0] = 0;
		v2[1] = 1;

		float scalar = v1[0] * v2[0] + v1[1] * v2[1];
		float norm1 = sqrt(pow(v1[0],2.0)+pow(v1[1],2.0));
		float norm2 = sqrt(pow(v2[0],2.0)+pow(v2[1],2.0));
		rotation = acos(scalar/(norm1*norm2)) * (180/_PI);
	}

	printf("Rotation: %f\n", rotation);
	*/
}

void LinearAnimation::apply(){
	glTranslatef(this->newX,this->newY,this->newZ);
}


CircularAnimation::CircularAnimation(string id, float span, float * center, float startang, float rotang): Animation(id,span,"circular"){
	this->center = center;
	this->startang = startang;
	this->rotang = rotang;
}