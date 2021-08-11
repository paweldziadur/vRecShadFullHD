void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = fragCoord/iResolution.xy;
    
    vec4 col = texture(iChannel1, uv);
    
    // Output to screen
    fragColor = vec4(col);
    
    // We just show the texture using iChannel1 as is
    // Shadertoy format code (that would work on the shadertoy.com website)
    // by Pawel Dziadur, 2019
}
