// Computer graphic lab 2
// Variant 20
// Copyright © 2017-2018 Roman Khomenko (8O-308)
// All rights reserved

#ifndef CG_LAB_VERTEX_HPP_
#define CG_LAB_VERTEX_HPP_

#include <Matrix.hpp>

using Matrix4x4 = Matrix<float, 4, 4>;

class Vertex {
public:
    using PositionType = Matrix<float, 1, 4>;
    using ReferencePositionType = PositionType&;
    using ConstReferencePositionType = const PositionType&;

    using FloatType = float;
    using IntType = std::int32_t;

    constexpr Vertex() : Vertex{0.0, 0.0, 0.0, 1.0} {}
    constexpr Vertex(FloatType x, FloatType y) : Vertex{x, y, 0.0, 1.0} {}
    constexpr Vertex(FloatType x, FloatType y, FloatType z)
        : Vertex{x, y, z, 1.0} {}
    constexpr Vertex(FloatType x, FloatType y, FloatType z, FloatType h)
        : Position{x, y, z, h} {}
    constexpr Vertex(ConstReferencePositionType position)
        : Position{position} {}

    constexpr Vertex operator*(const Matrix4x4& matrix) const {
        return Position * matrix;
    }

    constexpr ConstReferencePositionType GetPositon() const { return Position; }

    static constexpr IntType GetTupleSize() { return TUPLE_SIZE; }
    static constexpr IntType GetOffset() { return offsetof(Vertex, Position); }
    static constexpr IntType GetStride() { return sizeof(Vertex); }

private:
    static const IntType TUPLE_SIZE = 3;

    PositionType Position;
};

#endif  // CG_LAB_VERTEX_HPP_