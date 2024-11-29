#include <GL/glut.h>
#include <cmath>

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
};

RubikCube cube;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glRotatef(45.0f, 1.0f, 1.0f, 0.0f);

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

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Rubik's Cube");

    glEnable(GL_DEPTH_TEST);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
