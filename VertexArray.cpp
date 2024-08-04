//program for cheching GL functions inspired by the cherno's OpenGL series
//https://www.youtube.com/watch?v=W3gAzLwfIP0&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2

#include "VertexArray.h"
#include "Debug.h"

//generate a vertex array 
VertexArray::VertexArray()
{
    GLCall( glGenVertexArrays(1, &m_RendererID) );
}
//Destry vertex array 
VertexArray::~VertexArray()
{
    GLCall( glDeleteVertexArrays(1, &m_RendererID) );
}
//add buffer 
void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    Bind();
    vb.Bind();
    const std::vector<VertexBufferElement> elements = layout.GetElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size() ; i++)
    {
        const VertexBufferElement element = elements[i];
        GLCall( glEnableVertexAttribArray(i) );
        GLCall( glVertexAttribPointer(i, element.count, element.type, element.normalized,
                                      layout.GetStride(), INT2VOIDP(offset)) );
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
}
//bind buffer 
void VertexArray::Bind() const
{
    GLCall( glBindVertexArray(m_RendererID) );
}
//unbind buffer
void VertexArray::Unbind() const
{
    GLCall( glBindVertexArray(0) );
};
