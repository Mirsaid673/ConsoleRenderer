#pragma once

using uint = unsigned int;
using uint8_t = unsigned char;

enum class DataType
{
    INT8,
    UINT8,
    INT16,
    UINT16,
    INT32,
    UINT32,
    FLOAT32,
    INT64,
    UINT64,
    FLOAT64,
    MAX,
};

const uint DataTypeSize[(uint)DataType::MAX]{
    1, // INT8
    1, // UINT8
    2, // INT16
    2, // UINT16
    4, // INT32
    4, // UINT32
    4, // FLOAT32
    8, // INT64
    8, // UINT64
    8, // FLOAT64
};

enum class DataDemension
{
    SCALAR,
    VEC2,
    VEC3,
    VEC4,
    MAT2,
    MAT3,
    MAT4,
    MAX,
};

const uint DataDemensionSize[(uint)DataDemension::MAX]{
    1,  // SCALAR
    2,  // VEC2
    3,  // VEC3
    4,  // VEC4
    4,  // MAT2
    9,  // MAT3
    16, // MAT4
};
