#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;
uniform vec2 u_Center;
uniform float u_Radius;

void main() 
{
    if (u_Radius < 0) {
        color = u_Color;
    } else {
        if (distance(gl_FragCoord.xy, vec2(u_Center)) > u_Radius)
            discard;
        else
            color = u_Color;
    }
}