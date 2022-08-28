#pragma once

#include <glm/glm.hpp>

class VertexShader
{
public:
    uint8_t *in_data_ptr;
    virtual glm::vec4 main() = 0;

    virtual ~VertexShader() {};
};
