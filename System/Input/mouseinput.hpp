#pragma once
#include <unordered_map>
#include "abstractinput.hpp"

class MouseInput : public AbstractInput
{
public:
    int x();
    int y();
    int xRel();
    int yRel();
    bool button(unsigned value);

    void reset();

    void update(SDL_Event const &event);

    void show(bool enable) const;
    void grab(bool enable) const;

private:
    std::unordered_map<unsigned, bool> mButtons;
    int mX, mY, mXrel, mYrel;
};
