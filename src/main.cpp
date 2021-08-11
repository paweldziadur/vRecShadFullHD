#include "ofMain.h"
#include "ofApp.h"
#include "ofGLProgrammableRenderer.h"

//========================================================================
int main( ){
    
    ofGLWindowSettings settings;
  //  ofGLFWWindowSettings settings;
    settings.setGLVersion(4,1);
    settings.width = 1920 ;
    settings.height = 1080 ;
    
    
   // settings.resizable = true;
    ofCreateWindow(settings);
    
    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp());
}

