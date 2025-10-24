// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/Core/Vector.h>

namespace ftk
{
    //! \name Matrices
    ///@{
        
    //! Base class for matrices. Matrix elements are row-major.
    template<int R, int C, typename T>
    class Matrix
    {
    public:
        constexpr Matrix();

        constexpr T get(int row, int column) const;
        constexpr void set(int row, int column, T);

        constexpr T operator [] (int) const;
        constexpr T& operator [] (int);
            
        constexpr const T* data() const;
        constexpr T* data();

    private:
        std::array<T, R * C> _e;
    };

    //! 3x3 matrix.
    template<typename T>
    class Matrix<3, 3, T>
    {
    public:
        constexpr Matrix();
        constexpr Matrix(
            T e0, T e1, T e2,
            T e3, T e4, T e5,
            T e6, T e7, T e8);

        constexpr T get(int row, int column) const;
        constexpr void set(int row, int column, T);

        constexpr T operator [] (int) const;
        constexpr T& operator [] (int);
            
        constexpr const T* data() const;
        constexpr T* data();

    private:
        std::array<T, 9> _e;
    };

    //! 4x4 matrix.
    template<typename T>
    class Matrix<4, 4, T>
    {
    public:
        constexpr Matrix();
        constexpr Matrix(
            T e0, T e1, T e2, T e3,
            T e4, T e5, T e6, T e7,
            T e8, T e9, T e10, T e11,
            T e12, T e13, T e14, T e15);

        constexpr T get(int row, int column) const;
        constexpr void set(int row, int column, T);

        constexpr T operator [] (int) const;
        constexpr T& operator [] (int);
            
        constexpr const T* data() const;
        constexpr T* data();

    private:
        std::array<T, 16> _e;
    };

    typedef Matrix<3, 3, float> M33F;
    typedef Matrix<4, 4, float> M44F;

    //! Create a translation matrix.
    template<typename T>
    constexpr Matrix<3, 3, T> translate(const Vector<2, T>&);

    //! Create a translation matrix.
    template<typename T>
    constexpr Matrix<4, 4, T> translate(const Vector<3, T>&);

    //! Create a X rotation matrix.
    template<typename T>
    Matrix<4, 4, T> rotateX(T);

    //! Create a Y rotation matrix.
    template<typename T>
    Matrix<4, 4, T> rotateY(T);

    //! Create a Z rotation matrix.
    template<typename T>
    Matrix<4, 4, T> rotateZ(T);

    //! Create a scale matrix.
    template<typename T>
    constexpr Matrix<4, 4, T> scale(const Vector<3, T>&);

    //! Create an orthographic matrix.
    template<typename T>
    constexpr Matrix<4, 4, T> ortho(T left, T right, T bottom, T top, T nearClip, T farClip);

    //! Create a perspective matrix.
    template<typename T>
    constexpr Matrix<4, 4, T> perspective(T fov, T aspect, T nearClip, T farClip);

    //! Invert a matrix.
    template<typename T>
    bool invert(const Matrix<4, 4, T>&, Matrix<4, 4, T>&);

    void to_json(nlohmann::json&, const M33F&);
    void to_json(nlohmann::json&, const M44F&);

    void from_json(const nlohmann::json&, M33F&);
    void from_json(const nlohmann::json&, M44F&);

    template<typename T>
    Matrix<3, 3, T> operator * (const Matrix<3, 3, T>&, const Matrix<3, 3, T>&);
    template<typename T>
    Vector<2, T> operator * (const Vector<2, T>& , const Matrix<3, 3, T>&);
    template<typename T>
    Matrix<4, 4, T> operator * (const Matrix<4, 4, T>&, const Matrix<4, 4, T>&);
    template<typename T>
    Vector<3, T> operator * (const Vector<3, T>& , const Matrix<4, 4, T>&);
    template<typename T>
    Vector<4, T> operator * (const Vector<4, T>& , const Matrix<4, 4, T>&);
        
    template<int R, int C, typename T>
    constexpr bool operator == (const Matrix<R, C, T>&, const Matrix<R, C, T>&);
    template<int R, int C, typename T>
    constexpr bool operator != (const Matrix<R, C, T>&, const Matrix<R, C, T>&);

    template<int R, int C, typename T>
    std::ostream& operator << (std::ostream&, const Matrix<R, C, T>&);
    template<int R, int C, typename T>
    std::istream& operator >> (std::istream&, Matrix<R, C, T>&);

    ///@}
}

#include <ftk/Core/MatrixInline.h>

