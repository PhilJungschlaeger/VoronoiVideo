#pragma once

#include "ofMain.h"
#include <vector>

class ofApp : public ofBaseApp {

public:

    void setup();
    void update();
    void draw();

private:
    ofVideoGrabber          vidGrabber;     // WebCam
    ofPixels                currentImg;     // to work with, set here -> load to vidTex
    ofTexture               videoTexture1;  // Voronoi Texture, Shown on Screen
    ofTexture               videoTexture2;  // Original Texture, Shown on Screen

    std::vector<ofPoint>    samplePoints;   // Points to sample on Videoframes
    int                     sampleAmount;   // Amount of Points
    
    int camWidth;
    int camHeight;
};