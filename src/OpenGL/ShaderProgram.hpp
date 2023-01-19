#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <glad/glad.h>
#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct ShaderProgram {
    GLuint Id = 0;

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

    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);
    void setMat4(const std::string& name, glm::mat4& matPtr);

    ShaderProgram();
    ~ShaderProgram();
};

#endif // SHADERPROGRAM_HPP