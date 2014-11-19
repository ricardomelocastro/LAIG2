#include "Camera.h"


Camera::Camera(string camera_id, float near, float far){
	this->camera_id = camera_id;
	this->near = near;
	this->far = far;

}

string Camera::getId(){
	return this->camera_id;
}

int Camera::getCameraType(){
	return 0;
}

Perspective::Perspective(string camera_id, float near, float far, float * pos, float * target):
	Camera(camera_id,near,far){
		
		this->setX(pos[0]);
		this->setY(pos[1]);
		this->setZ(pos[2]);

		this->target[0] = target[0];
		this->target[1] = target[1];
		this->target[2] = target[2];
}

int Perspective::getCameraType(){
	return 1;
}

Ortho::Ortho(string camera_id, string direction, float near, float far, float left, float right, float top, float bottom):
	Camera(camera_id,near,far){
		this->direction = direction;
		this->left = left;
		this->right = right;
		this->top = top;
		this->bottom = bottom;

}

void Camera::applyView(){
}
void Camera::updateProjectionMatrix(int width, int height){
}

void Ortho::updateProjectionMatrix(int width, int height){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(left,right,bottom,top,near,far);
}

void Ortho::applyView(){
	if(this->direction == "x"){
		glRotated(90,0,1,0);
	}else if(this->direction == "y"){
		glRotated(90,1,0,0);
	}
}

void Perspective::updateProjectionMatrix(int width, int height){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	
	gluPerspective(angle, width/height, near,far);
}

void Perspective::applyView(){
	gluLookAt(position[0],position[1],position[2],target[0],target[1],target[2],0,1,0);
}


int Ortho::getCameraType(){
	return 2;
}

