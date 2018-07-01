#include "ofApp.h"
int tiempo = 0;
//--------------------------------------------------------------
void ofApp::setup(){
	/*
	part = Particula(ofVec3f(0, 0, 0), 5);
	part.setup();
	*/

	analizaCSV();
	setupGUI();

	//ofSetFrameRate(120);
	ofSetVerticalSync(true);
	//ofSetBackgroundAuto(false);

	/// MESH
	mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP_ADJACENCY);
	//mesh.setMode(OF_PRIMITIVE_POINTS);

	meshLines.setMode(OF_PRIMITIVE_LINE_STRIP);

	for (int i = 0; i < markerPos.size(); i++) {
		ofVec3f vertice(markerPos[i].x, markerPos[i].y, markerPos[i].z);
		mesh.addVertex(vertice);
		meshLines.addVertex(vertice);
		float val = ofRandom(1);
		//mesh.addColor(ofFloatColor(val, val, val, ofRandom(1)));
		mesh.addColor(ofFloatColor(val, val, val,ofRandom(1)));
		offsets.push_back(ofVec3f(ofRandom(0, 100000), ofRandom(0, 100000), ofRandom(0, 100000)));
	}
	
	for (int i = 0; i < markerPos.size() - 2; i += 3) {
		mesh.addIndex(i);
		mesh.addIndex(i + 1);
		mesh.addIndex(i + 2);
		meshLines.addIndex(i);
		/*
		meshLines.addIndex(i + 1);
		meshLines.addIndex(i + 2);
		*/
	}
	
	/// CAMARA
	cam.disableMouseInput();

	/// LUCES
	light.setup();
	light.setPosition(0, 200, 0);

	pointLight.setPointLight();

}

void ofApp::analizaCSV() {
	ofFileDialogResult result = ofSystemLoadDialog("Selecciona un archivo csv para analizar");

	if (result.bSuccess) {
		string name = result.filePath;
		ofLogNotice("Se abre archivo: " + name);

		ofFile archivoCSV;
		archivoCSV.open(ofToDataPath(name), ofFile::ReadOnly, false);

		buffer = archivoCSV.readToBuffer(); // Se almacena el archivo
		/// OPCION B
		for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
			linea.push_back(*it);
		}
		ofLogNotice("Numero de Lineas: " + ofToString(linea.size()));
		//////////////////////////

		encabezado = linea[0]; // Se lee el encabezado

		vector<string> etiquetas = ofSplitString(linea[2], ","); // Se almacenan las etiquetas
		totalEtiquetas = etiquetas.size();

		tagTransform = ofSplitString(linea[5], ",");

		if (debug) {
			ofLogNotice("ENCABEZADO: " + encabezado);
			//ofLogNotice("" + e);
			ofLogNotice("ETIQUETAS: " + ofToString(etiquetas));
			ofLogNotice("TRANSFORMACIONES: " + ofToString(tagTransform));
		}
		coordenada.resize(totalEtiquetas);
		/// COMPROBACIONES DE ETIQUETAS Y ALMACENAMIENTO DE VALORES EN VARIABLES
		esMarker.resize(etiquetas.size());
		esRigidMarker.resize(etiquetas.size());
		esBoneMarker.resize(etiquetas.size());

		esRigid.resize(etiquetas.size());
		esBone.resize(etiquetas.size());

		esRot.resize(etiquetas.size());
		esPos.resize(etiquetas.size());

		/// Contador para vectores
		int numMarker = 0, numRigidMarker = 0, numBoneMarker = 0, numRigid = 0, numBone = 0, numVacios = 0;

		/// LEEMOS TODAS LAS ETIQUETAS
		for (int i = 0; i < etiquetas.size(); i++) {
			if (etiquetas[i] != "")
			{
				if (etiquetas[i] == "Marker" || etiquetas[i] == "Marker\r")
				{
					esMarker[i] = true;
					numMarker++;
				}
				else if (etiquetas[i] == "Rigid Body Marker" || etiquetas[i] == "Rigid Body Marker\r") // 18
				{
					esRigidMarker[i] = true;
					numRigidMarker++;
				}
				else if (etiquetas[i] == "Bone Marker" || etiquetas[i] == "Bone Marker\r")
				{
					esBoneMarker[i] = true;
					numBoneMarker++;
				}
				else if (etiquetas[i] == "Rigid Body" || etiquetas[i] == "Rigid Body\r") // 6
				{
					esRigid[i] = true;
					numRigid++;
				}
				else if (etiquetas[i] == "Bone" || etiquetas[i] == "Bone\r")
				{
					esBone[i] = true;
					numBone++;
				}
				else
				{
					esRigid[i] = false;
					esRigidMarker[i] = false;
					esMarker[i] = false;
					esBone[i] = false;
					esBoneMarker[i] = false;
					numVacios++;
				}
			}
			else {
				numVacios++;
			}
		}

		// IMPRIME Cantidad de etiquetas
		if (debug) {
			ofLogNotice("Total Etiquetas: " + ofToString(etiquetas.size()));
			ofLogNotice("Num Marker: " + ofToString(numMarker));
			ofLogNotice("Num RigidMarker: " + ofToString(numRigidMarker));
			ofLogNotice("Num BoneMarker: " + ofToString(numBoneMarker));
			ofLogNotice("Num Rigid: " + ofToString(numRigid));
			ofLogNotice("Num Bone: " + ofToString(numBone));
			ofLogNotice("Num Vacios: " + ofToString(numVacios));
			ofLogNotice("Suma: " + ofToString(numMarker + numRigidMarker + numBoneMarker + numRigid + numBone + numVacios));
		}

		// VECTORES MARCADORES
		/// MARCADORES
		markerPos.resize(numMarker / 3); // 6 indices
		markerPosBone.resize(numBoneMarker / 3); // 6 indices
		markerPosRigid.resize(numRigidMarker / 3); // 6 indices

		/// RIGID Posicion y Rotacion
		rigidPos.resize(numRigid / 3); // 6 indices
		rigidRot.resize(numRigid / 3); // 6 indices
									   /// BONE Posicion y Rotacion
		bonePos.resize(numBone / 3); // 6 indices
		boneRot.resize(numBone / 3); // 6 indices
	}
	coordenada = ofSplitString(linea[6], ",");
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
	for (int i = 0; i < parts.size(); i++) {
		parts[i].update();
		parts[i].applyForce(ofVec3f(0, 0.1, 0));
		//if (!parts[i].vive) {
			//Particula p = parts[i];
			//parts.pop_back();
			//parts.clear();
			//delete parts[i];
		//}
	}

	/*	
	vector<Particula>::iterator itP = parts.begin();
	for (; itP != parts.end(); ++itP) {
		if (!(*itP).vive) {
			parts.erase(itP);
		}
	}
	*/
	//vector<Particula>::iterator itP = parts.;
	ofRemove(parts, checkVive);

	/*
	bool partVive(Particula p) {
		return !p.vive;
	}
	*/
