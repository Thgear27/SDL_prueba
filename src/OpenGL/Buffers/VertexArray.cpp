#include "VertexArray.hpp"

VertexArray::VertexArray(VertexBuffer* vbo, ElementBuffer* ebo) :
    m_vbo(vbo), m_ebo(ebo)
{
    glGenVertexArrays(1, &Id);
} 

VertexArray::VertexArray() {
    glGenVertexArrays(1, &Id);
}

VertexArray::~VertexArray() {
    if (Id != 0) glDeleteVertexArrays(1, &Id);
}

void VertexArray::linkBuffers() {
    glBindVertexArray(Id);
    m_vbo->bind();
    m_ebo->bind();

    int offset = 0;
    for (int i = 0; i < m_vbo->m_vertexAttribCount; i++) {
        glVertexAttribPointer(
            i, 
            m_vbo->m_AttribsLayouts[i].count,
            m_vbo->m_AttribsLayouts[i].type,
            m_vbo->m_AttribsLayouts[i].normalized,
            m_vbo->m_stride,
            (const void*)(std::size_t)(offset)
        );
        glEnableVertexAttribArray(i);
        offset += m_vbo->m_AttribsLayouts[i].count * m_vbo->getTypeSize(m_vbo->m_AttribsLayouts[i].type);
    }
    glBindVertexArray(0);
}

void VertexArray::deleteVertexArray() {
    if (Id != 0) {
        glDeleteVertexArrays(1, &Id);
        Id = 0;
    }
}

void VertexArray::addVertexBuffer(VertexBuffer* vbo_ptr) {
    m_vbo = vbo_ptr;
}

void VertexArray::addElementBuffer(ElementBuffer* ebo_ptr) {
    m_ebo = ebo_ptr;
}

void VertexArray::bind() {
    glBindVertexArray(Id);
}

void VertexArray::unBind() {
    glBindVertexArray(0);
}