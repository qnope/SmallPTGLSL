#pragma once

#include <GL/glew.h>
#include "System/noncopyable.hpp"

struct DrawElementsIndirect {
    GLuint count;
    GLuint primCount = 1;
    GLuint firstIndex;
    GLuint baseVertex;
    GLuint baseInstance;
};

class GLResource : NonCopyable {
public:
    operator GLuint() {
        return mId;
    }

protected:
    GLuint mId = 0;
};
