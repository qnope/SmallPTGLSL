#pragma once
#include "abstracttexture.hpp"

class Image2D : public AbstractTexture
{
public:
    Image2D(std::string const &path);
};
