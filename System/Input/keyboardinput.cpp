#include "keyboardinput.hpp"

bool KeyboardInput::key(SDL_Keycode code) {
    return mKeys[code];
}

void KeyboardInput::reset(SDL_Keycode code) {
    mKeys[code] = false;
}

void KeyboardInput::update(const SDL_Event &event) {
    if(event.type == SDL_KEYDOWN)
        mKeys[event.key.keysym.sym] = true;

    else if(event.type == SDL_KEYUP)
        mKeys[event.key.keysym.sym] = false;
}
