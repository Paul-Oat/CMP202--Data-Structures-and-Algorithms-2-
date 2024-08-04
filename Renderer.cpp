//program for cheching GL functions inspired by the cherno's OpenGL series
//https://www.youtube.com/watch?v=W3gAzLwfIP0&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2

#include "Renderer.h"
#include <iostream>

//clear buffer 
void Renderer::Clear() const
{
        GLCall( glClear( GL_COLOR_BUFFER_BIT ) );
}

//draw triangles and bind shader, vertwx array and indexbuffer 
void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
        shader.Bind();
        va.Bind();
        ib.Bind();
        GLCall( glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr) );
}

