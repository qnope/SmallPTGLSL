#pragma once
#include <memory>
#include <string>
#include <SDL2/SDL_image.h>
#include "System/GL/glresource.hpp"

class AbstractTexture : public GLResource
{
public:
    AbstractTexture(GLenum target, bool mipmap, bool linear, GLuint w, GLuint h = 1, GLuint d = 1);

    void buildMipMap();

    GLuint width() const;
    GLuint height() const;
    GLuint depth() const;

    virtual ~AbstractTexture();

protected:
    bool mMipmap;
    GLuint mW, mH, mD;
};
