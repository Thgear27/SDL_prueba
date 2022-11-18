#version 330 core

layout (location = 0) in vec3 aPos;

out vec4 vertexColor; // output for the fragment shader

void main() {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vertexColor = vec4(aPos, 1.0);
}