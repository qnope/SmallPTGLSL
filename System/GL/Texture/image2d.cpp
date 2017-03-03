#include "imageloader.hpp"
#include "image2d.hpp"

Image2D::Image2D(std::string const &path) :
    AbstractTexture(GL_TEXTURE_2D, true, true, 0, 0, 1)
{
    ImageLoader il(path);
    mW = il.width();
    mH = il.height();

    GLsizei levels = log2(std::max(il.width(), il.height())) + 1;

    glTextureStorage2D(mId, levels, il.internalFormat(), il.width(), il.height());
    glTextureSubImage2D(mId, 0, 0, 0, il.width(), il.height(),
                        il.format(), GL_UNSIGNED_BYTE, il.data());
    buildMipMap();
}
