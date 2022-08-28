#include "framebuffer.h"
#include "renderer.h"
#include "global.h"
#include "shader.h"

#include <chrono>
#include <sys/ioctl.h>
#include <unistd.h>

#include <glm/gtc/matrix_transform.hpp>

class MyShader : public VertexShader
{
public:
    struct InData
    {
        glm::vec3 aPos;
    } & in;

    glm::mat4 PM;

    glm::vec4 main() override
    {
        return PM * glm::vec4(in.aPos, 1);
    }

    MyShader() : in(*(new InData))
    {
        in_data_ptr = reinterpret_cast<uint8_t *>(&in);
    }
    ~MyShader() override
    {
        delete &in;
    }
};

const int width = 80;
const int height = 20;

Framebuffer b(width, height);

glm::vec3 verts[6]{
    glm::vec3(-0.5f, -0.5f, -2),
    glm::vec3(-0.5f, 0.5f, -2),
    glm::vec3(0.5f, -0.5f, -2),
    glm::vec3(0.5f, 0.5f, -2),
};

uint ind[]{
    0, 1, 2,
    1, 2, 3
   };

int main(int, char **)
{
    Renderer::init(&b);
    MyShader sh;
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), (float)b.getWidth() / (float)b.getHeight() / 2, 0.1f, 100.0f);
    glm::mat4 model(1.0f);

    // auto start = std::chrono::system_clock::now();

    uint buf = Global::genBuffer((uint8_t *)&verts[0][0], sizeof(verts));
    uint ebf = Global::genBuffer((uint8_t *)ind, sizeof(ind));
    uint bao = Global::genBufferArray();
    DataAttrib da;
    da.buffer_id = buf;
    da.data_type = DataType::FLOAT32;
    da.data_demension = DataDemension::VEC3;
    da.in_data_offset = offsetof(MyShader::InData, aPos);
    da.offset = 0;
    da.stride = sizeof(verts[0]);
    Global::bindBufferArray(bao);
    Global::linkAttrib(da);
    Global::linkElementBuffer(ebf);
    Global::useShader(&sh);

    while (true)
    {
        system("clear");
        b.clearChar(' ');
        b.clear();

        glm::mat4 PM = projection * model;
        model = glm::rotate(model, glm::radians(1.f), glm::vec3(1, 1, 1));

        // std::chrono::duration<double> time = start - std::chrono::system_clock::now();
        sh.PM = PM;
        Global::drawElements(0, sizeof(ind) / sizeof(ind[0]));
        b.display();

        b.updateSize();
        usleep(1000000 / 120);
    }
}
