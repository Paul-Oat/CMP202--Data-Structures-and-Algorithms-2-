//program for cheching GL functions inspired by the cherno's OpenGL series
//https://www.youtube.com/watch?v=W3gAzLwfIP0&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2

#pragma once

#include <GL/glew.h>

#include "Debug.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer
{
    public:
        void Clear() const;
        void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};
