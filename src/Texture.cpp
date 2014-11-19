#include "Texture.h"

Texture::Texture(string texture_id, string file, float textlength_s, float textlength_t): CGFtexture(file)
{
	this->texture_id = texture_id;
	this->textlength_s = textlength_s;
	this->textlength_t = textlength_t;

}

string Texture::getId(){
	return this->texture_id;
}

float Texture::getTextLengS() 
{
	return this->textlength_s;
}

float Texture::getTextLengT()
{
	return this->textlength_t;
}

unsigned int Texture::getID(){
	return CGFtexture::texID;
}