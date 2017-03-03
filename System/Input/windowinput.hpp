#pragma once
#include "abstractinput.hpp"

class WindowInput : public AbstractInput {
public:
    WindowInput(unsigned width, unsigned height);

    void reset();

    bool isRunning() const {
        return !mQuit;
    }

    unsigned width() const {
        return mWidth;
    }

    unsigned height() const {
        return mHeight;
    }

    bool isResized() const {
        return mIsResized;
    }

    void update(SDL_Event const &event);

    ~WindowInput() = default;

private:
    bool mQuit = false;
    bool mIsResized = false;
    unsigned mWidth = 0;
    unsigned mHeight = 0;
};
