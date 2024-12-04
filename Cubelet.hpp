/*
 * Cubelet.h
 *
 *  Created on: Nov 30, 2024
 *      Author: Hursh Patel & Ciara Trinh
 */

#ifndef CUBELET_H
#define CUBELET_H
#include "Matrix.hpp"
#include "Vector.hpp"

class Cubelet {

private:
	float x, y, z;
	float xRot, yRot, zRot;
	float cubeletSize;
	float spacing;
	Vector facecols[6];


public:
	Matrix mc;

	void drawCubelet();
	Cubelet();
	Cubelet(float x0, float y0, float z0, Vector colors[6]);
	void setPos(float x0, float y0, float z0);
	void dotVertex(Vector v);
	void setColors(Vector colors[6], GLfloat x0, GLfloat y0, GLfloat z0);
	void ctmMultiply();

	/* Getters */

	float getX() const {
		return x;
	}

	float getY() const {
		return y;
	}

	float getZ() const {
		return z;
	}

	float getXRot() const {
		return xRot;
	}

	float getYRot() const {
		return yRot;
	}

	float getZRot() const {
		return zRot;
	}

	float getSpacing() const {
		return spacing;
	}

	/* Getters end */

	/* Setters */

	void addXRot(GLfloat newRot) {
		xRot += newRot;
	}

	void addYRot(GLfloat newRot) {
		yRot += newRot;
	}

	void addZRot(GLfloat newRot) {
		zRot += newRot;
	}

	/* Setters end */


};

#endif /* CUBELET_H_ */
