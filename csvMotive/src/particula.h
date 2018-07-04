#pragma once

#include "ofMain.h"

class Particula {
public:
	Particula();
	Particula(ofVec3f pos, float mass);
	void draw();
	void update();
	void applyForce(ofVec3f force);

	ofVec3f posicion;
	ofVec3f aceleracion;
	ofVec3f velocidad;
	ofVec3f gravedad;

	float masa;
	float secondsInMove=1;

	bool muere;
	float tam = 4;
	float limInf = 0;

	void invierteGravedad();
	bool invGrav;
	int valGrav = 0.98;
};