#include <iostream>
#include <stdexcept>
#include <cassert>
#include <GL/glew.h>
#include "device.hpp"
#include "contextinitializer.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl_gl3.h"

void callBack(GLenum, GLenum, GLuint, GLenum,
              GLsizei, const GLchar *message, const void *) {
    std::cerr << message << std::endl;
}

Device::Device(int width, int height, std::string name, bool debug) :
    mInitializer(std::make_unique<ContextInitializer>(debug)),
    mName(std::move(name)) {
    mMainWindow = SDL_CreateWindow(mName.c_str(),
                                   SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                   width, height,
                                   SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if(mMainWindow == nullptr)
        throw std::runtime_error(std::string("Unable to create Window : ") +
                                 SDL_GetError());

    mContext = SDL_GL_CreateContext(mMainWindow);
    assert(mContext);

    glewExperimental = true;
    assert(glewInit() == GLEW_OK);

    if(debug) {
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(callBack, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE,
                              0, nullptr, true);
    }

    ImGui_ImplSdlGL3_Init(mMainWindow);
}

void Device::assignInput(std::shared_ptr<AbstractInput> input) {
    mInputs.push_back(input);
}

void Device::updateInputs() {
    SDL_Event event;

    for(auto &input : mInputs)
        input->reset();

    while(SDL_PollEvent(&event)) {
        ImGui_ImplSdlGL3_ProcessEvent(&event);
        for(auto &input : mInputs)
            input->update(event);
    }

    ImGui_ImplSdlGL3_NewFrame(mMainWindow);
}

void Device::swapBuffers() {
    ImGui::Render();
    SDL_GL_SwapWindow(mMainWindow);
}

Device::~Device() {
    ImGui_ImplSdlGL3_Shutdown();
    SDL_GL_DeleteContext(mContext);
    SDL_DestroyWindow(mMainWindow);
}
