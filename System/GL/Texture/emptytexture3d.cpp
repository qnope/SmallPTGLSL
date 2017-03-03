#include "emptytexture3d.hpp"
#include "System/tools.hpp"
#include <vector>

EmptyTexture3D::EmptyTexture3D(GLenum target, GLenum internalFormat, GLsizei w, GLsizei h, GLsizei d, bool mipmap, bool linear) :
AbstractTexture(target, mipmap, linear, w, h, d) {
    GLsizei levels = std::log2(max(w, h, d)) + 1;

    glTextureStorage3D(mId, levels, internalFormat, w, h, d);
    glTextureParameteri(mId, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(mId, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTextureParameteri(mId, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void EmptyTexture3D::clear(GLenum format, GLenum type) {
    glClearTexImage(mId, 0, format, type, nullptr);
}
