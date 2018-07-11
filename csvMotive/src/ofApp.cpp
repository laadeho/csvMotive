#include "ofApp.h"
int tiempo = 0;
//--------------------------------------------------------------
void ofApp::setup(){
	partConfig = Particula();
	ofEnableSmoothing();
	/// SIMPLE SHADOW
	simple_shadow.setup(&cam);
	
	setupGUI();
	//ofSetFrameRate(120);
	ofSetVerticalSync(true);
	//ofSetBackgroundAuto(false);
	
	myfont.load("arial.ttf", 10);

	/// MESH
	mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP_ADJACENCY);
	//mesh.setMode(OF_PRIMITIVE_POINTS);

	meshLines.setMode(OF_PRIMITIVE_LINE_STRIP);

	for (int i = 0; i < analiza.markerPos.size(); i++) {
		ofVec3f vertice(analiza.markerPos[i].x, analiza.markerPos[i].y, analiza.markerPos[i].z);
		mesh.addVertex(vertice);
		meshLines.addVertex(vertice);
		float val = ofRandom(1);
		//mesh.addColor(ofFloatColor(val, val, val, ofRandom(1)));
		mesh.addColor(ofFloatColor(val, val, val,ofRandom(1)));
		offsets.push_back(ofVec3f(ofRandom(0, 100000), ofRandom(0, 100000), ofRandom(0, 100000)));
	}
	
	for (int i = 0; i < analiza.markerPos.size() - 2; i += 3) {
		mesh.addIndex(i);
		mesh.addIndex(i + 1);
		mesh.addIndex(i + 2);
		meshLines.addIndex(i);
		//meshLines.addIndex(i + 1);
		//meshLines.addIndex(i + 2);
	}
	
	bMesh.setup();
	//bMeshes.setup(analiza.bonePos);
	/// CAMARA
	cam.disableMouseInput();

	/// LUCES
	light.setup();
	light.setPosition(0, 200, 0);

	pointLight.setPointLight();
	pointLight.setPosition(500, 200, 500);

	ofSetFrameRate(analiza.fpsFromFile);
}

/*--- GUI --------------------------------------*/
void ofApp::setupGUI() {	////////////// OFXDATGUI
	std::string pathGui;
	pathGui = "../";
	ofxDatGui::setAssetPath(pathGui);
	gui = new ofxDatGui(ofGetWidth() - 300, 50);
	//gui = new ofxDatGui(ofxDatGuiAnchor::TOP_RIGHT);
	//gui->setTheme(new ofxDatGuiThemeSmoke());
	gui->addLabel(": : : C  O  N  F  I  G  U  R  A  D  O  R : : :");

	ofxDatGuiFolder* guiDatos = gui->addFolder(":: V I S U A L I Z A R ::", ofColor::blue);
	guiDatos->addToggle("ETIQUETAS")->setChecked(false);
	
	ofxDatGuiSlider* slider = gui->addSlider("DIST CAM", 100, 1500, 500);
	slider->onSliderEvent(this, &ofApp::onSliderEvent);

	ofxDatGuiSlider* sliGrav = gui->addSlider("GRAVEDAD", 0.1, 20, 9.8);
	sliGrav->onSliderEvent(this, &ofApp::onSliderEvent);

	guiDatos->addToggle("GRAVEDAD")->setChecked(false);
	guiDatos->addToggle("PARTICULAS")->setChecked(false);
	guiDatos->addToggle("MESH")->setChecked(false);
	guiDatos->addToggle("MARKER SPHERE")->setChecked(false);
	guiDatos->addToggle("MARKER")->setChecked(false);
	guiDatos->addToggle("MARKER RIGID")->setChecked(false);
	guiDatos->addToggle("MARKER BONE")->setChecked(false);
	guiDatos->addToggle("RIGID")->setChecked(false);
	guiDatos->addToggle("BONE")->setChecked(false);

	gui->addBreak()->setHeight(10.0f);
	gui->addFooter();
	gui->getFooter()->setLabelWhenExpanded(" - M I N I M I Z A R - ");
	gui->getFooter()->setLabelWhenCollapsed(" - E X P A N D I R :: M E N U - ");
	gui->collapse();
	///////// EVENTOS ///////////////////////////////////
	gui->onDropdownEvent(this, &ofApp::onDropdownEvent);
	gui->onToggleEvent(this, &ofApp::onToggleEvent);
	/// GUI A MOSTRAR AL INICIO /////////////////////////
}

