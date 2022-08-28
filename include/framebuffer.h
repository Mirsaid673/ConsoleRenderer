#pragma once

#include "defines.h"

#include <iostream>
#include <vector>

class Framebuffer
{
private:
    char_t clear_char = ' ';
    int width;
    int height;
    std::vector<string_t> buffer;

public:

    Framebuffer() {}
    Framebuffer(int w, int h) { resize(w, h); }

    void resize(int w, int h);
    void updateSize();
    void clearChar(char_t ch) { clear_char = ch; };
    void clear();

    void display();
    void setPoint(int x, int y, char_t ch = '#') { buffer[y][x] = ch; }

    int getWidth() { return width; }
    int getHeight() { return height; }

    bool isInside(int x, int y) { return x >= 0 && x < width && y >= 0 && y < height; }

    string_t &operator[](size_t index) { return buffer[index]; }

private:
};