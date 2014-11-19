#include "tinyxml.h"

//#include "CGFappearance.h"
//#include "CGFcamera.h"
//#include "CGFlight.h"

#include "Attributes.h"

#include <stdio.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>



using namespace std;

class Parser
{
public: 
	Parser(const char* filename, Attributes * att);
	//~Parser();

	static TiXmlElement *findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val);

protected:
	TiXmlDocument* doc;
	TiXmlElement* camerasElement; 
	TiXmlElement* lightsElement;
	TiXmlElement* texturesElement;
	TiXmlElement* appearancesElement;
	TiXmlElement* graphElement;
	TiXmlElement* globalsElement;
	TiXmlElement* animationsElement;


};