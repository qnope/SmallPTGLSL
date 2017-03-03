#include <cassert>
#include "abstracttexture.hpp"

AbstractTexture::AbstractTexture(GLenum target, bool mipmap, bool linear, GLuint w, GLuint h, GLuint d) : mMipmap(mipmap),
    mW(w), mH(h), mD(d){
    glCreateTextures(target, 1, &mId);

    if(linear) {
        if(mipmap)
            glTextureParameteri(mId, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

        else
            glTextureParameteri(mId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(mId, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    else {
        if(mipmap)
            glTextureParameteri(mId, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

        else
            glTextureParameteri(mId, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTextureParameteri(mId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
}

void AbstractTexture::buildMipMap() {
    assert(mMipmap);
    glGenerateTextureMipmap(mId);
}

GLuint AbstractTexture::width() const {
    return mW;
}

GLuint AbstractTexture::height() const {
    return mH;
}

GLuint AbstractTexture::depth() const {
    return mD;
}

AbstractTexture::~AbstractTexture() {
    glDeleteTextures(1, &mId);
}
