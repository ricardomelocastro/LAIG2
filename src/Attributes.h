#ifndef _ATTRIBUTES_H_
#define _ATTRIBUTES_H_

#include "Globals.h"
#include "Camera.h"
#include "Light.h"
#include "Node.h"
#include "Appearance.h"
#include "Texture.h"
#include "Animation.h"



class Attributes
{

protected:

	Globals globals;
	string initial_camera;

	map<string, Camera* > cameras;
	vector<Light *> lights;
	map<string, Texture* > textures;
	map<string, Appearance* > appearances;
	map<string, Node *> graph;
	string root_node_id;
	map<string, Animation* > animations;


public:
	Attributes();
	//~Attributes();

	Globals getGlobals(){return this->globals;}

	void setRootId(string root);
	void setInitialCamera(string camera_id);
	string getInitialCamera();
	void setGlobals(string mode, string shading, float * backgroundcolor, string cullingface, string order, bool doublesided, bool local, bool enabled, float * ambientlight);
	
	void addCamera(Camera * cam);
	void addNode(Node * node);
	void addTexture(Texture * text);
	void addAppearance(Appearance *);
	void addAnimation(Animation *);

	map<string, Camera* > getCameras();
	map<string, Node* > getGraph();
	vector< Light* > getLights();
	map<string, Texture * > getTexture();
	map<string, Appearance* > getAppearances();
	void addSpotLight(string light_id, bool enabled, bool marker,float * posistion, float * ambient ,float * diffuse, float * speccular,float  angle,float exponent,float * target);
	void addOmniLight(string light_id, bool enabled, bool marker, float * position, float * ambient, float * diffuse, float * specular);


	void processglobals();
	void drawlights();
	

	string getRoot();

	void cameraById(int id);

	bool verifyTextureref(string textureref);

	void processnodes(string root, Appearance * parentapp);
	void createDisplay(string root,  Appearance * parentapp);
	void processNodesForList(string root, Appearance * parentapp);

	//void setIndex(int newIndex);
	//int getIndex();
	//void incIndex();
	
};

#endif