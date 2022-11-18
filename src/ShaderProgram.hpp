#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <glad/glad.h>
#include <string>

struct ShaderProgram {
    GLuint sp_id = 0;

    std::string vertex_shader_source;
    std::string fragment_shader_source;

    enum ShaderType {
        FRAGMENT,
        VERTEX
    };

    void loadSource(const std::string& file_name, ShaderType type);
    void createShaderProgram();
    void useProgram();
    void deleteProgram();

    ShaderProgram();
    ~ShaderProgram();
};

#endif // SHADERPROGRAM_HPP