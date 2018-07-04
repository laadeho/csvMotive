#pragma once

#include "ofMain.h"

class Analiza {
public:
	Analiza();
	void draw();
	void update();

	void analizaCSV();

	ofFile editado;
	ofBuffer buffer;
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

	string encabezado;
	int totalEtiquetas;
	vector <string> linea;
	//vector<string> nameMarker; /// //////

	int fpsFromFile;

	bool dibujaMarkerSphere, dibujaMesh, creaParticulas, dibujaEtiqueta;
	bool dibujaMarker, dibujaRigidMarker, dibujaBoneMarker, dibujaRigid, dibujaBone;

	bool anima;
	int lineaAnalisis = 7;		// Slider inicio anim
	int saltoLinea = 1;			// Velocidad / salto lectura
	float escala = 1.0f;		// Slider flotante
};