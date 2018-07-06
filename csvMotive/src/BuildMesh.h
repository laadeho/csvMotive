#pragma once

#include "ofMain.h"

class BuildMesh {
public:
	BuildMesh();
	void setup(vector<ofVec3f> nodos);
	void update(vector<ofVec3f> nodos);
	void draw();

	vector<ofVec3f> nodoIndex;
	ofMesh mesh;
	
	ofPath path;
	ofVboMesh tessellation;
	ofMatrix4x4 m;

private:
	//
};
