#pragma once
#include "ofMain.h"
#include "ofUtils.h"
#include <winsock2.h>
#include <vector>
#include "ofxDatGui.h"
#include "particula.h"
#include "Analiza.h"
#include "BuildMesh.h"

#include "ofxShadow.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void updateMesh();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	
	void windowResized(int w, int h);

	/// SIMPLE SHADOW
	ofxShadow simple_shadow;
	ofVec3f light_pos;

	/// PARTICULAS
	Particula partConfig;
	vector<Particula> parts;

	/// ANALIZA DATOS
	Analiza analiza;

	/// BUILD MESH
	BuildMesh bMesh;
	//BuildMesh bMeshes;

	bool invierteGravedad;
	float gravedad = 9.8;
	
	bool borra = true; // no se para que se esta usando actualmente

	/// GUI
	void setupGUI();
	ofxDatGui* gui;
	void onDropdownEvent(ofxDatGuiDropdownEvent e);
	void onToggleEvent(ofxDatGuiToggleEvent e);
	void onSliderEvent(ofxDatGuiSliderEvent e);
	bool showGui;
	
	bool grid;

	/// CAMARA
	ofEasyCam cam;
	ofVec3f posCam;
	int distCam = 500;
	float angulo;
	bool fs = true;
	bool rota;
	bool moveCam;

	ofTrueTypeFont myfont;

	/// LUCES
	ofLight pointLight, light;

	/// MESH
	vector<ofVec3f> offsets;
	ofMesh mesh, meshLines;

	/// DEBUIG
	bool debug = true;

};
