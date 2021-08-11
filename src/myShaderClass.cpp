//
//  myShaderClass.cpp
//  inheritanceAgain
//
//  Created by Pawel Dziadur on 15/10/2017.
//
//

#include "myShaderClass.hpp"

//
// usage:
//
// in header
//
// myShaderClass s; ofPlanePrimitive plane;
//
// in setup
//
// s.loadShadertoy("myShadertoyCodeCopiedFromShadertoy.com",0,0,0,0);
//
// in draw
//
// s.begin(); s.setShadertoyUniforms();
// s.setTexture("iChannel0", img, 1); s.setTexture("iChannel0", img, 2); s.setTexture("iChannel0", img, 3); s.setTexture("iChannel0", img, 4);

// draw....
// s.end;

bool myShaderClass::loadShadertoy(string shaderfilename,  int chan0samplerOption, int chan1samplerOption, int chan2samplerOption, int chan3samplerOption)
{
    
    samplerOptions.reserve(4);
    samplerOptions[0]=chan0samplerOption;
    samplerOptions[1]=chan1samplerOption;
    samplerOptions[2]=chan2samplerOption;
    samplerOptions[3]=chan3samplerOption;
    
    string vertprogram = string("#version 330\n"
                                "precision mediump float;\n"
                                "uniform mat4 modelViewProjectionMatrix;\n"
                                "uniform mat4 tCameraMatrix;\n"
                                "in vec4 position;\n\n"
                                "void main(){"
                                " gl_Position = modelViewProjectionMatrix * position;"
                                " }");
    
    setupShaderFromSource(GL_VERTEX_SHADER, vertprogram);

    ofFile f;
    f.open(shaderfilename);
    ofBuffer b = f.readToBuffer();
    
    string codeToUndergoReplacementOf_texture_to_custom_command = b.getText();
    using Poco::RegularExpression;
   
    // only if protected variable performRegexp is set to true we will tamper with the text content
    // of the original code (our fragprogram from shadertoy beta website), rather then pasting into
    // central part of our shader we generate directly
    if (performRegexp)
    {
        RegularExpression re1("([t][e][x][t][u][r][e][\(])");
        int nOccurances; // this variable will tell us how many occurances of 'texture(' is in the code
        string s; // work string
    
        // line below uses regular expression to count the number of occurnces of exact word
        nOccurances = re1.extract(codeToUndergoReplacementOf_texture_to_custom_command, s);
        cout << " nOccurances = re1.extract(codeToUndergoReplacementOf_texture_to_custom_command, s); nOccurances==" << nOccurances << " " << s << endl;
    
        // if there are any occurances then replace them with our own function textura, which will work
        // exactly like texture in shader toy beta
            if (nOccurances > 0)
            {
                // the first argument is the string which undergoes an algorithm of it's chunks being replaced accoring to our re1 regexp formula, 2nd argument is the string that will replace the chunks of text matched by the re1 regexp formula (in this it will change all 'texture(' to 'textura('
                // the 3rd argument RegularExpression::RE_GLOBAL is needed because if it was not there only the first occurance of 'texture(' would be replaced to 'textura(' and this way we replace all
                re1.subst(codeToUndergoReplacementOf_texture_to_custom_command, "textura(", RegularExpression::RE_GLOBAL);
            }
        
        cout << "replaced code below:" << endl;
        cout << codeToUndergoReplacementOf_texture_to_custom_command << endl;
    }
    
    string fragprogram =
    string("#version 330\n"
           "precision mediump float;\n"
           "vec4 textura(sampler2DRect tex, vec2 coords) { vec2 bigUV = (vec2(0.0, 1.0) - vec2(coords.x, coords.y)) * textureSize(tex); bigUV = mod(bigUV,textureSize(tex)); return texture(tex, bigUV); }\n"
           "vec4 textura(sampler2D tex, vec2 coords) { vec2 smallUV = (vec2(0.0, 1.0) - vec2(coords.x, coords.y)); return texture(tex, mod(smallUV,vec2(1.0,1.0))); }\n"
           "vec4 myTexture(sampler2DRect tex, vec2 coords) { vec2 bigUV = (vec2(0.0, 1.0) - vec2(coords.x, coords.y)) * textureSize(tex); bigUV = mod(bigUV,textureSize(tex)); return texture(tex, bigUV); }\n"
           "vec4 myTexture(sampler2D tex, vec2 coords) { vec2 smallUV = (vec2(0.0, 1.0) - vec2(coords.x, coords.y)); return texture(tex, mod(smallUV,vec2(1.0,1.0))); }\n"
           "vec4 texture2D(sampler2DRect tex, vec2 coords) { return texture(tex, coords*512.0+vec2(512,-512)); }\n"
           "vec4 texture2D(sampler2D tex, vec2 coords) { return texture(tex, coords.xy); }\n"
           "#define texture2DCube texture\n"
           "uniform vec3      iResolution;\n"
           "uniform float     iGlobalTime;\n"
           "uniform float     iTime;\n"
           "uniform int       iFrame;\n"
           "uniform float     iChannelTime[4];\n"
           "uniform vec4      iMouse;\n"
           "uniform vec4      iDate;\n"
           "uniform float     iSampleRate;\n"
           "uniform vec3      iChannelResolution[4];\n"
           "uniform mat4      tCameraMatrix;\n")+ getSamplerOptionsUniformLines() + "\n" +
        codeToUndergoReplacementOf_texture_to_custom_command +
    string("\nout vec4 FragColor;\n"
           "void main( void )\n"
           "{\n"
           "vec4 color = vec4(0.0,0.0,0.0,1.0);\n"
           "mainImage( color, gl_FragCoord.xy );\n"
           "color.w = 1.0;\n"
           "FragColor = color;\n"
           "}");
    
    // let's print out what we have, both generated VERTPROGRAM and FRAGPROGRAM to the console
    cout << "//[pawel here myShaderClass VERTPROGRAM BELOW ****************]" << endl;
    cout << vertprogram << endl;
    cout << "//[pawel here myShaderClass VERTPROGRAM END ******************]\n" << endl;
   
    cout << "//[pawel here myShaderClass FRAGPROGRAM BELOW ****************]" << endl;
    cout << "//[shaderfilename: " << shaderfilename << " ]" << endl;
    cout <<  "//[absolute: " << string(ofToDataPath(shaderfilename, true)) << " ]" << endl;
    cout << fragprogram << endl;
    cout << "//[pawel here myShaderClass FRAGPROGRAM END ******************]\n" << endl;
    
    if(!setupShaderFromSource(GL_FRAGMENT_SHADER, fragprogram)) {
        ofLogError("shader") << "error loading shader";
        return false;
    } else {
        if(linkProgram()) {
            bindDefaults();
            setUniform1f("iGlobalTime", ofGetElapsedTimef());
            setUniform1f("iTime", ofGetElapsedTimef());
            setUniform4f("iMouse", mousepos.x, mousepos.y, ofGetMousePressed()?1:0, 0);
            dimensions.set(ofGetWindowWidth(), ofGetWindowHeight());
            setUniform3f("iResolution", dimensions.x, dimensions.y, 4.0f);
            setUniform4f("iDate", ofGetYear(), ofGetMonth(), ofGetDay(), ((ofGetHours()*60+ofGetMinutes())*60)+ofGetSeconds());
            setUniformMatrix4f("tCameraMatrix", ofMatrix4x4::newIdentityMatrix());
          //  shader = currentShader;
            return true;
        } else {
            ofLogError("shader") << "did not link";
            return false;
        }
    }
 //   load(shaderfilename);
}

