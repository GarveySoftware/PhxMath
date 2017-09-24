/*  

The MIT License (MIT)

Copyright (c) 2017 Jim Garvey

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE

*/

#ifndef _PHX_MATH_VECTOR2_H_
#define _PHX_MATH_VECTOR2_H_

namespace Phx {
namespace Math {

    class Vector2
    {
    public:
        float X;
        float Y;

    public:
        static const Vector2 Zero;
        static const Vector2 One;
        static const Vector2 UnitX;
        static const Vector2 UnitY;
        static const Vector2 Max;
        static const Vector2 Min;
        static const Vector2 Epsilon;
        static const Vector2 Tolerance;

    public:
        inline Vector2()
        { 
            // Do nothing in the default ctor.
            // So we don't have to pay for arrays or vectors initialized as an out parameter.
        }
        inline explicit Vector2(float f);
        inline explicit Vector2(float x, float y);
        inline Vector2(const Vector2 &src);

        inline ~Vector2() { }

        inline Vector2& operator=(const Vector2 &rhs);

        inline float& operator[](unsigned int idx);
        inline const float& operator[](unsigned int idx) const;

        inline Vector2& operator+=(const Vector2 &rhs);
        inline Vector2& operator+=(float rhs);

        inline Vector2& operator-=(const Vector2 &rhs);
        inline Vector2& operator-=(float rhs);

        inline Vector2& operator*=(const Vector2 &rhs);
        inline Vector2& operator*=(float rhs);

        inline Vector2& operator/=(const Vector2 &rhs);
        inline Vector2& operator/=(float rhs);

        inline void Transform(const Matrix4x4 &m);
        inline void Transform(const Quaternion &q);

        inline void Clamp(const Vector2 &min, const Vector2 &max);

        inline float Length() const;
        inline float LengthSquared() const;

        inline void Normalize();

        inline void Negate();

        inline void Copy(const Vector2 &src);
        inline void Copy(const float *pSrc);
        inline void Copy(float x, float y);
        inline void Copy(float f);

        inline float * ToArray();
        inline const float * ToArray() const;
    };

    inline bool operator==(const Vector2 &lhs, const Vector2 &rhs);
    inline bool operator!=(const Vector2 &lhs, const Vector2 &rhs);
    inline bool operator>(const Vector2 &lhs, const Vector2 &rhs);
    inline bool operator>=(const Vector2 &lhs, const Vector2 &rhs);
    inline bool operator<(const Vector2 &lhs, const Vector2 &rhs);
    inline bool operator<=(const Vector2 &lhs, const Vector2 &rhs);

    inline Vector2 operator+(const Vector2 &lhs, const Vector2 &rhs);
    inline Vector2 operator+(const Vector2 &lhs, float rhs);

    inline Vector2 operator-(const Vector2 &lhs, const Vector2 &rhs);
    inline Vector2 operator-(const Vector2 &lhs, float rhs);
    inline Vector2 operator-(const Vector2 &v);

    inline Vector2 operator*(const Vector2 &lhs, const Vector2 &rhs);
    inline Vector2 operator*(const Vector2 &lhs, float rhs);

    inline Vector2 operator/(const Vector2 &lhs, const Vector2 &rhs);
    inline Vector2 operator/(const Vector2 &lhs, float rhs);

    inline bool ExactlyEqual(const Vector2 &lhs, const Vector2 &rhs);
    inline bool ExactlyZero(const Vector2 &v);

    inline bool NearlyEqual(const Vector2 &lhs, const Vector2 &rhs);
    inline bool NearlyZero(const Vector2 &v);

    inline bool AllLess(const Vector2 &lhs, const Vector2 &rhs);
    inline bool AllLessEqual(const Vector2 &lhs, const Vector2 &rhs);

    inline bool AllGreater(const Vector2 &lhs, const Vector2 &rhs);
    inline bool AllGreaterEqual(const Vector2 &lhs, const Vector2 &rhs);

    inline bool IsNormalized(const Vector2 &v);

    inline Vector2 Add(const Vector2 &lhs, const Vector2 &rhs);
    inline Vector2 Add(const Vector2 &lhs, float rhs);
    inline void Add(const Vector2 &lhs, const Vector2 &rhs, Vector2 &out);
    inline void Add(const Vector2 &lhs, float rhs, Vector2 &out);

    inline Vector2 Subtract(const Vector2 &lhs, const Vector2 &rhs);
    inline Vector2 Subtract(const Vector2 &lhs, float rhs);
    inline void Subtract(const Vector2 &lhs, const Vector2 &rhs, Vector2 &out);
    inline void Subtract(const Vector2 &lhs, float rhs, Vector2 &out);

    inline Vector2 Multiply(const Vector2 &lhs, const Vector2 &rhs);
    inline Vector2 Multiply(const Vector2 &lhs, float rhs);
    inline void Multiply(const Vector2 &lhs, const Vector2 &rhs, Vector2 &out);
    inline void Multiply(const Vector2 &lhs, float rhs, Vector2 &out);

    inline Vector2 Transform(const Vector2 &v, const Matrix4x4 &m);
    inline Vector2 Transform(const Vector2 &v, const Quaternion &q);
    inline void Transform(const Vector2 &v, const Matrix4x4 &m, Vector2 &out);
    inline void Transform(const Vector2 &v, const Quaternion &q, Vector2 &out);

    inline Vector2 Divide(const Vector2 &lhs, const Vector2 &rhs);
    inline Vector2 Divide(const Vector2 &lhs, float rhs);
    inline void Divide(const Vector2 &lhs, const Vector2 &rhs, Vector2 &out);
    inline void Divide(const Vector2 &lhs, float rhs, Vector2 &out);

    inline Vector2 Clamp(const Vector2 &v, const Vector2 &min, const Vector2 &max);
    inline void Clamp(const Vector2 &v, const Vector2 &min, const Vector2 &max, Vector2 &out);

    inline float Length(const Vector2 &v);
    inline float LengthSquared(const Vector2 &v);

    inline float Distance(const Vector2 &lhs, const Vector2 &rhs);
    inline float DistanceSquared(const Vector2 &lhs, const Vector2 &rhs);

    inline Vector2 Normalize(const Vector2 &v);
    inline void Normalize(const Vector2 &v, Vector2 &out);

    inline Vector2 Negate(const Vector2 &v);
    inline void Negate(const Vector2 &v, Vector2 &out);

    inline float Dot(const Vector2 &lhs, const Vector2 &rhs);

    inline Vector2 Lerp(const Vector2 &v1, const Vector2 &v2, float weight);
    inline void Lerp(const Vector2 &v1, const Vector2 &v2, float weight, Vector2 &out);

    inline Vector2 Hermite(const Vector2 &v1, const Vector2 &t1, const Vector2 &v2, const Vector2 &t2, float weight);
    inline void Hermite(const Vector2 &v1, const Vector2 &t1, const Vector2 &v2, const Vector2 &t2, float weight, Vector2 &out);

    inline Vector2 SmoothStep(const Vector2 &v1, const Vector2 &v2, float weight);
    inline void SmoothStep(const Vector2 &v1, const Vector2 &v2, float weight, Vector2 &out);

} //namespace Math
} //namespace Phx

#endif //_PHX_MATH_VECTOR2_H_