//	ofRemove(parts, partVive);

	

	/*for (size_t i = 0; i < parts.size(); i++) {
		Particula p = parts[i];
		p.update();
		if (!p.vive) {
			parts.cl;
		}
		*/

		/*
		parts[i].update();
		if (!parts[i].vive) {
			//Particula p = parts[i];
			parts.pop_back();
		}
		
	}
	*/
	tiempo = int(ofGetElapsedTimef());
	/*
	std::stringstream strm;
	strm << "fps: " << ofGetFrameRate();
	ofSetWindowTitle(strm.str());
	*/


	updateVal();
	updateMesh();	

	//ofSaveScreen("Frame_"+ofToString(ofGetFrameNum()) + ".png");
	/*if (ofGetFrameNum() > 10)
	{
		ofExit();
		OF_EXIT_APP(0);
		ofExitCallback();
	}*/
	/*
	ofExit();
	OF_EXIT_APP(0);
	ofExitCallback();
	*/
	/// CAMARA
	cam.setPosition(posCam);
	cam.setTarget(ofVec3f(0, 150, 0));
	posCam = ofVec3f(sin(ofGetElapsedTimeMillis()*.0001)*distCam, 165, cos(ofGetElapsedTimeMillis()*.0001) * distCam);
}

//--------------------------------------------------------------
void ofApp::updateVal() {
	int escribeMarker = 0, cuentaMarker = 0;
	int escribeMarkerBone = 0, cuentaMarkerBone = 0;
	int escribeMarkerRigid = 0, cuentaMarkerRigid = 0;
	int escribeBone = 0, cuentaBone = 0;
	int escribeRigid = 0, cuentaRigid = 0;

	vector<string> valores = ofSplitString(linea[lineaAnalisis], ",");
	lineaAnalisis += saltoLinea;

	if (lineaAnalisis % (linea.size() - 1) == 0 || lineaAnalisis > linea.size() - 1) {
		lineaAnalisis = 7;
	}

	for (int i = 0; i < totalEtiquetas; i++)
	{
		if (esMarker[i])
		{
			if (valores[i] != "")
			{
				if (coordenada[i] == "X")
				{
					markerPos[escribeMarker].x = ofToFloat(valores[i]) * escala;
					cuentaMarker++;
				}
				else if (coordenada[i] == "Y")
				{
					markerPos[escribeMarker].y = ofToFloat(valores[i]) * escala;
					cuentaMarker++;
				}
				else if (coordenada[i] == "Z" || valores[i] == "Z\r" || valores[i] == "Z\n")
				{
					markerPos[escribeMarker].z = ofToFloat(valores[i]) * escala;
					cuentaMarker++;
				}
				else
				{
					return;
				}

				if (cuentaMarker % 3 == 0)
				{
					escribeMarker++;
					escribeMarker = escribeMarker % markerPos.size();
				}
			}
		}
		else if (esRigidMarker[i])
		{
			if (valores[i] != "")
			{
				if (coordenada[i] == "X")
				{
					markerPosRigid[escribeMarkerRigid].x = ofToFloat(valores[i]) * escala;
					cuentaMarkerRigid++;
				}
				else if (coordenada[i] == "Y")
				{
					markerPosRigid[escribeMarkerRigid].y = ofToFloat(valores[i]) * escala;
					cuentaMarkerRigid++;
				}
				else if (coordenada[i] == "Z" || valores[i] == "Z\r" || valores[i] == "Z\n")
				{
					markerPosRigid[escribeMarkerRigid].z = ofToFloat(valores[i]) * escala;
					cuentaMarkerRigid++;
				}
				else
				{
					return;
				}

				if (cuentaMarkerRigid % 3 == 0)
				{
					escribeMarkerRigid++;
					escribeMarkerRigid = escribeMarkerRigid % markerPosRigid.size();
				}
			}
		}
		else if (esBoneMarker[i])
		{
			if (valores[i] != "")
			{
				if (coordenada[i] == "X")
				{
					markerPosBone[escribeMarkerBone].x = ofToFloat(valores[i]) * escala;
					cuentaMarkerBone++;
				}
				else if (coordenada[i] == "Y")
				{
					markerPosBone[escribeMarkerBone].y = ofToFloat(valores[i]) * escala;
					cuentaMarkerBone++;
				}
				else if (coordenada[i] == "Z" || valores[i] == "Z\r" || valores[i] == "Z\n")
				{
					markerPosBone[escribeMarkerBone].z = ofToFloat(valores[i]) * escala;
					cuentaMarkerBone++;
				}
				else
				{
					return;
				}

				if (cuentaMarkerBone % 3 == 0)
				{
					escribeMarkerBone++;
					escribeMarkerBone = escribeMarkerBone % markerPosBone.size();
				}
			}
		}
		else if (esRigid[i])
		{
			if (valores[i] != "")
			{
				if (tagTransform[i] == "Position") {
					if (coordenada[i] == "X")
					{
						rigidPos[escribeRigid].x = ofToFloat(valores[i]) * escala;
						cuentaRigid++;
					}
					else if (coordenada[i] == "Y")
					{
						rigidPos[escribeRigid].y = ofToFloat(valores[i]) * escala;
						cuentaRigid++;
					}
					else if (coordenada[i] == "Z" || valores[i] == "Z\r" || valores[i] == "Z\n")
					{
						rigidPos[escribeRigid].z = ofToFloat(valores[i]) * escala;
						cuentaRigid++;
					}
					else
					{
						return;
					}

					if (cuentaRigid % 3 == 0)
					{
						escribeRigid++;
						escribeRigid = escribeRigid % rigidPos.size();
					}
				}
			}
		}
		else if (esBone[i])
		{
			if (valores[i] != "")
			{
				if (tagTransform[i] == "Position") {
					if (coordenada[i] == "X")
					{
						bonePos[escribeBone].x = ofToFloat(valores[i]) * escala;
						cuentaBone++;
					}
					else if (coordenada[i] == "Y")
					{
						bonePos[escribeBone].y = ofToFloat(valores[i]) * escala;
						cuentaBone++;
					}
					else if (coordenada[i] == "Z" || valores[i] == "Z\r" || valores[i] == "Z\n")
					{
						bonePos[escribeBone].z = ofToFloat(valores[i]) * escala;
						cuentaBone++;
					}
					else
					{
						return;
					}

					if (cuentaBone % 3 == 0)
					{
						escribeBone++;
						escribeBone = escribeBone % bonePos.size();
					}
				}
			}
		}
	}
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
		vert = markerPos[i];
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

	if (dibujaMarker) {
		ofSetColor(255);
		ofFill();
		for (int i = 0; i < markerPos.size(); i++) {
			ofDrawEllipse(markerPos[i], 5, 5);
		}
	}
	if (dibujaRigidMarker) {
		ofSetColor(255, 0, 0);
		ofFill();
		for (int i = 0; i < markerPosRigid.size(); i++) {
			ofDrawEllipse(markerPosRigid[i], 5, 5);
		}
	}
	if (dibujaBoneMarker) {
		ofSetColor(0, 255, 0);
		ofFill();
		for (int i = 0; i < markerPosBone.size(); i++) {
			ofDrawEllipse(markerPosBone[i], 5, 5);
		}
	}
	if (dibujaRigid) {
		ofSetColor(0, 0, 255);
		ofFill();
		for (int i = 0; i < rigidPos.size(); i++) {
			ofDrawEllipse(rigidPos[i], 5, 5);
		}
	}
	if (dibujaBone) {
		ofSetColor(0, 255, 255);
		ofFill();
		for (int i = 0; i < bonePos.size(); i++) {
			ofDrawEllipse(bonePos[i], 5, 5);
			ofBox(bonePos[i], 20, 100, 20);
		}
	}
	if (dibujaMarkerSphere) {
		ofSetIcoSphereResolution(3); /// ///////////////////////
		for (int i = 0; i < markerPos.size(); i++) {
			//ofDrawEllipse(markerPos[i], 5, 5);
			//ofDrawBox(markerPos[i], 15);
			//ofDrawArrow(markerPos[i], markerPos[i]*1.1, 15);
			ofSetColor(200);
			ofFill();
			ofDrawIcoSphere(markerPos[i], 15);
			ofSetColor(50);
			ofNoFill();
			ofPushMatrix();
			ofTranslate(markerPos[i]);
			ofRotateX(ofGetElapsedTimeMillis()*.05);
			ofRotateY(ofGetElapsedTimeMillis()*.025);
			ofDrawIcoSphere(ofPoint(0, 0, 0), 17);
			ofPopMatrix();
		}
	}

	if (!creaParticulas) {
		for (int i = 0; i < markerPos.size(); i++) {
			//if(i%2==0)
			parts.push_back(Particula(ofVec3f(markerPos[i].x, markerPos[i].y, markerPos[i].z), ofRandom(1,50)));
		}
	}

	for (int i = 0; i < parts.size(); i++) {
		parts[i].draw();
	}

	ofSetColor(120);
	ofFill();
	//ofBox(ofPoint(0, 0, 0), 1100, 10, 800);

	if (dibujaMesh) {
		mesh.draw();
		ofSetColor(0);
		ofNoFill();
		meshLines.draw();
	}
	
	light.disable();
	pointLight.disable();
	ofDisableLighting();

	cam.end();
	ofDisableDepthTest();

		
	if (debug) {
		ofSetColor(255);
		ofFill();
		float val = ofGetFrameRate();
		ofDrawBitmapString("fps: " + ofToString(val), ofPoint(ofGetWindowWidth() - 200, ofGetWindowHeight() - 150));
		ofDrawBitmapString("linea: " + ofToString(lineaAnalisis), ofPoint(ofGetWindowWidth() - 200, ofGetWindowHeight() - 130));
		ofDrawBitmapString("tiempo: " + ofToString(tiempo), ofPoint(ofGetWindowWidth() - 200, ofGetWindowHeight() - 110));
		//if(parts.size()!=NULL)
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
	if (e.target->is("DEBUG")) debug = !debug;
	if (e.target->is("PARTICULAS")) creaParticulas = !creaParticulas;
	if (e.target->is("MESH")) dibujaMesh = !dibujaMesh;
	if (e.target->is("MARKER")) dibujaMarker = !dibujaMarker;
	if (e.target->is("MARKER SPHERE")) dibujaMarkerSphere = !dibujaMarkerSphere;
	if (e.target->is("MARKER RIGID")) dibujaRigidMarker = !dibujaRigidMarker;
	if (e.target->is("MARKER BONE")) dibujaBoneMarker = !dibujaBoneMarker;
	if (e.target->is("RIGID")) dibujaRigid = !dibujaRigid;
	if (e.target->is("BONE")) dibujaBone = !dibujaBone;
}
void ofApp::onDropdownEvent(ofxDatGuiDropdownEvent e)
{
}
