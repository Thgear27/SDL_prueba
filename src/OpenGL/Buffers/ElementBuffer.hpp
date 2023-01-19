#ifndef ELEMENT_BUFFER_HPP
#define ELEMENT_BUFFER_HPP

#include <glad/glad.h>
#include <../GLerror.hpp>

class ElementBuffer {
public:
    ElementBuffer(const ElementBuffer&) = delete;
    ElementBuffer& operator=(const ElementBuffer&) = delete;

    ElementBuffer();
    ElementBuffer(GLsizeiptr size, const void* data, GLenum usage);
    ~ElementBuffer();

    void loadData(GLsizeiptr size, const void* data, GLenum usage);
    void bind();
    void unBind();
    void deleteBuffer();

    GLuint Id = 0;
};

#endif // ELEMENT_BUFFER_HPP