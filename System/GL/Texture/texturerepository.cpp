#include "texturerepository.hpp"

GLuint TextureRepository::image2D(const std::string &path) {
    if(mTextures.find(path) == mTextures.end())
        mTextures.emplace(path, std::make_unique<Image2D>(path));
    return *mTextures[path];
}
