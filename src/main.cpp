#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main() {
	ofSetupOpenGL(2 * 400 + 60, 400 + 40, OF_WINDOW);
	ofRunApp(new ofApp());
}
