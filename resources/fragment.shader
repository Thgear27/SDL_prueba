#version 330 core

out vec4 fragcolor;
uniform vec4 ourColor;

void main() { 
    // fragcolor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    fragcolor = ourColor;
}