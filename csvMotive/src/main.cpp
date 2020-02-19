#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){
	/*
	ofSetupOpenGL(1024,768,OF_FULLSCREEN);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
	*/

	ofAppGlutWindow window;

	window.setGlutDisplayString("rgb double depth>=32 alpha");

	//window.setGlutDisplayString("rgba double samples>=4"); // no f
	//window.setGlutDisplayString("rgb double depth>=32 alpha samples>=4"); // no f
	//window.setGlutDisplayString("rgba double samples>=4 depth>=32");  
	ofSetupOpenGL(&window, 3840, 2400, OF_FULLSCREEN);
	ofRunApp(new ofApp());
}
/*
Probablemente sea necesario dibujar en un vbo
con mayor resolucion y comprimirlo, para acceder 
a una mejor resolucion
*/