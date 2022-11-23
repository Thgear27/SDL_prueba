#ifndef VERTEX_BUFFER_HPP
#define VERTEX_BUFFER_HPP

#include <glad/glad.h>

#include <vector>

class VertexBuffer {
private:
    struct VertexAttribLayout{
        GLuint type;
        GLuint normalized;
        GLuint count;
    };

public:
    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;

    VertexBuffer(GLsizeiptr size, const void* data, GLenum usage);
    VertexBuffer();
    ~VertexBuffer();

    void loadData(GLsizeiptr size, const void* data, GLenum usage);
    int getTypeSize(GLuint type);
    void setVertexAttribCount(int count);
    void push_VertexAttribLayout(GLuint type, GLuint normalized, GLuint count);
    void bind();
    void unBind();
    void deleteBuffer();

    GLuint Id = 0;
    int m_stride;
    int m_vertexAttribCount;
    std::vector<VertexAttribLayout> m_AttribsLayouts;
};

#endif // VERTEX_BUFFER_HPP