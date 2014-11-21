#ifndef INTERFACE_H
#define INTERFACE_H

#include "Scene.h"
#include "CGFinterface.h"
#include "Light.h"
#include <iostream>
class Interface: public CGFinterface {
	public:
		Interface();
		virtual void initGUI();
		

};


#endif
