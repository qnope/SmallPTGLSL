#pragma once

#include <assimp/material.h>
#include "System/glm.hpp"
#include "System/GL/Texture/texturerepository.hpp"

struct Material {
    Material(aiMaterial *mtl, TextureRepository &textureManager, std::string const &globalPath);

    bool useDiffuseTexture = false;
    bool useSpecularTexture = false;

    glm::vec3 albedo;
    float roughness = 0.0;
    float metalness = 0.0;
    float emissivness = 0.0;
    std::string name;

    GLuint diffuseTexture = 0;
    GLuint specularTexture = 0;

    GLuint pipelineRenderGBuffer;
    GLuint pipelineVoxelizeGeometry;
    GLuint pipelineVoxelizeInjectEmissivness;
};
