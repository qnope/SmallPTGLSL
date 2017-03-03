#pragma once
#include <unordered_map>
#include "image2d.hpp"

class TextureRepository
{
public:
    GLuint image2D(std::string const &path);

private:
    std::unordered_map<std::string, std::unique_ptr<Image2D>> mTextures;
};
