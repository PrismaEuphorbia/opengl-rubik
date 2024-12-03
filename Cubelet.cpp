#include <GL/glut.h>
#include "Cubelet.hpp"



void Cubelet::drawCubelet(float colors[7][3]) {

	glPushMatrix();
	glTranslatef(x, y, z);

	// enable lighting for cube surface
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glBegin(GL_QUADS);

	// Draw the cube with different colors on each face
	// front face (initially yellow)
	glColor3fv(z == 1 ? colors[3] : colors[6]);

	dotVertex(Vector(-0.5f, -0.5f, 0.5f));
	dotVertex(Vector(0.5f, -0.5f, 0.5f));
	dotVertex(Vector(0.5f, 0.5f, 0.5f));
	dotVertex(Vector(-0.5f, 0.5f, 0.5f));

	//bottom face (initially green)
	glColor3fv(y == -1 ? colors[1] : colors[6]);
	dotVertex(Vector(-0.5f, -0.5f, -0.5f));
	dotVertex(Vector(0.5f, -0.5f, -0.5f));
	dotVertex(Vector(0.5f, -0.5f, 0.5f));
	dotVertex(Vector(-0.5f, -0.5f, 0.5f));

	//left face (initially white)
	glColor3fv(x == -1 ? colors[5] : colors[6]);
	dotVertex(Vector(-0.5f, -0.5f, -0.5f));
	dotVertex(Vector(-0.5f, -0.5f, 0.5f));
	dotVertex(Vector(-0.5f, 0.5f, 0.5f));
	dotVertex(Vector(-0.5f, 0.5f, -0.5f));

	//right face (initially red)
	glColor3fv(x == 1 ? colors[0] : colors[6]);
	dotVertex(Vector(0.5f, -0.5f, -0.5f));
	dotVertex(Vector(0.5f, 0.5f, -0.5f));
	dotVertex(Vector(0.5f, 0.5f, 0.5f));
	dotVertex(Vector(0.5f, -0.5f, 0.5f));

	//back face (initially orange)
	glColor3fv(z == -1 ? colors[4] : colors[6]);
	dotVertex(Vector(-0.5f, -0.5f, -0.5f));
	dotVertex(Vector(-0.5f, 0.5f, -0.5f));
	dotVertex(Vector(0.5f, 0.5f, -0.5f));
	dotVertex(Vector(0.5f, -0.5f, -0.5f));

	//top face (initially blue)
	glColor3fv(y == 1 ? colors[2] : colors[6]);
	dotVertex(Vector(-0.5f, 0.5f, -0.5f));
	dotVertex(Vector(0.5f, 0.5f, -0.5f));
	dotVertex(Vector(0.5f, 0.5f, 0.5f));
	dotVertex(Vector(-0.5f, 0.5f, 0.5f));

	glEnd(); // End of drawing the cube

	// disable lighting for outline
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);

	// Optionally draw a wireframe around the cubelet
	glColor3f(0.0f, 0.0f, 0.0f); // Set color for the wireframe
	glLineWidth(5);
	glutWireCube(cubeletSize); // Draw the wireframe cube

	glPopMatrix(); // Restore the previous transformation state
}

Cubelet::Cubelet() {

	x = 0, y = 0, z = 0;
	cubeletSize = 1.0;
	spacing = 0.1;

};

Cubelet::Cubelet(float x0, float y0, float z0) {

	x = x0 * (cubeletSize + spacing);
	y = y0 * (cubeletSize + spacing);
	z = z0 * (cubeletSize + spacing);

	cubeletSize = 1.0;
	spacing = 0.1;

};

void Cubelet::setPos(float x0, float y0, float z0) {

	x = x0, y = y0, z = z0;
	return;

}

void Cubelet::dotVertex(Vector v) {

	GLfloat normX, normY, normZ;

	// Check if cubelet position corresponds to vertex position, for each dimension
	normX = (x * v.x > 0 ? v.x : 0);
	normY = (y * v.y > 0 ? v.y : 0);
	normZ = (z * v.z > 0 ? v.z : 0);

	glNormal3f(normX, normY, normZ);
	glVertex3f(v.x, v.y, v.z);

}
