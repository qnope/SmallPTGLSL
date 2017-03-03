#include "emptytexture2d.hpp"

EmptyTexture2D::EmptyTexture2D(unsigned width, unsigned height, GLenum internalFormat, bool linear) :
    AbstractTexture(GL_TEXTURE_2D, false, linear, width, height)
{
    glTextureParameteri(mId, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(mId, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTextureStorage2D(mId, 1, internalFormat, width, height);
}
