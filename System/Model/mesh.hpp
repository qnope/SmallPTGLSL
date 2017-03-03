#pragma once

#include <vector>
#include <GL/glew.h>
#include <assimp/mesh.h>
#include "aabb.hpp"
#include "System/glm.hpp"

struct Mesh {
    Mesh(aiMesh const *mesh);

    unsigned materialIndex;
    unsigned numberVertex;
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    AABB aabb;
};
