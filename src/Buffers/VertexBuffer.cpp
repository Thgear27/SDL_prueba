#include "VertexBuffer.hpp"
#include <stdexcept>

VertexBuffer::VertexBuffer(GLsizeiptr size, const void* data, GLenum usage) {
    glGenBuffers(1, &Id);
    glBindBuffer(GL_ARRAY_BUFFER, Id);
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
    m_stride = 0;
}

VertexBuffer::VertexBuffer() {
    glGenBuffers(1, &Id);
    m_stride = 0;
}

void VertexBuffer::loadData(GLsizeiptr size, const void* data, GLenum usage) {
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

VertexBuffer::~VertexBuffer() {
    if (Id != 0) glDeleteBuffers(1, &Id);
}

void VertexBuffer::deleteBuffer() {
    if (Id != 0) {
        glDeleteBuffers(1, &Id);
        Id = 0;
    } 
}

int VertexBuffer::getTypeSize(GLuint type) {
    if (type == GL_FLOAT)
        return sizeof(float);
    if (type == GL_UNSIGNED_BYTE)
        return sizeof(unsigned char);
    if (type == GL_UNSIGNED_INT)
        return sizeof(unsigned int);
    throw std::runtime_error("Cannot recognize GLtype in function VertexBuffer::getTypeSize()");
}

void VertexBuffer::setVertexAttribCount(int count) {
    m_vertexAttribCount = count;
    m_AttribsLayouts.reserve(count);
}

void VertexBuffer::push_VertexAttribLayout(GLuint type, GLuint normalized, GLuint count) {
    m_AttribsLayouts.push_back({ type, normalized, count });
    m_stride += count * getTypeSize(type);
    m_vertexAttribCount++;
}

void VertexBuffer::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, Id);
}

void VertexBuffer::unBind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}