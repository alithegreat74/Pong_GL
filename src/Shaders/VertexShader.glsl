#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 texCoords;

uniform mat4 transform;

uniform float shakeStrength;
uniform bool shake;
uniform float time;

void main()
{
    gl_Position = transform * vec4(aPos,0.0, 1.0);
    texCoords=aTexCoords;

    if (shake)
    {
        gl_Position.x += cos(time * 10) * shakeStrength;        
        gl_Position.y += cos(time * 15) * shakeStrength;        
    }
}