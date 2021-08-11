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
