#include "ElementBuffer.hpp"

ElementBuffer::ElementBuffer(GLsizeiptr size, const void* data, GLenum usage) {
    GLCall(glGenBuffers(1, &Id));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Id));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage));
}

ElementBuffer::ElementBuffer() {
    GLCall(glGenBuffers(1, &Id));
}

void ElementBuffer::loadData(GLsizeiptr size, const void* data, GLenum usage) {
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
}

ElementBuffer::~ElementBuffer() {
    if (Id != 0) glDeleteBuffers(1, &Id);
}

void ElementBuffer::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Id);
}

void ElementBuffer::unBind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ElementBuffer::deleteBuffer() {
    if (Id != 0) {
        glDeleteBuffers(1, &Id);
        Id = 0;
    }
}