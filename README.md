# vRecShadFullHD

The project is aimed at three objectives:

To read, translate and display shaders written in shadertoy.com format 

To manupulate prerecorded video, and / or connected cameras using above shaders 

To be able to record the output into static video in Full HD, in decent visual quality using decent compression 

Example of usage is below:

https://youtu.be/qpz_hBnN

To record a video in the application press R, to stop recording press R again

To use my shadertoy shader translation class in your code:

In header:

    myShaderClass customShader;

In cpp file:

    customShader.texture_to_textura(true); // this is to change texture handling to similar to shader toy 
    customShader.loadShadertoy("shadertoy/shadertoy4.frag",1,1,1,1);   // this is to load a shadertoy shader from specified path

In cpp file in the draw routine:

    customShader.begin();
    customShader.setShadertoyUniforms();
    
    customShader.setUniformTexture("iChannel0", movie.getTextureReference(), 1);
    customShader.setUniformTexture("iChannel1", camera.getTextureReference(), 2);
    
    ofPushMatrix();
    customShader.draw(0, 0);
    ofPopMatrix();
    
    customShader.end();
