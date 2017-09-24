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

#ifndef _PHX_MATH_VECTOR3_H_
#define _PHX_MATH_VECTOR3_H_

namespace Phx {
namespace Math {

    class Vector3
    {
    public:
        float X;
        float Y;
        float Z;

    public:
        static const Vector3 Zero;
        static const Vector3 One;
        static const Vector3 UnitX;
        static const Vector3 UnitY;
        static const Vector3 UnitZ;
        static const Vector3 Max;
        static const Vector3 Min;
        static const Vector3 Epsilon;
        static const Vector3 Tolerance;

        static const Vector3 Up;
        static const Vector3 Down;
        static const Vector3 Left;
        static const Vector3 Right;
        static const Vector3 Forward;
        static const Vector3 Backward;

    public:
        inline Vector3()
        { 
            // Do nothing in the default ctor.
            // So we don't have to pay for arrays or vectors initialized as an out parameter.
        }
        inline explicit Vector3(float f);
        inline explicit Vector3(float x, float y, float z);
        inline explicit Vector3(const Vector2 &src, float z);
        inline Vector3(const Vector3 &src);

        inline ~Vector3() { }

        inline Vector3& operator=(const Vector3 &rhs);

        inline float& operator[](unsigned int idx);
        inline const float& operator[](unsigned int idx) const;

        inline Vector3& operator+=(const Vector3 &rhs);
        inline Vector3& operator+=(float rhs);

        inline Vector3& operator-=(const Vector3 &rhs);
        inline Vector3& operator-=(float rhs);

        inline Vector3& operator*=(const Vector3 &rhs);
        inline Vector3& operator*=(float rhs);

        inline Vector3& operator/=(const Vector3 &rhs);
        inline Vector3& operator/=(float rhs);

        inline void Transform(const Matrix4x4 &rhs);
        inline void Transform(const Quaternion &q);

        inline void Clamp(const Vector3 &min, const Vector3 &max);

        inline float Length() const;
        inline float LengthSquared() const;

        inline void Normalize();

        inline void Negate();

        inline void Copy(const Vector3 &src);
        inline void Copy(const float *pSrc);
        inline void Copy(float x, float y, float z);
        inline void Copy(float f);

        inline float * ToArray();
        inline const float * ToArray() const;
    };

    inline bool operator==(const Vector3 &lhs, const Vector3 &rhs);
    inline bool operator!=(const Vector3 &lhs, const Vector3 &rhs);
    inline bool operator>(const Vector3 &lhs, const Vector3 &rhs);
    inline bool operator>=(const Vector3 &lhs, const Vector3 &rhs);
    inline bool operator<(const Vector3 &lhs, const Vector3 &rhs);
    inline bool operator<=(const Vector3 &lhs, const Vector3 &rhs);

    inline Vector3 operator+(const Vector3 &lhs, const Vector3 &rhs);
    inline Vector3 operator+(const Vector3 &lhs, float rhs);

    inline Vector3 operator-(const Vector3 &lhs, const Vector3 &rhs);
    inline Vector3 operator-(const Vector3 &lhs, float rhs);
    inline Vector3 operator-(const Vector3 &v);

    inline Vector3 operator*(const Vector3 &lhs, const Vector3 &rhs);
    inline Vector3 operator*(const Vector3 &lhs, float rhs);

    inline Vector3 operator/(const Vector3 &lhs, const Vector3 &rhs);
    inline Vector3 operator/(const Vector3 &lhs, float rhs);

    inline bool ExactlyEqual(const Vector3 &lhs, const Vector3 &rhs);
    inline bool ExactlyZero(const Vector3 &v);

    inline bool NearlyEqual(const Vector3 &lhs, const Vector3 &rhs);
    inline bool NearlyZero(const Vector3 &v);

    inline bool AllLess(const Vector3 &lhs, const Vector3 &rhs);
    inline bool AllLessEqual(const Vector3 &lhs, const Vector3 &rhs);

    inline bool AllGreater(const Vector3 &lhs, const Vector3 &rhs);
    inline bool AllGreaterEqual(const Vector3 &lhs, const Vector3 &rhs);

    inline bool IsNormalized(const Vector3 &v);

    inline Vector3 Add(const Vector3 &lhs, const Vector3 &rhs);
    inline Vector3 Add(const Vector3 &lhs, float rhs);
    inline void Add(const Vector3 &lhs, const Vector3 &rhs, Vector3 &out);
    inline void Add(const Vector3 &lhs, float rhs, Vector3 &out);

    inline Vector3 Subtract(const Vector3 &lhs, const Vector3 &rhs);
    inline Vector3 Subtract(const Vector3 &lhs, float rhs);
    inline void Subtract(const Vector3 &lhs, const Vector3 &rhs, Vector3 &out);
    inline void Subtract(const Vector3 &lhs, float rhs, Vector3 &out);

    inline Vector3 Multiply(const Vector3 &lhs, const Vector3 &rhs);
    inline Vector3 Multiply(const Vector3 &lhs, float rhs);
    inline void Multiply(const Vector3 &lhs, const Vector3 &rhs, Vector3 &out);
    inline void Multiply(const Vector3 &lhs, float rhs, Vector3 &out);

    inline Vector3 Transform(const Vector3 &v, const Matrix4x4 &m);
    inline Vector3 Transform(const Vector3 &v, const Quaternion &q);
    inline void Transform(const Vector3 &v, const Matrix4x4 &m, Vector3 &out);
    inline void Transform(const Vector3 &v, const Quaternion &q, Vector3 &out);

    inline Vector3 Divide(const Vector3 &lhs, const Vector3 &rhs);
    inline Vector3 Divide(const Vector3 &lhs, float rhs);
    inline void Divide(const Vector3 &lhs, const Vector3 &rhs, Vector3 &out);
    inline void Divide(const Vector3 &lhs, float rhs, Vector3 &out);

    inline Vector3 Clamp(const Vector3 &v, const Vector3 &min, const Vector3 &max);
    inline void Clamp(const Vector3 &v, const Vector3 &min, const Vector3 &max, Vector3 &out);

    inline float Length(const Vector3 &v);
    inline float LengthSquared(const Vector3 &v);

    inline float Distance(const Vector3 &lhs, const Vector3 &rhs);
    inline float DistanceSquared(const Vector3 &lhs, const Vector3 &rhs);

    inline Vector3 Normalize(const Vector3 &v);
    inline void Normalize(const Vector3 &v, Vector3 &out);

    inline Vector3 Negate(const Vector3 &v);
    inline void Negate(const Vector3 &v, Vector3 &out);

    inline float Dot(const Vector3 &lhs, const Vector3 &rhs);

    inline Vector3 Cross(const Vector3 &lhs, const Vector3 &rhs);
    inline void Cross(const Vector3 &lhs, const Vector3 &rhs, Vector3 &out);

    inline Vector3 Lerp(const Vector3 &v1, const Vector3 &v2, float weight);
    inline void Lerp(const Vector3 &v1, const Vector3 &v2, float weight, Vector3 &out);

    inline Vector3 Hermite(const Vector3 &v1, const Vector3 &t1, const Vector3 &v2, const Vector3 &t2, float weight);
    inline void Hermite(const Vector3 &v1, const Vector3 &t1, const Vector3 &v2, const Vector3 &t2, float weight, Vector3 &out);

    inline Vector3 SmoothStep(const Vector3 &v1, const Vector3 &v2, float weight);
    inline void SmoothStep(const Vector3 &v1, const Vector3 &v2, float weight, Vector3 &out);

} //namespace Math
} //namespace Phx

#endif //_PHX_MATH_VECTOR3_H_
