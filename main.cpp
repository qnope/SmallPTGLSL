#include <random>
#include "System/device.hpp"
#include "System/Input/windowinput.hpp"
#include "System/Input/mouseinput.hpp"
#include "System/Input/keyboardinput.hpp"
#include "System/GL/Pipeline/pipeline.hpp"
#include "System/GL/Pipeline/shaderrepository.hpp"
#include "System/GL/Pipeline/vao.hpp"
#include "System/glm.hpp"
#include "System/GL/Buffer/unmappablebuffer.hpp"
#include "System/tools.hpp"

using namespace glm;

struct Material {
    vec4 emission;
    vec4 albedoType;
};

struct Sphere {
    vec4 positionRadius;
    int materialIndex;
    int padd, padd2, padd3;
};

struct Plane {
    vec4 equation;
    int materialIndex;
    int padd, padd2, padd3;
};


#define DIFF 0.0
#define SPEC 1.0
#define REFR 2.0

Sphere make_sphere(glm::vec3 position, float radius, int materialIndice) {
    return Sphere{vec4(position, radius), materialIndice, 0, 0, 0};
}

Material make_material(glm::vec3 emission, glm::vec3 albedo, float type) {
    return Material{vec4(emission, 0), vec4(albedo, type)};
}

Plane make_plane(vec4 eq, int materialIndex) {
    return Plane{eq, materialIndex, 0, 0, 0};
}

int main(int, char **) {
    Device device(800, 600, "Wave Tracer", true);

    auto windowInput = std::make_shared<WindowInput>(800, 600);

    device.assignInput(windowInput);

    Pipeline pipeline;
    ShaderRepository repo;

    pipeline.attach(repo.shader("../Shaders/simple.vert", GL_VERTEX_SHADER));
    pipeline.attach(repo.shader("../Shaders/simple.frag", GL_FRAGMENT_SHADER));

    pipeline.create();

    Vao quad;

    std::vector<Sphere> spheres;
    std::vector<Plane> planes;
    std::vector<Material> materials;

    materials << make_material(vec3(), vec3(1.0), DIFF);
    materials << make_material(vec3(), vec3(1.0, 0., 0.), DIFF);
    materials << make_material(vec3(), vec3(0., 1.0, 0.), DIFF);
    materials << make_material(vec3(6), vec3(0., .0, .0), DIFF);

    materials << make_material(vec3(), vec3(), SPEC);
    materials << make_material(vec3(), vec3(), REFR);

    planes << make_plane(vec4(0, 1, 0, 0), 0);
    planes << make_plane(vec4(1, 0, 0, 0), 1);
    planes << make_plane(vec4(-1, 0, 0, 500), 2);
    planes << make_plane(vec4(0, -1, 0, 500), 0);
    planes << make_plane(vec4(0, 0, -1, 500), 0);

    spheres << make_sphere(vec3(150, 100, 376), 100, 4);
    spheres << make_sphere(vec3(350, 100, 100), 100, 5);
    spheres << make_sphere(vec3(250, 600, 250), 150, 3);

    UnmappableTypedBuffer<Sphere> sphereBuffer(spheres.size(), spheres.data(), GL_STATIC_DRAW);
    UnmappableTypedBuffer<Plane> planeBuffer(planes.size(), planes.data(), GL_STATIC_DRAW);
    UnmappableTypedBuffer<Material> materialBuffer(materials.size(), materials.data(), GL_STATIC_DRAW);

    UnmappableBuffer randomBuffer(1000002 * sizeof(float), nullptr, GL_STATIC_DRAW);

    GLuint value = 1000000;

    randomBuffer.pushData(&value, sizeof value);
    value = 0;
    randomBuffer.pushData(&value, sizeof value);

    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(0.0f, 1.0f);

    for(int i = 0; i < 1000000; ++i) {
        float value = distribution(generator);
        randomBuffer.pushData(&value, sizeof value);
    }

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, sphereBuffer);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, planeBuffer);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, materialBuffer);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, randomBuffer);

    while(windowInput->isRunning()) {
        device.updateInputs();
        glClear(GL_COLOR_BUFFER_BIT);
        PipelineState ps = pipeline.pipelineState();
        ps.viewPortState.width = windowInput->width();
        ps.viewPortState.height = windowInput->height();
        pipeline.setPipelineState(ps);

        pipeline.bind();
        glBindVertexArray(quad);
        glm::vec3 posCamera = glm::vec3(278, 273, -800);
        glm::mat4 mat = glm::infinitePerspectiveLH(glm::radians(40.44f), (float)windowInput->width() / windowInput->height(), 1.0f) * glm::lookAtLH(posCamera, posCamera + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 1.0, 0.0));
        glUniformMatrix4fv(0, 1, false, glm::value_ptr(mat));
        glUniform3fv(1, 1, glm::value_ptr(posCamera));
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        device.swapBuffers();
    }

    return 0;
}
