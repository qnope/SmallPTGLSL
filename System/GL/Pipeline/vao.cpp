#include "vao.hpp"

Vao::Vao() {
    glCreateVertexArrays(1, &mId);
}

void Vao::attribBinding(GLuint attribIndex, GLuint bindingIndex) {
    glVertexArrayAttribBinding(mId, attribIndex, bindingIndex);
}

void Vao::bindingDivisor(GLuint bindingIndex, GLuint divisor) {
    glVertexArrayBindingDivisor(mId, bindingIndex, divisor);
}

void Vao::bindElementBuffer(GLuint buffer) {
    glVertexArrayElementBuffer(mId, buffer);
}

void Vao::bindVertexBuffer(GLuint bindingIndex, GLuint buffer,
                           GLintptr offset, GLsizei stride) {
    glVertexArrayVertexBuffer(mId, bindingIndex, buffer, offset, stride);
}

void Vao::bindVertexBuffers(GLuint firstBindingIndex, GLsizei count,
                            GLuint *buffers, GLintptr *offsets, GLsizei *strides) {
    glVertexArrayVertexBuffers(mId, firstBindingIndex, count,
                               buffers, offsets, strides);
}

void Vao::enableArray(GLuint index) {
    glEnableVertexArrayAttrib(mId, index);
}

void Vao::format(GLuint attribIndex, int size,
                 GLenum type, bool normalized, GLuint relativeOffset) {
    glVertexArrayAttribFormat(mId, attribIndex, size, type, normalized, relativeOffset);
}

Vao::~Vao() {
    glDeleteVertexArrays(1, &mId);
}
