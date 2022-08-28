#include "renderer.h"

Framebuffer *Renderer::buffer;

glm::ivec2 Renderer::getCoord(const glm::vec2 &coord)
{
    glm::ivec2 res;
    res.x = std::round((1 + coord.x) * ((float)buffer->getWidth() - 1) / 2.0f);
    res.y = std::round((1 - coord.y) * ((float)buffer->getHeight() - 1) / 2.0f);

    return res;
}

void Renderer::drawPoint(const glm::ivec2 &point)
{
    if (buffer->isInside(point.x, point.y))
        buffer->setPoint(point.x, point.y);
}

void Renderer::drawLine(const glm::ivec2 &s, const glm::ivec2 &e)
{
    glm::ivec2 start = s;
    glm::ivec2 end = e;

    void (*set_point_fnc)(int x, int y) = [](int x, int y)
    { buffer->setPoint(x, y); };

    bool fliped = std::abs(end.y - start.y) > std::abs(end.x - start.x);
    if (fliped)
    {
        std::swap(start.x, start.y);
        std::swap(end.x, end.y);
        set_point_fnc = [](int x, int y)
        { buffer->setPoint(y, x); };
    }
    if (start.x > end.x)
    {
        std::swap(start, end);
    }

    int dx = end.x - start.x;
    int dy = std::abs(end.y - start.y);
    int error = dx / 2;
    int ystep = glm::sign(end.y - start.y);
    int y = start.y;
    int x = std::max(0, start.x);
    int line_end = std::min(end.x, (fliped ? buffer->getHeight() : buffer->getWidth()) - 1);

    for (; x <= line_end; x++)
    {
        if (buffer->isInside(fliped ? y : x, fliped ? x : y))
            set_point_fnc(x, y);
        error -= dy;
        if (error < 0)
        {
            y += ystep;
            error += dx;
        }
    }
}

void Renderer::drawTriangle(const glm::ivec2 &p1, const glm::ivec2 &p2, const glm::ivec2 &p3)
{
    drawLine(p1, p2);
    drawLine(p2, p3);
    drawLine(p3, p1);
}

glm::vec3 Renderer::baricentric(const glm::ivec2 &p1, const glm::ivec2 &p2, const glm::ivec2 &p3, const glm::ivec2 &point)
{
    int determinator = (p2.y - p3.y) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.y - p3.y);
    float w1 = (p2.y - p3.y) * (point.x - p3.x) + (p3.x - p2.x) * (point.y - p3.y);
    float w2 = (p3.y - p1.y) * (point.x - p3.x) + (p1.x - p3.x) * (point.y - p3.y);
    w1 /= float(determinator);
    w2 /= float(determinator);
    float w3 = 1.0f - w1 - w2;
    return glm::vec3(w1, w2, w3);
}

void Renderer::drawFilledTriangle(const glm::ivec2 &p1, const glm::ivec2 &p2, const glm::ivec2 &p3)
{
    glm::ivec2 t0 = p1;
    glm::ivec2 t1 = p2;
    glm::ivec2 t2 = p3;

    if (t0.y > t1.y)
        std::swap(t0, t1);
    if (t0.y > t2.y)
        std::swap(t0, t2);
    if (t1.y > t2.y)
        std::swap(t1, t2);

    int total_height = t2.y - t0.y;

    int segment_height = t1.y - t0.y;
    if (segment_height > 0)
    {
        int y = std::max(0, t0.y);
        int end_y = std::min(t1.y, buffer->getHeight() - 1);
        for (; y <= end_y; y++)
        {
            float alpha = (float)(y - t0.y) / total_height;
            float beta = (float)(y - t0.y) / segment_height;

            int x0 = t0.x + (t2.x - t0.x) * alpha;
            int x1 = t0.x + (t1.x - t0.x) * beta;
            if (x0 > x1)
                std::swap(x0, x1);

            int i = std::max(0, x0);
            int end = std::min(x1, buffer->getWidth() - 1);
            for (; i <= end; i++)
            {
                buffer->setPoint(i, y);
            }
        }
    }

    segment_height = t2.y - t1.y;
    if (segment_height > 0)
    {
        int y = std::max(0, t1.y);
        int end_y = std::min(t2.y, buffer->getHeight() - 1);
        for (; y <= end_y; y++)
        {
            float alpha = (float)(y - t0.y) / total_height;
            float beta = (float)(y - t1.y) / segment_height;

            int x0 = t0.x + (t2.x - t0.x) * alpha;
            int x1 = t1.x + (t2.x - t1.x) * beta;
            if (x0 > x1)
                std::swap(x0, x1);

            int i = std::max(0, x0);
            int end = std::min(x1, buffer->getWidth() - 1);
            for (; i <= end; i++)
            {
                buffer->setPoint(i, y);
            }
        }
    }

    drawTriangle(p1, p2, p3);
}