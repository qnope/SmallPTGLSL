#pragma once
#include <unordered_map>
#include "abstractinput.hpp"

class KeyboardInput : public AbstractInput
{
public:
    bool key(SDL_Keycode code);
    void update(SDL_Event const &event);
    void reset() {}
    void reset(SDL_Keycode code);

private:
    std::unordered_map<SDL_Keycode, bool> mKeys;
};
