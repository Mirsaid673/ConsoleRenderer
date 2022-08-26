#include "renderer.h"

Framebuffer *Renderer::buffer;

glm::ivec2 Renderer::getCoord(const glm::vec2 &coord)
{
    glm::ivec2 res;
    res.x = std::round((1 + coord.x) * ((float)buffer->getWidth() - 1) / 2.0f);
    res.y = std::round((1 - coord.y) * ((float)buffer->getHeight() - 1) / 2.0f);

    return res;
}

void Renderer::drawPoint(const glm::vec2 &point)
{
    glm::ivec2 coord = getCoord(point);

    if (buffer->isInside(coord.x, coord.y))
        buffer->setPoint(coord.x, coord.y);
}

void Renderer::drawLine(const glm::vec2 &s, const glm::vec2 &e)
{
    glm::ivec2 start = getCoord(s);
    glm::ivec2 end = getCoord(e);

    if (std::abs(end.y - start.y) > std::abs(end.x - start.x))
    {
        if (start.y > end.y)
        {
            std::swap(start, end);
        }

        int dy = end.y - start.y;
        int dx = std::abs(end.x - start.x);
        int error = dy / 2;
        int xstep = glm::sign(end.x - start.x);
        int x = start.x;

        for (int y = start.y; y <= end.y; y++)
        {
            if (buffer->isInside(x, y))
                buffer->setPoint(x, y);

            error -= dx;
            if (error < 0)
            {
                x += xstep;
                error += dy;
            }
        }
    }
    else
    {
        if (start.x > end.x)
        {
            std::swap(start, end);
        }

        int dx = end.x - start.x;
        int dy = std::abs(end.y - start.y);
        int error = dx / 2;
        int ystep = glm::sign(end.y - start.y);
        int y = start.y;

        for (int x = start.x; x <= end.x; x++)
        {
            if (buffer->isInside(x, y))
                buffer->setPoint(x, y);
            error -= dy;
            if (error < 0)
            {
                y += ystep;
                error += dx;
            }
        }
    }
}

void Renderer::drawTriange(const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec2 &p3)
{
    drawLine(p1, p2);
    drawLine(p2, p3);
    drawLine(p3, p1);
}