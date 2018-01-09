#include <Pyramid.hpp>

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>

#include <QDebug>

Pyramid::Pyramid(SizeType facesCount,
                 LenghtType baseRadius,
                 LenghtType topRadius,
                 LenghtType height)
    : FacesCount{facesCount},
      BaseRadius{baseRadius},
      TopRadius{topRadius},
      Height{height} {
    const auto PI = 4 * std::atan(1.0f);
    const auto PHI = 2 * PI / FacesCount;

    auto createVertex = [PHI](auto radius, auto height, auto i) {
        return Vertex(radius * std::cos(i * PHI), radius * std::sin(i * PHI),
                      height);
    };

    for (auto i = 0U; i < FacesCount; i++) {
        VertexVector face;
        face.emplace_back(createVertex(BaseRadius, 0, i));
        face.emplace_back(createVertex(TopRadius, Height, i));
        face.emplace_back(createVertex(TopRadius, Height, i + 1));
        face.emplace_back(createVertex(BaseRadius, 0, i + 1));
        face.emplace_back(createVertex(BaseRadius, 0, i));
        Surfaces.emplace_back(Surface::SurfaceType::FACE, face);
    }

    auto generateBase = [this, createVertex](auto radius, auto height) {
        VertexVector base;
        base.emplace_back(createVertex(0, height, 0));
        for (auto i = 0U; i < FacesCount; i++) {
            base.emplace_back(createVertex(radius, height, i));
        }
        base.emplace_back(createVertex(radius, height, 0));
        return base;
    };

    Surfaces.emplace_back(Surface::SurfaceType::BASE,
                          generateBase(BaseRadius, 0));
    Surfaces.emplace_back(Surface::SurfaceType::BASE,
                          generateBase(TopRadius, Height));
}

const Pyramid::VertexVector& Pyramid::Surface::GetVertices() const {
    return Data;
}

Pyramid::SizeType Pyramid::GetVerticesCount() const {
    auto count = 0UL;
    for (auto&& surface : Surfaces) {
        count += surface.GetVerticesCount();
    }
    return count;
}

Pyramid::SurfaceVector Pyramid::GenerateVertices(
    const QVector4D& viewPoint,
    const QMatrix4x4& rotateAndShit,
    const QMatrix4x4& projMoveScale) const {
    auto surfaces = ApplyMatrix(Surfaces, rotateAndShit);
    SortSurfaces(surfaces, viewPoint);
    return ApplyMatrix(surfaces, projMoveScale);
}

Pyramid::SurfaceVector Pyramid::ApplyMatrix(const SurfaceVector& surfaces,
                                            const QMatrix4x4& matrix) {
    SurfaceVector newSurfaces;

    for (auto&& surface : surfaces) {
        VertexVector vertices;
        for (auto&& vertex : surface.GetVertices()) {
            vertices.emplace_back(vertex.GetPosition() * matrix);
        }
        newSurfaces.emplace_back(surface.GetType(), vertices);
    }

    return newSurfaces;
}

void Pyramid::SortSurfaces(SurfaceVector& surfaces,
                           const QVector4D& viewPoint) {
    auto getDistance = [](auto&& surface, auto&& point) {
        auto middle = surface.GetCenter();
        auto vec = middle.GetPosition() - point;
        return vec.length();
    };

    std::sort(surfaces.begin(), surfaces.end(),
              [viewPoint, getDistance](auto&& left, auto&& right) {
                  return getDistance(left, viewPoint) >=
                         getDistance(right, viewPoint);
              });
}

Vertex Pyramid::Surface::GetCenter() const {
    Vertex result;

    switch (Type) {
        case SurfaceType::BASE: {
            result = Data[0];
        } break;
        case SurfaceType::FACE: {
            result = 1.0f / 2 * (Data[0].GetPosition() + Data[1].GetPosition());
        } break;
    }

    return result;
}
