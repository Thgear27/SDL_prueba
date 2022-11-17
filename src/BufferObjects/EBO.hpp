#ifndef EBO_HPP
#define EBO_HPP

#include <glad/glad.h>
#include <iostream>

struct EBO {
    GLuint EBO_obj = 0;

    inline ~EBO() {
        if (EBO_obj != 0) {
            glDeleteBuffers(1, &EBO_obj);
            std::cout << "~EBO() called\n";
        }
    }

    inline void deleteBuffer() {
        if (EBO_obj != 0) {
            glDeleteBuffers(1, &EBO_obj);
        }
        EBO_obj = 0;
    }
    
    inline void genBuffer() {
        if (EBO_obj != 0) glDeleteBuffers(1, &EBO_obj);
        glGenBuffers(1, &EBO_obj);
    }

    inline void bindBuffer() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_obj);
    }

    inline void bufferData(GLsizeiptr size, void* data, GLenum usage) {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
    }

    inline void unBind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
};

#endif // EBO_HPP