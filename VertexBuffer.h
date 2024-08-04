//program for cheching GL functions inspired by the cherno's OpenGL series
//https://www.youtube.com/watch?v=W3gAzLwfIP0&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2

#pragma once

class VertexBuffer
{
    private:
        unsigned int m_RendererID;

    public:
        VertexBuffer(const void* data, unsigned int size);
        ~VertexBuffer();

        void Bind() const;
        void Unbind() const;
};
