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

	aceleracion = ofVec3f(0, -0.5, 0);
	velocidad = ofVec3f(ofRandom(-3, 3), ofRandom(1), ofRandom(-3, 3));
}

void Particula::update() {
	velocidad += aceleracion;
	posicion += velocidad;
	if (tam > 0)
		tam -= 0.1;
	else
		muere = true;

	if (posicion.y < -20) {
		muere = true;
	}
}

void Particula::applyForce(ofVec3f force) {
	ofVec3f f = force;
	f = f / masa;
	aceleracion += f;
}


void Particula::draw() {
	//ofPushMatrix();
	ofPushStyle();
	ofSetColor(255);
	ofFill();
	//ofBox(posicion.x, posicion.y, posicion.z, 5);
	//ofTranslate(posicion.x, posicion.y, posicion.z);
	//ofRotateZ(cos(ofGetElapsedTimeMillis()*.1));
	//ofDrawCircle(0,0,0, tam);
	//ofDrawBox(posicion.x, posicion.y, posicion.z, tam);
	ofDrawCircle(posicion.x, posicion.y, posicion.z, tam);

	ofPopStyle();
	//ofPopMatrix();
}