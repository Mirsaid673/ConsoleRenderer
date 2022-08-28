#include "global.h"

#include <cstring>

std::vector<Buffer> Global::buffers;
std::vector<BufferArray> Global::buffer_arrays;

BufferArray *Global::current_buffer_array = nullptr;
VertexShader *Global::vert_shader = nullptr;

uint Global::genBufferArray()
{
    buffer_arrays.push_back(BufferArray());
    return buffer_arrays.size() - 1; // the last element id
}

void Global::bindBufferArray(uint id)
{
    current_buffer_array = &buffer_arrays[id];
}

void Global::unbindBufferArray()
{
    current_buffer_array = nullptr;
}

uint Global::genBuffer(uint8_t *data, uint data_size)
{
    buffers.push_back(Buffer(data, data_size));
    return buffers.size() - 1; // the last element id
}

void Global::linkAttrib(const DataAttrib &attr)
{
    current_buffer_array->data_attribs.push_back(attr);
}

void Global::linkElementBuffer(uint id)
{
    current_buffer_array->element_buffer_id = id;
}

void Global::drawArrays(uint start, uint count)
{
    glm::vec4 points[3];
    for (int i = start; i < count; i++)
    {
        for (const auto &attrib : current_buffer_array->data_attribs)
        {
            void *dest = vert_shader->in_data_ptr + attrib.in_data_offset;
            void *src = buffers[attrib.buffer_id].data + attrib.offset + attrib.stride * i;
            std::memcpy(dest, src, DataTypeSize[(int)attrib.data_type] * DataDemensionSize[(int)attrib.data_demension]);
        }
        points[i % 3] = vert_shader->main();
        if (i % 3 == 2)
        {
            Renderer::drawTriangle(points[0], points[1], points[2]);
        }
    }
}

void Global::drawElements(uint start, uint count)
{
    uint EB_id = current_buffer_array->element_buffer_id;
    uint* buff = (uint*)buffers[EB_id].data;
    
    //std::vector<glm::vec4> Positions;


    glm::vec4 points[3];
    for (int i = start; i < count; i++)
    {
        for (const auto &attrib : current_buffer_array->data_attribs)
        {
            void *dest = vert_shader->in_data_ptr + attrib.in_data_offset;
            void *src = buffers[attrib.buffer_id].data + attrib.offset + attrib.stride * buff[i];
            std::memcpy(dest, src, DataTypeSize[(int)attrib.data_type] * DataDemensionSize[(int)attrib.data_demension]);
        }
        points[i % 3] = vert_shader->main();
        if (i % 3 == 2)
        {
            Renderer::drawFilledTriangle(points[0], points[1], points[2]);
        }
    }
}

void Global::useShader(VertexShader *v)
{
    vert_shader = v;
}