#include "framebuffer.h"

#include <sys/ioctl.h>
#include <unistd.h>

void Framebuffer::resize(int w, int h)
{
    width = w;
    height = h;

    buffer.resize(height);

    for (auto &line : buffer)
        line.resize(width);
}

void Framebuffer::updateSize()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    if (width != w.ws_col || height != w.ws_row)
        resize(w.ws_col, w.ws_row);
}

void Framebuffer::clear()
{
    for (auto &line : buffer)
        for (auto &ch : line)
            ch = clear_char;
}

void Framebuffer::display()
{
    for (auto &line : buffer)
        std::cout << line << '\n'; // '\n' is faster than std::endl
}