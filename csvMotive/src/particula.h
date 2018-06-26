#pragma once

#include "ofMain.h"

class Particula {
public:
	Particula();
	Particula(ofVec3f pos, float mass);
	void setup();
	void draw();
	void update();
	void applyForce(ofVec3f force);

	ofVec3f posicion;
	ofVec3f aceleracion;
	ofVec3f velocidad;
	float masa;
	float secondsInMove=1;
};