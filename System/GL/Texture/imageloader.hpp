#pragma once
#include <string>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>

class ImageLoader
{
public:
    ImageLoader(std::string const &path);

    void *data() const;
    unsigned width() const;
    unsigned height() const;
    GLenum internalFormat() const;
    GLenum format() const;

    virtual ~ImageLoader();

private:
    SDL_Surface *mSurface;
    unsigned mWidth;
    unsigned mHeight;
    GLenum mInternalFormat;
    GLenum mFormat;
    void *mData;
};
