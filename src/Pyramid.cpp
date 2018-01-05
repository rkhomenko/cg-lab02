#include <Pyramid.hpp>

#include <array>
#include <cmath>

#include <QDebug>

Pyramid::Pyramid(SizeType facesCount,
                 LenghtType baseRadius,
                 LenghtType topRadius,
                 LenghtType height)
    : FacesCount{facesCount},
      BaseRadius{baseRadius},
      TopRadius{topRadius},
      Height{height} {
    GenerateVertices();
}

Pyramid::SizeType Pyramid::GetVerticesCount() const {
    return Vertices.size();
}

Pyramid::SizeType Pyramid::GetFacesCount() const {
    return FacesCount;
}

const Vertex* Pyramid::GetData() const {
    return Vertices.data();
}

void Pyramid::GenerateVertices() {
    const auto PI = 4 * std::atan(1.0f);
    const auto PHI = 2 * PI / FacesCount;

    auto createVertex = [PHI](auto radius, auto height, auto i) {
        return Vertex(radius * std::cos(i * PHI), radius * std::sin(i * PHI),
                      height);
    };

    for (auto i = 0U; i < FacesCount; i++) {
        Vertices.emplace_back(createVertex(BaseRadius, 0, i));
        Vertices.emplace_back(createVertex(TopRadius, Height, i));
        Vertices.emplace_back(createVertex(TopRadius, Height, i + 1));
        Vertices.emplace_back(createVertex(BaseRadius, 0, i + 1));
    }
}
