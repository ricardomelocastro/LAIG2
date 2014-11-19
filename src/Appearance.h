#ifndef APPEARANCE_H
#define APPEARANCE_H

#include <string>
#include <iostream>
#include <CGFappearance.h>
#include "Texture.h"

using namespace std;



class Appearance: public CGFappearance {
protected:
	string appearance_id;
	string textureref;
	bool hasText;

public:
	Appearance(string appearance_id, float shininess, float * ambient, float * diffuse, float * specular);
	string getId();
	void setText(string text);
	string getTextReference();
	Texture * getTexture();
	void setHasText();
	bool getHasText();
	float * getAmbient();
	float * getDiffuse();
	float * getSpecular();
};

#endif