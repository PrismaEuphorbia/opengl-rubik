#include "RubikCube.hpp"
#include <math.h>

/*
 * An object of the popular puzzle toy with six faces and many "cubelets"
 * that are shifted around to solve the puzzle; get all six faces
 */
RubikCube::RubikCube() {

	// Initialize colors
	colors[0] = Vector(1, 0.3, 0.3); // Red
	colors[1] = Vector(0.3, 1, 0.3); // Green
	colors[2] = Vector(0.2, 0.2, 1); // Blue
	colors[3] = Vector(1, 1, 0); // Yellow
	colors[4] = Vector(1, 0.5, 0); // Orange
	colors[5] = Vector(1, 1, 1); // White

	for (int x = 0; x <= 2; x++) {
		for (int y = 0; y <= 2; y++) {
			for (int z = 0; z <= 2; z++) {

				cubelets[x][y][z].setPos(x - 1, y - 1, z - 1);
				cubelets[x][y][z].setColors(colors, x - 1, y - 1, z - 1);

			}
		}
	}

	reset(); // Initialize colors to represent a solved state
}

// Render the cube
void RubikCube::render(GLfloat angleX, GLfloat angleY) {
	for (int x = 0; x <= 2; x++) {
		for (int y = 0; y <= 2; y++) {
			for (int z = 0; z <= 2; z++) {

				Cubelet *curr = &(cubelets[x][y][z]);

				glPushMatrix();

				// Rotation must be last; rotates ALL cubelets together!
				glRotatef(angleX, 1.0f, 0.0f, -1.0f); // Rotate around viewer's X-axis
				glRotatef(angleY, 0.0f, 1.0f, 0.0f); // Rotate around viewer's Y-axis
				glTranslatef(curr->getX() * (1 + curr->getSpacing()), curr->getY() * (1 + curr->getSpacing()), curr->getZ() * (1 + curr->getSpacing()));

				// Rotate based on Rubik's cube keyboard inputs
				curr->ctmMultiply();

				glTranslatef(-curr->getX() * (1 + curr->getSpacing()), -curr->getY() * (1 + curr->getSpacing()), -curr->getZ() * (1 + curr->getSpacing()));

				curr->drawCubelet();

				glPopMatrix();

			}
		}
	}
}

// Reset the cube to its factory-fresh condition
void RubikCube::reset() {

	// Reset positions and rotation matrices

	for (int x = 0; x <= 2; x++) {
		for (int y = 0; y <= 2; y++) {
			for (int z = 0; z <= 2; z++) {

				cubelets[x][y][z].mc.loadIdentity();
				cubelets[x][y][z].setPos(x - 1, y - 1, z - 1);

			}
		}
	}

}

/*
 * Rotate any of the six standard faces. Use Shift or Caps Lock to rotate the other way!
 */
