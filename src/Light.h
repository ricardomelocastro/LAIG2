#ifndef LIGHT_H
#define LIGHT_H

#include <string>
#include <iostream>
#include <CGFlight.h>

using namespace std;



class Light: public CGFlight {
protected:
	string light_id;
	bool marker;
	//bool enabled;
	//float *dir;
	//float * light_pos;
	//float * light_ambient;
	//float * light_diffuse;
	//float * light_specular;


public:


	Light(unsigned int light_num, string light_id, float* position, bool marker);
	Light(unsigned int light_num, string light_id, float* position, bool marker, float * direction);
	~Light();
	void draw();
	void setEnabled(bool enabled);
	void toggleEnabled();
	void setExponent(float exponent);
	string getId();
	bool isEnabled();
	unsigned int getLightNum();
	bool & InterfaceLightValue();

	void printvalues();


	


};
#endif