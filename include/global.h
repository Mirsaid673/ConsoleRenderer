#pragma once

#include "buffer.h"
#include "renderer.h"
#include "shader.h"
#include "renderer.h"

#include <vector>

class Global
{
private:
static std::vector<Buffer> buffers;
static std::vector<BufferArray> buffer_arrays;

static BufferArray* current_buffer_array;
static VertexShader* vert_shader;

public:
    static uint genBufferArray();
    static void bindBufferArray(uint id);
    static void unbindBufferArray();

    static uint genBuffer(uint8_t* data, uint data_size);
    static void linkAttrib(const DataAttrib &attr);
    static void linkElementBuffer(uint id);

    static void drawArrays(uint start, uint count);
    static void drawElements(uint start, uint count);

    static void useShader(VertexShader* v);
};