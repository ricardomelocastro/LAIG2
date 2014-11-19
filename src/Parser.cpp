#include "Parser.h"




Parser::Parser(const char* filename, Attributes * att)
{
//------------------------------------------------

	doc = new TiXmlDocument( filename );
	bool loadOkay = doc->LoadFile();

	if ( !loadOkay )
	{
		printf( "Could not load file '%s'. Error='%s'. Exiting.\n", filename, doc->ErrorDesc() );
		system("pause");
		exit( 1 );
	}

	TiXmlElement* anfElement= doc->FirstChildElement( "anf" );

	if (anfElement == NULL)
	{
		printf("Main anf block element not found! Exiting!\n");
		system("pause");
		exit(1);
	}

	printf("ANF FOUND\n");


	globalsElement = anfElement->FirstChildElement( "globals" );
	camerasElement = anfElement->FirstChildElement( "cameras" );
	lightsElement = anfElement->FirstChildElement( "lights" );
	texturesElement =  anfElement->FirstChildElement( "textures" );
	appearancesElement =  anfElement->FirstChildElement( "appearances" );
	graphElement =  anfElement->FirstChildElement( "graph" );


	//----------------------------------------------- GLOBALS -------------------------------------

	if (globalsElement == NULL){
		printf("Globals block not found!\n");
		system("pause");
		exit(1);
	}
	else
	{
		printf("Processing globals block:\n");


		TiXmlElement* drawingElement = globalsElement->FirstChildElement( "drawing" );
		TiXmlElement* cullingElement = globalsElement->FirstChildElement( "culling" );
		TiXmlElement* lightingElement = globalsElement->FirstChildElement( "lighting" );

		char* mode = NULL;
		char* shading = NULL;
		char* background=NULL;

		char* face=NULL;
		char* order=NULL;

		bool doublesidedB = false;
		bool localB = false;
		bool enabledB = false;

		float r , g, b, a, x1, y1, z1, alpha1;
		float * backgroundcolor = new float[4];
		float * ambientlight = new  float[4];


		if(drawingElement==NULL){
			printf("drawing not found!\n");
			system("pause");
			exit(1);
		}
		else{
			



			mode = (char*) drawingElement->Attribute("mode");
			shading = (char*) drawingElement->Attribute("shading");
			background =(char *) drawingElement->Attribute("background");


			if ((strcmp(mode,"fill") == 0 || strcmp(mode,"line") == 0 || strcmp(mode,"point") == 0) &&
				(strcmp(shading,"flat") == 0 || strcmp(shading,"gouraud") == 0)){
					printf("Drawing mode: %s\n", mode);
			}
			else{
				printf("Wrong mode attribute!\n");
				system("pause");
				exit(1);
			}



			if(background && sscanf(background,"%f %f %f %f",&r, &g, &b, &a) == 4){
				//store values
				printf("background values (XYZ Alpha): %f %f %f %f\n", r, g, b, a);
				backgroundcolor[0]=r;
				backgroundcolor[1]=g;
				backgroundcolor[2]=b;
				backgroundcolor[3]=a;
				
			}
			else{
				printf("Wrong background values!\n");
				system("pause");
				exit(1);
			}

		}

		//---------------------------Culling-----------------------------------
		
		if(cullingElement==NULL){
			printf("culling not found!\n");
			system("pause");
			exit(1);
		}
		else{
			face = (char *) cullingElement->Attribute("face");
			order = (char *) cullingElement->Attribute("order");

			if(strcmp(face,"none")==0){
				printf("CullFace: none\n");
				
			}
			else if(strcmp(face,"back")==0){
				printf("CullFace: back\n");
			}
			else if(strcmp(face,"front")==0){
				printf("CullFace: front\n");
			}
			else if(strcmp(face,"both")==0){
				printf("CullFace: both\n");
			}
			else{
				printf("wrong cullface value\n");
				system("pause");
				exit(1);
			}


			if(strcmp(order,"ccw")==0){
				printf("Culling order: ccw\n");

			}
			else if(strcmp(order,"cw")==0){
				printf("Culling order: cw\n");
				
				
			}
			else{
				printf("wrong cull order value\n");
				system("pause");
				exit(1);
			}
		}


		//--------------------------LIGHTING-----------------------------------------

		if(lightingElement==NULL){
			printf("lighting not found!\n");
		}
		else{
			char * doublesided = NULL;
			doublesided = (char *) lightingElement->Attribute("doublesided");
			char * local = NULL;
			local = (char *) lightingElement->Attribute("local");
			char * enabled = NULL;
			enabled = (char *) lightingElement->Attribute("enabled");



			if(strcmp(doublesided,"true")==0){
				printf("Doublesided: true\n");
				doublesidedB = true;
				

			}
			else if(strcmp(doublesided,"false")==0){
				printf("Doublesided: false\n");

			}
			else{
				printf("wrong argument for parameter doublesided\n");
				system("pause");
				exit(1);
			}

			//.................

			if(strcmp(local,"true")==0){
				printf("Local: true\n");
				localB = true;
				
			}
			else if(strcmp(local,"false")==0){
				printf("Local: false\n");
				
			}
			else{
				printf("wrong argument for parameter local\n");
				system("pause");
				exit(1);
			}


			if(strcmp(enabled,"true")==0){
				printf("Enabled: true\n");
				enabledB = true;
			}
			else if(strcmp(enabled,"false")==0){
				printf("Enabled: false\n");
				
			}
			else{
				printf("wrong argument for parameter enabled\n");
				system("pause");
				exit(1);
			}


			char *ambient=NULL;
			ambient = (char *) lightingElement->Attribute("ambient");

			if(ambient && sscanf(ambient,"%f %f %f %f",&x1, &y1, &z1, &alpha1)==4){
				//store values
				printf("Ambient values (XYZ Alpha): %f %f %f %f\n", x1, y1, z1, alpha1);
				ambientlight[0]=x1;
				ambientlight[1]=y1;
				ambientlight[2]=z1;
				ambientlight[3]=alpha1;

				
			}
			else{
				printf("Wrong ambient values!\n");
				system("pause");
				exit(1);
			}
		}
		//Storing in the Globals
		att->setGlobals(mode ,shading, backgroundcolor, face, order, doublesidedB, localB, enabledB, ambientlight);

	}

	//--------------------------------------------------CAMERAS-----------------------------------------
	if (camerasElement == NULL){
		printf("Cameras block not found!\n");
		system("pause");
		exit(1);
	}
	else
	{
		printf("Processing Cameras block:\n");

		char * initialcamera = NULL;
		initialcamera = (char *) camerasElement->Attribute("initial");
		printf("Initial Camera: %s\n\n", initialcamera);

		att->setInitialCamera(initialcamera);

		TiXmlElement* cameraElement = camerasElement->FirstChildElement();

		while(cameraElement){

			const char * typecams=cameraElement->Value();


			if((strcmp(typecams,"perspective") == 0)){
				printf("Parsing perspective camera\n\n");

				


				char * camera_id = NULL;
				float near, far, angle;
				float pos[3];
				float target[3];
				float px, py,pz;
				float tx,ty,tz;

				camera_id = (char *) cameraElement->Attribute("id");

				if(camera_id==NULL){
					printf("Perspective camera id not found\n");
					system("pause");
					exit(1);
				}

				if (cameraElement->QueryFloatAttribute("near",&near)==TIXML_SUCCESS && 
					cameraElement->QueryFloatAttribute("far",&far)==TIXML_SUCCESS && 
					cameraElement->QueryFloatAttribute("angle",&angle)==TIXML_SUCCESS){
						char *temppos=NULL;
						char *temptarget=NULL;
						temppos=(char *) cameraElement->Attribute("pos");
						temptarget=(char *) cameraElement->Attribute("target");
						if((temppos && sscanf(temppos,"%f %f %f",&px, &py, &pz)==3)&&
							(temptarget && sscanf(temptarget,"%f %f %f",&tx, &ty, &tz)==3)){

								printf("Perspective camera %s attributes\n near:%f, far:%f, angle:%f\n", camera_id, near, far, angle);
								printf("Perspective position: %f %f %f\n", px, py, pz);
								printf("Perspective target: %f %f %f\n\n", tx, ty, tz);

								pos[0]=px;
								pos[1]=py;
								pos[2]=pz;

								target[0]=tx;
								target[1]=ty;
								target[2]=tz;

								Camera * perspective = new Perspective(camera_id, near,far,pos,target);
								att->addCamera(perspective);

						}
						else{
							printf("error parsing perspective camera position or target\n");
							system("pause");
							exit(1);
						}
				}
				else{
					printf("error parsing perspective camera near, far or angle\n");
					system("pause");
					exit(1);
				}


			}

			else if((strcmp(typecams,"ortho") == 0)){
				printf("Parsing ortho camera\n");

				char * camera_id = NULL;
				char * direction = NULL;
				float near, far, left, right, top, bottom;

				camera_id = (char *) cameraElement->Attribute("id");
				direction = (char *) cameraElement->Attribute("direction");

				if(camera_id == NULL || direction == NULL){
					printf("ortho camera id or direction not found");
					system("pause");
					exit(1);
				}


				if (cameraElement->QueryFloatAttribute("near",&near)==TIXML_SUCCESS && 
					cameraElement->QueryFloatAttribute("far",&far)==TIXML_SUCCESS && 
					cameraElement->QueryFloatAttribute("left",&left)==TIXML_SUCCESS &&
					cameraElement->QueryFloatAttribute("right",&right)==TIXML_SUCCESS &&
					cameraElement->QueryFloatAttribute("top",&top)==TIXML_SUCCESS &&
					cameraElement->QueryFloatAttribute("bottom",&bottom)==TIXML_SUCCESS){
						
						printf("Ortho camera '%s' attributes \n direction:%s, near:%f, far:%f\n", camera_id, direction, near, far);
						printf("left:%f, right:%f, bottom:%f, top:%f\n\n", left, right, bottom, top);

						Camera * ortho = new Ortho(camera_id, direction, near, far, left, right,top, bottom);
						att->addCamera(ortho);

				}
				else{
					printf("error parsing ortho camera attributes\n");
					system("pause");
					exit(1);
				}
			}

			else{
				printf("ERROR!! unknown camera type\n");
				system("pause");
				exit(1);
			}

			cameraElement = cameraElement->NextSiblingElement();

		}
		
	}

	//------------------------------------------------------LIGHTS-------------------------------------

	if(lightsElement == NULL){
		printf("Lights block not found!\n");
		system("pause");
		exit(1);
	}
	else{
		printf("Processing lights block:\n");

		TiXmlElement* lightElement = lightsElement->FirstChildElement("light");

		while(lightElement){

			const char * typelight=lightElement->Attribute("type");

			if((strcmp(typelight,"omni") == 0)){
				printf("Parsing omni light\n\n");

				

				char * light_id = NULL;
				bool enabled = false;
				bool marker = false;
				float * pos = new float[4]();
				float * amb = new float[3]();
				float * dif = new float[3]();
				float * spec = new float[3]();
				float x1, x2,x3, x4;
				float x,y,z;

				pos[3] = 1;

				light_id = (char *) lightElement->Attribute("id");

				if(light_id == NULL){
					printf("light id not found\n");
					system("pause");
					exit(1);

				}


				const char* enabledtemp = lightElement->Attribute("enabled");
				const char* markertemp = lightElement->Attribute("marker");

				if((strcmp(enabledtemp,"true") == 0))
				{
					printf("The light (id %s) is enabled\n", light_id);
					enabled = true;
					
				}
				if((strcmp(markertemp,"true") == 0))
				{
					printf("The light (id %s) has marker\n", light_id);
					marker = true;
					
				}

				char * temppos = NULL;
				temppos=(char *) lightElement->Attribute("pos");
				if(temppos && sscanf(temppos,"%f %f %f",&x, &y, &z)==3){
					printf("Ligh with id %s is in pos %f %f %f\n", light_id, x, y,z);
					pos[0] = x;
					pos[1] = y;
					pos[2] = z;

					
				}
				else{
					printf("error parsing light position\n");
					system("pause");
					exit(1);
				}

				TiXmlElement* componentElement = lightElement->FirstChildElement("component");

				while(componentElement)
				{
					char * type = NULL;
					char * tempvalue=NULL;
					type = (char*) componentElement->Attribute("type");
					tempvalue = (char *) componentElement->Attribute("value");

					if(tempvalue && sscanf(tempvalue,"%f %f %f %f",&x1, &x2, &x3, &x4)==4){
						if(strcmp(type,"ambient") == 0){
							amb[0] = x1;
							amb[1] = x2;
							amb[2] = x3;
							amb[3] = x4;
							printf("Ambient values %f , %f , %f  ,%f\n", x1,x2,x3,x4);
							
						}
						else if(strcmp(type,"diffuse") == 0){
							dif[0] = x1;
							dif[1] = x2;
							dif[2] = x3;
							dif[3] = x4;
							printf("Diffuse values %f , %f , %f  ,%f\n", x1,x2,x3,x4);
							
						}
						else if(strcmp(type,"specular") == 0){
							spec[0] = x1;
							spec[1] = x2;
							spec[2] = x3;
							spec[3] = x4;
							printf("Specular values %f , %f , %f  ,%f\n", x1,x2,x3,x4);
							
						}
						else{
							printf("Error parsing light with id %s", light_id);
							system("pause");
							exit(1);
						}

						
					}
					componentElement = componentElement->NextSiblingElement();
				}

				
				att->addOmniLight(light_id, enabled, marker, pos, amb, dif, spec);

			}
			else{
				if((strcmp(typelight,"spot") == 0)){
					printf("Parsing spot light\n\n");

					



					char * light_id = NULL;
					bool enabled = false;
					bool marker = false;

					float * pos = new float[4]();
					float * amb = new float[3]();
					float * dif = new float[3]();
					float * spec = new float[3]();
					float * target = new float[3]();
					float x1, x2, x3, x4;
					float x,y,z;
					float tgx, tgy, tgz;
					float angle, exponent;
					pos[3]=1;


					light_id = (char *) lightElement->Attribute("id");

					if(light_id == NULL){
						printf("Light id not found\n");
						system("pause");
						exit(1);

					}


					const char* enabledtemp = lightElement->Attribute("enabled");
					const char* markertemp = lightElement->Attribute("marker");

					if((strcmp(enabledtemp,"true") == 0))
					{
						printf("The light (id %s) is enabled\n", light_id);
						enabled = true;
						
					}
					if((strcmp(markertemp,"true") == 0))
					{
						printf("The light (id %s) has marker\n", light_id);
						marker = true;
						
					}

					char * temppos = NULL;
					temppos=(char *) lightElement->Attribute("pos");
					if(temppos && sscanf(temppos,"%f %f %f",&x, &y, &z)==3){
						printf("Ligh with id %s is in pos %f %f %f\n", light_id, x, y,z);
						pos[0] = x;
						pos[1] = y;
						pos[2] = z;
						
					}
					else{
						printf("invalid or missing light position");
						system("pause");
						exit(1);

					}

					char * temptarg = NULL;
					temptarg=(char *) lightElement->Attribute("target");
					if(temptarg && sscanf(temptarg,"%f %f %f",&tgx, &tgy, &tgz)==3){
						printf("Ligh with id %s target is %f %f %f\n", light_id, tgx, tgy, tgz);
						target[0] = tgx;
						target[1] = tgy;
						target[2] = tgz;
						
					}
					else{
						printf("invalid or missing light target\n");
						system("pause");
						exit(1);

					}

					

					if(lightElement->QueryFloatAttribute("angle",&angle)==TIXML_SUCCESS &&
					lightElement->QueryFloatAttribute("exponent",&exponent)==TIXML_SUCCESS){
						printf("Angle %f\n",angle);
						printf("Exponent %f\n",exponent);
					}
					else{
						printf("invalid or missing light Angle or Exponent\n");
						system("pause");
						exit(1);
					}

					TiXmlElement* componentElement = lightElement->FirstChildElement("component");

					while(componentElement)
					{
						char * type = NULL;
						char * tempvalue=NULL;
						type = (char*) componentElement->Attribute("type");
						tempvalue = (char *) componentElement->Attribute("value");

						if(tempvalue && sscanf(tempvalue,"%f %f %f %f",&x1, &x2, &x3, &x4)==4){
							if(strcmp(type,"ambient") == 0){
								amb[0] = x1;
								amb[1] = x2;
								amb[2] = x3;
								amb[3] = x4;
								printf("Ambient values %f , %f , %f  ,%f\n", x1,x2,x3,x4);
								
							}
							else if(strcmp(type,"diffuse") == 0){
								dif[0] = x1;
								dif[1] = x2;
								dif[2] = x3;
								dif[3] = x4;
								printf("Diffuse values %f , %f , %f  ,%f\n", x1,x2,x3,x4);
								
							}
							else if(strcmp(type,"specular") == 0){
								spec[0] = x1;
								spec[1] = x2;
								spec[2] = x3;
								spec[3] = x4;
								printf("Ambient values %f , %f , %f  ,%f\n", x1,x2,x3,x4);
								
							}
							else{
								printf("Error parsing light with id %s", light_id);
								system("pause");
								exit(1);
							}
							

						}
						componentElement = componentElement->NextSiblingElement();
					}

					att->addSpotLight(light_id,  enabled, marker, pos, amb , dif,spec,  angle, exponent, target);
					}
				}
				lightElement = lightElement->NextSiblingElement();
			}

	}

		
	//--------------------------------------------TEXTURES--------------------------------------------------------

	if(texturesElement == NULL)
	{
		printf("Textures block not found!\n");
		system("pause");
		exit(1);
	}
	else
	{
		printf("Processing textures block:\n");

		TiXmlElement* textureElement = texturesElement->FirstChildElement("texture");

		while(textureElement){


			char * text_id = NULL;
			char * file = NULL;
			float textlength_s, textlength_t;
			

			text_id = (char*) textureElement->Attribute("id");
			file = (char *) textureElement->Attribute("file");

			if(text_id == NULL || file == NULL){
				printf("Texture id or file name not found\n");
				system("pause");
				exit(1);
			}
		
			printf("Texture ID: %s on file %s\n",text_id,file);

			if(textureElement->QueryFloatAttribute("texlength_s", &textlength_s) == TIXML_SUCCESS && 
				textureElement->QueryFloatAttribute("texlength_t", &textlength_t)== TIXML_SUCCESS){
					printf("Texture length s: %f\n",textlength_s);
					printf("Texture length t: %f\n\n",textlength_t);
			}
			else{
				printf("Texture length s or t not found!\n");
				system("pause");
				exit(1);
			}

			Texture * texture;

			try{
				texture = new Texture(text_id, file, textlength_s, textlength_t);

			}catch(...){
				printf("Texture with id %s not found!\n",text_id);
				system("pause");
				exit(1);
			}

			att->addTexture(texture);

			textureElement = textureElement->NextSiblingElement();
		}


	}


//----------------------------------APPEARANCES--------------------------------------------

	if(appearancesElement == NULL){
		printf("Appearances block not found!\n\n");
		system("pause");
		exit(1);
	}
	else{
		printf("Processing appearances block:\n\n");
		

		TiXmlElement* appearanceElement = appearancesElement->FirstChildElement( "appearance" );

		while(appearanceElement){
			

			char * appearance_id = NULL;
			float shininess;
			char * textureref = NULL;

			appearance_id = (char *) appearanceElement->Attribute("id");
			if(appearance_id == NULL){
				printf("appearance id not found\n");
				system("pause");
				exit(1);
			}

			printf("appearance id: %s\n", appearance_id);
			if(appearanceElement->QueryFloatAttribute("shininess", &shininess) == TIXML_SUCCESS){
				printf("appearance shininess %f\n", shininess);
			}
			else{
				printf("invalid or not found appearance shininess\n");
				system("pause");
				exit(1);
			
			}

			textureref = (char *) appearanceElement->Attribute("textureref");
			if(textureref!=NULL){

				if ( !att->verifyTextureref(textureref) ) {
					printf("Texture with textureref %s not found\n", textureref);
					system("pause");
					exit(1);
				} else {
				  printf("appearance textureref %s\n", textureref);
				}
			}
			else
				printf("no textureref\n");



			TiXmlElement* componentappearanceElement = appearanceElement->FirstChildElement("component");
			float * amb3 = new float[4];
			float * dif3 = new float[4];
			float * spec3 = new float[4];
			bool ambfound = false;
			bool diffound = false;
			bool specfound = false;

			while(componentappearanceElement){
					
						float x1,x2,x3,x4;
						char * type = NULL;
						char * tempvalue=NULL;
						type = (char*) componentappearanceElement->Attribute("type");
						tempvalue = (char *) componentappearanceElement->Attribute("value");

						if(tempvalue && sscanf(tempvalue,"%f %f %f %f",&x1, &x2, &x3, &x4)==4){
							if(strcmp(type,"ambient") == 0){
								amb3[0] = x1;
								amb3[1] = x2;
								amb3[2] = x3;
								amb3[3] = x4;
								ambfound = true;
								printf("Ambient values %f , %f , %f  ,%f\n", x1,x2,x3,x4);
							}
							else if(strcmp(type,"diffuse") == 0){
								dif3[0] = x1;
								dif3[1] = x2;
								dif3[2] = x3;
								dif3[3] = x4;
								diffound = true;
								printf("Diffuse values %f , %f , %f  ,%f\n", x1,x2,x3,x4);
							}
							else if(strcmp(type,"specular") == 0){
								spec3[0] = x1;
								spec3[1] = x2;
								spec3[2] = x3;
								spec3[3] = x4;
								specfound = true;
								printf("specular values %f , %f , %f  ,%f\n", x1,x2,x3,x4);
							}
							else{
								printf("Error parsing ambient, diffuse or specular values of appearance with id %s", appearance_id);
								system("pause");
								exit(1);
							}

						}

				componentappearanceElement = componentappearanceElement->NextSiblingElement();
			}

			if(!ambfound || !specfound || !diffound){
				printf("ambient, diffuse or specular values of appearance with id %s missing", appearance_id);
				system("pause");
				exit(1);
			}
			Appearance * appearance = new Appearance(appearance_id , shininess,  amb3, dif3,  spec3);
					Texture * text = NULL;
						if(textureref!=NULL){
							text = att->getTexture()[textureref];
							appearance->setHasText();
							appearance->setText(textureref);
							appearance->setTexture(text);

			}
			att->addAppearance(appearance);
			
			

			appearanceElement = appearanceElement->NextSiblingElement();
		}

	}




	//----------------------------------GRAPH--------------------------------------------
	if(graphElement == NULL)
	{
		printf("Graph block not found!\n");
		system("pause");
		exit(1);
	}
	else
	{
		printf("Processing graph:\n\n");
		//First node

		
		char * rootid = NULL;
		rootid = (char *) graphElement->Attribute("rootid");

		if(rootid == NULL){
			printf("Root id not found\n");
			system("pause");
			exit(1);
		}

		printf("RootID: %s\n\n", rootid);
		att->setRootId(rootid);


		TiXmlElement* nodeElement = graphElement->FirstChildElement("node");

		while(nodeElement){

			TiXmlElement* transformsElement=nodeElement->FirstChildElement("transforms");
			TiXmlElement* appearancerefElement=nodeElement->FirstChildElement("appearanceref");
			TiXmlElement* primitivesElement=nodeElement->FirstChildElement("primitives");
			TiXmlElement* descendantsElement=nodeElement->FirstChildElement("descendants");

			

			char * node_id = NULL;
			node_id = (char *) nodeElement->Attribute("id");

			if(node_id == NULL){
				printf("Node id not found\n");
				system("pause");
				exit(1);
			}

			printf("\nProcessing node %s\n",node_id);

			Node * node = new Node(node_id);
			//-------------------------------------Changed ------------------------------------------------
			
			bool displaylistB;
			char * displaylist = NULL;
			
			displaylist = (char *) nodeElement->Attribute("displaylist");
			if(displaylist == NULL){
				printf("There is no displaylist reference!\n");
				displaylistB = false;
			}else{
				if(strcmp(displaylist,"true")==0){
					printf("Displaylist: true\n");
					displaylistB = true;}
				else{
					printf("Displaylist: false\n");
					displaylistB = false;}
			}

			node->setDisplaylist(displaylistB);
			//---------------------------------------------------------------------------------------------

			if(!transformsElement){
				printf("ERROR! transsforms block missing\n\n");
				system("pause");
				exit(1);
			}
			else{

				printf("Transforms\n");

				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();


				TiXmlElement* transformElement=transformsElement->FirstChildElement("transform");

				while(transformElement){


					char* transformtype = (char *) transformElement->Attribute("type");

					
					
					if(strcmp(transformtype,"translate") == 0){

						float tox, toy, toz;
						char * translateto = NULL;
						translateto=(char *) transformElement->Attribute("to");
						if(translateto && sscanf(translateto,"%f %f %f",&tox, &toy, &toz)==3){
							glTranslatef(tox, toy, toz);
							printf("Translate values: %f %f %f\n", tox, toy, toz);
						}
						else{
							printf("error parsing translate\n\n");
							system("pause");
							exit(1);
						}

					}

					else if(strcmp(transformtype,"rotate") == 0){

						float angle;
						char * axis = NULL;
						axis = (char *) transformElement->Attribute("axis");
						

						if(transformElement->QueryFloatAttribute("angle",&angle)==TIXML_SUCCESS){
							if(strcmp(axis,"x") == 0){
								glRotatef(angle,1,0,0);
								printf("Rotate values - angle:%f , axis:%s\n",angle,axis);
							}
							else if(strcmp(axis,"y") == 0){
								glRotatef(angle,0,1,0);
								printf("Rotate values - angle:%f , axis:%s\n",angle,axis);
							}
							else if(strcmp(axis,"z") == 0){
								glRotatef(angle,0,0,1);
								printf("Rotate values - angle:%f , axis:%s\n",angle,axis);
							}
							else{
								printf("error parsing axis value\n");
								system("pause");
								exit(1);
							}
						}
						else{
							printf("error parsing angle\n");
							system("pause");
							exit(1);
						}

					}

					else if(strcmp(transformtype,"scale") == 0){

						float factorx, factory, factorz;
						char * scalefactor = NULL;
						scalefactor=(char *) transformElement->Attribute("factor");
						if(scalefactor && sscanf(scalefactor,"%f %f %f",&factorx, &factory, &factorz)==3){
							glScalef(factorx, factory, factorz);
							printf("Scale values: %f %f %f\n\n", factorx, factory, factorz);
						}
						else{
							printf("error parsing Scale\n");
							system("pause");
							exit(1);
						}
					}

					else{
						printf("ERROR!! Wrong kind of transformation\n");
						system("pause");
						exit(1);
					}

					transformElement = transformElement->NextSiblingElement();
				}
				
				

				float * transformation_matrix = new float[16]();

				glGetFloatv(GL_MODELVIEW_MATRIX,transformation_matrix);

				node->set_Matrix(transformation_matrix);

			}



			//appearanceref

			if(!appearancerefElement){
				printf("ERROR! Appearance Reference Id block missing\n\n");
				system("pause");
				exit(1);
			}
			else{
				printf("\napperanceref\n");
				char * apprefid = NULL;
				apprefid = (char *) appearancerefElement->Attribute("id");

				if(apprefid == NULL){
					printf("ERROR parsing appearenceref id\n\n");
					system("pause");
					exit(1);
				}
				else{

					if(strcmp(apprefid,"inherit") == 0){
						printf("Node inherits parent appearance\n\n");
						node->set_appearanceref(apprefid);
					}
					else{
						printf("Node appearance id: %s\n\n",apprefid);
						node->set_appearanceref(apprefid);
				
					}
				}
			}
			

			if(!primitivesElement && !descendantsElement){
				printf("ERROR! Primitives and descendants block not found\n\n");
				system("pause");
				exit(1);
			}

			if(primitivesElement){

				printf("Primitives\n");
				

				TiXmlElement* primitiveElement = primitivesElement->FirstChildElement();

				while(primitiveElement){

					const char * typeprims=primitiveElement->Value();

					//rectangle
					if((strcmp(typeprims,"rectangle") == 0)){
					
						float x1, y1, x2, y2;
						char * rectanglexy1 = NULL;
						char * rectanglexy2 = NULL;
						rectanglexy1=(char *) primitiveElement->Attribute("xy1");
						rectanglexy2=(char *) primitiveElement->Attribute("xy2");
						if((rectanglexy1 && sscanf(rectanglexy1,"%f %f",&x1, &y1)==2) &&
							(rectanglexy2 && sscanf(rectanglexy2,"%f %f",&x2, &y2)==2)){

								Primitive * p = new Rectangle(x1,y1,x2,y2);
								node->addPrimitive(p);
								printf("Rectangle primitive with x1:%f, y1:%f, x2:%f,y2:%f\n",x1,y1,x2,y2);
						}
						else{
							printf("Error parsing rectangle\n");
							system("pause");
							exit(1);
						}

					}

						
					

					//triangle
					else if((strcmp(typeprims,"triangle") == 0)){

					
						float x1, y1, z1, x2, y2, z2, x3, y3, z3;
						char * trianglexyz1 = NULL;
						char * trianglexyz2 = NULL;
						char * trianglexyz3 = NULL;
						trianglexyz1=(char *) primitiveElement->Attribute("xyz1");
						trianglexyz2=(char *) primitiveElement->Attribute("xyz2");
						trianglexyz3=(char *) primitiveElement->Attribute("xyz3");
						if((trianglexyz1 && sscanf(trianglexyz1,"%f %f %f",&x1, &y1, &z1)==3) &&
							(trianglexyz2 && sscanf(trianglexyz2,"%f %f %f",&x2, &y2, &z2)==3) &&
							(trianglexyz3 && sscanf(trianglexyz3,"%f %f %f",&x3, &y3, &z3)==3)){

								Primitive * p = new Triangle(x1,y1,z1,x2,y2,z2,x3,y3,z3);
								node->addPrimitive(p);
								printf("Triangle primitive with x1:%f, y1:%f, z1:%f, x2:%f, y2:%f, z2:%f, x3:%f, y3:%f, z3:%f\n",x1,y1,z1,x2,y2,z2,x3,y3,z3);
						}
						else{
							printf("Error parsing triangle\n");
							system("pause");
							exit(1);
						}

					
					}

					//cylinder
					else if((strcmp(typeprims,"cylinder") == 0)){
					
						float base, top, height;
						int slices, stacks;
						if(primitiveElement->QueryFloatAttribute("base",&base)==TIXML_SUCCESS&&
							primitiveElement->QueryFloatAttribute("top",&top)==TIXML_SUCCESS&&
							primitiveElement->QueryFloatAttribute("height",&height)==TIXML_SUCCESS&&
							primitiveElement->QueryIntAttribute("slices",&slices)==TIXML_SUCCESS&&
							primitiveElement->QueryIntAttribute("stacks",&stacks)==TIXML_SUCCESS){

								Primitive * p = new Cylinder(base,top,height,slices,stacks);
								node->addPrimitive(p);
								printf("Cylinder primitive with base:%f, top:%f, height:%f, slices:%i, stacks:%i\n",base,top,height,slices,stacks);
						}
						else{
							printf("Error parsing cylinder for node %s \n\n", node_id);
							system("pause");
							exit(1);

						}
						
					}

					//sphere
					else if((strcmp(typeprims,"sphere") == 0)){

						float radius;
						int slices, stacks;
						if(primitiveElement->QueryFloatAttribute("radius",&radius)==TIXML_SUCCESS&&
							primitiveElement->QueryIntAttribute("slices",&slices)==TIXML_SUCCESS&&
							primitiveElement->QueryIntAttribute("stacks",&stacks)==TIXML_SUCCESS){

								Primitive * p = new Sphere(radius,slices,stacks);
								node->addPrimitive(p);
								printf("Sphere primitive with radius:%f, slices:%i, stacks:%i\n",radius,slices,stacks);
						}
						else{
							printf("Error parsing sphere for node %s \n\n", node_id);
							system("pause");
							exit(1);
						}

						
					}
				
					//Torus
					else if((strcmp(typeprims,"torus") == 0)){

					
						float inner, outer;
						int slices, loops;
						if(primitiveElement->QueryFloatAttribute("inner",&inner)==TIXML_SUCCESS&&
							primitiveElement->QueryFloatAttribute("outer",&outer)==TIXML_SUCCESS&&
							primitiveElement->QueryIntAttribute("slices",&slices)==TIXML_SUCCESS&&
							primitiveElement->QueryIntAttribute("loops",&loops)==TIXML_SUCCESS){

								Primitive * p = new Torus(inner,outer,slices,loops);
								node->addPrimitive(p);
								printf("Torus primitive with inner:%f, outer:%f, slices:%i, loops:%i\n",inner,outer,slices,loops);
						}
						else{
							printf("Error parsing Cylinder for node %s \n\n", node_id);
							system("pause");
							exit(1);
						}
					}



					//Plane
					else if((strcmp(typeprims,"plane") == 0)){

						int parts;
						if(primitiveElement->QueryIntAttribute("parts",&parts)==TIXML_SUCCESS){

								Primitive * p = new Plane(parts);
								node->addPrimitive(p);
								printf("Plane primitive with parts:%i\n",parts);
						}
						else{
							printf("Error parsing Plane for node %s \n\n", node_id);
							system("pause");
							exit(1);
						}
					}

					//patch
					else if((strcmp(typeprims,"patch") == 0)){

						<patch order=”ii” partsU=”ii” partsV=”ii” compute=”ss”>
							<controlpoint x=”ff” y=”ff” z=”ff” />

					
						float inner, outer;
						int slices, loops;
						if(primitiveElement->QueryFloatAttribute("inner",&inner)==TIXML_SUCCESS&&
							primitiveElement->QueryFloatAttribute("outer",&outer)==TIXML_SUCCESS&&
							primitiveElement->QueryIntAttribute("slices",&slices)==TIXML_SUCCESS&&
							primitiveElement->QueryIntAttribute("loops",&loops)==TIXML_SUCCESS){

								Primitive * p = new Torus(inner,outer,slices,loops);
								node->addPrimitive(p);
								printf("Torus primitive with inner:%f, outer:%f, slices:%i, loops:%i\n",inner,outer,slices,loops);
						}
						else{
							printf("Error parsing Cylinder for node %s \n\n", node_id);
							system("pause");
							exit(1);
						}
					}

					else{
						printf("Invalid primitive type for node %s \n", node_id);
						system("pause");
						exit(1);
					}


					primitiveElement = primitiveElement->NextSiblingElement();
					}

			}

			if(descendantsElement){
				printf("\nDescendants\n");
				

				TiXmlElement* noderefElement = descendantsElement->FirstChildElement("noderef");

				while(noderefElement){
					
					char * noderef_id = NULL;
					noderef_id = (char *) noderefElement->Attribute("id");

					if(noderef_id == NULL){
						printf("ERROR! No noderef id declared for node %s\n\n",node_id);
						system("pause");
						exit(1);
					}
					else{
						node->addDescendant(noderef_id);
						printf("Node %s\n",noderef_id);
					}

					noderefElement=noderefElement->NextSiblingElement();
				}
			}


			att->addNode(node);

			printf("\nNode %s added\n\n",node_id);

			nodeElement=nodeElement->NextSiblingElement();

		}//end while node

	}


printf("\n FILE ALL PARSED\n");
}
