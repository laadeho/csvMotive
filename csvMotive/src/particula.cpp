#include "ofMain.h"
#include "ofApp.h"
#include "particula.h"

Particula::Particula(void) {

}

Particula::Particula(ofVec3f pos, float mass) {
	gravedad = ofVec3f(0, -0.98, 0);

	posicion = pos;
	masa = mass;
	muere = false;
	tam = ofRandom(3,5);

	aceleracion = ofVec3f(0, -0.15, 0);
	velocidad = ofVec3f(ofRandom(-0.1, 0.1), ofRandom(-0.5), ofRandom(-0.1, 0.1));
}

void Particula::update() {
	velocidad += aceleracion;
	posicion += velocidad;
	aceleracion *= 0;

	if (tam > 0)
		tam -= 0.125;
	else
		muere = true;

	if (posicion.y < -20) {
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
	ofSetColor(255);
	ofFill();
	ofDrawCircle(posicion.x, posicion.y, posicion.z, tam);
	ofPopStyle();
}