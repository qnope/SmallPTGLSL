#pragma once
#include <GL/glew.h>

struct ViewPortState {
    GLsizei width = 512;
    GLsizei height = 512;
};

struct ColorState {
    bool rMask = true;
    bool gMask = true;
    bool bMask = true;
    bool aMask = true;
};

struct DepthStencilState {
    bool depthEnable = false;
    bool depthMask = true;
    GLenum depthFunc = GL_LESS;
};

struct BlendingState {
    bool blendingEnable = false;
    GLenum srcFactor = GL_ONE;
    GLenum destFactor = GL_ZERO;
};

struct PipelineState
{
    void perform() const;

    ColorState colorState;
    DepthStencilState depthStencilState;
    BlendingState blendingState;
    ViewPortState viewPortState;
};

