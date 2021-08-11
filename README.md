# vRecShadFullHD

The project is aimed at three objectives:

1) To read, translate and display shaders written in shadertoy.com format. To use this capability we just need the myShaderClass from the project.

2) To manupulate prerecorded video, and / or connected cameras using above shaders. 

3) To be able to record the resulting shader stack output plus anything being drawn as part of the project into static video in Full HD, in decent visual quality using decent compression. 

Example of usage is below:

https://youtu.be/qpz_hBnN

To record a video in the application press R, to stop recording press R again.

To use my shadertoy shader translation class in your code:

In the C++ header file:

    myShaderClass customShader;

In the C++ .cpp file - setup:

    customShader.texture_to_textura(true); // this is to change texture handling to similar to shader toy 
    customShader.loadShadertoy("shadertoy/shadertoy4.frag",1,1,1,1);   // this is to load a shadertoy shader from specified path

In C++ .cpp file in the draw routine:

    customShader.begin();
    customShader.setShadertoyUniforms();
    
    customShader.setUniformTexture("iChannel0", movie.getTextureReference(), 1);
    customShader.setUniformTexture("iChannel1", camera.getTextureReference(), 2);
    
    ofPushMatrix();
    customShader.draw(0, 0);
    ofPopMatrix();
    
    customShader.end();

We just need one dependecy, the addon ofxVideoRecorder: https://github.com/timscaffidi/ofxVideoRecorder

Tested with openFrameworks 0.98.

The future development of the project would include a different type of a video-recorder with offline rendering, as such with capability to use heavy shaders and record video output without the limitation of the realtime framerate achievable on given CPU / GPU.
