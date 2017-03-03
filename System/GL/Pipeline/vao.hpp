#pragma once
#include "System/GL/glresource.hpp"

class Vao : public GLResource {
public:
    Vao();

    void enableArray(GLuint index);

    void bindElementBuffer(GLuint buffer);

    void bindVertexBuffer(GLuint bindingIndex, GLuint buffer,
                          GLintptr offset, GLsizei stride = 0);

    void bindVertexBuffers(GLuint firstBindingIndex, GLsizei count,
                           GLuint *buffers,
                           GLintptr *offsets,
                           GLsizei *strides);

    void format(GLuint attribIndex, int size, GLenum type,
                bool normalized, GLuint relativeOffset);

    void attribBinding(GLuint attribIndex, GLuint bindingIndex);

    void bindingDivisor(GLuint bindingIndex, GLuint divisor);

    ~Vao();
};
