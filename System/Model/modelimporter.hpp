#pragma once

#include "material.hpp"
#include "mesh.hpp"

struct ModelImporter {
    ModelImporter(std::string const &path, TextureRepository &texManager);

    std::vector<Material> mMaterials;
    std::vector<Mesh> mMeshes;
};
