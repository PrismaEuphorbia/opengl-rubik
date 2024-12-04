#include <GL/glut.h>
#include "Cubelet.hpp"
#include <stdio.h>
#include <math.h>

void Cubelet::drawCubelet() {

	glPushMatrix();
	glTranslatef(x * (1 + spacing), y * (1 + spacing), z * (1 + spacing));

	// Array for glColor3fv
	GLfloat colorSet[3];

	// enable lighting for cube surface
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glBegin(GL_QUADS);

	// Draw the cube with different colors on each face
	// front face (initially yellow)

	colorSet[0] = facecols[0].x;
	colorSet[1] = facecols[0].y;
	colorSet[2] = facecols[0].z;
	glColor3fv(colorSet);

	dotVertex(Vector(-0.5f, -0.5f, 0.5f));
	dotVertex(Vector(0.5f, -0.5f, 0.5f));
	dotVertex(Vector(0.5f, 0.5f, 0.5f));
	dotVertex(Vector(-0.5f, 0.5f, 0.5f));

	//bottom face (initially green)

	colorSet[0] = facecols[1].x;
	colorSet[1] = facecols[1].y;
	colorSet[2] = facecols[1].z;
	glColor3fv(colorSet);

	dotVertex(Vector(-0.5f, -0.5f, -0.5f));
	dotVertex(Vector(0.5f, -0.5f, -0.5f));
	dotVertex(Vector(0.5f, -0.5f, 0.5f));
	dotVertex(Vector(-0.5f, -0.5f, 0.5f));

	//left face (initially white)

	colorSet[0] = facecols[2].x;
	colorSet[1] = facecols[2].y;
	colorSet[2] = facecols[2].z;
	glColor3fv(colorSet);

	dotVertex(Vector(-0.5f, -0.5f, -0.5f));
	dotVertex(Vector(-0.5f, -0.5f, 0.5f));
	dotVertex(Vector(-0.5f, 0.5f, 0.5f));
	dotVertex(Vector(-0.5f, 0.5f, -0.5f));

	//right face (initially red)

	colorSet[0] = facecols[3].x;
	colorSet[1] = facecols[3].y;
	colorSet[2] = facecols[3].z;
	glColor3fv(colorSet);

	dotVertex(Vector(0.5f, -0.5f, -0.5f));
	dotVertex(Vector(0.5f, 0.5f, -0.5f));
	dotVertex(Vector(0.5f, 0.5f, 0.5f));
	dotVertex(Vector(0.5f, -0.5f, 0.5f));

	//back face (initially orange)

	colorSet[0] = facecols[4].x;
	colorSet[1] = facecols[4].y;
	colorSet[2] = facecols[4].z;
	glColor3fv(colorSet);

	dotVertex(Vector(-0.5f, -0.5f, -0.5f));
	dotVertex(Vector(-0.5f, 0.5f, -0.5f));
	dotVertex(Vector(0.5f, 0.5f, -0.5f));
	dotVertex(Vector(0.5f, -0.5f, -0.5f));

	//top face (initially blue)

	colorSet[0] = facecols[5].x;
	colorSet[1] = facecols[5].y;
	colorSet[2] = facecols[5].z;
	glColor3fv(colorSet);

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
	xRot = 0, yRot = 0, zRot = 0;
	cubeletSize = 1.0;
	spacing = 0.2;

};

/*
 * Each 27th of a cube. Many faces are black depending on the position at which the cube was created,
 * and the center cubelet, while existent, is fundamentally useless but kept to simplify functions.
 */

Cubelet::Cubelet(float x0, float y0, float z0, Vector colors[6]) {

	x = x0 * (cubeletSize + spacing);
	y = y0 * (cubeletSize + spacing);
	z = z0 * (cubeletSize + spacing);

	xRot = 0, yRot = 0, zRot = 0;

	cubeletSize = 1.0;
	spacing = 0.6;

	// Set to black if inner face; otherwise use cube colors

	printf("%f\n", z0);

	facecols[0] = (z0 == 1 ? colors[3] : Vector(0, 0, 0));
	facecols[1] = (y0 == -1 ? colors[1] : Vector(0, 0, 0));
	facecols[2] = (x0 == -1 ? colors[5] : Vector(0, 0, 0));
	facecols[3] = (x0 == 1 ? colors[0] : Vector(0, 0, 0));
	facecols[4] = (z0 == -1 ? colors[4] : Vector(0, 0, 0));
	facecols[5] = (y0 == 1 ? colors[2] : Vector(0, 0, 0));

};

void Cubelet::dotVertex(Vector v) {

	GLfloat normX, normY, normZ;

	// Check if cubelet position corresponds to vertex position, for each dimension
	normX = (x * v.x > 0 ? v.x : 0);
	normY = (y * v.y > 0 ? v.y : 0);
	normZ = (z * v.z > 0 ? v.z : 0);

	glNormal3f(normX, normY, normZ);
	glVertex3f(v.x, v.y, v.z);

}

void Cubelet::setColors(Vector colors[6], GLfloat x0, GLfloat y0, GLfloat z0) {

	facecols[0] = (z0 == 1 ? colors[3] : Vector(0, 0, 0));
	facecols[1] = (y0 == -1 ? colors[1] : Vector(0, 0, 0));
	facecols[2] = (x0 == -1 ? colors[5] : Vector(0, 0, 0));
	facecols[3] = (x0 == 1 ? colors[0] : Vector(0, 0, 0));
	facecols[4] = (z0 == -1 ? colors[4] : Vector(0, 0, 0));
	facecols[5] = (y0 == 1 ? colors[2] : Vector(0, 0, 0));

}

void Cubelet::ctmMultiply() {
	GLfloat M[16];
	M[0] = mc.mat[0][0];
	M[1] = mc.mat[1][0];
	M[2] = mc.mat[2][0];
	M[3] = 0;
	M[4] = mc.mat[0][1];
	M[5] = mc.mat[1][1];
	M[6] = mc.mat[2][1];
	M[7] = 0;
	M[8] = mc.mat[0][2];
	M[9] = mc.mat[1][2];
	M[10] = mc.mat[2][2];
	M[11] = 0;
	M[12] = mc.mat[0][3];
	M[13] = mc.mat[1][3];
	M[14] = mc.mat[2][3];
	M[15] = 1;
	glMultMatrixf(M);
}

void Cubelet::setPos(float x0, float y0, float z0) {

	x = x0, y = y0, z = z0;
	return;

}
