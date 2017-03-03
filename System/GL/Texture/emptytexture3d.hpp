#pragma once
#include "abstracttexture.hpp"

class EmptyTexture3D : public AbstractTexture
{
public:
    EmptyTexture3D(GLenum target, GLenum internalFormat, GLsizei w, GLsizei h, GLsizei d, bool mipmap, bool linear);

    void clear(GLenum format, GLenum type);
};

