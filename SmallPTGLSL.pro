TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    System/device.cpp \
    System/contextinitializer.cpp \
    System/GL/Pipeline/vao.cpp \
    System/GL/Pipeline/pipeline.cpp \
    System/GL/Pipeline/shader.cpp \
    System/GL/Pipeline/pipelinestate.cpp \
    System/tools.cpp \
    System/GL/Texture/framebuffer.cpp \
    System/GL/Buffer/unmappablebuffer.cpp \
    System/GL/Buffer/mappablebuffer.cpp \
    System/Model/mesh.cpp \
    System/Model/material.cpp \
    System/Model/modelimporter.cpp \
    System/GL/Texture/texturerepository.cpp \
    System/GL/Pipeline/shaderrepository.cpp \
    System/Input/windowinput.cpp \
    System/GL/Texture/abstracttexture.cpp \
    System/GL/Texture/emptytexture2d.cpp \
    System/GL/Texture/image2d.cpp \
    System/GL/Texture/imageloader.cpp \
    imgui/imgui.cpp \
    imgui/imgui_demo.cpp \
    imgui/imgui_draw.cpp \
    imgui/imgui_impl_sdl_gl3.cpp \
    System/Model/aabb.cpp \
    System/GL/Texture/emptytexture3d.cpp \
    System/Input/keyboardinput.cpp \
    System/Input/mouseinput.cpp \

LIBS += -lSDL2 -lGLEW -lGL -lSDL2_image -lassimp

HEADERS += \
    System/device.hpp \
    System/contextinitializer.hpp \
    System/GL/glresource.hpp \
    System/GL/Pipeline/vao.hpp \
    System/GL/Pipeline/pipeline.hpp \
    System/GL/Pipeline/shader.hpp \
    System/noncopyable.hpp \
    System/GL/Pipeline/pipelinestate.hpp \
    System/tools.hpp \
    System/GL/Texture/framebuffer.hpp \
    System/GL/Buffer/unmappablebuffer.hpp \
    System/GL/Buffer/mappablebuffer.hpp \
    System/Model/mesh.hpp \
    System/Model/material.hpp \
    System/glm.hpp \
    System/Model/modelimporter.hpp \
    System/GL/Texture/texturerepository.hpp \
    System/GL/Pipeline/shaderrepository.hpp \
    System/Input/abstractinput.hpp \
    System/Input/windowinput.hpp \
    System/GL/Texture/abstracttexture.hpp \
    System/GL/Texture/emptytexture2d.hpp \
    System/GL/Texture/image2d.hpp \
    System/GL/Texture/imageloader.hpp \
    imgui/imconfig.h \
    imgui/imgui.h \
    imgui/imgui_internal.h \
    imgui/stb_rect_pack.h \
    imgui/stb_textedit.h \
    imgui/stb_truetype.h \
    imgui/imgui_impl_sdl_gl3.h \
    System/Model/aabb.hpp \
    System/Model/vertex.hpp \
    System/GL/Texture/emptytexture3d.hpp \
    System/Input/keyboardinput.hpp \
    System/Input/mouseinput.hpp \

DISTFILES += \
    Shaders/simple.vert \
    Shaders/simple.frag
