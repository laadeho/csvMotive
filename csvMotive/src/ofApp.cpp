#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	analizaCSV();
	setupGUI();
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
		///
		//////////////////////////
		/*
		encabezado = ofToString(buffer.getFirstLine()); // Se lee el encabezado
		string e = buffer.getNextLine(); // Salta linea vacia

		vector<string> etiquetas = ofSplitString(buffer.getNextLine(), ","); // Se almacenan las etiquetas
		totalEtiquetas = etiquetas.size();
		string id = buffer.getNextLine(); // se leen los nombres en un solo string
		string id2 = buffer.getNextLine();

		vector<string> tagTransform = ofSplitString(buffer.getNextLine(), ",");
		// Se separan etiquetas de transformacion: Rotate, Position
		vector<string> tagCoord = ofSplitString(buffer.getNextLine(), ",");
		*/
		
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

		/*for (ofBuffer::Line lin = buffer.getLines().begin(), end = buffer.getLines().end(); lin != end; ++lin) {
		}
		*/
	}
	coordenada = ofSplitString(linea[6], ",");

	/*
	/// DEFINE NOMBRE DE ARCHIVO CSV A ANALIZAR
	ofFile archivo(nombreArchivo + ".csv");
	if (!archivo.exists()) ofLogError("The file " + nombreArchivo + " is missing");
	else ofLogNotice("Archivo Encontrado: " + nombreArchivo + "\n Procesando...");
	/// Crea archivo a escribir con datos procesados
	editado.open(nombreArchivo + "_c_editado.csv", ofFile::WriteOnly);
	///
	ofBuffer buffer(archivo);
	for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
	linea.push_back(*it);
	}
	ofLogNotice("Lineas Totales (linea.size()): " + ofToString(linea.size()));
	for (int i = 0; i < 5; i++) {
	ofLogNotice("Size Linea " + ofToString(i) + " : " + ofToString(linea[i].size()));
	}
	//ofLogNotice(ofToString(linea[3]));
	words2 = ofSplitString(linea[2], ",");
	ofLogNotice("words2: " + ofToString(words2.size()));

	// linea 5 comienza con los datos de Posicion y Rotacion, la 6 son las valoress xyz
	//ofLogNotice(ofToString(linea[5]));
	words5 = ofSplitString(linea[5], ",");
	ofLogNotice("words5: " + ofToString(words5.size()));
	//
	//ofLogNotice(ofToString(linea[6]));
	words6 = ofSplitString(linea[6], ",");
	ofLogNotice("words6: " + ofToString(words6.size()));
	//
	coords.clear();

	for (int i = 0; i < words2.size(); i += saltoLinea) {
	if (words2[i] == "Bone") {
	editado << "Bone,";
	}
	}
	editado << "\n";
	for (int i = 0; i < words2.size(); i += saltoLinea) {
	if (words2[i] == "Bone") {
	if (words5[i] == "Position") {
	editado << "Position,";
	}
	}
	}
	editado << "\n";
	wordsFila = ofSplitString(linea[6], ",");

	for (int i = 0; i < words2.size(); i += saltoLinea) {
	if (words2[i] == "Bone") {
	if (words5[i] == "Position") {
	if (words6[i] == "X") {
	editado << "X,";
	x = ofToFloat(wordsFila[i]) * escala;
	}
	else if (words6[i] == "Y") {
	editado << "Y,";
	y = ofToFloat(wordsFila[i]) * escala;
	}
	else if (words6[i] == "Z") {
	editado << "Z,";
	z = ofToFloat(wordsFila[i]) * escala;
	}
	coords.push_back(ofPoint(x, y, z));
	}
	}

	}
	editado << "\n";

	for (int j = 7; j<linea.size() / 10 - 1; j++) {
	wordsFila = ofSplitString(linea[j], ",");
	//wordsFila = ofSplitString(linea[7], ",");
	int num = 0;
	for (int i = 0; i < words2.size(); i += saltoLinea) {
	if (words2[i] == "Bone") {
	if (words5[i] == "Position") {
	if (words6[i] == "X") {
	x = ofToFloat(wordsFila[i]) * escala;
	num++;
	editado << ofToString(x, 2) << ",";
	}
	else if (words6[i] == "Y") {
	y = ofToFloat(wordsFila[i]) * escala;
	num++;
	editado << ofToString(y, 2) << ",";
	}
	else if (words6[i] == "Z") {
	z = ofToFloat(wordsFila[i]) * escala;
	num++;
	editado << ofToString(z, 2);// << ",";
	}
	coords.push_back(ofPoint(x, y, z));
	//ofLogNotice("x:" + ofToString(x) + ",y:" + ofToString(y) + ",z:" + ofToString(z));
	//editado << x << "," << y << "," << z << ",";
	//editado << "\n";
	}
	}
	if (num == 3) {
	editado << "\n";
	num = 0;
	}
	}
	//editado << "\n";
	}
	editado.close();
	lineaAnalisis += 2;
	lineaAnalisis = lineaAnalisis % (linea.size() - 5);

	ofLogNotice("valoress Listas");
	*/
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

//--------------------------------------------------------------
void ofApp::update() {
	std::stringstream strm;
	strm << "fps: " << ofGetFrameRate();
	ofSetWindowTitle(strm.str());

	
/*
	int escribeMarker = 0, cuentaMarker = 0;
	int escribeMarkerBone = 0, cuentaMarkerBone = 0;
	int escribeMarkerRigid = 0, cuentaMarkerRigid = 0;
	int escribeBone = 0, cuentaBone = 0;
	int escribeRigid = 0, cuentaRigid = 0;

	vector<string> valores = ofSplitString(linea[lineaAnalisis], ",");
	//ofLogNotice(ofToString(lineaAnalisis));
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
	*/
}

//--------------------------------------------------------------
void ofApp::draw() {
	
	ofBackground(0);
	cam.begin();
	ofSetColor(120);
	ofFill();

	ofBox(ofPoint(0, 0, 0), 1100, 10, 800);
	/*
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
	*/
	cam.end();
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

///////////////// GUI 
/// ==== EVENTOS ===================================
void ofApp::onToggleEvent(ofxDatGuiToggleEvent e)
{
	if (e.target->is("DEBUG")) debug = !debug;
	if (e.target->is("MARKER")) dibujaMarker = !dibujaMarker;
	if (e.target->is("MARKER RIGID")) dibujaRigidMarker = !dibujaRigidMarker;
	if (e.target->is("MARKER BONE")) dibujaBoneMarker = !dibujaBoneMarker;
	if (e.target->is("RIGID")) dibujaRigid = !dibujaRigid;
	if (e.target->is("BONE")) dibujaBone = !dibujaBone;
}
void ofApp::onDropdownEvent(ofxDatGuiDropdownEvent e)
{
}