string myShaderClass::getSamplerOptionUniformLine(int iChannel, int option)
{
    string myOption;
    myOption = "sampler2D"; // the default one, in case there was sth wrong with functin args
    
    if (option == 0)
    {
        myOption = "sampler2D";
    }
    if (option == 1)
    {
        myOption = "sampler2DRect";
    }
    if (option == 2)
    {
        myOption = "sampler2DCube";
    }
    
    return string("uniform " + myOption + " iChannel" + ofToString(iChannel) + ";\n");
}

string myShaderClass::getSamplerOptionsUniformLines()
{
    string fourUniformLines;
    
    for (int iChannel = 0; iChannel < 4; iChannel++)
    {
        fourUniformLines += getSamplerOptionUniformLine(iChannel, samplerOptions[iChannel]);
    }
    
    return fourUniformLines;
}

void myShaderClass::setShadertoyUniforms() const
{
//    globalTime = ofGetElapsedTimef();
//    cout << "global time = " << globalTime << endl;
    
    setUniform1f("iGlobalTime", ofGetElapsedTimef());
    setUniform1f("iTime", ofGetElapsedTimef());
    
  //  setUniform1f("iGlobalTime", globalTime); // orignal lines
  //  setUniform1f("iTime", globalTime);
    setUniform4f("iMouse", mousepos.x, mousepos.y, ofGetMousePressed()?1:0, 0);
    setUniform3f("iResolution", dimensions.x, dimensions.y, 4.0f);
    setUniform4f("iDate", ofGetYear(), ofGetMonth(), ofGetDay(), ((ofGetHours()*60+ofGetMinutes())*60)+ofGetSeconds());
    if(camera) {
        ofMatrix4x4 cmtx(camera->getOrientationQuat());
        cmtx.setTranslation(-camera->getPosition());
        setUniformMatrix4f("tCameraMatrix", cmtx);
    } else {
        setUniformMatrix4f("tCameraMatrix", ofMatrix4x4::newIdentityMatrix());
    }
}

void myShaderClass::draw(float x, float y, float z, float w, float h) const {
   // begin();
    ofDrawRectangle(x, y, z, w, h);
   // end();
}

void myShaderClass::texture_to_textura(bool choice) { performRegexp = choice; }
