#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <iostream>
#include <CGFtexture.h>

using namespace std;



class Texture: public CGFtexture {
protected:
	string texture_id;
	float textlength_s;
	float textlength_t;


public:

	Texture(string texture_id, string file, float textlength_s, float textlength_t);
	string getId();
	float getTextLengS();
	float getTextLengT();
	unsigned int getID();


};

#endif