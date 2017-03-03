#include "shaderrepository.hpp"

GLuint ShaderRepository::shader(const std::string &path, GLenum type) {
    if(mShaders.find(path) == mShaders.end())
        mShaders.emplace(path, std::make_unique<Shader>(path, type));
    return *mShaders[path];
}
