#include "ofMain.h"
#include "ofApp.h"
#include "BuildMesh.h"

BuildMesh::BuildMesh(void) {
	//vector<ofVec3f> nodoIndex;

}

void BuildMesh::setup(vector<ofVec3f> nodos) {
	nodoIndex = nodos;
	mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP_ADJACENCY);
	
	//mesh.enableColors();
	//mesh.enableIndices();

	for (int i = 0; i < nodoIndex.size(); i++) {
		mesh.addVertex(nodoIndex[i]);
		mesh.addColor(255);
	}
	for (int i = 0; i < nodoIndex.size() - 2; i += 3) {
		mesh.addIndex(i);
		mesh.addIndex(i + 1);
		mesh.addIndex(i + 2);
	}
	ofLogNotice(ofToString(mesh.getNumVertices()));
	/*
	path.moveTo(20, 20);
	path.lineTo(40, 20);
	path.lineTo(40, 40);
	path.lineTo(20, 40);
	path.close();
	path.setStrokeColor(ofColor::blue);
	path.setFillColor(ofColor::red);
	path.setFilled(true);
	path.setStrokeWidth(2);
	tessellation = path.getTessellation();
	*/

	/*
	path.moveTo(20, 20);
	path.lineTo(40, 20);
	path.lineTo(40, 40);
	path.lineTo(20, 40);
	path.close();
	m.rotate(45, 0, 0, 1);
	m.translate(20, 20, 0);
	*/
}

void BuildMesh::update(vector<ofVec3f> nodos) {
	nodoIndex = nodos;

	for (int i = 0; i < mesh.getNumVertices(); i++) {
		ofVec3f vert = mesh.getVertex(i);
		vert = nodoIndex[i];

		mesh.setVertex(i, vert);
	}

	//if (ofGetFrameNum() % 5 == 0) {
		/*for (int i = 0; i < nodoIndex.size(); i++) {
			mesh.getVertex(i) = nodoIndex[i];
			//mesh.addVertex(nodoIndex[i]);
		}
		*/
		/*for (int i = 0; i < nodoIndex.size() - 2; i+=3) {
			mesh.addIndex(i);
			mesh.addIndex(i + 1);
			mesh.addIndex(i + 2);
		}*/
	//}
}

void BuildMesh::draw() {
	ofSetColor(255);
	ofFill();
	mesh.draw();
	//path.draw();
	//tessellation.drawWireframe();

	/*
	ofMultMatrix(m);
	path.draw();
	*/
	// https://openframeworks.cc/ofBook/chapters/advanced_graphics.html

	//for (nodoIndex : nodoIndex.size()++) {
	/*
	for (int i=0;i<nodoIndex.size(); i++){
		ofDrawCircle(nodoIndex[i], 1);
	}
	*/
}
