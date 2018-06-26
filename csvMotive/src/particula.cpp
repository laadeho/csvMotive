#include "ofMain.h"
#include "ofApp.h"
#include "particula.h"

Particula::Particula(void) {

}
Particula::Particula(ofVec3f pos, float mass) {
	posicion = pos;
	posicion = ofVec3f(0, 0, 0);
	masa = mass;
}

void Particula::setup() {	
	aceleracion = ofVec3f(0, 0.5, 0);
	velocidad = ofVec3f(ofRandom(-1,1), ofRandom(-2,0), ofRandom(-1,1));
}

void Particula::update() {
	velocidad += aceleracion;
	posicion += velocidad;

	if (posicion.y > ofGetHeight()) {
		posicion = ofVec3f(0, 0, 0);
		velocidad = ofVec3f(ofRandom(-1, 1), ofRandom(-2, 0), ofRandom(-1, 1));
	}
}
void Particula::applyForce(ofVec3f force) {
	ofVec3f f = force;
	f = f / masa;

}
void Particula::draw() {
	ofPushStyle();
	ofSetColor(255);
	ofFill();
	ofSphere(ofGetWidth() / 2+posicion.x, posicion.y, posicion.z, 10);
	ofPopStyle();
}