#include <stdexcept>
#include "imageloader.hpp"

ImageLoader::ImageLoader(std::string const &path) {
    mSurface = IMG_Load(path.c_str());

    if(mSurface == nullptr)
        throw std::runtime_error("Unable to open : " + path);

    if(mSurface->format->BytesPerPixel == 3) {
        mInternalFormat = GL_RGB8;

        if(mSurface->format->Rmask == 0x000000FF)
            mFormat = GL_RGB;

        else
            mFormat = GL_BGR;
    }

    else {
        mInternalFormat = GL_RGBA8;

        if(mSurface->format->Rmask == 0x000000FF)
            mFormat = GL_RGBA;

        else
            mFormat = GL_BGRA;
    }

    mWidth = mSurface->w;
    mHeight = mSurface->h;
    mData = mSurface->pixels;
}

GLenum ImageLoader::format() const {
    return mFormat;
}

GLenum ImageLoader::internalFormat() const {
    return mInternalFormat;
}

unsigned ImageLoader::width() const {
    return mWidth;
}

unsigned ImageLoader::height() const {
    return mHeight;
}

void *ImageLoader::data() const {
    return mData;
}

ImageLoader::~ImageLoader() {
    SDL_FreeSurface(mSurface);
}
