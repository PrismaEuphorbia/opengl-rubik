#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

class RubikCube {
private:
    float cubeletSize;
    float spacing;

public:
    RubikCube() : cubeletSize(1.0f), spacing(0.05f) {}

    void drawCubelet(float x, float y, float z, float r, float g, float b) {
        glPushMatrix();
        glTranslatef(x, y, z);

        glColor3f(r, g, b);
        glutSolidCube(cubeletSize);

        glColor3f(0.0f, 0.0f, 0.0f);
        glutWireCube(cubeletSize + 0.01f);

        glPopMatrix();
    }

    void render() {
        float colors[6][3] = {
            {1.0f, 0.0f, 0.0f},   // Red (right face)
            {0.0f, 1.0f, 0.0f},   // Green (left face)
            {0.0f, 0.0f, 1.0f},   // Blue (top face)
            {1.0f, 1.0f, 0.0f},   // Yellow (bottom face)
            {1.0f, 0.5f, 0.0f},   // Orange (front face)
            {1.0f, 1.0f, 1.0f}    // White (back face)
        };

        for (int x = -1; x <= 1; x++) {
            for (int y = -1; y <= 1; y++) {
                for (int z = -1; z <= 1; z++) {
                    float posX = x * (cubeletSize + spacing);
                    float posY = y * (cubeletSize + spacing);
                    float posZ = z * (cubeletSize + spacing);

                    // Correct color assignment for each face:
                    float r = (x == 1) ? colors[0][0] : ((x == -1) ? colors[1][0] : 0.5f);
                    float g = (y ==  1) ? colors[2][1] : ((y == -1) ? colors[3][1] : 0.5f);
                    float b = (z == 1) ? colors[4][2] : ((z == -1) ? colors[5][2] : 0.5f);

                    drawCubelet(posX, posY, posZ, r, g, b);
                }
            }
        }
    }

    void reset(){
    	//reset logic for the cube
    	//click reset and the rubik will turn back to solved
    }

    void scramble(){
    	//scramble rubik faces with random

    }

    void solve(){
    	//solve the rubik to make every faces same color
    }
};

RubikCube cube;

float angleX = 0.0f; // Rotation angle around X-axis
float angleY = 0.0f; // Rotation angle around Y-axis
int lastX, lastY; // Last mouse position
bool isMouseDown = false;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

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

void menu(){
	glutCreateMenu(mainMenu);
	glutAddMenuEntry("Reset", 1);
	glutAddMenuEntry("Scramble", 2);
	glutAddMenuEntry("Solve", 3);
	glutAddMenuEntry("Exit", 4);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void mouse(int btn, int state, int x, int y){
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		//mouse interaction code here
		isMouseDown = true;
	}else if (state == GLUT_UP){
		isMouseDown = false;
	}
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Rubik's Cube");

    glEnable(GL_DEPTH_TEST);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    menu();

    glutMouseFunc(mouse);

    glutMainLoop();
    return 0;
}
