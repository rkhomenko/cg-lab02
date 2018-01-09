// Computer graphic lab 2
// Variant 20
// Copyright © 2017-2018 Roman Khomenko (8O-308)
// All rights reserved

#ifndef CG_LAB_VERTEX_HPP_
#define CG_LAB_VERTEX_HPP_

#include <QVector4D>

class Vertex {
public:
    using PositionType = QVector4D;
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

    constexpr ConstReferencePositionType GetPosition() const { return Position; }

    static constexpr IntType GetTupleSize() { return TUPLE_SIZE; }
    static constexpr IntType GetOffset() { return offsetof(Vertex, Position); }
    static constexpr IntType GetStride() { return sizeof(Vertex); }

private:
    static const IntType TUPLE_SIZE = 4;

    PositionType Position;
};

#endif  // CG_LAB_VERTEX_HPP_
