#include <GL/glut.h>
#include "Cubelet.hpp"


void Cubelet::drawCubelet(float colors[7][3]) {

	glPushMatrix();
	glTranslatef(x, y, z);

	glBegin(GL_QUADS);

	// Draw the cube with different colors on each face
	//front face (yellow)
	glColor3fv(z == 1 ? colors[3] : colors[6]);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);

	//top face (green)
	glColor3fv(y == -1 ? colors[1] : colors[6]);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);

	//left face (white)
	glColor3fv(x == -1 ? colors[5] : colors[6]);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);

	//right face (red)
	glColor3fv(x == 1 ? colors[0] : colors[6]);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);

	//back face (orange)
	glColor3fv(z == -1 ? colors[4] : colors[6]);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);

	//bottom face (blue)
	glColor3fv(y == 1 ? colors[2] : colors[6]);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);

	glEnd(); // End of drawing the cube

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
