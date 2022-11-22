#version 330 core

out vec4 fragcolor;

in vec4 vertexPosition;
in vec3 ourVertexColor; // input from the vertex shader
in vec2 ourTexCoord;

uniform sampler2D ourTexture;

void main() { 
    // fragcolor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    // fragcolor = vec4(vertexPosition);
    fragcolor = texture(ourTexture, ourTexCoord) * vec4(ourVertexColor, 1.0);
}