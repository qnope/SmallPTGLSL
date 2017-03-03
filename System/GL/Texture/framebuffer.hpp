#pragma once
#include <vector>
#include "abstracttexture.hpp"

class FrameBuffer : public GLResource
{
public:
    FrameBuffer();

    void addColorRenderTarget(std::shared_ptr<AbstractTexture> colorBuffer);
    void changeDepthStencilBuffer(std::shared_ptr<AbstractTexture> depthStencilBuffer,
                                  bool depth, bool stencil);

    void bindTextures(GLuint firstColorBuffer, GLuint firstBinding, GLuint number) const;

    ~FrameBuffer();

private:
    std::vector<std::shared_ptr<AbstractTexture>> mColorBuffers;
    std::shared_ptr<AbstractTexture> mDepthStencilBuffer;
};
