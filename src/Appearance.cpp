#include "Appearance.h"

Appearance::Appearance(string appearance_id, float shininess, float * ambient, float * diffuse, float * specular): CGFappearance(ambient, diffuse, specular, shininess){
	this->appearance_id = appearance_id;
	//this->shininess = shininess;
	//this->textureref = textureref;
	//this->ambient = ambient;
	//this->diffuse = diffuse;
	//this->specular = specular;
	this->hasText = false;

}

string Appearance::getId()
{
	return this->appearance_id;
}

string Appearance::getTextReference(){
	return this->textureref;
}
void Appearance::setText(string textureref){
	this->textureref = textureref;
}
Texture * Appearance::getTexture(){
	return (Texture *)this->texture;	
}


float * Appearance::getAmbient(){
	return this->ambient;
}
float * Appearance::getDiffuse(){
	return this->diffuse;
}
float * Appearance::getSpecular(){
	return this->specular;
}

void Appearance::setHasText(){
	this->hasText = true;
}
bool Appearance::getHasText(){
	return hasText;
}

