#include "Cubelet.hpp"

class RubikCube {
	private:
		Vector colors[6]; // Store colors for each face
	public:
		RubikCube();
		Cubelet cubelets[3][3][3];
		void render(GLfloat angleX, GLfloat angleY);
		void reset();
		void scramble();
		void rotateFace(char key);
};
