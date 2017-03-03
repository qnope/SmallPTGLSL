#include <fstream>
#include "shader.hpp"

Shader::Shader(const std::string &path, GLenum type) {
    mId = glCreateShader(type);

    compile(getSource(path));
}

std::string Shader::getSource(const std::string &path) {
    std::ifstream stream(path, std::ios::binary);

    if(!stream.is_open())
        throw std::runtime_error(path + " does not opened");

    stream.seekg(0, std::ios::end);
    auto length = stream.tellg();
    stream.seekg(0, std::ios::beg);

    std::string src(length, 0);
    stream.read(&src[0], length);
    return src;
}

void Shader::compile(const std::string &src) {
    char const *sources = src.c_str();
    glShaderSource(mId, 1, &sources, NULL);
    glCompileShader(mId);

    int statCompilation;
    glGetShaderiv(mId, GL_COMPILE_STATUS, &statCompilation);

    if(statCompilation != true) {
        glGetShaderiv(mId, GL_INFO_LOG_LENGTH, &statCompilation);
        std::string log(statCompilation, 0);
        glGetShaderInfoLog(mId, statCompilation, &statCompilation, &log[0]);
        glDeleteShader(mId);
        throw std::runtime_error(log);
    }
}

Shader::~Shader() {
    glDeleteShader(mId);
}
