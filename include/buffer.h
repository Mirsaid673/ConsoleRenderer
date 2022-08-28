#pragma once

#include <vector>
#include "types.h"

struct Buffer
{
    uint8_t *data;
    uint size;

    Buffer() {}
    Buffer(uint8_t *d, uint s) : data(d), size(s) {}
};

struct DataAttrib
{
    uint buffer_id;
    uint offset;
    uint stride;
    uint in_data_offset;
    DataType data_type;
    DataDemension data_demension;

    DataAttrib(){}
    DataAttrib(uint buff_id, uint buff_offset, uint buff_stride, uint in_data_offs, DataType dt, DataDemension dd) : 
        buffer_id(buff_id), offset(buff_offset), stride(buff_offset), in_data_offset(in_data_offs), data_type(dt), data_demension(dd) {}
};

struct BufferArray
{
    uint element_buffer_id;
    std::vector<DataAttrib> data_attribs;
};