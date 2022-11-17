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
    }

    inline void deleteVAO() {
        if (VAO_obj != 0) {
            glDeleteBuffers(1, &VAO_obj);
        }
        VAO_obj = 0;
    }

    inline ~VAO() {
        if (VAO_obj != 0) {
            glDeleteBuffers(1, &VAO_obj);
            std::cout << "~VAO() called\n";
        }
    }

    inline void linkVBO(GLuint layout) {
        glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(layout);
    }
};

#endif // VAO_HPP