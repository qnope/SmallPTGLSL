#include "framebuffer.hpp"
#include <cassert>

static GLenum attachments[] = {GL_COLOR_ATTACHMENT0,
                               GL_COLOR_ATTACHMENT1,
                               GL_COLOR_ATTACHMENT2,
                               GL_COLOR_ATTACHMENT3,
                               GL_COLOR_ATTACHMENT4,
                               GL_COLOR_ATTACHMENT5,
                               GL_COLOR_ATTACHMENT6,
                               GL_COLOR_ATTACHMENT7,
                               GL_COLOR_ATTACHMENT8,
                               GL_COLOR_ATTACHMENT9,
                               GL_COLOR_ATTACHMENT10,
                               GL_COLOR_ATTACHMENT11,
                               GL_COLOR_ATTACHMENT12,
                               GL_COLOR_ATTACHMENT13,
                               GL_COLOR_ATTACHMENT14,
                               GL_COLOR_ATTACHMENT15
                              };

FrameBuffer::FrameBuffer()
{
    glCreateFramebuffers(1, &mId);
}

void FrameBuffer::addColorRenderTarget(std::shared_ptr<AbstractTexture> colorBuffer) {
    glNamedFramebufferTexture(mId, GL_COLOR_ATTACHMENT0 + mColorBuffers.size(),
                              *colorBuffer, 0);

    mColorBuffers.emplace_back(std::move(colorBuffer));

    glNamedFramebufferDrawBuffers(mId, mColorBuffers.size(), attachments);
}

void FrameBuffer::changeDepthStencilBuffer(std::shared_ptr<AbstractTexture> depthStencilBuffer,
                                           bool depth, bool stencil) {
    if(depth && stencil)
        glNamedFramebufferTexture(mId, GL_DEPTH_STENCIL_ATTACHMENT, *depthStencilBuffer, 0);

    else if(depth)
        glNamedFramebufferTexture(mId, GL_DEPTH_ATTACHMENT, *depthStencilBuffer, 0);

    else if(stencil)
        glNamedFramebufferTexture(mId, GL_STENCIL_ATTACHMENT, *depthStencilBuffer, 0);

    else
        assert("depthStencil buffer should be at least depth or stencil one");

    mDepthStencilBuffer = depthStencilBuffer;
}

void FrameBuffer::bindTextures(GLuint firstColorBuffer,
                               GLuint firstBinding,
                               GLuint number) const {
    static std::vector<GLuint> textures; // static for high perf

    for(auto i = 0u; i < number; ++i)
        textures.emplace_back(*mColorBuffers[firstColorBuffer + i]);

    glBindTextures(firstBinding, number, textures.data());

    textures.clear();
}

FrameBuffer::~FrameBuffer() {
    glDeleteFramebuffers(1, &mId);
}
