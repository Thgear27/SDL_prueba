#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec4 vertexPosition;
out vec3 ourVertexColor; // output for the fragment shader

void main() {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vertexPosition = vec4(aPos, 1.0);
    ourVertexColor = aColor;
}