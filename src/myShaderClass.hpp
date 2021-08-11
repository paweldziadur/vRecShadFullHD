//
//  myShaderClass.hpp
//  inheritanceAgain
//
//  Created by Pawel Dziadur on 15/10/2017.
//
//

#ifndef myShaderClass_hpp
#define myShaderClass_hpp

#include <stdio.h>
#include "Poco/RegularExpression.h"
#include <stdio.h>
#include "ofMain.h"
class myShaderClass : public ofShader{
    
protected:
    
    bool useMouse, advanceTime, performRegexp;
    ofVec2f mousepos;
    ofVec2f dimensions;
    ofCamera *camera;
    double globalTime;
    vector <int> samplerOptions;
    
public:
    //your new methods
    bool loadShadertoy(string shaderfilename,  int chan0samplerOption, int chan1samplerOption, int chan2samplerOption, int chan3samplerOption);
    void setShadertoyUniforms() const;
    string getSamplerOptionUniformLine(int iChannel, int option);
    string getSamplerOptionsUniformLines();
    
    void draw(float x, float y) const { draw(x, y, 0, dimensions.x, dimensions.y); }
    void draw(float x, float y, float w, float h) const { draw(x, y, 0, w, h); }
    void draw(float x, float y, float z, float w, float h) const;
    float getWidth() const { return dimensions.x; }
    float getHeight() const { return dimensions.y; }
    void setWidth(float w) { dimensions.x = w; }
    void setHeight(float h) { dimensions.y = h; }
    void texture_to_textura(bool choice);// { performRegexp = choice; }
    
    //and your overiden functions here
};

#endif /* myShaderClass_hpp */
