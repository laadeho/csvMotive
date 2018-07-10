#pragma once

#include "ofMain.h"

class BuildMesh {
public:
	BuildMesh();
	void setup(vector<ofVec3f> nodos);
	void update(vector<ofVec3f> nodos);
	void draw();

	void masIndex(int sumaleIndex);
	void addNodes(vector<ofVec3f> nodos);

	vector<ofVec3f> nodoIndex;
	int numNodo;
	ofMesh mesh;
	
	ofPath path;
	ofVboMesh tessellation;
	ofMatrix4x4 m;

	//int indices[19] = {};

private:
	//
};
