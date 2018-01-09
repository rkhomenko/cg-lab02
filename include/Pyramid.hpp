// Computer graphic lab 2
// Variant 20
// Copyright © 2017-2018 Roman Khomenko (8O-308)
// All rights reserved

#ifndef CG_LAB_PYRAMID_HPP_
#define CG_LAB_PYRAMID_HPP_

#include <Vertex.hpp>

#include <cstdint>
#include <vector>

class Pyramid {
public:
    using SizeType = std::size_t;
    using LenghtType = float;
    using VertexVector = std::vector<Vertex>;

    class Surface {
    public:
        enum class SurfaceType { BASE, FACE };

        Surface() = default;
        Surface(SurfaceType type, const VertexVector& data)
            : Type{type}, Data{data} {}

        Vertex GetCenter() const;
        SurfaceType GetType() const { return Type; };
        SizeType GetVerticesCount() const { return Data.size(); }

        const VertexVector& GetVertices() const;

    private:
        SurfaceType Type;
        VertexVector Data;
    };

    using SurfaceVector = std::vector<Surface>;

    Pyramid(SizeType facesCount,
            LenghtType baseRadius,
            LenghtType topRadius,
            LenghtType height);

    SizeType GetVerticesCount() const;
    LenghtType GetHeight() const { return Height; }
    SurfaceVector GenerateVertices(const QVector4D& viewPoint,
                                   const QMatrix4x4& rotateAndShit,
                                   const QMatrix4x4& projMoveScale) const;

private:
    static SurfaceVector ApplyMatrix(const SurfaceVector& surfaces,
                                     const QMatrix4x4& matrix);
    static void SortSurfaces(SurfaceVector& surfaces,
                             const QVector4D& viewPoint);

    SizeType FacesCount;
    LenghtType BaseRadius;
    LenghtType TopRadius;
    LenghtType Height;
    SurfaceVector Surfaces;
};

#endif  //  CG_LAB_PYRAMID_HPP_
