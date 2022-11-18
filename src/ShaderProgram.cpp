#include "ShaderProgram.hpp"
#include <stdexcept>
#include <iostream>
#include <fstream> 

ShaderProgram::ShaderProgram() {}

ShaderProgram::~ShaderProgram() {
    if (sp_id != 0) {
        glDeleteProgram(sp_id);
    }
}

void ShaderProgram::deleteProgram() {
    if (sp_id != 0) {
        glDeleteProgram(sp_id);
    }
    sp_id = 0;
}

void ShaderProgram::loadSource(const std::string& file_name, ShaderType type) {
    std::string source;
    std::ifstream input { file_name, std::ios::in };
    
    if (!input.is_open()) throw std::runtime_error("Unable to open the file: " + file_name);
    while(input.good()) {
        std::string temp;
        std::getline(input, temp, '\n');
        source += temp.append(1, '\n');
    }

    if (type == ShaderType::VERTEX)
        vertex_shader_source = source;
    if (type == ShaderType::FRAGMENT)
        fragment_shader_source = source;
}

void compileShader(GLuint shader) {
    glCompileShader(shader);
    char infoLog[512];
    int success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Fragment shader compilation failed:\n" << infoLog << '\n';
        throw std::runtime_error("Shader compilation failed");
    }
}

void linkShaderProgram(GLuint shader_program) {
    glLinkProgram(shader_program);
    char infoLog[512];
    int success;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_program, 512, nullptr, infoLog);
        std::cerr << "Unable to link the shader program:\n" << infoLog << '\n';
        throw std::runtime_error("Linked failed");
    }
}

void ShaderProgram::createShaderProgram() {
    GLuint vertex_shader   = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    const char* vertex_src_cstr   = vertex_shader_source.c_str();
    const char* fragment_src_cstr = fragment_shader_source.c_str();

    // Load the source to the shader object
    glShaderSource(vertex_shader, 1, &vertex_src_cstr, nullptr);
    glShaderSource(fragment_shader, 1, &fragment_src_cstr, nullptr);

    compileShader(vertex_shader);
    compileShader(fragment_shader);

    if (sp_id != 0) // True if shader program has been created
        glDeleteProgram(sp_id);

    sp_id = glCreateProgram();
    glAttachShader(sp_id, vertex_shader);
    glAttachShader(sp_id, fragment_shader);
    linkShaderProgram(sp_id);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

void ShaderProgram::useProgram() {
    glUseProgram(sp_id);
}
