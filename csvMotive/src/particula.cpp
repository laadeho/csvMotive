#include "ofMain.h"
#include "ofApp.h"
#include "particula.h"

Particula::Particula(void) {

}
Particula::Particula(ofVec3f pos, float mass) {
	posicion = pos;
	masa = mass;
	muere = false;
	tam = ofRandom(3,5);

	aceleracion = ofVec3f(0, -0.15, 0);
	velocidad = ofVec3f(ofRandom(-1, 1), ofRandom(-0.5), ofRandom(-1, 1));
}

void Particula::update() {
	velocidad += aceleracion;
	posicion += velocidad;
	if (tam > 0)
		tam -= 0.25;
	else
		muere = true;

	if (posicion.y < -20) {
		muere = true;
	}
	//applyForce(aceleracion);
}

void Particula::applyForce(ofVec3f force) {
	ofVec3f f = force;
	f = f / masa;
	aceleracion += f;
}


void Particula::draw() {
	ofPushStyle();
	ofSetColor(255);
	ofFill();
	ofDrawCircle(posicion.x, posicion.y, posicion.z, tam);
	ofPopStyle();
}