#include "unmappablebuffer.hpp"
#include "System/tools.hpp"

UnmappableBuffer::UnmappableBuffer(GLsizeiptr size, void const *data, GLenum usage) :
    mSize(nextPowerOfTwo(size)),
    mUsage(usage) {
    glCreateBuffers(1, &mId);
    glNamedBufferData(mId, mSize, nullptr, mUsage);

    if(data != nullptr) {
        glNamedBufferSubData(mId, 0, size, data);
        mOffset = size;
    }

    else
        mOffset = 0;
}

void UnmappableBuffer::pushData(void const *data, GLsizeiptr size) {
    if(mOffset + size > mSize)
        resizeBuffer(mOffset + size);
    glNamedBufferSubData(mId, mOffset, size, data);
    mOffset += size;
}

void UnmappableBuffer::changeData(const void *data, GLsizeiptr offset, GLsizeiptr size) {
    if(offset + size > mSize)
        resizeBuffer(offset + size);
    glNamedBufferSubData(mId, offset, size, data);
}

GLsizeiptr UnmappableBuffer::offset() const {
    return mOffset;
}

void UnmappableBuffer::resizeBuffer(GLsizeiptr size) {
    GLuint newBuffer;

    size = nextPowerOfTwo(size);

    glCreateBuffers(1, &newBuffer);
    glNamedBufferData(newBuffer, size, nullptr, mUsage);
    glCopyNamedBufferSubData(mId, newBuffer, 0, 0, mSize);
    glDeleteBuffers(1, &mId);

    mId = newBuffer;
    mSize = size;
}

UnmappableBuffer::~UnmappableBuffer() {
    glDeleteBuffers(1, &mId);
}
