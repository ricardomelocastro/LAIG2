 #include "Primitive.h"


Primitive::Primitive(){}

void Primitive::Draw(Texture * texture, Appearance * appearance){}

Rectangle::Rectangle(float x1, float y1, float x2, float y2)
{
	this -> x1 = x1;
	this -> y1 = y1;
	this -> x2 = x2;
	this -> y2 = y2;
}

void Rectangle::Draw(Texture * texture, Appearance * appearance)
{
	appearance->apply();

	unsigned int id; 
	float t; 
	float s;

	if(texture == NULL){
		id = 0;
		s = 0;
		t = 0;
	}
	else{
		id = texture->getID();
		s =  abs(x2-x1)/texture->getTextLengS();
		t = abs(y2-y1)/texture->getTextLengT();
	}



	glPushMatrix();
	glBegin(GL_QUADS);
		glTexCoord2f(0.0,0.0);
		glVertex2f(x1,y1);
		glTexCoord2f(s,0);
		glVertex2f(x2,y1);
		glTexCoord2f(s,t);
		glVertex2f(x2,y2);
		glTexCoord2f(0,t);
		glVertex2f(x1,y2);
	glEnd();
	glPopMatrix();
}

Triangle::Triangle(float x1, float y1, float z1, float x2, float y2, float z2,float x3, float y3, float z3)
{
	this -> x1 = x1;
	this -> y1 = y1;
	this -> z1 = z1;

	this -> x2 = x2;
	this -> y2 = y2;
	this -> z2 = z2;

	this -> x3 = x3;
	this -> y3 = y3;
	this -> z3 = z3;
	this->normal = new float[3]();

	this->calculateSurfaceNormal();

}

void Triangle::Draw(Texture * texture, Appearance * appearance)
{
	appearance->apply();

	float s; 
	float ss; 
	float tt;

	if(texture == NULL){
		s = 0;
		ss = 0;
		tt = 0;
	}
	else{
		s = this->baseDist/texture->getTextLengS();
		ss = this->minorBase/texture->getTextLengS();
		tt = this->height/texture->getTextLengT();
	}

	glPushMatrix();
	glNormal3f(normal[0],normal[1],normal[2]);
	glBegin(GL_TRIANGLES);
		glTexCoord2f(0.0,0.0);
		glVertex3f(this->x1,this->y1,this->z1);
		glTexCoord2f(s,0.0);
		glVertex3f(this->x2,this->y2,this->z2);
		glTexCoord2f(ss,tt);
		glVertex3f(this->x3,this->y3,this->z3);
	glEnd();
	glPopMatrix();

}

void Triangle::calculateSurfaceNormal()
{

	// https://www.opengl.org/wiki/Calculating_a_Surface_Normal 
	// 
	float * v1 = new float[3]();
	float * v2 = new float[3]();
	float * v3 = new float[3]();

	//vetor1 - calculo de coordenadas do vetor que vai do ponto 1 para o ponto 2

	v1[0] = this->x2 - this->x1;
	v1[1] = this->y2 - this->y1;
	v1[2] = this->z2 - this->z1;

	//vetor2 - calculo de coordenadas do vetor que vai do ponto 1 para o 3
	v2[0] = this->x3 - this->x1;
	v2[1] = this->y3 - this->y1;
	v2[2] = this->z3 - this->z1;

	//vetor3 - calculo de coordenadas do vetor que vai do ponto 2 para o 3
	v3[0] = this->x3 - this->x2;
	v3[1] = this->y3 - this->y2;
	v3[2] = this->z3 - this->z2;

	// a - |v3| ; b - |v2| ; c - |v1|
	float a, b, c;
	a = sqrt(pow(v3[0],2) + pow(v3[1],2) + pow(v3[2],2));
	b = sqrt(pow(v2[0],2) + pow(v2[1],2) + pow(v2[2],2));
	c = sqrt(pow(v1[0],2) + pow(v1[1],2) + pow(v1[2],2));

	//Calculo coordenadas de textura
	float cosB;
	
	cosB = (a*a - b*b + c*c)/(2*a*c);

	this->minorBase = c-(a*cosB);
	this->height = a*sin(acos(cosB));
	this->baseDist = c;

	//Calculo da normal

	this->normal[0] = v1[1]*v2[2] - v1[2]*v2[1];
	this->normal[1] = v1[2]*v2[0] - v1[0]*v2[2];
	this->normal[2] = v1[0]*v2[1] - v1[1]*v2[0];

	//Normalizar a normal
	float dist = sqrt(pow(normal[0],2) + pow(normal[1],2) + pow(normal[2],2));
	normal[0] /= dist;
	normal[1] /= dist;
	normal[2] /= dist;
}



Cylinder::Cylinder(float base, float top, float height, int slices, int stacks)
{
	this -> base = base;
	this -> top = top;
	this -> height = height;	
	this -> slices = slices;
	this -> stacks = stacks;
}

void Cylinder::Draw(Texture * texture, Appearance * appearance)
{
	appearance->apply();

	GLUquadricObj *disk, *disk1;
	GLUquadricObj *cylind;

	cylind = gluNewQuadric();
    disk = gluNewQuadric();
	disk1 = gluNewQuadric();

	//Tampa inferior
	if(texture != NULL){
	glPushMatrix();
	glRotatef(180,0,1,0);
	gluQuadricNormals(disk, GLU_SMOOTH);
	gluQuadricTexture(disk, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture->getID());
    gluDisk(disk, 0, base, slices, slices);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	}else{
		glPushMatrix();
		glRotatef(180,0,1,0);
		gluDisk(disk, 0, base, slices, slices);
		glPopMatrix();
	}
	


	//Cilindro
	if(texture != NULL){
	glPushMatrix();
	gluQuadricNormals(cylind, GLU_SMOOTH);
	gluQuadricTexture(cylind, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture->getID());
	gluCylinder(cylind, base, top, height, slices, stacks);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	}else{
		glPushMatrix();
		gluCylinder(cylind, base, top, height, slices, stacks);
		glPopMatrix();
	}


	//Tampa superior
	if(texture != NULL){
	glPushMatrix();
	glTranslatef(0,0,this->height);
	gluQuadricNormals(disk1, GLU_SMOOTH);
	gluQuadricTexture(disk1, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture->getID());
	gluDisk(disk1, 0, top, slices, slices);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	}else{
		glPushMatrix();
		glTranslatef(0,0,this->height);
		gluDisk(disk1, 0, top, slices, slices);
		glPopMatrix();
	}
}

