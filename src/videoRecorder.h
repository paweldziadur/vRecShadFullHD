//
//  videoRecorder.h
//  ofxVideoRecorderExample_ROI
//
//  Created by Stephan Schulz on 2016-04-15.
//  and corrected by Pawel Dziadur on 2019-08-06
//

/*
 install homebrew via http://brew.sh
 then install ffmpeg via terminal command: brew install ffmpeg
  make sure folder name or app name have no spaces
 */

#ifndef ofxVideoRecorderExample_ROI_videoRecorder_h
#define ofxVideoRecorderExample_ROI_videoRecorder_h

#include "ofxVideoRecorder.h"

class videoRecorder{
    
public:
    ofxVideoRecorder    vidRecorder;
    ofSoundStream       soundStream;
//    ofImage img;
    bool bRecording;
    int sampleRate;
    int channels;
    string fileName;
    string fileExt;
    
    int frameCount;
    
    ofFbo recordFbo;
    ofPixels recordPixels;
    
    int roiWidth, roiHeight;
    
    void setOutputResolution(int w, int h)
    {
        roiWidth = w;
        roiHeight = h;
    }

    void setup(){
       // roiWidth=1280; roiHeight=720;
        
        // if the outoput resolution had not been set before setup was run
        // set it to FULL HD
        if (roiWidth < 1 && roiHeight < 1)
        {
            roiWidth=1920; roiHeight=1080;
        }
        
        ofLog()<<"output resolution: " << roiWidth << " " << roiHeight;
         ofLog()<<"----------ffmpeg----------------";
        ofLog()<<"for recording to work:  install homebrew via http://brew.sh. /nthen install ffmpeg via terminal command: brew install ffmpeg /nmake sure folder name or app name have no spaces";
ofLog()<<"--------------------------------";
        
        sampleRate = 44100;
        channels = 2;
       // vidRecorder.setFfmpegLocation(ofFilePath::getAbsolutePath("ffmpeg")); // use this is you have ffmpeg installed in your data folder
        
        fileName = "testMovie";
        fileExt = ".mov"; // ffmpeg uses the extension to determine the container type. run 'ffmpeg -formats' to see supported formats
        
        // override the default codecs if you like
        // run 'ffmpeg -codecs' to find out what your implementation supports (or -formats on some older versions)
      //  vidRecorder.setVideoCodec("mpeg4");
       // vidRecorder.setVideoCodec("h264");
        // vidRecorder.setVideoCodec("prores_ks"); // 4444 high quality
       vidRecorder.setVideoCodec("prores"); // apcs
   //     vidRecorder.setVideoCodec("apcs"); // this is probably wrong
        
        vidRecorder.setVideoBitrate("50000k");  // original was actually 800k
//        vidRecorder.setAudioCodec("mp3");
//        vidRecorder.setAudioBitrate("192k");
        
        ofAddListener(vidRecorder.outputFileCompleteEvent, this, &videoRecorder::recordingComplete);
        
            soundStream.listDevices();
        //    soundStream.setDeviceID(11);
        //    soundStream.setup(this, 0, channels, sampleRate, 256, 4);
        
        //    ofSetWindowShape(vidGrabber.getWidth(), vidGrabber.getHeight()	);
        bRecording = false;
        frameCount = 0;
    }
    
    void update(ofImage &img){
        
//        roiWidth = img.getWidth();
//        roiHeight = img.getHeight();
        if(bRecording){
            
            bool success = vidRecorder.addFrame(img.getPixels());
            if (!success) {
                ofLogWarning("This frame via img was not added!");
            }else{
                 frameCount++;
            }
        }

    }
    void update(ofPixels &pix){
        
//        roiWidth = pix.getWidth();
//        roiHeight = img.getHeight();
        if(bRecording){
            
            bool success = vidRecorder.addFrame(pix);
            if (!success) {
                ofLogWarning("This frame via pix was not added!");
            }else{
                frameCount++;
            }
        }
        
    }
    
    
    void errorCheck(){
        // Check if the video recorder encountered any error while writing video frame or audio smaples.
        if (vidRecorder.hasVideoError()) {
            ofLogWarning("The video recorder failed to write some frames!");
        }
        
        if (vidRecorder.hasAudioError()) {
            ofLogWarning("The video recorder failed to write some audio samples!");
        }
    }
    
    void draw(){
        /*
        stringstream ss;
        ss << "video queue size: " << vidRecorder.getVideoQueueSize() << endl
        << "audio queue size: " << vidRecorder.getAudioQueueSize() << endl
        << "FPS: " << ofGetFrameRate() << endl
        << (bRecording?"pause":"start") << " recording: r" << endl
        << (bRecording?"close current video file: c":"") << endl;
        
        ofSetColor(0,0,0,100);
        ofDrawRectangle(0, 0, 260, 75);
        ofSetColor(255, 255, 255);
        ofDrawBitmapString(ss.str(),15,15);
        */
        ofPushStyle();
        if(bRecording){
            ofSetColor(255, 0, 0);
            ofDrawCircle(15, 15, 10);
        }
        ofPopStyle();

    }

    //--------------------------------------------------------------
    void audioIn(float *input, int bufferSize, int nChannels){
        if(bRecording)
            vidRecorder.addAudioSamples(input, bufferSize, nChannels);
    }
    
    //--------------------------------------------------------------
    void recordingComplete(ofxVideoRecorderOutputFileCompleteEventArgs& args){
        cout << "The recoded video file is now complete." << endl;
    }
    
    void exit(){
        ofRemoveListener(vidRecorder.outputFileCompleteEvent, this, &videoRecorder::recordingComplete);
        vidRecorder.close();
    }
    
    void stop(){
         bRecording = false;
//        if(vidRecorder.isInitialized()){
         vidRecorder.close();
             ofLogNotice("videoRecorder")<<"stop";
//        }
       frameCount = 0;
    }
    
    void start(string _name,int _w,int _h){
        if(!vidRecorder.isInitialized()){
            bRecording = true;
            vidRecorder.setup(_name+fileExt,_w,_h, 24);
            vidRecorder.start();
            
             ofLogNotice("videoRecorder")<<"start";
            frameCount = 0;

        }
    }
    
    //--------------------------------------------------------------
    void keyReleased(int key){

        if(key=='r'){
            bRecording = !bRecording;
            if(bRecording && !vidRecorder.isInitialized()) {
                //            vidRecorder.setup(fileName+ofGetTimestampString()+fileExt, roiWidth, roiHeight, 30, sampleRate, channels);
                vidRecorder.setup(fileName+ofGetTimestampString()+fileExt,roiWidth, roiHeight, 30); // no audio
                //            vidRecorder.setup(fileName+ofGetTimestampString()+fileExt, 0,0,0, sampleRate, channels); // no video
                //          vidRecorder.setupCustomOutput(vidGrabber.getWidth(), vidGrabber.getHeight(), 30, sampleRate, channels, "-vcodec mpeg4 -b 1600k -acodec mp2 -ab 128k -f mpegts udp://localhost:1234"); // for custom ffmpeg output string (streaming, etc)
                
                // Start recording
                vidRecorder.start();
            }
            else if(!bRecording && vidRecorder.isInitialized()) {
                vidRecorder.setPaused(true);
            }
            else if(bRecording && vidRecorder.isInitialized()) {
                vidRecorder.setPaused(false);
            }
        }
        if(key=='c'){
            bRecording = false;
            vidRecorder.close();
        }
 
    }

    
};
#endif
