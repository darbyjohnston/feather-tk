// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <ftk/Core/Math.h>

#include <cmath>

namespace ftk
{
    template<int R, int C, typename T>
    constexpr Matrix<R, C, T>::Matrix()
    {
        for (int r = 0; r < R; ++r)
        {
            for (int c = 0; c < C; ++c)
            {
                _e[r * C + c] = T(0);
            }
        }            
    }

    template<int R, int C, typename T>
    constexpr T Matrix<R, C, T>::get(int row, int column) const
    {
        return _e[row * C + column];
    }

    template<int R, int C, typename T>
    constexpr void Matrix<R, C, T>::set(int row, int column, T v)
    {
        _e[row * C + column] = v;
    }

    template<int R, int C, typename T>
    constexpr T Matrix<R, C, T>::operator [] (int index) const
    {
        return _e[index];
    }

    template<int R, int C, typename T>
    constexpr T& Matrix<R, C, T>::operator [] (int index)
    {
        return _e[index];
    }
            
    template<int R, int C, typename T>
    constexpr const T* Matrix<R, C, T>::data() const
    {
        return _e.data();
    }

    template<int R, int C, typename T>
    constexpr T* Matrix<R, C, T>::data()
    {
        return _e.data();
    }

    template<typename T>
    constexpr Matrix<3, 3, T>::Matrix() :
        _e({
            T(1), T(0), T(0),
            T(0), T(1), T(0),
            T(0), T(0), T(1)
        })
    {}

    template<typename T>
    constexpr Matrix<3, 3, T>::Matrix(
        T e0, T e1, T e2,
        T e3, T e4, T e5,
        T e6, T e7, T e8) :
        _e({
            e0, e1, e2,
            e3, e4, e5,
            e6, e7, e8
        })
    {}

    template<typename T>
    constexpr T Matrix<3, 3, T>::get(int row, int column) const
    {
        return _e[row * 3 + column];
    }

    template<typename T>
    constexpr void Matrix<3, 3, T>::set(int row, int column, T v)
    {
        _e[row * 3 + column] = v;
    }

    template<typename T>
    constexpr T Matrix<3, 3, T>::operator [] (int index) const
    {
        return _e[index];
    }

    template<typename T>
    constexpr T& Matrix<3, 3, T>::operator [] (int index)
    {
        return _e[index];
    }
            
    template<typename T>
    constexpr const T* Matrix<3, 3, T>::data() const
    {
        return _e.data();
    }

    template<typename T>
    constexpr T* Matrix<3, 3, T>::data()
    {
        return _e.data();
    }

    template<typename T>
    constexpr Matrix<4, 4, T>::Matrix() :
        _e({
            T(1), T(0), T(0), T(0),
            T(0), T(1), T(0), T(0),
            T(0), T(0), T(1), T(0),
            T(0), T(0), T(0), T(1)
        })
    {}

    template<typename T>
    constexpr Matrix<4, 4, T>::Matrix(
        T e0, T e1, T e2, T e3,
        T e4, T e5, T e6, T e7,
        T e8, T e9, T e10, T e11,
        T e12, T e13, T e14, T e15) :
        _e({
            e0, e1, e2, e3,
            e4, e5, e6, e7,
            e8, e9, e10, e11,
            e12, e13, e14, e15
        })
    {}

    template<typename T>
    constexpr T Matrix<4, 4, T>::get(int row, int column) const
    {
        return _e[row * 4 + column];
    }

    template<typename T>
    constexpr void Matrix<4, 4, T>::set(int row, int column, T v)
    {
        _e[row * 4 + column] = v;
    }

    template<typename T>
    constexpr T Matrix<4, 4, T>::operator [] (int index) const
    {
        return _e[index];
    }

    template<typename T>
    constexpr T& Matrix<4, 4, T>::operator [] (int index)
    {
        return _e[index];
    }

    template<typename T>
    constexpr const T* Matrix<4, 4, T>::data() const
    {
        return _e.data();
    }

    template<typename T>
    constexpr T* Matrix<4, 4, T>::data()
    {
        return _e.data();
    }

    template<typename T>
    constexpr Matrix<3, 3, T> translate(const Vector<2, T>& value)
    {
        return Matrix<3, 3, T>(
            T(1), T(0), T(0),
            T(0), T(1), T(0),
            value.x, value.y, T(1));
    }

    template<typename T>
    constexpr Matrix<4, 4, T> translate(const Vector<3, T>& value)
    {
        return Matrix<4, 4, T>(
            T(1), T(0), T(0), T(0),
            T(0), T(1), T(0), T(0),
            T(0), T(0), T(1), T(0),
            value.x, value.y, value.z, T(1));
    }

    template<typename T>
    inline Matrix<4, 4, T> rotateX(T angle)
    {
        const T a = std::cos(deg2rad(angle));
        const T b = std::sin(deg2rad(angle));
        return Matrix<4, 4, T>(
            T(1), T(0), T(0), T(0),
            T(0), a,    b,    T(0),
            T(0), -b,   a,    T(0),
            T(0), T(0), T(0), T(1));
    }

    template<typename T>
    inline Matrix<4, 4, T> rotateY(T angle)
    {
        const T a = std::cos(deg2rad(angle));
        const T b = std::sin(deg2rad(angle));
        return Matrix<4, 4, T>(
            a,    T(0), -b,   T(0),
            T(0), T(1), T(0), T(0),
            b,    T(0), a,    T(0),
            T(0), T(0), T(0), T(1));
    }

