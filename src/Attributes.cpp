#include "Attributes.h"

Attributes::Attributes(){}

int indexofdisplay;


void Attributes::setRootId(string root){
	this->root_node_id = root;
}

void Attributes::cameraById(int Id){
	map<string, Camera *>::iterator it;
	it = cameras.begin();
	int i = 0;
	while(i < Id -1)
	{
		it++;
		i++;
	}
	this->setInitialCamera(it->second->getId());
}

void Attributes::setInitialCamera(string camera_id){
	this->initial_camera = camera_id;
}

string Attributes::getInitialCamera(){
	return this->initial_camera;
}

void Attributes::addCamera(Camera * camera){

	cameras.insert(pair<string,Camera *>(camera->getId(), camera));

}

void Attributes::addNode(Node * node){

	graph.insert(pair<string,Node* > (node->getId(), node));
}

void Attributes::addTexture(Texture * texture){
	textures.insert(pair<string,Texture *>(texture->getId(), texture));
}

void Attributes::addAppearance(Appearance * appearance){
	appearances.insert(pair<string,Appearance *>(appearance->getId(), appearance));
}

void Attributes::addAnimation(Animation * animation){
	animations.insert(pair<string,Animation *>(animation->getId(),animation));
}

void Attributes::setGlobals(string mode, string shading, float * backgroundcolor, string cullingface, string order, bool doublesided, bool local, bool enabled, float * ambientlight) {

	this->globals.setDrawMode(mode);
	this->globals.setShading(shading);
	this->globals.setBackgroundColor(backgroundcolor);
	this->globals.setAmbientLight(ambientlight);
	this->globals.setCullface(cullingface);
	this->globals.setCullorder(order);
	this->globals.setDoublesided(doublesided);
	this->globals.setLocal(local);
	this->globals.setEnabled(enabled);

}



void Attributes::addOmniLight(string light_id, bool enabled, bool marker, float * position, float * ambient, float * diffuse, float * specular){
	unsigned light_num[8] = {GL_LIGHT0,GL_LIGHT1,GL_LIGHT2,GL_LIGHT3,GL_LIGHT4,GL_LIGHT5,GL_LIGHT6,GL_LIGHT7};

	Light * light = new Light(light_num[lights.size()],light_id, position, marker);

	light->setEnabled(enabled);
	light->setAmbient(ambient);
	light->setDiffuse(diffuse);
	light->setSpecular(specular);

	lights.push_back(light);

}



void Attributes::addSpotLight(string light_id, bool enabled, bool marker,float * position, float * ambient ,float * diffuse, float * specular,float  angle,float exponent,float * target){
	unsigned light_num[8] = {GL_LIGHT0,GL_LIGHT1,GL_LIGHT2,GL_LIGHT3,GL_LIGHT4,GL_LIGHT5,GL_LIGHT6,GL_LIGHT7};

	float direction[3]={(target[0]-position[0]),(target[1]-position[1]),(target[2]-position[2])};

	Light * light = new Light(light_num[lights.size()],light_id, position, marker,direction);

	light->setExponent(exponent);
	light->setAngle(angle);
	light->setEnabled(enabled);
	light->setAmbient(ambient);
	light->setDiffuse(diffuse);
	light->setSpecular(specular);


	lights.push_back(light);

}

void Attributes::drawlights(){

	vector<Light *>::iterator it;


	for(it=lights.begin();it!=lights.end();++it){
		(*it)->draw();
	}
}


void Attributes::processglobals(){

	//lighting
	
	if(globals.getLightingEnabled())
		glEnable(GL_LIGHTING);

	
	if(globals.getLightingLocal())
		glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);


	
	if(globals.getLightingDoublesided())
		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
	else
		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE,GL_FALSE);

	
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globals.getAmbientLight());



	//drawing
	
	if(globals.getDrawMode() == "fill"){
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	}
	else if(globals.getDrawMode() == "line"){
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	}
	else{
		glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
	}

	
	if(globals.getShading() == "flat"){
		glShadeModel(GL_FLAT);
	}
	else{
		glShadeModel(GL_SMOOTH);
	}

	glClearColor(globals.getBackgroundColor()[0],globals.getBackgroundColor()[1],globals.getBackgroundColor()[2],globals.getBackgroundColor()[3]);



	//culling
	if(globals.getCullface() == "back"){
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}
	else if(globals.getCullface() == "front"){
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
	}
	else if(globals.getCullface() == "both"){
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT_AND_BACK);
	}
	else{
		glDisable(GL_CULL_FACE);
	}

	if(globals.getCullorder() == "ccw"){
		glFrontFace(GL_CCW);
	}
	else{
		glFrontFace(GL_CW);
	}
}
map<string, Appearance* > Attributes::getAppearances(){
	return this->appearances;
}