bool checkVive(Particula &p) {
	return p.muere;
}

//--------------------------------------------------------------
void ofApp::update() {
	/// MAPPED SHADOW
	float alpha = ofMap(ofGetMouseX(), 0, ofGetWidth(), 0.0, 1.0);
	simple_shadow.setShadowColor(ofFloatColor(0., 0., 0., alpha));

	// updating light position
	float light_moving_speed = 0.1;
	float light_moving_radius = 50.;
	light_pos = ofVec3f(sin(2.0 * PI * (ofGetElapsedTimef()*light_moving_speed)) * light_moving_radius, 250, 200);
	simple_shadow.setLightPosition(light_pos);
	///

	for (int i = 0; i < parts.size(); i++) {
		parts[i].update();
		//parts[i].applyForce(ofVec3f(0, 0.1, 0));
	}

	ofRemove(parts, checkVive);

	tiempo = int(ofGetElapsedTimef());

	if (debug) {
		std::stringstream strm;
		strm << "fps: " << ofGetFrameRate();
		ofSetWindowTitle(strm.str());
	}

	analiza.update();
	updateMesh();	

	/*
	ofExit();
	OF_EXIT_APP(0);
	ofExitCallback();
	*/

	/// CAMARA
	if (!moveCam) {
		cam.setPosition(posCam);
		cam.setTarget(ofVec3f(0, 150, 0));
		posCam = ofVec3f(sin(angulo)*distCam, 165, cos(angulo) * distCam);
	}

	if (rota)
		angulo += 0.005;
	if (ofGetFrameNum() > 5) {
		if (ofGetFrameNum() % 20 == 0) {
			bMesh.addNodes(analiza.bonePos);
		}
	}

	
	//bMesh.update(analiza.bonePos);

}

//--------------------------------------------------------------
void ofApp::updateMesh() {
	int numVerts = mesh.getNumVertices();
	for (int i = 0; i < numVerts; ++i) {
		ofVec3f vert = mesh.getVertex(i);

		float time = ofGetElapsedTimef();
		float timeScale = 2;
		float displacementScale = 5;
		ofVec3f timeOffsets = offsets[i];
		vert = analiza.markerPos[i];
		//vert = markerPosBone[i%markerPosBone.size()];

		vert.x += (ofSignedNoise(time*timeScale + timeOffsets.x)) * displacementScale;
		vert.y += (ofSignedNoise(time*timeScale + timeOffsets.y)) * displacementScale;
		vert.z += (ofSignedNoise(time*timeScale + timeOffsets.z)) * displacementScale;

		mesh.setVertex(i, vert);
		meshLines.setVertex(i, vert);
	}
}
//--------------------------------------------------------------

