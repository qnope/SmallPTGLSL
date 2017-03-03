#include "pipelinestate.hpp"

void PipelineState::perform() const {
    glColorMask(colorState.rMask, colorState.gMask,
                colorState.bMask, colorState.aMask);

    if(depthStencilState.depthEnable == true) {
        glEnable(GL_DEPTH_TEST);
        glDepthMask(depthStencilState.depthMask);
        glDepthFunc(depthStencilState.depthFunc);
    }

    else
        glDisable(GL_DEPTH_TEST);

    if(blendingState.blendingEnable == true) {
        glEnable(GL_BLEND);
        glBlendFunc(blendingState.srcFactor, blendingState.destFactor);
    }

    else
        glDisable(GL_BLEND);

    glViewport(0, 0, viewPortState.width, viewPortState.height);
}