    template<typename T>
    inline Matrix<4, 4, T> rotateZ(T angle)
    {
        const T a = std::cos(deg2rad(angle));
        const T b = std::sin(deg2rad(angle));
        return Matrix<4, 4, T>(
            a,   -b,    T(0), T(0),
            b,    a,    T(0), T(0),
            T(0), T(0), T(1), T(0),
            T(0), T(0), T(0), T(1));
    }

    template<typename T>
    constexpr Matrix<4, 4, T> scale(const Vector<3, T>& value)
    {
        return Matrix<4, 4, T>(
            value.x, T(0),    T(0),    T(0),
            T(0),    value.y, T(0),    T(0),
            T(0),    T(0),    value.z, T(0),
            T(0),    T(0),    T(0),    T(1));
    }

    template<typename T>
    constexpr Matrix<4, 4, T> ortho(T left, T right, T bottom, T top, T nearClip, T farClip)
    {
        const T a = T(2) / (right - left);
        const T b = T(2) / (top - bottom);
        const T c = T(-2) / (farClip - nearClip);
        const T x = -(right + left) / (right - left);
        const T y = -(top + bottom) / (top - bottom);
        const T z = -(farClip + nearClip) / (farClip - nearClip);
        return Matrix<4, 4, T>(
            a,    T(0), T(0), T(0),
            T(0), b,    T(0), T(0),
            T(0), T(0), c,    T(0),
            x,    y,    z,    T(1));
    }

    template<typename T>
    constexpr Matrix<4, 4, T> perspective(T fov, T aspect, T nearClip, T farClip)
    {
        const T f = T(1) / std::tan(deg2rad(fov) / T(2));
        const T a = f / aspect;
        const T b = (farClip + nearClip) / (nearClip - farClip);
        const T c = T(2) * farClip * nearClip / (nearClip - farClip);
        return Matrix<4, 4, T>(
            a,    T(0), T(0), T(0),
            T(0), f,    T(0), T(0),
            T(0), T(0), b,    T(-1),
            T(0), T(0), c,    T(0));
    }

    template<typename T>
    inline Matrix<3, 3, T> operator * (const Matrix<3, 3, T>& a, const Matrix<3, 3, T>& b)
    {
        Matrix<3, 3, T> out;
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                float tmp = 0.F;
                for (int k = 0; k < 3; ++k)
                {
                    tmp += b.get(i, k) * a.get(k, j);
                }
                out.set(i, j, tmp);
            }
        }
        return out;
    }

    template<typename T>
    inline Vector<2, T> operator * (const Vector<2, T>& v, const Matrix<3, 3, T>& m)
    {
        const T x = v[0] * m[0] + v[1] * m[3] + m[6];
        const T y = v[0] * m[1] + v[1] * m[4] + m[7];
        return Vector<2, T>(x, y);
    }

    template<typename T>
    inline Matrix<4, 4, T> operator * (const Matrix<4, 4, T>& a, const Matrix<4, 4, T>& b)
    {
        Matrix<4, 4, T> out;
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                float tmp = 0.F;
                for (int k = 0; k < 4; ++k)
                {
                    tmp += b.get(i, k) * a.get(k, j);
                }
                out.set(i, j, tmp);
            }
        }
        return out;
    }

    template<typename T>
    inline Vector<3, T> operator * (const Vector<3, T>& v, const Matrix<4, 4, T>& m)
    {
        const T x = v[0] * m[0] + v[1] * m[4] + v[2] * m[8] + m[12];
        const T y = v[0] * m[1] + v[1] * m[5] + v[2] * m[9] + m[13];
        const T z = v[0] * m[2] + v[1] * m[6] + v[2] * m[10] + m[14];
        const T w = v[0] * m[3] + v[1] * m[7] + v[2] * m[11] + m[15];
        return Vector<3, T>(x / w, y / w, z / w);
    }

    template<typename T>
    inline Vector<4, T> operator * (const Vector<4, T>& v, const Matrix<4, 4, T>& m)
    {
        Vector<4, T> out;
        out.x = v[0] * m[0] + v[1] * m[4] + v[2] * m[8] + v[3] * m[12];
        out.y = v[0] * m[1] + v[1] * m[5] + v[2] * m[9] + v[3] * m[13];
        out.z = v[0] * m[2] + v[1] * m[6] + v[2] * m[10] + v[3] * m[14];
        out.w = v[0] * m[3] + v[1] * m[7] + v[2] * m[11] + v[3] * m[15];
        return out;
    }
        
    template<int R, int C, typename T>
    constexpr bool operator == (const Matrix<R, C, T>& a, const Matrix<R, C, T>& b)
    {
        bool out = true;
        for (int r = 0; r < R; ++r)
        {
            for (int c = 0; c < C; ++c)
            {
                out &= a.get(r, c) == b.get(r, c);
            }
        }
        return out;
    }
        
    template<int R, int C, typename T>
    constexpr bool operator != (const Matrix<R, C, T>& a, const Matrix<R, C, T>& b)
    {
        return !(a == b);
    }
        
    template<int R, int C, typename T>
    inline std::ostream& operator << (std::ostream& os, const Matrix<R, C, T>& m)
    {
        for (int r = 0; r < R; ++r)
        {
            for (int c = 0; c < C; ++c)
            {
                os << m.get(r, c);
                if (r * C + c < R * C - 1)
                {
                    os << " ";
                }
            }
        }
        return os;
    }
        
    template<int R, int C, typename T>
    inline std::istream& operator >> (std::istream& is, Matrix<R, C, T>& m)
    {
        for (int r = 0; r < R; ++r)
        {
            for (int c = 0; c < C; ++c)
            {
                T v;
                is >> v;
                m.set(r, c, v);
            }
        }
        return is;
    }
}
