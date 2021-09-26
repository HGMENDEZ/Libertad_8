#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 model1;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    TexCoords = aTexCoords;    
    gl_Position = projection * view * model1 * vec4(aPos, 1.0);
}