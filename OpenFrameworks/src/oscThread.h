#pragma once

//
//  oscThread.h
//  FACEDIFF
//
//  Created by Michael R Mulshine on 2/13/16.
//
//

#include "ofThread.h"
#include "ofxOsc.h"



/// This is a simple example of a ThreadedObject created by extending ofThread.
/// It contains data (count) that will be accessed from within and outside the
/// thread and demonstrates several of the data protection mechanisms (aka
/// mutexes).
class  OscThread: public ofThread
{
    
    
public:
    /// Create an OscThread and initialize the member
    /// variable in an initialization list.
    OscThread(): shouldThrowTestException(false)
    {
        
    }
    
    ofxOscSender sender;

    /// Start the thread.
    void start()
    {
        startThread();
        ofLog(OF_LOG_NOTICE, "thread start");
    }
    
    void setup() {
        sender.setup("localhost",54321);
         ofLog(OF_LOG_NOTICE, "thread setup");
    }
    
    /// Signal the thread to stop.  After calling this method,
    /// isThreadRunning() will return false and the while loop will stop
    /// next time it has the chance to.
    void stop()
    {
        stopThread();
    }
    
    /// Our implementation of threadedFunction.
    void sendBrightDiff(string label, float diff)
    {
        while(isThreadRunning())
        {
            ofLog(OF_LOG_NOTICE, "thread send diff");
            ofxOscMessage m;
            m.addStringArg(label);
            m.addFloatArg(diff);
            sender.sendMessage(m);
        }
    }
    
protected:
    // A flag to check and see if we should throw a test exception.
    Poco::AtomicCounter shouldThrowTestException;

};
