#pragma once
#include <memory>
#include <unordered_map>
#include "shader.hpp"

class ShaderRepository {
public:
    GLuint shader(std::string const &path, GLenum type);
    
private:
    std::unordered_map<std::string, std::unique_ptr<Shader>> mShaders;
};

