#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "Matrix.hpp"
#include "Cubelet.hpp"
#include "Camera.hpp"

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

	void render(GLfloat angleX, GLfloat angleY) {
		for (int x = 0; x <= 2; x++) {
			for (int y = 0; y <= 2; y++) {
				for (int z = 0; z <= 2; z++) {

					glPushMatrix();

					glRotatef(angleX, 1.0f, 0.0f, -1.0f); // Rotate around viewer's X-axis
					glRotatef(angleY, 0.0f, 1.0f, 0.0f); // Rotate around viewer's Y-axis

					cubelets[x][y][z].drawCubelet(colors);

					glPopMatrix();

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
Camera cam;

float angleX = 0.0f; // Rotation angle around X-axis
float angleY = 0.0f; // Rotation angle around Y-axis
int lastX = 0, lastY = 0; // Last mouse position
bool isMouseDown = false;

void display() {

	// Setting the background to be at least a little more comfy
	glClearColor(63.0/255.0, 49.0/255.0, 53.0/255.0, 1.0);

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
		angleY = fmod(angleY + dx * 0.4f, 360.0f);  // Horizontal mouse movement rotates around Y axis
		angleX = fmod(angleX + dy * 0.4f, 360.0f);  // Vertical mouse movement rotates around X axis

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

void keyboard(unsigned char key, int state, int x, int y) {

	switch(key) {

	}


}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("3D Rubik's Cube");



	// Initiate the lighting
	GLfloat ambient_light[4]={63.0/255.0, 49.0/255.0, 53.0/255.0, 1.0};
	GLfloat diffuse_light[4]={0.9,0.9,0.9,1.0};		// Diffuse, the main lighting
	GLfloat specular_light[4]={1.0, 1.0, 1.0, 1.0};	// Specular light, doesn't work well on low-vertex objects like cubes
	GLfloat light_position[4]={0.0, 12.0, 4.0, 12.0};

	// material brightness capacity
	GLfloat specularity[4]={1.0,1.0,1.0,1.0};
	GLint material_specularity = 60;

	// Gouraud colorization model
	glShadeModel(GL_SMOOTH);

	// material reflectability
	glMaterialfv(GL_FRONT,GL_SPECULAR, specularity);
	// brightness concentration
	glMateriali(GL_FRONT,GL_SHININESS,material_specularity);

	// activate ambient light
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_light);

	// define light parameters
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light );
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light );
	glLightfv(GL_LIGHT0, GL_POSITION, light_position );

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
