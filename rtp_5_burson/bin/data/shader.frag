uniform sampler2DRect sourceImg;
uniform sampler2DRect targetImg;
uniform vec2 mouse;
uniform vec2 screen;
varying vec2 texCoord;

void main()
{

    vec2 pos = gl_FragCoord.xy;
    pos.y = 480. - pos.y;
    pos.x -= 300.; // not sure why this is needed...
    vec3 sourceColor = texture2DRect(sourceImg, pos).rgb;
    vec3 targetColor = texture2DRect(targetImg, texCoord).rgb;
    vec3 color = mix(sourceColor, targetColor, clamp(mouse.x / screen.x, 0., 1.));
    
    gl_FragColor = vec4(color, 1.0);
}
