#pragma once

#include "System/GL/glresource.hpp"

class UnmappableBuffer : public GLResource {
public:
    UnmappableBuffer(GLsizeiptr size, void const *data, GLenum usage);

    void pushData(void const *data, GLsizeiptr size);
    void changeData(void const *data, GLsizeiptr offset, GLsizeiptr size);

    GLsizeiptr offset() const;

    ~UnmappableBuffer();

private:
    GLsizeiptr mSize;
    GLsizeiptr mOffset;
    GLenum mUsage;

    void resizeBuffer(GLsizeiptr size);
};

template<typename T>
class UnmappableTypedBuffer : public UnmappableBuffer {
public:
    UnmappableTypedBuffer(GLuint n, T const *data, GLenum usage) :
        UnmappableBuffer(sizeof(T) * n, data, usage) {}

    void pushData(T *data, GLuint n) {
        UnmappableBuffer::pushData(data, sizeof(T) * n);
    }

    void changeData(T *data, GLuint offset, GLuint n) {
        UnmappableBuffer::changeData(data, offset * sizeof(T), n * sizeof(T));
    }

    GLuint offset() {
        return UnmappableBuffer::offset() / sizeof(T);
    }

private:
};
