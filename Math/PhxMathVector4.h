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

#ifndef _PHX_MATH_VECTOR4_H_
#define _PHX_MATH_VECTOR4_H_

namespace Phx {
namespace Math {

    class Vector4
    {
    public:
        float X;
        float Y;
        float Z;
        float W;

    public:
        static const Vector4 Zero;
        static const Vector4 One;
        static const Vector4 UnitX;
        static const Vector4 UnitY;
        static const Vector4 UnitZ;
        static const Vector4 UnitW;
        static const Vector4 Max;
        static const Vector4 Min;
        static const Vector4 Epsilon;
        static const Vector4 Tolerance;

    public:
        inline Vector4()
        { 
            // Do nothing in the default ctor.
            // So we don't have to pay for arrays or vectors initialized as an out parameter.
        }
        inline explicit Vector4(float f);
        inline explicit Vector4(float x, float y, float z, float w);
        inline explicit Vector4(const Vector2 & src, float z, float w);
        inline explicit Vector4(const Vector3 & src, float w);
        inline Vector4(const Vector4 & src);

        inline ~Vector4() { }

        inline Vector4 & operator=(const Vector4 & rhs);

        inline float & operator[](unsigned int idx);
        inline const float & operator[](unsigned int idx) const;

        inline Vector4 & operator+=(const Vector4 & rhs);
        inline Vector4 & operator+=(float rhs);

        inline Vector4 & operator-=(const Vector4 & rhs);
        inline Vector4 & operator-=(float rhs);

        inline Vector4 & operator*=(const Vector4 & rhs);
        inline Vector4 & operator*=(float rhs);

        inline Vector4 & operator/=(const Vector4 & rhs);
        inline Vector4 & operator/=(float rhs);

        inline void Transform(const Matrix4x4 & m);

        inline void Clamp(const Vector4 & min, const Vector4 & max);
        inline void Clamp01();

        inline float Length() const;
        inline float LengthSquared() const;

        inline void Normalize();

        inline void Negate();

        inline void Copy(const Vector4 & src);
        inline void Copy(const float * pSrc);
        inline void Copy(float x, float y, float z, float w);
        inline void Copy(float f);

        inline float * ToArray();
        inline const float * ToArray() const;
    };

    inline bool operator==(const Vector4 & lhs, const Vector4 & rhs);
    inline bool operator!=(const Vector4 & lhs, const Vector4 & rhs);
    inline bool operator>(const Vector4 & lhs, const Vector4 & rhs);
    inline bool operator>=(const Vector4 & lhs, const Vector4 & rhs);
    inline bool operator<(const Vector4 & lhs, const Vector4 & rhs);
    inline bool operator<=(const Vector4 & lhs, const Vector4 & rhs);

    inline Vector4 operator+(const Vector4 & lhs, const Vector4 & rhs);
    inline Vector4 operator+(const Vector4 & lhs, float rhs);

    inline Vector4 operator-(const Vector4 & lhs, const Vector4 & rhs);
    inline Vector4 operator-(const Vector4 & lhs, float rhs);
    inline Vector4 operator-(const Vector4 & v);

    inline Vector4 operator*(const Vector4 & lhs, const Vector4 & rhs);
    inline Vector4 operator*(const Vector4 & lhs, float rhs);

    inline Vector4 operator/(const Vector4 & lhs, const Vector4 & rhs);
    inline Vector4 operator/(const Vector4 & lhs, float rhs);

    inline bool ExactlyEqual(const Vector4 & lhs, const Vector4 & rhs);
    inline bool ExactlyZero(const Vector4 & v);

    inline bool NearlyEqual(const Vector4 & lhs, const Vector4 & rhs);
    inline bool NearlyZero(const Vector4 & v);

    inline bool AllLess(const Vector4 & lhs, const Vector4 & rhs);
    inline bool AllLessEqual(const Vector4 & lhs, const Vector4 & rhs);

    inline bool AllGreater(const Vector4 & lhs, const Vector4 & rhs);
    inline bool AllGreaterEqual(const Vector4 & lhs, const Vector4 & rhs);

    inline bool IsNormalized(const Vector4 & v);

    inline Vector4 Add(const Vector4 & lhs, const Vector4 & rhs);
    inline Vector4 Add(const Vector4 & lhs, float rhs);
    inline void Add(const Vector4 & lhs, const Vector4 & rhs, Vector4 & out);
    inline void Add(const Vector4 & lhs, float rhs, Vector4 & out);