void ofApp::draw() {
	ofBackground(0);

	ofEnableDepthTest();

	ofEnableLighting();
	pointLight.enable();

	light.enable();
	
	cam.begin();

	if (analiza.dibujaMarker) {
		ofSetColor(255);
		ofFill();
		for (int i = 0; i <analiza.markerPos.size(); i++) {
			ofDrawEllipse(analiza.markerPos[i], 5, 5);
		}
	}
	if (analiza.dibujaRigidMarker) {
		ofSetColor(255, 0, 0);
		ofFill();
		for (int i = 0; i < analiza.markerPosRigid.size(); i++) {
			ofDrawEllipse(analiza.markerPosRigid[i], 5, 5);
		}
	}
	if (analiza.dibujaBoneMarker) {
		ofSetColor(0, 255, 0);
		ofFill();
		for (int i = 0; i < analiza.markerPosBone.size(); i++) {
			ofDrawEllipse(analiza.markerPosBone[i], 5, 5);
		}
	}
	if (analiza.dibujaRigid) {
		ofSetColor(0, 0, 255);
		ofFill();
		for (int i = 0; i < analiza.rigidPos.size(); i++) {
			ofDrawEllipse(analiza.rigidPos[i], 5, 5);
		}
	}
	
	if (analiza.dibujaBone) {
		ofSetColor(0, 255, 0);
		ofFill();
		for (int i = 0; i < analiza.bonePos.size(); i++) {
			if (i <= 18) {
				//ofDrawEllipse(analiza.bonePos[i], 5, 5);
				ofPushMatrix();
				ofTranslate(analiza.bonePos[i]);
				if (i >= 3 && i <= 12 && i != 4) {
					analiza.boneRot[i] += ofVec3f(0, 0, 90);
				}
				ofRotateX(analiza.boneRot[i].x);
				ofRotateY(analiza.boneRot[i].y);
				ofRotateZ(analiza.boneRot[i].z);

				//if (i < analiza.boneRot.size()) {

				//}
				ofBox(ofPoint(0, 0, 0), 5, 20, 5);
				ofPopMatrix();
			}
		}
	}
	
	if (analiza.dibujaMarkerSphere) {
		ofSetIcoSphereResolution(3); /// ///////////////////////
		for (int i = 0; i < analiza.markerPos.size(); i++) {
			//ofDrawEllipse(markerPos[i], 5, 5);
			//ofDrawBox(markerPos[i], 15);
			//ofDrawArrow(markerPos[i], markerPos[i]*1.1, 15);
			ofSetColor(200);
			ofFill();
			ofDrawIcoSphere(analiza.markerPos[i], 5);
			
			ofPushMatrix();
			ofTranslate(analiza.markerPos[i]);
			ofRotateX(ofGetElapsedTimeMillis()*.05);
			ofRotateY(ofGetElapsedTimeMillis()*.025);
			
			ofSetColor(150, 150);
			ofNoFill(); 
			ofDrawIcoSphere(ofPoint(0, 0, 0), 7);
			
			ofPopMatrix();
		}
	}
	if (analiza.creaParticulas) {
		//if (ofGetFrameNum() % 3 == 0) {
			for (int i = 0; i < analiza.markerPos.size(); i++) {
				//if(i%4==0)
				//parts.push_back(Particula(ofVec3f(analiza.markerPos[i].x, analiza.markerPos[i].y, analiza.markerPos[i].z), ofRandom(1, 20)));
				parts.push_back(Particula(ofVec3f(analiza.markerPos[i].x, analiza.markerPos[i].y, analiza.markerPos[i].z), 20, invierteGravedad, gravedad));
			//}
		}
	}

	if (analiza.dibujaEtiqueta) {
		ofColor(255);
		ofFill();
		for (int i = 0; i < analiza.bonePos.size(); i++) {
			if (i < 19) {
				ofPushMatrix();
				ofTranslate(analiza.bonePos[i]);
				myfont.drawString(ofToString(i), 0, 0);
				ofPopMatrix();
			}
		}
	}
	
	for (int i = 0; i < parts.size(); i++) {
		parts[i].draw();
	}

	
	if (grid) {
		ofSetColor(50);
		ofNoFill();
		ofPushMatrix();
		ofRotateX(90);
		ofRotateY(90);
		ofDrawGridPlane(100, 10, false);
		ofPopMatrix();
	}
	/*
	if (analiza.dibujaMesh) {
		mesh.draw();
		ofSetColor(0);
		ofNoFill();
		meshLines.draw();
	}
	*/

	/// de momento aca para no usar luces
	//bMesh.draw();
	
	/// SHADOW CAST
	//glEnable(GL_DEPTH_TEST);
	// axis
	if (debug) {
		ofDrawAxis(300);
		// light pos
		ofSetColor(255, 0, 255);
		ofDrawBox(light_pos, 3);
		ofDrawBitmapString("light", light_pos + 10);
		// red box
		ofSetColor(255, 0, 0);
		ofDrawBox(0, 150, 50, 30);
	}

	ofSetColor(255);
	ofFill();
	ofDrawBox(ofPoint(0, -10, 0), 1000, 5, 1000);
	if(bMesh.tipo1)
		bMesh.draw();

	/// shadow
	simple_shadow.begin();
	
	if (bMesh.tipo1)
		bMesh.draw();

	for (int i = 0; i < parts.size(); i++) {
		parts[i].draw();
	}
	ofDrawBox(0, 150, 50, 30);
	simple_shadow.end();
	//glDisable(GL_DEPTH_TEST);

	///

	
	light.disable();
	pointLight.disable();
	ofDisableLighting();
	

	cam.end();
	ofDisableDepthTest();
		
	if (debug) {
		ofSetColor(255);
		ofFill();
		float val = ofGetFrameRate();
		ofDrawBitmapString("FPS data: " + ofToString(analiza.fpsFromFile), ofPoint(ofGetWindowWidth() - 200, ofGetWindowHeight() - 180));
		ofDrawBitmapString("fps: " + ofToString(val), ofPoint(ofGetWindowWidth() - 200, ofGetWindowHeight() - 160));
		ofDrawBitmapString("linea: " + ofToString(analiza.lineaAnalisis), ofPoint(ofGetWindowWidth() - 200, ofGetWindowHeight() - 130));
		ofDrawBitmapString("tiempo: " + ofToString(tiempo), ofPoint(ofGetWindowWidth() - 200, ofGetWindowHeight() - 110));
		ofDrawBitmapString("Nparts: " + ofToString(parts.size()), ofPoint(ofGetWindowWidth() - 200, ofGetWindowHeight() - 90));
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {
	case '1':
		cam.dolly(-150);
		break;
	case '2':
		cam.dolly(150);
		break;
	case '3':
		cam.boom(-150);
		break;
	case '4':
		cam.boom(150);
		break;
	case 'r':
		rota = !rota;
		break;
	case 'a':
		analiza.anima = !analiza.anima;
		break;
	case 'e':
		analiza.dibujaEtiqueta = !analiza.dibujaEtiqueta;
		break;
	case 'p':
		analiza.creaParticulas = !analiza.creaParticulas;
		break;
	case 'g':
		grid = !grid;
		break;
	case 'm':
		moveCam = !moveCam;
		if (moveCam) {
			cam.enableMouseInput();
		}
		else {
			cam.disableMouseInput();
		}
		break;
	case 'G':
		invierteGravedad = !invierteGravedad;
		break;
	case 'f':
		fs = !fs;
		ofSetFullscreen(fs);
		if(!fs)
			ofSetWindowPosition(100, 100);
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	switch (key) {
	case 'd':
		debug = !debug;
		break;

	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
	//parts.push_back(Particula(ofVec3f(x, 0, 0), 100));
	//for (int i = 0; i < parts.size(); i++) {
	//parts.end.setup();
	//}
}


//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

///////////////// GUI 
/// ==== EVENTOS ===================================
void ofApp::onToggleEvent(ofxDatGuiToggleEvent e)
{
	if (e.target->is("GRAVEDAD"))  invierteGravedad = !invierteGravedad;
	if (e.target->is("ETIQUETAS")) analiza.dibujaEtiqueta = !analiza.dibujaEtiqueta;
	if (e.target->is("PARTICULAS")) analiza.creaParticulas = !analiza.creaParticulas;
	if (e.target->is("MESH")) analiza.dibujaMesh = !analiza.dibujaMesh;
	if (e.target->is("MARKER")) analiza.dibujaMarker = !analiza.dibujaMarker;
	if (e.target->is("MARKER SPHERE")) analiza.dibujaMarkerSphere = !analiza.dibujaMarkerSphere;
	if (e.target->is("MARKER RIGID")) analiza.dibujaRigidMarker = !analiza.dibujaRigidMarker;
	if (e.target->is("MARKER BONE")) analiza.dibujaBoneMarker = !analiza.dibujaBoneMarker;
	if (e.target->is("RIGID")) analiza.dibujaRigid = !analiza.dibujaRigid;
	if (e.target->is("BONE")) analiza.dibujaBone = !analiza.dibujaBone;
}
void ofApp::onDropdownEvent(ofxDatGuiDropdownEvent e)
{
}
void ofApp::onSliderEvent(ofxDatGuiSliderEvent e)
{
	if (e.target->is("DIST CAM")) distCam = e.value;
	if (e.target->is("GRAVEDAD")) gravedad = e.value;
}