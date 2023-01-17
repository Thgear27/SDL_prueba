#ifndef VERTEX_ARRAY_HPP
#define VERTEX_ARRAY_HPP

#include "VertexBuffer.hpp"
#include "ElementBuffer.hpp"
#include <glad/glad.h>

class VertexArray {
public:
    VertexArray(const VertexArray&) = delete;
    VertexArray& operator=(const VertexArray&) = delete;

    VertexArray(VertexBuffer* vbo, ElementBuffer* ebo);
    VertexArray();
    ~VertexArray();

    void bind();
    void unBind();
    void deleteVertexArray();
    void addVertexBuffer(VertexBuffer* vbo_ptr);
    void addElementBuffer(ElementBuffer* ebo_ptr);
    void linkBuffers();

    GLuint Id = 0;

    VertexBuffer* m_vbo = nullptr;
    ElementBuffer* m_ebo = nullptr;
};

#endif // VERTEX_ARRAY_HPP