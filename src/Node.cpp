#include "Node.h"

Node::Node(string node_id){
	this->node_id = node_id;
	this->animationIt = 0;
	this->animated = false;
}

void Node::set_appearanceref(string appref){
	this->appearanceref = appref;
}

void Node::addDescendant(string descendant){
	descendants.push_back(descendant);
}

void Node::addPrimitive(Primitive * primitive){
	primitives.push_back(primitive);
}

void Node::set_Matrix(float * T){
	this->T_matrix = T;

}


string Node::getId(){
	return this->node_id;
}


float * Node::getTransformationMatrix(){
	return this->T_matrix;
}

vector<Primitive *> Node::getPrimitives(){
	return this->primitives;
}

vector<string> Node::getDescendants(){
	return this->descendants;
}

string Node::getAppearanceRef(){
	return this->appearanceref;
}

void Node::setDisplaylist(bool display){
	this->displaylist = display;
}
bool Node::getDisplaylist(){
	return this->displaylist;
}
void Node::setIndex(int newI){
	this->indexofDL = newI;
}
int Node::getIndex(){
	return this->indexofDL;
}

void Node::addAnimation(string animation){

	this->animations.push_back(animation);

}

void Node::setAnimated(){

	this->animated = true;
}

bool Node::hasAnimation(){

	return animated;
}

string Node::getActiveAnimationID(){

	return this->animations[this->animationIt];
}