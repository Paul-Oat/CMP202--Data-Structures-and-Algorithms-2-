#include "VertexBuffer.h"
#include "Debug.h"

//Generate vertex buffer instance 
VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    GLCall( glGenBuffers(1, &m_RendererID) );
    GLCall( glBindBuffer(GL_ARRAY_BUFFER, m_RendererID) );
    GLCall( glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW) );
}

//delete vertex buffer intance
VertexBuffer::~VertexBuffer()
{
    GLCall( glDeleteBuffers(1, &m_RendererID) );
}
//bind buffer
void VertexBuffer::Bind() const
{
    GLCall( glBindBuffer(GL_ARRAY_BUFFER, m_RendererID) );
}

//unbind buffer
void VertexBuffer::Unbind() const
{
    GLCall( glBindBuffer(GL_ARRAY_BUFFER, 0) );
}
