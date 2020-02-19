#pragma once

#include "ofMain.h"

class BuildMesh {
public:
	BuildMesh();
	void setup();
	void setup(vector<ofVec3f> nodos);
	void update(vector<ofVec3f> nodos);
	void draw();
	void drawMeshes();

	void masIndex(ofMesh meshLoc, int sumaleIndex);
	void addNodes(vector<ofVec3f> nodos, bool addN);
	void addNodesMult(vector<ofVec3f> nodos, bool addN);

	vector<ofVec3f> nodoIndex;
	int numNodo;
	ofMesh mesh, meshWire;
	bool addNode = true;

	vector<ofMesh> meshes;
	
	ofPath path;
	ofVboMesh tessellation;
	ofMatrix4x4 m;

private:
	//
};
