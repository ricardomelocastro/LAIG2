#include "Interface.h"


Interface::Interface()
{
}




void Interface::initGUI()
{
	//Drawing Mode
	GLUI_Panel * panelDrawing = addPanel("Drawing Mode: ", 1);
	GLUI_RadioGroup * checkDrawing = addRadioGroupToPanel(panelDrawing,(int *)&((Scene * )this->scene)->drawingId, 1);
	addRadioButtonToGroup(checkDrawing, "Fill");
	addRadioButtonToGroup(checkDrawing, "Wireframe");
	
	addColumn();

	//Lights
	vector<Light *> lights = ((Scene *)this->scene)->getAttributes()->getLights();

	int i = 0;
	GLUI_Panel * panelLights = addPanel("Lights: ", 1);
	for(std::vector<Light *>::iterator it = lights.begin(); it != lights.end() ;it++){
		(*it)->isEnabled();
		addCheckboxToPanel (panelLights,(char *)((*it)->getId()).c_str(),(int *)&((*it)->InterfaceLightValue()), i);
		++i;
	}

	addColumn();

	//Cameras
	GLUI_Panel * panelCameras = addPanel("Cameras: ", 1);
	GLUI_RadioGroup * checkCamera = addRadioGroupToPanel(panelCameras,(int *)&((Scene * )this->scene)->cameraId, 1);
	int * camera = NULL;
	map<string, Camera *> cameras = ((Scene *)this->scene)->getAttributes()->getCameras();
	map<string, Camera *>::iterator it;

	addRadioButtonToGroup(checkCamera, "Default Camera");

	for (it = cameras.begin(); it != cameras.end(); it++)
	{
		addRadioButtonToGroup(checkCamera, (char * )it->second->getId().c_str());
	}
	
	addColumn();


}
