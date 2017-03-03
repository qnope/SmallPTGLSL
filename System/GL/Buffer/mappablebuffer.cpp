#include <cassert>
#include <GL/glew.h>
#include "mappablebuffer.hpp"

MappableBuffer::MappableBuffer(GLsizeiptr size, unsigned roundRobin, bool write, bool read, bool coherent) :
    mIndex(0),
    mRoundRobin(roundRobin) {
    assert(write | read);
    glCreateBuffers(1, &mId);

    GLint alignmentUniform, alignmentShaderStorage, alignment;
    glGetIntegerv(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT, &alignmentUniform);
    glGetIntegerv(GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT, &alignmentShaderStorage);

    alignment = (alignmentUniform > alignmentShaderStorage) ? alignmentUniform : alignmentShaderStorage;

    // We're going to align data on alignment bytes
    if(size % alignment != 0) {
        size = size + (alignment - (size % alignment));
    }

    mSize = size;
    mTotalSize = size * roundRobin;

    GLbitfield flags = GL_MAP_PERSISTENT_BIT;

    if(read)
        flags |= GL_MAP_READ_BIT;

    if(write)
        flags |= GL_MAP_WRITE_BIT;

    if(coherent)
        flags |= GL_MAP_COHERENT_BIT;

    glNamedBufferStorage(mId, mTotalSize, nullptr,
                         flags);

    if(write && !coherent)
        flags |= GL_MAP_FLUSH_EXPLICIT_BIT;

    mPtr = (char*)glMapNamedBufferRange(mId, 0, mTotalSize, flags);
}

GLintptr MappableBuffer::currentOffset() {
    return mSize * mIndex;
}

GLsizeiptr MappableBuffer::size() {
    return mSize;
}

void MappableBuffer::performRoundRobin() {
    mIndex = (mIndex + 1) % mRoundRobin;
}

void MappableBuffer::flush() {
    glFlushMappedNamedBufferRange(mId, mSize * mIndex, mSize);
}

MappableBuffer::~MappableBuffer() {
    glDeleteBuffers(1, &mId);
}
