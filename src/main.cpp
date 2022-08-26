#include "framebuffer.h"
#include "renderer.h"
#include <chrono>

#include <sys/ioctl.h>
#include <unistd.h>

const int width = 80;
const int height = 20;

Framebuffer b(width, height);

int main(int, char **)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int char_width = w.ws_xpixel / w.ws_col;
    int char_height = w.ws_ypixel / w.ws_row;

    auto start = std::chrono::system_clock::now();
    Renderer::init(&b);
    glm::vec2 p1(-0.5f, -0.5f), p2(0.5f, -0.5f), p3(0.0f, 0.5f);

    while (true)
    {
        system("clear");
        b.clear();
        std::chrono::duration<double> time = start - std::chrono::system_clock::now();
        Renderer::drawTriange(p1, p2, p3);

        b.draw();

        b.updateSize();
        usleep(1000000 / 60);
    }
}
