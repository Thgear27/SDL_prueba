#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec4 vertexPosition;
out vec3 ourVertexColor; // output for the fragment shader
out vec2 ourTexCoord;

void main() {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vertexPosition = vec4(aPos, 1.0);
    ourVertexColor = aColor;
    ourTexCoord = aTexCoord;
}