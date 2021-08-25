#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

struct Vertex final {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
    // tangent
    glm::vec3 tangent;
    // bitangent
    glm::vec3 bitangent;
};
