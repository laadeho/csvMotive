#pragma once

#include "ofMain.h"
#include "ofUtils.h"
#include <winsock2.h>
#include <vector>
#include "ofxDatGui.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	
	void windowResized(int w, int h);

	//void coordenadas();

	void analizaCSV();

	ofFile editado;

	/// GUI
	void setupGUI();
	ofxDatGui* gui;
	void onDropdownEvent(ofxDatGuiDropdownEvent e);
	void onToggleEvent(ofxDatGuiToggleEvent e);
	
	bool showGui;

	vector<string> coordenada;
	vector<string> tagTransform;
	// VECTORES
	/// BOLEANOS
	vector<bool> esMarker, esRigidMarker, esBoneMarker;		// Tipo de marker
	vector<bool> esRigid, esBone;							// Tipo de objeto
	vector<bool> esRot, esPos;								// Tipo de transformacion
	///
	vector<ofVec3f> markerPos;								// Marcadores sueltos
	vector<ofVec3f> markerPosRigid;							// Marcadores de Rigid Body
	vector<ofVec3f> markerPosBone;							// Marcadores de Bone
	/// VECTORES TRANSFORMACIONES
	vector<ofVec3f> rigidPos, rigidRot;						// Posicion y Rotacion de Rigid Body // CENTROIDE
	vector<ofVec3f> bonePos, boneRot;						// Posicion y Rotacion de Bone // CENTROIDE

	///
	string encabezado;
	int totalEtiquetas;
	vector <string> linea;

	bool borra = true;

	bool dibujaMarker, dibujaRigidMarker, dibujaBoneMarker, dibujaRigid, dibujaBone;

	bool analiza = true;		
	int lineaAnalisis = 7;		// Slider inicio anim
	int saltoLinea = 2;			// Velocidad / salto lectura
	float escala = 1.0f;		// Slider flotante

	ofBuffer buffer;

	/// CAMARA
	ofEasyCam cam;

	bool debug = true;
};
