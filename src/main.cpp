/* 
 * G0_Base: projeto inicial de CGra
 * 
 */

#include <iostream>
#include <exception>
#include "Scene.h"
#include "CGFapplication.h"
#include "Interface.h"

using std::cout;
using std::exception;


int main(int argc, char* argv[]) {


	/*
	Attributes * att = new Attributes();

	Parser teste = Parser("teste3.anf", att);

	printf("parser done\n");
	getchar();

	string a = att->getGlobals().getDrawMode();
	string b = att->getGlobals().getShading();

	printf("drawmode = %s\n", a.c_str());
	printf("shading = %s\n", b.c_str());

	getchar();
	
	
	map<string, Camera* > cams = att->getCameras();

	map<string, Camera* >::iterator it;

	for(it = cams.begin(); it!= cams.end(); ++it){

		cout << "id" << (*it).first << "=" <<(*it).second->getId() << " - " << (*it).second->getType() << endl;

	}
	
	getchar();


	*/


	CGFapplication app = CGFapplication();

	try {
		app.init(&argc, argv);

		app.setScene(new Scene());
		app.setInterface(new Interface());
		
		app.run();
	}
	
	catch(GLexception& ex) {
		cout << "Error: " << ex.what();
		return -1;
	}
	catch(exception& ex) {
		cout << "Unexpected error: " << ex.what();
		return -1;
	}
	
	

	return 0;
}