#pragma once
#include <SDL2/SDL.h>

class AbstractInput {
public:
    AbstractInput() = default;

    virtual void update(SDL_Event const &event) = 0;
    virtual void reset() {}

    virtual ~AbstractInput() = default;
};
