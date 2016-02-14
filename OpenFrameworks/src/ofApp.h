#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "oscThread.h"
#include "ofSoundStream.h"

#define BUF1_LEN 1024

class ofApp : public ofBaseApp, ofThread {

	public:
		void setup();
		void update();
		void draw();

#if 0
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
#endif
   
    void audioOut(float * output, int buffersize, int nChannels);
    
    // OSC STUFF
    ofxOscSender sender;
    //OscThread oscThread;
    
    // AUDIO
    float audioB1[BUF1_LEN];
    
    
    ofVideoGrabber grabber;
    ofPixels currPixels;
    ofPixels lastPixels;
    ofTexture texture;
    int width;
    int height;
		
};
