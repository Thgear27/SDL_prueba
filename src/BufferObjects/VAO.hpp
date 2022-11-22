#ifndef VAO_HPP
#define VAO_HPP

#include <glad/glad.h>
#include <iostream>

struct VAO {
    GLuint VAO_obj = 0;

    inline void bind() {
        glBindVertexArray(VAO_obj);
    }

    inline void unBind() {
        glBindVertexArray(0);
    }

    inline void createVAO() {
        if (VAO_obj != 0) glDeleteBuffers(1, &VAO_obj);
        glGenVertexArrays(1, &VAO_obj);
        std::cout << "VAO created\n";
    }

    inline void deleteVAO() {
        if (VAO_obj != 0) {
            glDeleteBuffers(1, &VAO_obj);
            std::cout << "VAO destroyed\n";
        }
        VAO_obj = 0;
    }

    inline ~VAO() {
        if (VAO_obj != 0) {
            glDeleteBuffers(1, &VAO_obj);
            std::cout << "VAO destroyed\n";
        }
    }

    inline void linkVBO(GLuint layout, int size, GLenum type, GLboolean normalized, GLsizei stride, const void* data) {
        glVertexAttribPointer(layout, size, type, normalized, stride, data);
        glEnableVertexAttribArray(layout); // layout 0
    }
};

#endif // VAO_HPP