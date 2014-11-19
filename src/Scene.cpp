#include "Scene.h"
#include "Parser.h"




Scene::Scene(): CGFscene(){
} 

void Scene::init() 
{

	attributes = new Attributes();
	string filename;
	cout << "Insert the ANF filename: " << endl;
	cin >> filename;


	Parser teste = Parser(filename.c_str(), attributes);
	
	attributes->processglobals();
	
	//attributes->createDisplay(attributes->getRoot(), NULL);

	plane = new Plane(2);
	/*
	vector<vector<float>> points;
	vector<float> st;
	//{0.0,0.0,0.0},{0.0,2.0,-1.0},{0.0,2.0,-2.0},{0.0,0.0,-3.0},
		//{4.0,0.0,0.0},{4.0,2.0,-1.0},{4.0,2.0,-2.0},{4.0,0.0,-3.0}
	st.push_back(0.0);
	st.push_back(0.0);
	st.push_back(0.0);
	points.push_back(st);
	vector<float> sec;
	sec.push_back(0.0);
	sec.push_back(2.0);
	sec.push_back(-1.0);
	points.push_back(sec);
	vector<float> trd;
	trd.push_back(0.0);
	trd.push_back(2.0);
	trd.push_back(-2.0);
	points.push_back(trd);
	vector<float> fth;
	fth.push_back(0.0);
	fth.push_back(0.0);
	fth.push_back(-3.0);
	points.push_back(fth);
	vector<float> f5h;
	fth.push_back(4.0);
	fth.push_back(0.0);
	fth.push_back(0.0);
	points.push_back(f5h);
	vector<float> f6h;
	fth.push_back(4.0);
	fth.push_back(2.0);
	fth.push_back(-1.0);
	points.push_back(f6h);
	vector<float> f7h;
	fth.push_back(4.0);
	fth.push_back(2.0);
	fth.push_back(-2.0);
	points.push_back(f7h);
	vector<float> f8h;
	fth.push_back(4.0);
	fth.push_back(0.0);
	fth.push_back(-3.0);
	points.push_back(f8h);
	*/
	float * points = new float[27];
	points[0] = 0.0;
	points[1] = 0.0;
	points[2] = 0.0;
	points[3] = 0.0;
	points[4] = 2.0;
	points[5] = -1.0;
	points[6] = 0.0;
	points[7] = 3.0;
	points[8] = -1.5;
	points[9] = 0.0;
	points[10] = 2.0;
	points[11] = -2.0;
	points[12] = 0.0;
	points[13] = 0.0;
	points[14] = -3.0;
	points[15] = 4.0;
	points[16] = 0.0;
	points[17] = 0.0;
	points[18] = 4.0;
	points[19] = 2.0;
	points[20] = -1.0;
	points[21] = 4.0;
	points[22] = 2.0;
	points[23] = -1.0;
	points[24] = 4.0;
	points[25] = 0.0;
	points[26] = -3.0;
	/*{
		{0.0,0.0,0.0},{0.0,2.0,-1.0},{0.0,2.0,-2.0},{0.0,0.0,-3.0},
		{4.0,0.0,0.0},{4.0,2.0,-1.0},{4.0,2.0,-2.0},{4.0,0.0,-3.0}};*/

	patch = new Patch(2, 5, 5, points, "fill");
	setUpdatePeriod(30);
}

void Scene::update(unsigned long t)
{
	
}
	
void Scene::display() 
{

	// ---- BEGIN Background, camera and axis setup
	
	// Clear image and depth buffer everytime we update the scene
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// Initialize Model-View matrix as identity (no transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Associate texture to appearance
	
	chooseDrawing();
	chooseCamera();
	
	

	// Draw (and update) light
	
	attributes->drawlights();

	// Draw axis

	axis.draw();


	// ---- END Background, camera and axis setup


	// ---- BEGIN feature demos

	
	//attributes->processnodes(attributes->getRoot(),NULL);
	
	//plane->draw(attributes->getTexture()["mesaText"], attributes->getAppearances()["mesaApp"]);
	patch->draw(attributes->getTexture()["redeText"], attributes->getAppearances()["redeApp"]);


	// ---- END feature demos

	// We have been drawing in a memory area that is not visible - the back buffer, 
	// while the graphics card is showing the contents of another buffer - the front buffer
	// glutSwapBuffers() will swap pointers so that the back buffer becomes the front buffer and vice-versa
	glutSwapBuffers();

}

Scene::~Scene()
{
	
}


void Scene::chooseDrawing(){
	if(this->drawingId == 0){
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	}
	else if(this->drawingId == 1){
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	}
}

void Scene::applyCamera(){
	activeCamera = this->attributes->getCameras()[attributes->getInitialCamera()];
	CGFapplication::activeApp->forceRefresh();
	this->attributes->getCameras()[attributes->getInitialCamera()]->applyView();
	
}
void Scene::chooseCamera(){
	if(this->cameraId == 0)
	{
		this->initCameras();
		glLoadIdentity();
		this->activeCamera->applyView();
	}
	else{
		this->attributes->cameraById(this->cameraId);
		applyCamera();
	}
}


Attributes * Scene::getAttributes(){
	return this->attributes;
}