void Attributes::processnodes(string root, Appearance * parentapp){

		Node * no = graph[root];
		if(no->getDisplaylist()){
			glCallList(no->getIndex());
		}else{
			
			//printf("appearanceref processnodes: %s\n", no->appearanceref);
			glMultMatrixf(no->T_matrix);
			Appearance * appearanceToApply;



			if(no->hasAnimation()){
				

				if(no->animationIt>0){
					for(int i = 0; i < no->animationIt;++i){
						
						this->animations[no->animations[i]]->applyCompleted();
						printf("entrou aqui 2\n");
						
					}

				}

				
				this->animations[no->getActiveAnimationID()]->apply();
				
				
			}
			
			if((no->appearanceref != "inherit") || (parentapp == NULL)){
				appearanceToApply = appearances[no->appearanceref];
			}
			else{
				appearanceToApply = parentapp;
			}

			for(vector<string>::iterator it = no->descendants.begin(); it!= no->descendants.end();++it){
			glPushMatrix();
				processnodes((*it), appearanceToApply);
			glPopMatrix();
			}
	
			//appearanceToApply->apply();

			for(vector<Primitive *>::iterator ite = no->primitives.begin(); ite!= no->primitives.end();++ite){
				if(appearanceToApply->getHasText())
					(*ite)->Draw(appearanceToApply->getTexture(), appearanceToApply);
				else
				(*ite)->Draw(NULL, appearanceToApply);
			}
		}
}

//GETS

map<string, Camera* > Attributes::getCameras(){
	return this->cameras;
}

map<string, Node* > Attributes::getGraph(){
	return this->graph;
}

vector< Light* > Attributes::getLights(){
	return this->lights;
}

string Attributes::getRoot(){

	return this->root_node_id;
}


map<string, Texture * > Attributes::getTexture(){
	return this->textures;
}

bool Attributes::verifyTextureref(string textureref){
	bool result = true;

	if(textures.find(textureref) == textures.end())
		result = false;

	return result;

}

void Attributes::createDisplay(string root, Appearance * parentapp){
	Node * no = graph[root];

	if(no->getDisplaylist()){
		indexofdisplay = glGenLists(1);
		graph[root]->setIndex(indexofdisplay);
		glNewList(indexofdisplay,GL_COMPILE);
		processNodesForList(root,parentapp);
		glEndList();
	}else
		{
			for(vector<string>::iterator it = no->descendants.begin(); it!= no->descendants.end();++it)
			{
				createDisplay((*it),parentapp);
			}
		}
}

void Attributes::processNodesForList(string root, Appearance * parentapp){
	Node * no = graph[root];
	Appearance * appearanceToApply;

	//printf("appearanceref: %s\n", no->appearanceref);
	if((no->appearanceref != "inherit") || (parentapp == NULL)){
		appearanceToApply = appearances[no->appearanceref];
	}		
	else{
		appearanceToApply = parentapp;
	}



	if(no->hasAnimation()){
		

		if(no->animationIt>0){
			for(int i = 0; i < no->animationIt;++i){
				this->animations[no->animations[i]]->applyCompleted();
			}

		}

		this->animations[no->getActiveAnimationID()]->apply();
	}



	glMultMatrixf(no->T_matrix);

	for(vector<string>::iterator it = no->descendants.begin(); it!= no->descendants.end();++it){
				glPushMatrix();
				processNodesForList((*it), appearanceToApply);
				glPopMatrix();
		}

	//appearanceToApply->apply();

	for(vector<Primitive *>::iterator ite = no->primitives.begin(); ite!= no->primitives.end();++ite){
			if(appearanceToApply->getHasText())
				(*ite)->Draw(appearanceToApply->getTexture(), appearanceToApply);
			else
				(*ite)->Draw(NULL, appearanceToApply);
		}
}



void Attributes::updateAnimationsNodes(unsigned long t){

	map<string, Node *>::iterator it;

    for (it = graph.begin(); it != graph.end(); ++it) {

		if((*it).second->hasAnimation()){

			printf("encontrou!!\n");

			if(this->animations[(*it).second->getActiveAnimationID()]->hasEnded() && ((*it).second->animationIt < (*it).second->animations.size()-1)){
				++(*it).second->animationIt;
			}

			this->animations[(*it).second->getActiveAnimationID()]->update(t);

		}

	}

}

void Attributes::resetAnimations(){
	map<string, Node *>::iterator it;

    for (it = graph.begin(); it != graph.end(); ++it) {

		if((*it).second->hasAnimation()){

			(*it).second->resetAnimation();
		}

	}

	map<string, Animation *>::iterator ite;

    for (ite = animations.begin(); ite != animations.end(); ++ite) {

		(*ite).second->defaultValues();

	}


}


/*
void Attributes::setIndex(int newIndex){
	this->indexofdisplay = newIndex;
}
	
int Attributes::getIndex(){
	return this->indexofdisplay;
}

void Attributes::incIndex(){
	this->indexofdisplay++;
}
*/