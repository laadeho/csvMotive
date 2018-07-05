#include "ofMain.h"
#include "ofApp.h"
#include "Analiza.h"

Analiza::Analiza() {
	analizaCSV();
}

void Analiza::analizaCSV() {
	ofFileDialogResult result = ofSystemLoadDialog("Selecciona un archivo csv para analizar");

	if (result.bSuccess) {
		string name = result.filePath;
		//ofLogNotice("Se abre archivo: " + name);

		ofFile archivoCSV;
		archivoCSV.open(ofToDataPath(name), ofFile::ReadOnly, false);

		buffer = archivoCSV.readToBuffer(); // Se almacena el archivo
		/// OPCION B
		for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
			linea.push_back(*it);
		}
		//ofLogNotice("Numero de Lineas: " + ofToString(linea.size()));
		//////////////////////////

		encabezado = linea[0]; // Se lee el encabezado
		vector<string> datosEncabezado = ofSplitString(linea[0], ",");
		fpsFromFile = ofToInt(datosEncabezado[7]);

		vector<string> etiquetas = ofSplitString(linea[2], ","); // Se almacenan las etiquetas
		totalEtiquetas = etiquetas.size();

		vector<string> nameMarkerLinea = ofSplitString(linea[3], ",");

		//coordenada.resize(totalEtiquetas);
		tagTransform = ofSplitString(linea[5], ",");
		coordenada = ofSplitString(linea[6], ",");

		// nameMarker
		/*
		int escribeNameMarker = 0;
		int cuentaNameMarker = 0;
		for(int i = 0; i < nameMarkerLinea.size(); i++) {
			if (tagTransform[i] == "Rotation") {
				if (coordenada[i] == "X")
				{
					cuentaNameMarker++;
				}
				else if (coordenada[i] == "Y")
				{
					cuentaNameMarker++;
				}
				else if (coordenada[i] == "Z" || coordenada[i] == "Z\r" || coordenada[i] == "Z\n")
				{
					cuentaNameMarker++;
				}
				else
				{
					return;
				}
			}
			else if (tagTransform[i] == "Position") {
				if (coordenada[i] == "X")
				{
					cuentaNameMarker++;
					nameMarker.push_back(nameMarkerLinea[i]);
				}
				else if (coordenada[i] == "Y")
				{
					cuentaNameMarker++;
				}
				else if (coordenada[i] == "Z" || coordenada[i] == "Z\r" || coordenada[i] == "Z\n")
				{
					cuentaNameMarker++;
				}
				else
				{
					return;
				}
			}
			ofLogNotice(nameMarker);
			if (cuentaNameMarker % 3 == 0)
			{
				escribeNameMarker++;
				escribeNameMarker = escribeNameMarker % nameMarkerLinea.size(); /// posiblemente no sea necesario, dado que ésto solo corre una vez
			}
		}
		*/

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

		int cuentaBone = 0, cuentaBoneR = 0;

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
					if (tagTransform[i] == "Position") {
						esBone[i] = true;
						numBone++;

						if (coordenada[i] == "X")
						{
							cuentaBone++;
						}
						else if (coordenada[i] == "Y")
						{
							cuentaBone++;
						}
						else if (coordenada[i] == "Z" || coordenada[i] == "Z\r" || coordenada[i] == "Z\n")
						{
							cuentaBone++;
						}
						else
						{
							return;
						}

						if (cuentaBone % 3 == 0)
						{
							bonePos.push_back(ofPoint(0, 0, 0));
						}
					}
					else if (tagTransform[i] == "Rotation") {
						esBone[i] = true;
						numBone++;
						if (coordenada[i] == "X")
						{
							cuentaBoneR++;
						}
						else if (coordenada[i] == "Y")
						{
							cuentaBoneR++;
						}
						else if (coordenada[i] == "Z" || coordenada[i] == "Z\r" || coordenada[i] == "Z\n")
						{
							cuentaBoneR++;
						}
						else
						{
							return;
						}

						if (cuentaBoneR % 3 == 0)
						{
							boneRot.push_back(ofPoint(0, 0, 0));
						}
					}
					// ofLogNotice("Pos: " + ofToString(posB)+", Rot: " + ofToString(rotB)); 
					/// imprime 63 y 63 para el archivo de FERMIN
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
		}
		//int cuentaBone = 0, cuentaBoneR = 0;
		/*for (int i = 0; i < totalEtiquetas; i++) {
			if (esBone[i])
			{
				if (tagTransform[i] == "Position") {
					if (coordenada[i] == "X")
					{
						cuentaBone++;
					}
					else if (coordenada[i] == "Y")
					{
						cuentaBone++;
					}
					else if (coordenada[i] == "Z" || coordenada[i] == "Z\r" || coordenada[i] == "Z\n")
					{
						cuentaBone++;
					}
					else
					{
						return;
					}

					if (cuentaBone % 3 == 0)
					{
						bonePos.push_back(ofPoint(0,0,0));
						ofLogNotice("va un Pos: " + ofToString(bonePos.size()));

					}
				}
				if (tagTransform[i] == "Rotation") {
					if (coordenada[i] == "X")
					{
						cuentaBoneR++;
					}
					else if (coordenada[i] == "Y")
					{
						cuentaBoneR++;
					}
					else if (coordenada[i] == "Z" || coordenada[i] == "Z\r" || coordenada[i] == "Z\n")
					{
						cuentaBoneR++;
					}
					else
					{
						return;
					}

					if (cuentaBoneR % 3 == 0)
					{
						boneRot.push_back(ofPoint(0,0,0));
						ofLogNotice("va un Rot: "+ofToString(boneRot.size()));

					}
				}
			}
		}
		*/
		ofLogNotice("Pos: "+ofToString(bonePos.size()));
		ofLogNotice("Rot: "+ofToString(boneRot.size()));

		// IMPRIME Cantidad de etiquetas
		/*if (debug) {
		ofLogNotice("Total Etiquetas: " + ofToString(etiquetas.size()));
		ofLogNotice("Num Marker: " + ofToString(numMarker));
		ofLogNotice("Num RigidMarker: " + ofToString(numRigidMarker));
		ofLogNotice("Num BoneMarker: " + ofToString(numBoneMarker));
		ofLogNotice("Num Rigid: " + ofToString(numRigid));
		ofLogNotice("Num Bone: " + ofToString(numBone));
		ofLogNotice("Num Vacios: " + ofToString(numVacios));
		ofLogNotice("Suma: " + ofToString(numMarker + numRigidMarker + numBoneMarker + numRigid + numBone + numVacios));
		}*/

		// VECTORES MARCADORES
		/// MARCADORES
		markerPos.resize(numMarker / 3); // 6 indices
		markerPosBone.resize(numBoneMarker / 3); // 6 indices
		markerPosRigid.resize(numRigidMarker / 3); // 6 indices

		/// RIGID Posicion y Rotacion
		rigidPos.resize(numRigid / 3); // 6 indices
		rigidRot.resize(numRigid / 3); // 6 indices
		/// BONE Posicion y Rotacion
		//bonePos.resize(numBone / 3); // 6 indices /// el tamanio no es correcto dado que hay rotaciones
		//boneRot.resize(numBone / 3); // 6 indices
	}
}

