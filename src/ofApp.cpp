#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //img.loadImage("vlc_snap.png");
    ofSetFrameRate(30);
    
    // we allocate FBO so that we can send the FBO later to video recorder
    fbo.allocate(1920, 1080, GL_RGB); // with alpha, 8 bits red, 8 bits green, 8 bits blue, 8 bits alpha, from 0 to 255 in 256 steps
    
    int camWidth = 1920;
    int camHeight = 1080;
    
    camera.setVerbose(false);
    camera.initGrabber(camWidth, camHeight);
    
    movie.loadMovie("video/testVideoToBeManipulated.mov");
    movie.play();
    
    customShader.texture_to_textura(true);
    customShader.loadShadertoy("shadertoy/shadertoy4.frag",1,1,1,1);  // can try to load shadertoy2.frag or other one instead
    
    schulzRecorder.setOutputResolution(1920, 1080);
    schulzRecorder.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    movie.update();
    camera.update();
  //bool success = schulzRecorder.vidRecorder.addFrame(img.getPixels());
    fbo.readToPixels(pixels);
    bool success = schulzRecorder.vidRecorder.addFrame(pixels);
}

//--------------------------------------------------------------
void ofApp::draw(){
     ofSetWindowTitle("PROJECTOR 1 FPS="+ofToString(ofGetFrameRate()));
    fbo.begin();
    ofClear(255,255,255, 0);
    
    //
    // customShader.loadShadertoy("shadertoy/shadertoy4.frag",1,1,1,1);  // comment out when live coding not needed
    // enable when live coding needed
    
    customShader.begin();
    customShader.setShadertoyUniforms();
    
    customShader.setUniformTexture("iChannel0", movie.getTextureReference(), 1);
    customShader.setUniformTexture("iChannel1", camera.getTextureReference(), 2);
    
    ofPushMatrix();
    customShader.draw(0, 0);
    ofPopMatrix();
    
    customShader.end();
    
    // we just draw some circle on top of the video, to demonstrate that everything will be recroded
    ofPushMatrix();
    ofSetColor(255, 0, 255, 128);
    
    ofDrawCircle(1500, 500, 500);
    ofPopMatrix();
    
    fbo.end();
    
    ofPushMatrix();
    fbo.draw(0,0,1920, 1080);
    //fbo.draw(0,0);
    ofPopMatrix();
    
    schulzRecorder.draw();
    
   
   

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
schulzRecorder.keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
