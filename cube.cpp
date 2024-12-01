#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "Matrix.hpp"
#include "Cubelet.hpp"

class RubikCube {
private:
	float colors[7][3]; // Store colors for each face
	Cubelet cubelets[3][3][3];

public:
	RubikCube() {

		for (int x = 0; x <= 2; x++) {
			for (int y = 0; y <= 2; y++) {
				for (int z = 0; z <= 2; z++) {

					cubelets[x][y][z].setPos(x - 1, y - 1, z - 1);

				}
			}
		}

		reset(); // Initialize colors to represent a solved state
	}

	void render() {
		for (int x = 0; x <= 2; x++) {
			for (int y = 0; y <= 2; y++) {
				for (int z = 0; z <= 2; z++) {
					cubelets[x][y][z].drawCubelet(colors);
				}
			}
		}
	}

	void reset() {
		// Initialize the cube colors to represent a solved state
		colors[0][0] = 1.0f; colors[0][1] = 0.0f; colors[0][2] = 0.0f; // Red
		colors[1][0] = 0.0f; colors[1][1] = 1.0f; colors[1][2] = 0.0f; // Green
		colors[2][0] = 0.0f; colors[2][1] = 0.0f; colors[2][2] = 1.0f; // Blue
		colors[3][0] = 1.0f; colors[3][1] = 1.0f; colors[3][2] = 0.0f; // Yellow
		colors[4][0] = 1.0f; colors[4][1] = 0.5f; colors[4][2] = 0.0f; // Orange
		colors[5][0] = 1.0f; colors[5][1] = 1.0f; colors[5][2] = 1.0f; // White
		colors[6][0] = 0.18f; colors[6][1] = 0.015f; colors[6][2] = 0.18f; // Blackish
	}

	void scramble() {
		// Scramble logic for the cube
	}

	void solve() {
		// Set all faces to the same color (e.g., red)
		colors[0][0] = 1.0f; colors[0][1] = 0.0f; colors[0][2] = 0.0f; // Red
		colors[1][0] = 0.0f; colors[1][1] = 1.0f; colors[1][2] = 0.0f; // Green
		colors[2][0] = 0.0f; colors[2][1] = 0.0f; colors[2][2] = 1.0f; // Blue
		colors[3][0] = 1.0f; colors[3][1] = 1.0f; colors[3][2] = 0.0f; // Yellow
		colors[4][0] = 1.0f; colors[4][1] = 0.5f; colors[4][2] = 0.0f; // Orange
		colors[5][0] =  1.0f; colors[5][1] = 1.0f; colors[5][2] = 1.0f; // White

	}

	void rotateCube(float dx, float dy) {
		// Implement cube rotation logic if needed
		// This could involve updating internal cube state
	}
};

RubikCube cube;

float angleX = 0.0f; // Rotation angle around X-axis
float angleY = 0.0f; // Rotation angle around Y-axis
int lastX = 0, lastY = 0; // Last mouse position
bool isMouseDown = false;

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(8.0, 8.0, 8.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glRotatef(angleX, 1.0f, 0.0f, 0.0f); // Rotate around X-axis
	glRotatef(angleY, 0.0f, 1.0f, 0.0f); // Rotate around Y-axis

	cube.render();

	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void mainMenu (GLint option){
	switch (option){
	case 1:
		cube.reset();
		break;
	case 2:
		cube.scramble();
		break;
	case 3:
		cube.solve();
		break;
	case 4:
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
		angleY += dx * 0.4f;  // Horizontal mouse movement rotates around Y axis
		angleX += dy * 0.4f;  // Vertical mouse movement rotates around X axis

		// Optional: Limit rotation to prevent extreme angles
		// angleX = fmax(-90.0f, fmin(90.0f, angleX));

		// Update cube rotation
		cube.rotateCube(dx, dy);

		// Update last mouse position
		lastX = x;
		lastY = y;

		// Redraw the scene
		glutPostRedisplay();
	}
}

void menu(){
	glutCreateMenu(mainMenu);
	glutAddMenuEntry("Reset", 1);
	glutAddMenuEntry("Scramble", 2);
	glutAddMenuEntry("Solve", 3);
	glutAddMenuEntry("Exit", 4);

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

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("3D Rubik's Cube");

	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);  // Add motion callback for mouse drag

	menu();

	glutMainLoop();
	return 0;
}
