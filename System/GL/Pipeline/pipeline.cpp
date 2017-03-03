#include <string>
#include <stdexcept>
#include "pipeline.hpp"

Pipeline::Pipeline() {
    mId = glCreateProgram();
}

void Pipeline::attach(GLuint shader) {
    glAttachShader(mId, shader);
}

void Pipeline::bind() {
    glUseProgram(mId);
    mPipelineState.perform();
}

PipelineState Pipeline::pipelineState() const {
    return mPipelineState;
}

void Pipeline::setPipelineState(const PipelineState &ps) {
    mPipelineState = ps;
}

void Pipeline::create() {
    glLinkProgram(mId);

    int statLink;

    glGetProgramiv(mId, GL_LINK_STATUS, &statLink);

    if(statLink != true) {
        glGetProgramiv(mId, GL_INFO_LOG_LENGTH, &statLink);
        std::string log(statLink, 0);
        glGetProgramInfoLog(mId, statLink, &statLink, &log[0]);
        throw std::runtime_error(log);
    }
}

Pipeline::~Pipeline() {
    glDeleteProgram(mId);
}
