#pragma once

#include "ofMain.h"

class Particula {
public:
	Particula();
	Particula(ofVec3f pos, float mass);
	Particula(ofVec3f pos, float mass, bool invertGrav);
	Particula(ofVec3f pos, float mass, bool invertGrav, float g);
	void draw();
	void update();
	void setup(float g);
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

	/// COLOR PARTICULA
	ofVec3f color = ofVec3f(255, 255, 255);
	float colMono = 255;

	void setGravedad(float g);
	//bool invGrav;
	float valGrav;
};