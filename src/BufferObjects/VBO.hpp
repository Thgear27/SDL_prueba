#ifndef VBO_HPP
#define VBO_HPP

#include <glad/glad.h>
#include <iostream>

struct VBO {
    GLuint VBO_obj = 0;

    inline ~VBO() { 
        if (VBO_obj != 0) {
            glDeleteBuffers(1, &VBO_obj);
            std::cout << "VBO destroyed\n";
        }
    }

    inline void deleteBuffer() {
        if (VBO_obj != 0) {
            glDeleteBuffers(1, &VBO_obj);
            std::cout << "VBO destroyed\n";
        }
        VBO_obj = 0;
    }

    inline void genBuffer() {
        if (VBO_obj != 0) glDeleteBuffers(1, &VBO_obj);
        glGenBuffers(1, &VBO_obj);
        std::cout << "VBO created\n";
    }

    inline void bindBuffer() {
        glBindBuffer(GL_ARRAY_BUFFER, VBO_obj);
    }

    inline void bufferData(GLsizeiptr size, void* data, GLenum usage) {
        glBufferData(GL_ARRAY_BUFFER, size, data, usage);
    }

    inline void unBind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
};

#endif // VBO_HPP