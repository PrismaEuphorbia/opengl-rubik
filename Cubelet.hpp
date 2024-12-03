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
	float cubeletSize;
	float spacing;
	float facecols[6];
	Matrix mc;

public:
	void drawCubelet(float colors[7][3]);

	Cubelet();
	Cubelet(float x0, float y0, float z0);
	void setPos(float x0, float y0, float z0);
	void dotVertex(Vector v);

};

#endif /* CUBELET_H_ */
