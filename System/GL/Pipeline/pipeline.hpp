#pragma once

#include "System/GL/glresource.hpp"
#include "System/GL/Pipeline/pipelinestate.hpp"

class Pipeline : public GLResource
{
public:
    Pipeline();

    void attach(GLuint shader);
    void create();
    void bind();

    PipelineState pipelineState() const;
    void setPipelineState(PipelineState const &ps);

    ~Pipeline();

protected:
    PipelineState mPipelineState;
};
