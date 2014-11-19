#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <string>
#include <iostream>
#include <CGFobject.h>
#include "Texture.h"
#include "Appearance.h"


using namespace std;


//Super Primitive
class Primitive: public CGFobject{
public:
	Primitive();
	virtual void Draw(Texture * texture, Appearance * appearance);

};

//Rectangle
class Rectangle: public Primitive
{
	private:
		float x1,y1,x2,y2;
	public:
		Rectangle(float x1, float y1, float x2, float y2);
		void Draw(Texture * texture, Appearance * appearance);
};


//Triangle
class Triangle: public Primitive
{
	float baseDist;
	float height;
	float minorBase;
	float * normal;
	float tx1,ty1,tx2,ty2,tx3,ty3;
	float x1,y1,z1,x2,y2,z2,x3,y3,z3;
	public:
		Triangle(float x1, float y1, float z1, float x2, float y2, float z2,float x3, float y3, float z3);
		void calculateSurfaceNormal();
		void Draw(Texture * texture, Appearance * appearance);
};


//Cylinder
class Cylinder: public Primitive
{
		float base, top, height;
		int slices, stacks;
	public:
		Cylinder(float base, float top, float height, int slices, int stacks);
		void Draw(Texture * texture, Appearance * appearance);
};


//Sphere
class Sphere: public Primitive
{
		float radius;
		int slices, stacks;
	public:
		Sphere(float radius, int slices, int stacks);
		void Draw(Texture * texture, Appearance * appearance);
};


//Torus
class Torus: public Primitive
{
		float inner, outer;
		int slices, loops;
	public:
		Torus(float inner, float outer, int slices, int loops);
		void Draw(Texture * texture, Appearance * appearance);
};



//Plane
class Plane : public Primitive {
public:
	Plane();
	Plane(int parts);
	void draw(Texture * texture, Appearance * appearance);

private:
	int parts;
	float u1; 
	float u2; 
    int ustride;
    int uorder;
    float v1;
    float v2;
    int vstride;
    int vorder;
};


class Patch : public Primitive {
public:
	Patch(int order, int partsU, int partsV, float * control, string compute);
	Patch(int order, int partsU, int partsV, string compute);
	void draw();

private:	
	int order, partsU, partsV;
	string compute;
	float * control; // num pontos = (ordem+1)^2
};

/*
class Vehicle : public Primitive {
public:
	Vehicle();

	void draw();

	// create object
	void createTube();
	void createFront();
	void createBack();
	void createTail();
	void createBridge();
	void createBridgeTower();

protected:

	vector<Primitive *> obj;
	int numPatches;

};

*/


#endif