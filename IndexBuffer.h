//program for cheching GL functions inspired by the cherno's OpenGL series
//https://www.youtube.com/watch?v=W3gAzLwfIP0&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2

#pragma once

class IndexBuffer
{
    private:
        unsigned int m_RendererID;
        unsigned int m_Count;

    public:
        IndexBuffer(const unsigned int* indices, unsigned int count);
        ~IndexBuffer();

        void Bind() const;
        void Unbind() const;

        inline unsigned int GetCount() const { return m_Count; }
};