    inline Vector4 Subtract(const Vector4 & lhs, const Vector4 & rhs);
    inline Vector4 Subtract(const Vector4 & lhs, float rhs);
    inline void Subtract(const Vector4 & lhs, const Vector4 & rhs, Vector4 & out);
    inline void Subtract(const Vector4 & lhs, float rhs, Vector4 & out);

    inline Vector4 Multiply(const Vector4 & lhs, const Vector4 & rhs);
    inline Vector4 Multiply(const Vector4 & lhs, float rhs);
    inline void Multiply(const Vector4 & lhs, const Vector4 & rhs, Vector4 & out);
    inline void Multiply(const Vector4 & lhs, float rhs, Vector4 & out);

    inline Vector4 Transform(const Vector4 & v, const Matrix4x4 & m);
    inline void Transform(const Vector4 & v, const Matrix4x4 & m, Vector4 & out);

    inline Vector4 Divide(const Vector4 & lhs, const Vector4 & rhs);
    inline Vector4 Divide(const Vector4 & lhs, float rhs);
    inline void Divide(const Vector4 & lhs, const Vector4 & rhs, Vector4 & out);
    inline void Divide(const Vector4 & lhs, float rhs, Vector4 & out);

    inline Vector4 Clamp(const Vector4 & v, const Vector4 & min, const Vector4 & max);
    inline void Clamp(const Vector4 & v, const Vector4 & min, const Vector4 & max, Vector4 & out);

    inline Vector4 Clamp01(const Vector4 & v);
    inline void Clamp01(const Vector4 & v, Vector4 & out);

    inline Vector4 Remap(const Vector4 & in, const Vector4 & inRangeMin, const Vector4 & inRangeMax, const Vector4 & outRangeMin, const Vector4 & outRangeMax);
    inline void Remap(const Vector4 & in, const Vector4 & inRangeMin, const Vector4 & inRangeMax, const Vector4 & outRangeMin, const Vector4 & outRangeMax, Vector4 & out);

    inline Vector4 Max(const Vector4 & v1, const Vector4 & v2);
    inline void Max(const Vector4 & v1, const Vector4 & v2, Vector4 & out);

    inline Vector4 Min(const Vector4 & v1, const Vector4 & v2);
    inline void Min(const Vector4 & v1, const Vector4 & v2, Vector4 & out);

    inline Vector4 Ceiling(const Vector4 & v);
    inline void Ceiling(const Vector4 & v, Vector4 & out);

    inline Vector4 Floor(const Vector4 & v);
    inline void Floor(const Vector4 & v, Vector4 & out);

    inline Vector4 Round(const Vector4 & v);
    inline void Round(const Vector4 & v, Vector4 & out);

    inline float Length(const Vector4 & v);
    inline float LengthSquared(const Vector4 & v); 

    inline float Distance(const Vector4 & lhs, const Vector4 & rhs);
    inline float DistanceSquared(const Vector4 & lhs, const Vector4 & rhs);

    inline Vector4 Normalize(const Vector4 & v);
    inline void Normalize(const Vector4 & v, Vector4 & out);

    inline Vector4 Negate(const Vector4 & v);
    inline void Negate(const Vector4 & v, Vector4 & out);

    inline float Dot(const Vector4 & lhs, const Vector4 & rhs);

    inline Vector4 Lerp(const Vector4 & v1, const Vector4 & v2, float weight);
    inline void Lerp(const Vector4 & v1, const Vector4 & v2, float weight, Vector4 & out);

    inline Vector4 Hermite(const Vector4 & v1, const Vector4 & t1, const Vector4 & v2, const Vector4 & t2, float weight);
    inline void Hermite(const Vector4 & v1, const Vector4 & t1, const Vector4 & v2, const Vector4 & t2, float weight, Vector4 & out);

    inline Vector4 SmoothStep(const Vector4 & v1, const Vector4 & v2, float weight);
    inline void SmoothStep(const Vector4 & v1, const Vector4 & v2, float weight, Vector4 & out);

    inline void Swap(Vector4 & v1, Vector4 & v2);

} //namespace Math
} //namespace Phx

#endif //_PHX_MATH_VECTOR4_H_
