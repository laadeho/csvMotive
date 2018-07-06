#include "ofMain.h"
#include "ofApp.h"
#include "particula.h"

Particula::Particula(void) {
	//gravedad = ofVec3f(0, -valGrav, 0);
}

Particula::Particula(ofVec3f pos, float mass) {
	gravedad = ofVec3f(0, -valGrav, 0);

	posicion = pos;
	masa = mass;
	muere = false;
	tam = ofRandom(tam / 2, tam);

	aceleracion = ofVec3f(0, 0, 0);
	velocidad = ofVec3f(ofRandom(-0.5, 0.5), 0, ofRandom(-0.5, 0.5));
}
Particula::Particula(ofVec3f pos, float mass, bool invertGrav) {
	if (invertGrav) {
		valGrav *= -1;
	}
	gravedad = ofVec3f(0, valGrav, 0);

	posicion = pos;
	masa = mass;
	muere = false;
	tam = ofRandom(tam / 2, tam);

	aceleracion = ofVec3f(0, 0, 0);
	velocidad = ofVec3f(ofRandom(-0.5, 0.5), 0, ofRandom(-0.5, 0.5));
}
Particula::Particula(ofVec3f pos, float mass, bool invertGrav, float g) {
	valGrav = -g;
	if (invertGrav) {
		valGrav *= -1;
	}
	gravedad = ofVec3f(0, valGrav, 0);

	posicion = pos;
	masa = mass;
	muere = false;
	tam = ofRandom(tam / 2, tam);

	aceleracion = ofVec3f(0, 0, 0);
	velocidad = ofVec3f(ofRandom(-0.5, 0.5), 0, ofRandom(-0.5, 0.5));
}

void Particula::setup(float g) {
	valGrav = g;
	//ofLogNotice("VAL GRAV: " + ofToString(valGrav));
}
void Particula::setGravedad(float g) {
	valGrav = g;
	//ofLogNotice("VAL GRAV: " + ofToString(valGrav));
}
void Particula::update() {
	velocidad += aceleracion;
	posicion += velocidad;
	aceleracion *= 0;

	if (tam > 0)
		tam -= 0.05;
	else
		muere = true;

	if (colMono > 0) {
		colMono-=5;
	}

	if (posicion.y < -20 || posicion.y > 2000) {
		muere = true;
	}
	applyForce(gravedad);
}

void Particula::applyForce(ofVec3f force) {
	ofVec3f f = force;
	f = f / masa;
	aceleracion += f;
}

void Particula::draw() {
	ofPushStyle();
	ofSetColor(colMono);
	ofFill();
	ofDrawCircle(posicion.x, posicion.y, posicion.z, tam);
	ofPopStyle();
}