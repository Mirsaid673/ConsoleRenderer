#pragma once

#include "framebuffer.h"
#include <glm/glm.hpp>

class Renderer // static class
{
private:
    static Framebuffer *buffer;

public:
    static void init(Framebuffer *f) { buffer = f; };

    static glm::ivec2 getCoord(const glm::vec2 &coord); // return framebuffer coord from normalized
    static void drawPoint(const glm::vec2 &point);
    static void drawLine(const glm::vec2 &start, const glm::vec2 &end);
    static void drawTriangle(const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec2 &p3);
    static glm::vec3 baricentric(const glm::ivec2 &p1, const glm::ivec2 &p2, const glm::ivec2 &p3, const glm::ivec2 &point);
    static void drawFilledTriangle(const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec2 &p3);
};