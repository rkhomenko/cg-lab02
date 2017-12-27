// Computer graphic lab 2
// Variant 20
// Copyright © 2017-2018 Roman Khomenko (8O-308)
// All rights reserved

#ifndef CG_LAB_VERTEX_HPP_
#define CG_LAB_VERTEX_HPP_

#include <QVector3D>

class Vertex {
public:
    using PositionType = QVector3D;
    using ReferencePositionType = PositionType&;
    using ConstReferencePositionType = const PositionType&;

    using FloatType = float;
    using IntType = std::int32_t;

    constexpr Vertex() : Position{0.0, 0.0, 0.0} {}
    constexpr Vertex(FloatType x, FloatType y) : Position{x, y, 0.0} {}
    constexpr Vertex(ConstReferencePositionType position)
        : Position{position} {}

    constexpr ConstReferencePositionType GetPositon() const { return Position; }

    static constexpr IntType GetTupleSize() { return TUPLE_SIZE; }
    static constexpr IntType GetOffset() { return offsetof(Vertex, Position); }
    static constexpr IntType GetStride() { return sizeof(Vertex); }

private:
    static const IntType TUPLE_SIZE = 3;

    PositionType Position;
};

#endif  // CG_LAB_VERTEX_HPP_
