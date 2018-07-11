#pragma once

#include "ofMain.h"

class BuildMesh {
public:
	BuildMesh();
	void setup();
	void setup(vector<ofVec3f> nodos);
	void update(vector<ofVec3f> nodos);
	void draw();

	void masIndex(int sumaleIndex);
	void addNodes(vector<ofVec3f> nodos);

	vector<ofVec3f> nodoIndex;
	int numNodo;
	ofMesh mesh;

	vector<ofMesh> meshes;
	
	ofPath path;
	ofVboMesh tessellation;
	ofMatrix4x4 m;

	bool tipo1 = true;
	bool tipo2 = false;
	//int indices[19] = {};

private:
	//
};
