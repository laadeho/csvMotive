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
	/*for (int i = 0; i < nodoIndex.size() - 2; i += 3) {
		mesh.addIndex(i);
		mesh.addIndex(i + 1);
		mesh.addIndex(i + 2);
	}*/

	//for (int i = 0; i < size()->indices; i++) {
	//}
	//masIndex(0);
	//masIndex();

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
void BuildMesh::masIndex(int mInd) {
	mesh.addIndex(15 + mInd);
	mesh.addIndex(14 + mInd);
	mesh.addIndex(13 + mInd);
	mesh.addIndex(0 + mInd);
	///
	mesh.addIndex(18 + mInd);
	mesh.addIndex(17 + mInd);
	mesh.addIndex(16 + mInd);
	mesh.addIndex(0 + mInd);
	///
	mesh.addIndex(0 + mInd);
	mesh.addIndex(1 + mInd);
	mesh.addIndex(2 + mInd);
	mesh.addIndex(3 + mInd);
	mesh.addIndex(4 + mInd);
	///
	mesh.addIndex(8 + mInd);
	mesh.addIndex(7 + mInd);
	mesh.addIndex(6 + mInd);
	mesh.addIndex(5 + mInd);
	mesh.addIndex(3 + mInd);
	mesh.addIndex(9 + mInd);
	mesh.addIndex(10 + mInd);
	mesh.addIndex(11 + mInd);
	mesh.addIndex(12 + mInd);
}

void BuildMesh::addNodes(vector<ofVec3f> nodos) {
	vector<ofVec3f> temp = nodos;
	masIndex(numNodo);

	for (int i = 0; i < temp.size(); i++) {
		mesh.addVertex(temp[i]);
		mesh.addColor(ofColor(ofRandom(150,255), ofRandom(100,255)));
	}
	numNodo += nodoIndex.size();
}

void BuildMesh::update(vector<ofVec3f> nodos) {
	//nodoIndex = nodos;
	/*vector<ofVec3f> temp = nodos;

	for (int i = 0; i < temp.size(); i++) {
		mesh.addVertex(temp[i]);
		mesh.addColor(ofRandom(255));
	}
	masIndex();*/

	/*
	for (int i = 0; i < mesh.getNumVertices(); i++) {
		ofVec3f vert = mesh.getVertex(i);
		vert = nodoIndex[i];
		
		//mesh.addVertex(nodoIndex[i]);
		//mesh.addColor(ofRandom(255));
		mesh.setVertex(i, vert);
	}
	*/

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