void RubikCube::rotateFace(char key) {

	switch (tolower(key)) {

	// FRONT: Affects the front layer
	case 'f':

		for (int x = 0; x <= 2; x++) {
			for (int y = 0; y <= 2; y++) {
				for (int z = 0; z <= 2; z++) {

					Cubelet *curr = &(cubelets[x][y][z]);

					if (fabs(curr->getZ() - 1) <= 0.01) {

						// Use rotation matrix to apply rotation
						Matrix rotate;
						// CCW
						if (key == 'F')
							rotate.rotateMatrix(0, 0, 1, -90);
						// CW
						else
							rotate.rotateMatrix(0, 0, 1, 90);

						curr->mc.matrixPreMultiply(&rotate);

						// Update cubelet's dimensions based on position and direction
						curr->setPos(curr->getY() * (key == 'F' ? 1 : -1), -curr->getX() * (key == 'F' ? 1 : -1), curr->getZ());

					}

				}
			}
		}

		break;

		// UP: Affects the top face
	case 'u':

		for (int x = 0; x <= 2; x++) {
			for (int y = 0; y <= 2; y++) {
				for (int z = 0; z <= 2; z++) {

					Cubelet *curr = &(cubelets[x][y][z]);

					if (fabs(curr->getY() - 1) <= 0.01) {

						// Use rotation matrix to apply rotation
						Matrix rotate;
						// CCW
						if (key == 'U')
							rotate.rotateMatrix(0, 1, 0, -90);
						// CW
						else
							rotate.rotateMatrix(0, 1, 0, 90);


						curr->mc.matrixPreMultiply(&rotate);

						// Update cubelet's dimensions based on position and direction
						curr->setPos(-curr->getZ() * (key == 'U' ? 1 : -1), curr->getY(), curr->getX() * (key == 'U' ? 1 : -1));

					}

				}
			}
		}

		break;

		// DOWN: Affects the bottom face
	case 'd':

		for (int x = 0; x <= 2; x++) {
			for (int y = 0; y <= 2; y++) {
				for (int z = 0; z <= 2; z++) {

					Cubelet *curr = &(cubelets[x][y][z]);

					if (fabs(curr->getY() + 1) <= 0.01) {

						// Use rotation matrix to apply rotation
						Matrix rotate;
						// CCW
						if (key == 'D')
							rotate.rotateMatrix(0, 1, 0, 90);
						// CW
						else
							rotate.rotateMatrix(0, 1, 0, -90);


						curr->mc.matrixPreMultiply(&rotate);

						// Update cubelet's dimensions based on position and direction
						curr->setPos(curr->getZ() * (key == 'D' ? 1 : -1), curr->getY(), -curr->getX() * (key == 'D' ? 1 : -1));

					}

				}
			}
		}

		break;

		// BACK: Affects the back face
	case 'b':

		for (int x = 0; x <= 2; x++) {
			for (int y = 0; y <= 2; y++) {
				for (int z = 0; z <= 2; z++) {

					Cubelet *curr = &(cubelets[x][y][z]);

					if (fabs(curr->getZ() + 1) <= 0.01) {

						// Use rotation matrix to apply rotation
						Matrix rotate;
						// CCW
						if (key == 'B')
							rotate.rotateMatrix(0, 0, 1, 90);
						// CW
						else
							rotate.rotateMatrix(0, 0, 1, -90);

						curr->mc.matrixPreMultiply(&rotate);

						// Update cubelet's dimensions based on position and direction
						curr->setPos(-curr->getY() * (key == 'B' ? 1 : -1), curr->getX() * (key == 'B' ? 1 : -1), curr->getZ());

					}

				}
			}
		}

		break;

		// LEFT: Affects the left face
	case 'l':

		for (int x = 0; x <= 2; x++) {
			for (int y = 0; y <= 2; y++) {
				for (int z = 0; z <= 2; z++) {

					Cubelet *curr = &(cubelets[x][y][z]);

					if (fabs(curr->getX() + 1) <= 0.01) {

						// Use rotation matrix to apply rotation
						Matrix rotate;
						// CCW
						if (key == 'L')
							rotate.rotateMatrix(1, 0, 0, 90);
						// CW
						else
							rotate.rotateMatrix(1, 0, 0, -90);

						curr->mc.matrixPreMultiply(&rotate);

						// Update cubelet's dimensions based on position and direction
						curr->setPos(curr->getX(), -curr->getZ() * (key == 'L' ? 1 : -1), curr->getY() * (key == 'L' ? 1 : -1));

					}

				}
			}
		}

		break;

		// RIGHT: Affects the right face
	case 'r':

		for (int x = 0; x <= 2; x++) {
			for (int y = 0; y <= 2; y++) {
				for (int z = 0; z <= 2; z++) {

					Cubelet *curr = &(cubelets[x][y][z]);

					if (fabs(curr->getX() - 1) <= 0.01) {

						// Use rotation matrix to apply rotation
						Matrix rotate;
						// CCW
						if (key == 'R')
							rotate.rotateMatrix(1, 0, 0, -90);
						// CW
						else
							rotate.rotateMatrix(1, 0, 0, 90);

						curr->mc.matrixPreMultiply(&rotate);

						// Update cubelet's dimensions based on position and direction
						curr->setPos(curr->getX(), curr->getZ() * (key == 'R' ? 1 : -1), -curr->getY() * (key == 'R' ? 1 : -1));

					}

				}
			}
		}

		break;

	}

}

/*
 * Use the power of pseudorandomness to generate a new, solvable puzzle!
 */
void RubikCube::scramble() {

	char letters[6];

	letters[0] = 'u';
	letters[1] = 'd';
	letters[2] = 'l';
	letters[3] = 'r';
	letters[4] = 'f';
	letters[5] = 'b';

	for (int i = 0; i < 100; i++) {

		char choice = letters[rand() % 6];

		rotateFace(choice);

	}
};
