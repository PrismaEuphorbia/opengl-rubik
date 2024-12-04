/*
 * main.cpp
 * The base class for the Rubik's Cube puzzle.
 *
 * Created on: Nov 30, 2024
 * 	 	Author: Hursh Patel & Ciara Trinh
 */

#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "Matrix.hpp"
#include "Cubelet.hpp"
#include "Camera.hpp"
#include "RubikCube.hpp"

RubikCube cube;
Camera cam;

float angleX = 0.0f; // Rotation angle around X-axis
float angleY = 0.0f; // Rotation angle around Y-axis
int lastX = 0, lastY = 0; // Last mouse position
bool isMouseDown = false;

void display() {

	// Setting the background to be at least a little more comfy
	glClearColor(63.0 / 255.0, 49.0 / 255.0, 53.0 / 255.0, 1.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	gluLookAt(8.0, 8.0, 8.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	cube.render(angleX, angleY);

	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float) w / (float) h, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void mainMenu(GLint option) {
	switch (option) {
	case 1:
		cube.reset();
		break;
	case 2:
		cube.scramble();
		break;
	case 3:
		exit(0);
		break;
	}
	glutPostRedisplay();
}

void motion(int x, int y) {
	if (isMouseDown) {

		// Calculate the change in mouse position
		float dx = x - lastX;
		float dy = y - lastY;

		// Update rotation angles
		// Adjust sensitivity by scaling dx and dy
		angleY = fmod(angleY + dx * 0.4f, 360.0f); // Horizontal mouse movement rotates around Y axis
		angleX = fmod(angleX + dy * 0.4f, 360.0f); // Vertical mouse movement rotates around X axis

		// Optional: Limit rotation to prevent extreme angles
		// angleX = fmax(-90.0f, fmin(90.0f, angleX));

		// Update last mouse position
		lastX = x;
		lastY = y;

		// Redraw the scene
		glutPostRedisplay();
	}
}

void menu() {
	glutCreateMenu(mainMenu);
	glutAddMenuEntry("Reset", 1);
	glutAddMenuEntry("Scramble", 2);
	glutAddMenuEntry("Exit", 3);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void mouse(int btn, int state, int x, int y) {
	if (btn == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			// Start tracking mouse movement
			isMouseDown = true;
			lastX = x;
			lastY = y;

		} else if (state == GLUT_UP) {
			// Stop tracking mouse movement
			isMouseDown = false;
		}
	}
}

// Track keyboard presses and perform actions based on the key pressed

void keyboard(unsigned char key, int x, int y) {

	cube.rotateFace(key);

	glutPostRedisplay();

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Rubik's Cube Puzzle");

	// Initiate the lighting
	GLfloat ambient_light[4] = { 99.0 / 255.0, 75.0 / 255.0, 83.0 / 255.0, 1.0 };
	GLfloat diffuse_light[4] = { 0.9, 0.9, 0.9, 1.0 };// Diffuse, the main lighting
	GLfloat specular_light[4] = { 1.0, 1.0, 1.0, 1.0 };	// Specular light, doesn't work well on low-vertex objects like cubes
	GLfloat light_position[4] = { 0.0, 12.0, 4.0, 12.0 };

	// material brightness capacity
	GLfloat specularity[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLint material_specularity = 60;

	// Gouraud colorization model
	glShadeModel(GL_SMOOTH);

	// material reflectability
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularity);
	// brightness concentration
	glMateriali(GL_FRONT, GL_SHININESS, material_specularity);

	// activate ambient light
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_light);

	// define light parameters
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	// enable changing material color
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_DEPTH_TEST);

	// End of setting background

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMotionFunc(motion);  // Add motion callback for mouse drag

	menu();

	glutMainLoop();
	return 0;
}
