#version 330 core

layout (location = 0) in vec3 aPos;
// layout (location = 1) in vec3 aColor;
layout (location = 1) in vec2 aTexCoord;

out vec3 ourVertexColor; // output for the fragment shader
out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    // gl_Position = model * view * projection * vec4(aPos, 1.0);
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    // ourVertexColor = aColor;
    texCoord = aTexCoord;
}