Sphere::Sphere(float radius, int slices, int stacks)
{
	this -> radius = radius;
	this -> slices = slices;
	this -> stacks = stacks;
}

void Sphere::Draw(Texture * texture, Appearance * appearance)
{
	appearance->apply();

	if(texture != NULL){
	glPushMatrix();
	GLUquadricObj *qobj = gluNewQuadric();
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluQuadricTexture(qobj, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture->getID());
	gluSphere(qobj, radius, slices, stacks);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	}else{
		glPushMatrix();
		GLUquadricObj *qobj = gluNewQuadric();
		gluSphere(qobj, radius, slices, stacks);
		glPopMatrix();
	}
}

Torus::Torus(float inner, float outer, int slices, int loops)
{
	this -> inner = inner;
	this -> outer = outer;
	this -> slices = slices;
	this -> loops = loops;
}

void Torus::Draw(Texture * texture, Appearance * appearance)
{
	appearance->apply();

	if(texture != NULL){
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR );
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR );
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);
		glBindTexture(GL_TEXTURE_2D, texture->getID());
		glutSolidTorus(inner, outer, slices, loops);
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}else{
		glPushMatrix();
		glutSolidTorus(inner, outer, slices, loops);
		glPopMatrix();
	}
}


// Plane
Plane::Plane(){
	this->parts=0;
	this->u1 = 0.0;
	this->v1 = 0.0;
	this->u2 = 1.0;
	this->v2 = 1.0;
}

Plane::Plane(int parts){
	this->parts=parts;
	this->u1 = 0.0;
	this->u2 = 1.0;
	this->ustride= 3; //numero de floats ou doubles entre dois pontos de controlo em u
	this->uorder= 2; //ordem
	this->v1 = 0.0;
	this->v2 = 1.0;
	this->vstride = 6; //numero de floats ou doubles entre dois pontos de controlo em v
	this->vorder= 2; //ordem
}

void Plane::draw(Texture * texture, Appearance * appearance){
	GLfloat controlPoints[4][3] = {
		//{0.0,0.0,0.0},{0.0,2.0,-1.0},{0.0,2.0,-2.0},{0.0,0.0,-3.0},
		//{4.0,0.0,0.0},{4.0,2.0,-1.0},{4.0,2.0,-2.0},{4.0,0.0,-3.0}
		{0.5, 0.0, 0.5},	
		{-0.5, 0.0, 0.5}, 
		{0.5, 0.0, -0.5},
		{-0.5, 0.0, -0.5},
		
	};

	GLfloat normals[4][3] = {
		{0.0, 1.0, 0.0}, 
		{0.0, 1.0, 0.0},
		{0.0, 1.0, 0.0}, 
		{0.0, 1.0, 0.0}
	};

	GLfloat texPoints[4][3] = {
		{0.0, 0.0, 0.0},
		{1.0, 0.0, 0.0},
		{0.0, 0.0, 1.0},
		{1.0, 0.0, 1.0}, 
	};

	//Draw
	glMap2f(GL_MAP2_VERTEX_3, u1, u2, ustride, uorder, v1, v2, vstride, vorder, &controlPoints[0][0]);

	//Normalize
	glMap2f(GL_MAP2_NORMAL, u1, u2, ustride, uorder, v1, v2, vstride, vorder, &normals[0][0]);

	//Texturize
	glMap2f(GL_MAP2_TEXTURE_COORD_2, u1, u2, ustride, uorder, v1, v2, vstride, vorder, &texPoints[0][0]);

	//Enable
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_NORMAL);
	glEnable(GL_MAP2_TEXTURE_COORD_2);
	glMapGrid2f(parts, u1, u2, parts, v1, v2);
	glEvalMesh2(GL_FILL, 0, parts, 0, parts);
}

//Patch
Patch::Patch(int order, int partsU, int partsV, string compute){
	this->order = order + 1;
	this->partsU = partsU;
	this->partsV = partsV;
	this->compute = compute;
}

Patch::Patch(int order, int partsU, int partsV, float * controlPts, string compute){
	this->control = controlPts;
	this->order = order + 1; 
	this->partsU = partsU;
	this->partsV = partsV;
	this->compute = compute;
}

void Patch::draw(){

	glEnable(GL_MAP2_VERTEX_3);
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, order,  0.0, 1.0, 3 * order, order, control);
	
	glEnable(GL_AUTO_NORMAL);

	glMapGrid2f(partsU, 0.0, 1.0, partsV, 0.0, 1.0); 

	glEnable(GL_LIGHTING);
	
	if(compute == "fill")
		glEvalMesh2(GL_FILL, 0, this->partsU, 0, this->partsV);
	else if(compute == "line"){
		glEvalMesh2(GL_LINE, 0, this->partsU, 0, this->partsV);
	}else{
		glEvalMesh2(GL_POINT, 0, this->partsU, 0, this->partsV);
	}
	glDisable(GL_MAP2_VERTEX_3);
}