void Analiza::update() {
	int escribeMarker = 0, cuentaMarker = 0;
	int escribeMarkerBone = 0, cuentaMarkerBone = 0;
	int escribeMarkerRigid = 0, cuentaMarkerRigid = 0;
	int escribeBone = 0, cuentaBone = 0;
	int escribeBoneR = 0, cuentaBoneR = 0;
	int escribeRigid = 0, cuentaRigid = 0;

	vector<string> valores = ofSplitString(linea[lineaAnalisis], ",");

	if (anima)
		lineaAnalisis += saltoLinea;

	if (lineaAnalisis % (linea.size() - 1) == 0 || lineaAnalisis > linea.size() - 1) {
		lineaAnalisis = 7;
	}
	float tx = 0, ty = 0, tz = 0;
	float txr = 0, tyr = 0, tzr = 0;

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
				else if (coordenada[i] == "Z" || coordenada[i] == "Z\r" || coordenada[i] == "Z\n")
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
				else if (coordenada[i] == "Z" || coordenada[i] == "Z\r" || coordenada[i] == "Z\n")
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
				else if (coordenada[i] == "Z" || coordenada[i] == "Z\r" || coordenada[i] == "Z\n")
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
					else if (coordenada[i] == "Z" || coordenada[i] == "Z\r" || coordenada[i] == "Z\n")
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
						//bonePos.push_back()
						tx = ofToFloat(valores[i]) * escala;
						//bonePos[escribeBone].x = ofToFloat(valores[i]) * escala;
						cuentaBone++;
					}
					else if (coordenada[i] == "Y")
					{
						ty = ofToFloat(valores[i]) * escala;
						//bonePos[escribeBone].y = ofToFloat(valores[i]) * escala;
						cuentaBone++;
					}
					else if (coordenada[i] == "Z" || coordenada[i] == "Z\r" || coordenada[i] == "Z\n")
					{
						tz = ofToFloat(valores[i]) * escala;
						//bonePos[escribeBone].z = ofToFloat(valores[i]) * escala;
						cuentaBone++;
					}
					else
					{
						return;
					}

					if (cuentaBone % 3 == 0)
					{
						//bonePos.push_back(ofPoint(tx, ty, tz));
						bonePos[escribeBone] = ofPoint(tx, ty, tz);
						escribeBone++;
						escribeBone = escribeBone % bonePos.size();
					}
				}
				else if (tagTransform[i] == "Rotation") {
					if (coordenada[i] == "X")
					{
						txr = ofToFloat(valores[i]);
						cuentaBoneR++;
					}
					else if (coordenada[i] == "Y")
					{
						tyr = ofToFloat(valores[i]);
						cuentaBoneR++;
					}
					else if (coordenada[i] == "Z" || coordenada[i] == "Z\r" || coordenada[i] == "Z\n")
					{
						tzr = ofToFloat(valores[i]);
						cuentaBoneR++;
					}
					else
					{
						return;
					}

					if (cuentaBoneR % 3 == 0)
					{
						boneRot[escribeBone] = ofPoint(txr, tyr, tzr);
						escribeBoneR++;
						escribeBoneR = escribeBoneR % boneRot.size();
					}
				}
			}
		}
	}
	//ofLogNotice("Pos: " + ofToString(bonePos[0]) + ", Rot: " + ofToString(boneRot[0]));
}


void Analiza::draw() {
	
}