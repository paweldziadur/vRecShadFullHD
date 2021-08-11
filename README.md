# vRecShadFullHD

The project is aimed at three objectives:

1) To read, translate and display shaders written in shadertoy.com format. To use this capability we just need the myShaderClass from the project.

2) To manupulate prerecorded video, and / or connected cameras using above shaders. 

3) To be able to record the resulting shader stack output plus anything being drawn as part of the project into static video in Full HD, in decent visual quality using decent compression: to record a video in the application press R, to stop recording press R again.

Example of usage is below:

https://youtu.be/qpz_hBnN

The above example shows a video being manipulated and then recorded with the following shadertoy.com format shader:

    void mainImage( out vec4 fragColor, in vec2 fragCoord )
    {
        // Normalized pixel coordinates (from 0 to 1)
        vec2 uv = fragCoord/iResolution.xy;

        uv.y += sin(uv.y + (iTime * 1.5)) * 0.26;

        uv.x += sin(uv.y + (iTime * 0.5)) * 0.16;

        vec2 shift;

        shift.x = abs(sin(cos(iTime+32.*uv.y)*22.*uv.x+iTime));
        shift.y = abs(cos(sin(iTime+22.*uv.x)*33.*uv.y+iTime));

        uv += (shift * 0.03);

        vec4 col = texture(iChannel0, uv);

        // Output to screen
        fragColor = vec4(col);

        // We deform the texture of the video with a few triginometric functions using time as input
        // Shadertoy format code (that would work on the shadertoy.com website)
        // by Pawel Dziadur, 2019
    }


Below is explanation how to use my shadertoy shader translation class in your code:

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
