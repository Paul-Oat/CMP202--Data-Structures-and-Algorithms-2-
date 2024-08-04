//program for cheching GL functions inspired by the cherno's OpenGL series
//https://www.youtube.com/watch?v=W3gAzLwfIP0&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2

#include "IndexBuffer.h"
#include "Debug.h"


//Generate and bind buffers
IndexBuffer::IndexBuffer(const unsigned int* indices, unsigned int count)
  :
    m_Count(count)
{
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    GLCall( glGenBuffers(1, &m_RendererID) );
    GLCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID) );
    GLCall( glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW) );
}

//delete buffers 
IndexBuffer::~IndexBuffer()
{
    GLCall( glDeleteBuffers(1, &m_RendererID) );
}

//bind buffer
void IndexBuffer::Bind() const
{
    GLCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID) );
}

//unbind buffer  
void IndexBuffer::Unbind() const
{
    GLCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) );
}
