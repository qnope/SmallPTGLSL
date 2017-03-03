#pragma once
#include "abstracttexture.hpp"

class EmptyTexture2D : public AbstractTexture
{
public:
    EmptyTexture2D(unsigned width, unsigned height, GLenum internalFormat, bool linear);
};
