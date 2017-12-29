// Computer graphic lab 2
// Variant 20
// Copyright © 2017-2018 Roman Khomenko (8O-308)
// All rights reserved

#ifndef CG_LAB_MATRIX_HPP_
#define CG_LAB_MATRIX_HPP_

#include <algorithm>
#include <array>
#include <cstdint>

template <class T, std::size_t N, std::size_t M>
class Matrix {
public:
    using ArrayType = std::array<T, N * M>;
    using SizeType = std::size_t;
    using ReferenceType = T&;
    using ConstReferenceType = const T&;

    constexpr Matrix() {}
    constexpr Matrix(std::initializer_list<T> init) { *this = init; }

    constexpr Matrix& operator=(std::initializer_list<T> init) {
        if (init.size() == N * M) {
            std::copy(init.begin(), init.end(), Data.begin());
        }
        return *this;
    }

    constexpr ReferenceType operator()(SizeType i, SizeType j) {
        if (i >= N || j >= M) {
            return Data[0];
        }
        return Data[i * M + j];
    }

    constexpr ConstReferenceType operator()(SizeType i, SizeType j) const {
        if (i >= N || j >= M) {
            return Data[0];
        }
        return Data[i * M + j];
    }

    constexpr SizeType GetRowsCount() const { return N; }
    constexpr SizeType GetColsCount() const { return M; }

private:
    ArrayType Data;
};

template <class Type, std::size_t P, std::size_t Q, std::size_t R>
constexpr Matrix<Type, P, R> operator*(const Matrix<Type, P, Q>& m1,
                                       const Matrix<Type, Q, R>& m2) {
    Matrix<Type, P, R> result;
    for (auto row = 0UL; row < m1.GetRowsCount(); row++) {
        for (auto col = 0UL; col < m2.GetColsCount(); col++) {
            Type sum = 0;
            for (auto i = 0UL; i < m1.GetColsCount(); i++) {
                sum += m1(row, i) * m2(i, col);
            }
            result(row, col) = sum;
        }
    }
    return result;
}

#endif  // CG_LAB_MATRIX_HPP_
