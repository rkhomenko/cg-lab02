#include <Pyramid.hpp>

#include <array>
#include <cmath>

#include <QDebug>

Pyramid::Pyramid(SizeType facesCount, LenghtType radius, LenghtType height)
    : FacesCount{facesCount}, Radius{radius}, Height{height} {
    GenerateVertices();
}

Pyramid::SizeType Pyramid::GetVerticesCount() const {
    return Vertices.size();
}
const Vertex* Pyramid::GetData() const {
    return Vertices.data();
}

void Pyramid::GenerateVertices() {
    const auto TOP = Vertex(0.0f, 0.f, Height);
    const auto PI = 4 * std::atan(1.0f);
    const auto PHI = 2 * PI / FacesCount;

    auto createVertex = [this, PHI](auto i) {
        return Vertex(Radius * std::cos(i * PHI), Radius * std::sin(i * PHI),
                      0);
    };

    Vertices.emplace_back(TOP);
    for (auto i = 0UL; i <= FacesCount; i++) {
        Vertices.emplace_back(createVertex(i));
    }
}
