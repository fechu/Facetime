#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    width = 320;  // try to grab at this size.
    height = 240;
    
    // oscThread
    //oscThread.setup();
    //oscThread.start();
    
    //AUDIO STUFF
    ofSoundStreamSetup(2, 0, 44100, BUF1_LEN, 4);
    ofSoundStreamStart();
    
    
    //we can now get back a list of devices.
    vector<ofVideoDevice> devices = grabber.listDevices();
    
    
    for(int i = 0; i < devices.size(); i++){
        if(devices[i].bAvailable){
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
        }else{
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
        }
    }
    
    grabber.setDeviceID(0);
    grabber.setDesiredFrameRate(1);
    grabber.initGrabber(width, height);
    
    currPixels.allocate(width, height, OF_PIXELS_RGB);
    lastPixels.allocate(width, height, OF_PIXELS_RGB);
    texture.allocate(currPixels);
    ofSetVerticalSync(true);
}

//--------------------------------------------------------------
void ofApp::update(){
    ofBackground(0, 0, 0);
    grabber.update();
    
    if(grabber.isFrameNew()){
        ofPixels & pxs = grabber.getPixels();
        float dBright, dLight, dSat;
        for(int i = 0; i < pxs.size(); i+=3) {
            currPixels[i] = pxs[i];
            lastPixels[i] = currPixels[i];
            ofColor curr = currPixels.getColor(i);
            ofColor last = lastPixels.getColor(i);
            //brightness,lightness, saturation, hue angle
            //dBright = (curr.getBrightness() - last.getBrightness())/255.;
            dLight = (curr.getLightness() - last.getLightness())/255.;
            //dSat =(curr.getSaturation() - last.getSaturation())/255.;
            if ((i % ((width*height*3)/BUF1_LEN)) == 0) {
                audioB1[i/3] = dLight;
            }
        
        }
        //texture.loadData(currPixels);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetHexColor(0xffffff);
    grabber.draw(20, 20);
    texture.draw(20 + width, 20, width, height);
}

void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    for (int i = 0; i < bufferSize; i++){
        output[i*nChannels    ] = audioB1[i];
        output[i*nChannels + 1] = audioB1[i];
    }
}

#if 0
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
#endif
