#ifndef VERTEX_ARRAY_HPP
#define VERTEX_ARRAY_HPP

#include "VertexBuffer.hpp"
#include "ElementBuffer.hpp"
#include <glad/glad.h>

class VertexArray {
public:
    VertexArray() = delete;
    VertexArray(const VertexArray&) = delete;
    VertexArray& operator=(const VertexArray&) = delete;

    VertexArray(VertexBuffer& vbo, ElementBuffer& ebo);
    ~VertexArray();

    void bind();
    void unBind();
    void deleteVertexArray();
    void linkBuffers();

    GLuint Id = 0;

    VertexBuffer& m_vbo;
    ElementBuffer& m_ebo;
};

#endif // VERTEX_ARRAY_HPP