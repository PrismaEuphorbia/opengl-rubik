#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

class RubikCube {
private:
    float cubeletSize;
    float spacing;
    float colors[7][3]; // Store colors for each face

public:
    RubikCube() : cubeletSize(1.0f), spacing(0.05f) {
        reset(); // Initialize colors to represent a solved state
    }

    void drawCubelet(float x, float y, float z, float r, float g, float b) {

		float posX = x * (cubeletSize + spacing);
        float posY = y * (cubeletSize + spacing);
        float posZ = z * (cubeletSize + spacing);

    	glPushMatrix();
        glTranslatef(posX, posY, posZ);

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
        glutWireCube(cubeletSize + 0.01f); // Draw the wireframe cube

        glPopMatrix(); // Restore the previous transformation state
    }

    void render() {
        for (int x = -1; x <= 1; x++) {
        	for (int y = -1; y <= 1; y++) {
        		for (int z = -1; z <= 1; z++) {

                    // Determine the color based on the position of the cubelet
                    float r = 0.5f, g = 0.5f, b = 0.5f; // Default color (grey)
                    if (x == 1) { r = colors[0][0]; g = colors[0][1]; b = colors[0][2]; } // Right face
                    else if (x == -1) { r = colors[1][0]; g = colors[1][1]; b = colors[1][2]; } // Left face
                    else if (y == 1) { r = colors[2][0]; g = colors[2][1]; b = colors[2][2]; } // Top face
                    else if (y == -1) { r = colors[3][0]; g = colors[3][1]; b = colors[3][2]; } // Bottom face
                    else if (z == 1) { r = colors[4][0]; g = colors[4][1]; b = colors[4][2]; } // Front face
                    else if (z == -1) { r = colors[5][0]; g = colors[5][1]; b = colors[5][2]; } // Back face
                    drawCubelet((float)x, (float)y, (float)z, r, g, b);
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

void motion(int x, int y) {
    if (isMouseDown) {
        // Calculate the change in mouse position
        float dx = x - lastX;
        float dy = y - lastY;

        // Update rotation angles
        // Adjust sensitivity by scaling dx and dy
        angleY += dx * 0.5f;  // Horizontal mouse movement rotates around Y axis
        angleX += dy * 0.5f;  // Vertical mouse movement rotates around X axis

        // Optional: Limit rotation to prevent extreme angles
        angleX = fmax(-90.0f, fmin(90.0f, angleX));

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
