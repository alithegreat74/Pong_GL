#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoords;

out vec2 TexCoords;
out vec4 ParticleColor;

uniform vec2 offset;
uniform vec4 color;
uniform vec2 scale;
void main()
{
    
    TexCoords = texCoords;
    ParticleColor = color;
    gl_Position =  vec4((position * scale) + offset, 0.0, 1.0);
}