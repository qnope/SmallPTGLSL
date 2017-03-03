#include "windowinput.hpp"

WindowInput::WindowInput(unsigned width, unsigned height) :
    mWidth(width),
    mHeight(height) {

}

void WindowInput::reset() {
    mIsResized = false;
}

void WindowInput::update(const SDL_Event &event) {
    if(event.type == SDL_WINDOWEVENT) {
        switch(event.window.event) {
        case SDL_WINDOWEVENT_CLOSE:
            mQuit = true;
        break;

        case SDL_WINDOWEVENT_RESIZED:
            mWidth = event.window.data1;
            mHeight = event.window.data2;
            mIsResized = true;
            break;

        default:break;
        }
    }
}
