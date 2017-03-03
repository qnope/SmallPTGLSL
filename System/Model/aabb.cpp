#include "aabb.hpp"
#include "System/tools.hpp"

AABB::AABB(glm::vec3 p1, glm::vec3 p2) : mP1(p1), mP2(p2) {
    adjust();
}

void AABB::adjust() {
    auto min = glm::min(mP1, mP2);
    auto max = glm::max(mP1, mP2);

    mP1 = min; mP2 = max;
}

AABB &AABB::operator *=(glm::mat4 m) {
    mP1 = m * glm::vec4(mP1, 1.f);
    mP2 = m * glm::vec4(mP2, 1.f);

    adjust();
    return *this;
}

AABB AABB::operator *(glm::mat4 m) {
    AABB aabb(*this);
    aabb *= m;
    return aabb;
}

AABB &AABB::operator <<(AABB aabb) {
    mP1 = glm::min(mP1, aabb.mP1);
    mP2 = glm::max(mP2, aabb.mP2);
    return *this;
}

AABB &AABB::operator<<(Vertex v) {
    mP1 = glm::min(mP1, v.position);
    mP2 = glm::max(mP2, v.position);
    return *this;
}

std::ostream &operator <<(std::ostream &stream, AABB aabb) {
    stream << "p1 : " << aabb.mP1 << std::endl;
    stream << "p2 : " << aabb.mP2;
    return stream;
}

glm::vec4 AABB::getCube() const {
    const glm::vec3 s = mP2 - mP1;
    const glm::vec3 p = (mP2 + mP1) / 2.0f;

    return glm::vec4(p, max(s.x, s.y, s.z));
}
