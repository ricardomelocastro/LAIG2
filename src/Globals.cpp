#include "Globals.h"

Globals::Globals(){
}

Globals::Globals( string drawmode, string shading, string cullface, string cullorder){
	
	this->cullface = cullface;
	this->cullorder = cullorder;
	this->drawmode = drawmode;
	this->shading = shading;
}
