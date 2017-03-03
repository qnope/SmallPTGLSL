#include "mouseinput.hpp"
#include <iostream>

void MouseInput::update(const SDL_Event &event) {
    if(event.type == SDL_MOUSEBUTTONDOWN)
        mButtons[event.button.button] = true;

    else if(event.type == SDL_MOUSEBUTTONUP)
        mButtons[event.button.button] = false;

    else if(event.type == SDL_MOUSEMOTION) {
        mX = event.motion.x;
        mY = event.motion.y;
        mXrel = event.motion.xrel;
        mYrel = event.motion.yrel;
    }
}

void MouseInput::reset() {
    mXrel = mYrel = 0;
}

int MouseInput::x() {
    return mX;
}

int MouseInput::y() {
    return mY;
}

int MouseInput::xRel() {
    return mXrel;
}

int MouseInput::yRel() {
    return mYrel;
}

bool MouseInput::button(unsigned value) {
    return mButtons[value];
}

void MouseInput::show(bool enable) const {
    SDL_ShowCursor(!enable ? SDL_DISABLE : SDL_ENABLE);
}

void MouseInput::grab(bool enable) const {
    SDL_SetRelativeMouseMode(enable ? SDL_TRUE : SDL_FALSE);
}
