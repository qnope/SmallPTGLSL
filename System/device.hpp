#pragma once
#include <string>
#include <memory>
#include <SDL2/SDL.h>
#include <vector>
#include "contextinitializer.hpp"
#include "Input/abstractinput.hpp"

class Device
{
public:
    Device(int width, int height, std::string name, bool debug = false);

    void assignInput(std::shared_ptr<AbstractInput> input);

    void updateInputs();
    void swapBuffers();

    ~Device();
private:
    std::unique_ptr<ContextInitializer> mInitializer;
    std::vector<std::shared_ptr<AbstractInput>> mInputs;

    SDL_Window *mMainWindow;
    SDL_GLContext mContext;

    std::string mName;
};
