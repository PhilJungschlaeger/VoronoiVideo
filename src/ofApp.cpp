#include "ofApp.h"
#include <iostream>
//--------------------------------------------------------------

void ofApp::setup() {
    // set up
    camWidth = 400;
    camHeight = 400;
    sampleAmount = 200;

    // find camera
    vector<ofVideoDevice> devices = vidGrabber.listDevices();
    for (size_t i = 0; i < devices.size(); i++) {
        if (devices[i].bAvailable) {
            //log the device
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
        }
        else {
            //log the device and note it as unavailable
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
        }
    }
    vidGrabber.setDeviceID(0);
    //vidGrabber.setDesiredFrameRate(10);
    vidGrabber.initGrabber(camWidth, camHeight);

    // Allocate videoTextures
    currentImg.allocate(camWidth, camHeight, OF_PIXELS_RGB);
    videoTexture1.allocate(currentImg);
    videoTexture2.allocate(currentImg);

    // Do naive random sampling
    for (int i = 0; i < sampleAmount; i++) {    // Compute Samples:
        samplePoints.push_back(ofPoint(rand() % camWidth, rand() % camHeight));
    }

    //ofSetVerticalSync(true);
}


//--------------------------------------------------------------
void ofApp::update() {
    ofBackground(0, 0, 0);
    vidGrabber.update();

    ofPixels pixels = vidGrabber.getPixels();
    ofPixels pixels2 = vidGrabber.getPixels();
    videoTexture2.loadData(pixels2);                        // show plain camera image

    // Transform Image to Voronoi:
    float minDistCurr = 999999;
    ofColor colorCurr = ofColor::pink;
    for (int x = 0; x < camWidth; x++)
    {
        for (int y = 0; y < camHeight; y++)
        {
            // find closest sample and draw it
            minDistCurr = 999999;
            for (int i = 0; i < sampleAmount; i++) {
                float newDist = samplePoints[i].distance(ofPoint(x, y));
                if (newDist < minDistCurr) {
                    minDistCurr = newDist;
                    colorCurr = pixels.getColor(samplePoints[i].x, samplePoints[i].y);
                }
            }
            pixels.setColor(x, y, colorCurr);
        }
    }
    videoTexture1.loadData(pixels);                         // show voronoi image
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofSetHexColor(0xffffff);
    videoTexture1.draw(20, 20, camWidth, camHeight);
    videoTexture2.draw(20 + camWidth + 20, 20, camWidth, camHeight);
}