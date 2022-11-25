#version 330 core

out vec4 fragcolor;

in vec3 ourVertexColor; // input from the vertex shader
in vec2 texCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float si;

void main() { 
    // fragcolor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    // fragcolor = vec4(ourVertexColor, 1.0f);
    // fragcolor = texture(texture2, texCoord);
    fragcolor = mix(texture(texture1, texCoord), texture(texture2, texCoord), si);
}