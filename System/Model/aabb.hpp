#pragma once
#include <iostream>
#include "System/glm.hpp"
#include "vertex.hpp"

class AABB {
    friend class PipelineManager;
    friend std::ostream &operator<<(std::ostream &stream, AABB aabb);
    glm::vec3 mP1 = glm::vec3(std::numeric_limits<float>::max());
    glm::vec3 mP2 = glm::vec3(std::numeric_limits<float>::min());

public:
    AABB() = default;
    AABB(glm::vec3 p1, glm::vec3 p2);

    void adjust();
    AABB &operator*=(glm::mat4 m);
    AABB operator*(glm::mat4 m);
    AABB &operator<<(AABB aabb);
    AABB &operator<<(Vertex vertex);

    glm::vec4 getCube() const;
};

std::ostream &operator<<(std::ostream &stream, AABB aabb);

