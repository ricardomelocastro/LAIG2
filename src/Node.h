#ifndef NODE_H
#define NODE_H

#include <string>
#include <iostream>
#include <vector>
#include "Primitive.h"

using namespace std;

class Node{
protected:
	string node_id;

public:
	float * T_matrix;
	string appearanceref;
	vector<Primitive *> primitives;
	vector<string> descendants;
	bool displaylist;
	int indexofDL;


	Node(string node_id);
	void set_Matrix(float * T_matrix);
	void set_appearanceref(string id);
	void addPrimitive(Primitive * primitive);
	void addDescendant(string descendant);
	float * getTransformationMatrix();
	vector<Primitive *> getPrimitives();
	vector<string> getDescendants();
	string getId();
	string getAppearanceRef();
	void setDisplaylist(bool display);
	
	bool getDisplaylist();
	void setIndex(int newI);
	int getIndex();
};

#endif