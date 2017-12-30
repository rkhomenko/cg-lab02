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

    Pyramid(SizeType facesCount, LenghtType radius, LenghtType height);

    SizeType GetVerticesCount() const;
    const Vertex* GetData() const;

private:
    void GenerateVertices();

    SizeType FacesCount;
    LenghtType Radius;
    LenghtType Height;
    std::vector<Vertex> Vertices;
};

#endif  //  CG_LAB_PYRAMID_HPP_
