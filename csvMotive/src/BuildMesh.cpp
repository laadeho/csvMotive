#include "ofMain.h"
#include "ofApp.h"
#include "BuildMesh.h"

BuildMesh::BuildMesh(void) {
	//vector<ofVec3f> nodoIndex;
	mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP_ADJACENCY);
	meshWire.setMode(OF_PRIMITIVE_LINE_LOOP);
}

void BuildMesh::setup() {
	
	
	//mesh.enableColors();
	//mesh.enableIndices();

	/*for (int i = 0; i < nodoIndex.size(); i++) {
		mesh.addVertex(nodoIndex[i]);
		mesh.addColor(255);
	}*/
	/*for (int i = 0; i < nodoIndex.size() - 2; i += 3) {
		mesh.addIndex(i);
		mesh.addIndex(i + 1);
		mesh.addIndex(i + 2);
	}*/

	//for (int i = 0; i < size()->indices; i++) {
	//}
	//masIndex(0);
	//masIndex();

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

void BuildMesh::setup(vector<ofVec3f> nodos) {
	/*vector<ofVec3f> temp = nodos;
	
	for (int i = 0; i < nodos.size()-1; i++) {
		ofMesh tempMesh;
		meshes.push_back(ofMesh(tempMesh));
	}
	for (int i = 0; i < meshes.size(); i++) {
		meshes[i].setMode(OF_PRIMITIVE_TRIANGLE_STRIP_ADJACENCY);
	}

	ofLogNotice("Num Meshes: " + ofToString(meshes.size()));*/
}

void BuildMesh::masIndex(ofMesh meshLoc, int mInd) {
	meshLoc.addIndex(15 + mInd);
	meshLoc.addIndex(14 + mInd);
	meshLoc.addIndex(13 + mInd);
	meshLoc.addIndex(0 + mInd);
	///
	meshLoc.addIndex(18 + mInd);
	meshLoc.addIndex(17 + mInd);
	meshLoc.addIndex(16 + mInd);
	meshLoc.addIndex(0 + mInd);
	///
	meshLoc.addIndex(0 + mInd);
	meshLoc.addIndex(1 + mInd);
	meshLoc.addIndex(2 + mInd);
	meshLoc.addIndex(3 + mInd);
	meshLoc.addIndex(4 + mInd);
	///
	meshLoc.addIndex(8 + mInd);
	meshLoc.addIndex(7 + mInd);
	meshLoc.addIndex(6 + mInd);
	meshLoc.addIndex(5 + mInd);
	meshLoc.addIndex(3 + mInd);
	meshLoc.addIndex(9 + mInd);
	meshLoc.addIndex(10 + mInd);
	meshLoc.addIndex(11 + mInd);
	meshLoc.addIndex(12 + mInd);
}

void BuildMesh::addNodes(vector<ofVec3f> nodos, bool addN) {
	if (addN) {
		vector<ofVec3f> temp = nodos;
		ofVec3f ceros = ofPoint(0, 0, 0);

		masIndex(mesh, numNodo);
		masIndex(meshWire, numNodo);

		for (int i = 0; i < temp.size()-5; i++) {
			if (abs(ofDist(temp[i].x, temp[i].y, temp[i].z, ceros.x, ceros.y, ceros.z)) > 0) {}
			mesh.addVertex(temp[i]);
			mesh.addColor(ofColor(255));

			meshWire.addVertex(temp[i]);
		}
		numNodo += temp.size();
	}
	//masIndex(numNodo);

	//for (int i = 0; i < meshes.size(); i++) {
	/*for (int i = 0; i < 3; i++) {
		meshes[i].addVertex(temp[i]);
		meshes[i].addVertex(temp[i+1]);
	}*/
	/*
	meshes[0].addVertex(temp[0]);
	meshes[0].addVertex(temp[1]);

	meshes[0].addIndex(0);
	meshes[0].addIndex(1);
	*/
	//numNodo += nodoIndex.size();
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
	ofPushStyle();
	ofSetColor(255);
	ofFill();

	//mesh.draw();
	ofPopStyle();

	ofPushStyle();
	ofSetColor(150);
	ofNoFill();	
	meshWire.draw();
	ofPopStyle();
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
