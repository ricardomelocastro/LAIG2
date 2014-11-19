#ifndef _GLOBALS_H_
#define _GLOBALS_H_


#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

class Globals
{
public:
	Globals();
	Globals(string drawmode, string shading, string cullface, string cullorder);
	/*
	void setR(float r1) {r = r1;}
	void setG(float g1) {g = g1;}
	void setB(float b1) {b = b1;}
	void setA(float a1) {a = a1;}

	float getR() {return r;}
	float getG() {return g;}
	float getB() {return b;}
	float getA() {return a;}*/

	string getDrawMode() {return drawmode;}
	string getShading() {return shading;}
	string getCullface() {return cullface;}
	string getCullorder() {return cullorder;}
	bool getLightingDoublesided() {return lighting_doublesided;}
	bool getLightingLocal() {return lighting_local;}
	bool getLightingEnabled() {return lighting_enabled;}
	float * getAmbientLight() {return ambientlight;}
	float * getBackgroundColor() {return backgroundcolor;}


	void setDrawMode(string drawmode) {this->drawmode = drawmode;}
	void setShading(string shading) {this->shading = shading;}
	void setCullface(string cullface) {this->cullface = cullface;}
	void setCullorder(string cullorder) {this->cullorder = cullorder;}

	void setDoublesided(bool value) {this->lighting_doublesided = value;}
	void setLocal(bool value) {this->lighting_local = value;}
	void setEnabled(bool value) {this->lighting_enabled = value;}


	void setBackgroundColor(float * bc) {this->backgroundcolor = bc;}
	void setAmbientLight(float * al) {this->ambientlight = al;}


private:

	string drawmode;
	string shading;
	string cullface;
	string cullorder;

	bool lighting_doublesided;
	bool lighting_local;
	bool lighting_enabled;
	float * ambientlight;
	float * backgroundcolor;


};


#endif