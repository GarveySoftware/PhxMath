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

#ifndef _PHX_MATH_VECTOR2_INL_
#define _PHX_MATH_VECTOR2_INL_

namespace Phx {
namespace Math {

    inline Vector2::Vector2(float f) 
        : X(f), Y(f)
    { }

    inline Vector2::Vector2(float x, float y)
        : X(x), Y(y)
    { }
    
    inline Vector2::Vector2(const Vector2 & src)
    { 
        Set(src);
    }

    inline Vector2 & Vector2::operator=(const Vector2 & rhs)
    {
        Set(rhs);
        return *this;
    }

    inline float & Vector2::operator[](unsigned int idx)
    {
        DebugAssert(idx < 2, "Invalid idx (%u) into a vector 2!", idx);
        return ToArray()[idx];
    }

    inline const float & Vector2::operator[](unsigned int idx) const
    {
        DebugAssert(idx < 2, "Invalid idx (%u) into a vector 2!", idx);
        return ToArray()[idx];
    }

    inline Vector2 & Vector2::operator+=(const Vector2 & rhs)
    {
        Math::Add(*this, rhs, *this);
        return *this;
    }

    inline Vector2 & Vector2::operator+=(float rhs)
    {
        Math::Add(*this, rhs, *this);
        return *this;
    }

    inline Vector2 & Vector2::operator-=(const Vector2 & rhs)
    {
        Math::Subtract(*this, rhs, *this);
        return *this;
    }

    inline Vector2 & Vector2::operator-=(float rhs)
    {
        Math::Subtract(*this, rhs, *this);
        return *this;
    }

    inline Vector2 & Vector2::operator*=(const Vector2 & rhs)
    {
        Math::Multiply(*this, rhs, *this);
        return *this;
    }

    inline Vector2 & Vector2::operator*=(float rhs)
    {
        Math::Multiply(*this, rhs, *this);
        return *this;
    }

    inline Vector2 & Vector2::operator/=(const Vector2 & rhs)
    {
        Math::Divide(*this, rhs, *this);
        return *this;
    }

    inline Vector2 & Vector2::operator/=(float rhs)
    {
        Math::Divide(*this, rhs, *this);
        return *this;
    }

    inline void Vector2::Transform(const Matrix4x4 & m)
    {
        Math::Transform(*this, m, *this);
    }

    inline void Vector2::Transform(const Quaternion & q)
    {
        Math::Transform(*this, q, *this);
    }

    inline void Vector2::Clamp(const Vector2 & min, const Vector2 & max)
    {
        Math::Clamp(*this, min, max, *this);
    }

    inline void Vector2::Clamp01()
    {
        Math::Clamp01(*this, *this);
    }

    inline float Vector2::Length() const
    {
        return Math::Length(*this);
    }

    inline float Vector2::LengthSquared() const
    {
        return Math::LengthSquared(*this);
    }

    inline void Vector2::Normalize()
    {
        Math::Normalize(*this, *this);
    }

    inline void Vector2::Negate()
    {
        Math::Negate(*this, *this);
    }

    inline void Vector2::Set(const Vector2 & src)
    {
        memcpy(this, &src, sizeof(Vector2));
    }

    inline void Vector2::Set(const float * pSrc)
    {
        memcpy(ToArray(), pSrc, sizeof(Vector2));
    }

    inline void Vector2::Set(float x, float y)
    {
        this->X = x;
        this->Y = y;
    }

    inline void Vector2::Set(float f)
    {
        this->X = f;
        this->Y = f;
    }

    inline const float * Vector2::ToArray() const
    {
        return &(this->X);
    }

    inline float * Vector2::ToArray()
    {
        return &(this->X);
    }

    inline bool operator==(const Vector2 & lhs, const Vector2 & rhs)
    {
        return ExactlyEqual(lhs, rhs);
    }

    inline bool operator!=(const Vector2 & lhs, const Vector2 & rhs)
    {
        return (false == ExactlyEqual(lhs, rhs));
    }

    inline bool operator>(const Vector2 & lhs, const Vector2 & rhs)
    {
        return AllGreater(lhs, rhs);
    }

    inline bool operator>=(const Vector2 & lhs, const Vector2 & rhs)
    {
        return AllGreaterEqual(lhs, rhs);
    }

    inline bool operator<(const Vector2 & lhs, const Vector2 & rhs)
    {
        return AllLess(lhs, rhs);
    }

    inline bool operator<=(const Vector2 & lhs, const Vector2 & rhs)
    {
        return AllLessEqual(lhs, rhs);
    }

    inline Vector2 operator+(const Vector2 & lhs, const Vector2 & rhs)
    {
        Vector2 out;
        Add(lhs, rhs, out);
        return out;
    }

    inline Vector2 operator+(const Vector2 & lhs, float rhs)
    {
        Vector2 out;
        Add(lhs, rhs, out);
        return out;
    }

    inline Vector2 operator-(const Vector2 & lhs, const Vector2 & rhs)
    {
        Vector2 out;
        Subtract(lhs, rhs, out);
        return out;
    }

    inline Vector2 operator-(const Vector2 & lhs, float rhs)
    {
        Vector2 out;
        Subtract(lhs, rhs, out);
        return out;
    }

    inline Vector2 operator-(const Vector2 & v)
    {
        Vector2 out;
        Negate(v, out);
        return out;
    }

    inline Vector2 operator*(const Vector2 & lhs, const Vector2 & rhs)
    {
        Vector2 out;
        Multiply(lhs, rhs, out);
        return out;
    }

    inline Vector2 operator*(const Vector2 & lhs, float rhs)
    {
        Vector2 out;
        Multiply(lhs, rhs, out);
        return out;
    }

    inline Vector2 operator/(const Vector2 & lhs, const Vector2 & rhs)
    {
        Vector2 out;
        Divide(lhs, rhs, out);
        return out;
    }

    inline Vector2 operator/(const Vector2 & lhs, float rhs)
    {
        Vector2 out;
        Divide(lhs, rhs, out);
        return out;
    }

    inline bool ExactlyEqual(const Vector2 & lhs, const Vector2 & rhs)
    {
        return (ExactlyEqual(lhs.X, rhs.X) && ExactlyEqual(lhs.Y, rhs.Y));
    }

    inline bool ExactlyZero(const Vector2 & v)
    {
        return ExactlyEqual(v, Vector2::Zero);
    }

    inline bool NearlyEqual(const Vector2 & lhs, const Vector2 & rhs)
    {
        return NearlyZero(lhs - rhs);
    }

    inline bool NearlyZero(const Vector2 & v)
    {
        return (NearlyZero(v.X) && NearlyZero(v.Y));
    }

    inline bool AllLess(const Vector2 & lhs, const Vector2 & rhs)
    {
        return ((lhs.X < rhs.X) && (lhs.Y < rhs.Y));
    }

    inline bool AllLessEqual(const Vector2 & lhs, const Vector2 & rhs)
    {
        return ((lhs.X <= rhs.X) && (lhs.Y <= rhs.Y));
    }

    inline bool AllGreater(const Vector2 & lhs, const Vector2 & rhs)
    {
        return ((lhs.X > rhs.X) && (lhs.Y > rhs.Y));
    }

    inline bool AllGreaterEqual(const Vector2 & lhs, const Vector2 & rhs)
    {
        return ((lhs.X >= rhs.X) && (lhs.Y >= rhs.Y));
    }

    inline bool IsNormalized(const Vector2 & v)
    {
        return NearlyEqual(LengthSquared(v), 1.0f);
    }

    inline Vector2 Add(const Vector2 & lhs, const Vector2 & rhs)
    {
        Vector2 out;
        Add(lhs, rhs, out);
        return out;
    }

    inline Vector2 Add(const Vector2 & lhs, float rhs)
    {
        Vector2 out;
        Add(lhs, rhs, out);
        return out;
    }

    inline void Add(const Vector2 & lhs, const Vector2 & rhs, Vector2 & out)
    {
        out.X = lhs.X + rhs.X;
        out.Y = lhs.Y + rhs.Y;
    }

    inline void Add(const Vector2 & lhs, float rhs, Vector2 & out)
    {
        out.X = lhs.X + rhs;
        out.Y = lhs.Y + rhs;
    }

    inline Vector2 Subtract(const Vector2 & lhs, const Vector2 & rhs)
    {
        Vector2 out;
        Subtract(lhs, rhs, out);
        return out;
    }

    inline Vector2 Subtract(const Vector2 & lhs, float rhs)
    {
        Vector2 out;
        Subtract(lhs, rhs, out);
        return out;
    }

    inline void Subtract(const Vector2 & lhs, const Vector2 & rhs, Vector2 & out)
    {
        out.X = lhs.X - rhs.X;
        out.Y = lhs.Y - rhs.Y;
    }

    inline void Subtract(const Vector2 & lhs, float rhs, Vector2 & out)
    {
        out.X = lhs.X - rhs;
        out.Y = lhs.Y - rhs;
    }

    inline Vector2 Multiply(const Vector2 & lhs, const Vector2 & rhs)
    {
        Vector2 out;
        Multiply(lhs, rhs, out);
        return out;
    }

    inline Vector2 Multiply(const Vector2 & lhs, float rhs)
    {
        Vector2 out;
        Multiply(lhs, rhs, out);
        return out;
    }

    inline void Multiply(const Vector2 & lhs, const Vector2 & rhs, Vector2 & out)
    {
        out.X = lhs.X * rhs.X;
        out.Y = lhs.Y * rhs.Y;
    }

    inline void Multiply(const Vector2 & lhs, float rhs, Vector2 & out)
    {
        out.X = lhs.X * rhs;
        out.Y = lhs.Y * rhs;
    }

    inline Vector2 Transform(const Vector2 & v, const Matrix4x4 & m)
    {
        Vector2 out;
        Transform(v, m, out);
        return out;
    }

    inline Vector2 Transform(const Vector2 & v, const Quaternion & q)
    {
        Vector2 out;
        Transform(v, q, out);
        return out;
    }

    inline void Transform(const Vector2 & v, const Matrix4x4 & m, Vector2 & out)
    {
        const float x = v.X * m.M11 + v.Y * m.M21 + m.M41;
        const float y = v.X * m.M12 + v.Y * m.M22 + m.M42;
        out.Set(x, y);
    }

    inline void Transform(const Vector2 & v, const Quaternion & q, Vector2 & out)
    {
        // The formula for rotating a vector by a unit quaternion is:
        // result = q * v * Inverse(q)
        //
        // If you treat v as a quaternion with 0 Z and W components, expand, and simplify you can get: 
        // result = v.XYZ + 2 * q.W * cross(q.XYZ, v.XYZ) + 2 * cross(q.XYZ, cross(q.XYZ, v.XYZ))
        //
        // The implementation below is an unrolled version of this equation.
        //
        // Note: This is more expensive that transforming by a matrix, if you have a lot of
        //       vectors to tranform, convert the quaternion to a matrix and then tranform.
        //
        // Ref: http://molecularmusings.wordpress.com/2013/05/24/a-faster-quaternion-vector-multiplication/
        //      https://code.google.com/p/kri/wiki/Quaternions
        //      TODO: http://gamedev.stackexchange.com/questions/28395/rotating-vector3-by-a-quaternion
        //      points out a alternate version of this expansion/simplification that may be less expensive

        DebugAssert(IsNormalized(q), "Quaternions need to be normalized in order to tranform a vector.");

        const float cX = -2.0f * (q.Z * v.Y);
        const float cY =  2.0f * (q.Z * v.X);

        const float x = v.X + q.W * cX - (q.Z * cY);
        const float y = v.Y + q.W * cY + (q.Z * cX);

        out.Set(x, y);
    }

    inline Vector2 Divide(const Vector2 & lhs, const Vector2 & rhs)
    {
        Vector2 out;
        Divide(lhs, rhs, out);
        return out;
    }
    
    inline Vector2 Divide(const Vector2 & lhs, float rhs)
    {
        Vector2 out;
        Divide(lhs, rhs, out);
        return out;
    }

    inline void Divide(const Vector2 & lhs, const Vector2 & rhs, Vector2 & out)
    {
        DebugAssert(false == NearlyZero(rhs.X), "Divide by zero!");
        DebugAssert(false == NearlyZero(rhs.Y), "Divide by zero!");
        out.X = lhs.X / rhs.X;
        out.Y = lhs.Y / rhs.Y;
    }

    inline void Divide(const Vector2 & lhs, float rhs, Vector2 & out)
    {
        DebugAssert(false == NearlyZero(rhs), "Divide by zero!");
        const float inv = 1.0f / rhs;
        out.X = lhs.X * inv;
        out.Y = lhs.Y * inv;
    }

    inline Vector2 Clamp(const Vector2 & v, const Vector2 & min, const Vector2 & max)
    {
        Vector2 out;
        Clamp(v, min, max, out);
        return out;
    }

    inline void Clamp(const Vector2 & v, const Vector2 & min, const Vector2 & max, Vector2 & out)
    {
        out.X = Clamp(v.X, min.X, max.X);
        out.Y = Clamp(v.Y, min.Y, max.Y);
    }

    inline Vector2 Clamp01(const Vector2 & v)
    {
        Vector2 out;
        Clamp01(v, out);
        return out;
    }

    inline void Clamp01(const Vector2 & v, Vector2 & out)
    {
        out.X = Clamp01(v.X);
        out.Y = Clamp01(v.Y);
    }

    inline Vector2 Remap(const Vector2 & in, const Vector2 & inRangeMin, const Vector2 & inRangeMax, const Vector2 & outRangeMin, const Vector2 & outRangeMax)
    {
        Vector2 out;
        Remap(in, inRangeMin, inRangeMax, outRangeMin, outRangeMax, out);
        return out;
    }

    inline void Remap(const Vector2 & in, const Vector2 & inRangeMin, const Vector2 & inRangeMax, const Vector2 & outRangeMin, const Vector2 & outRangeMax, Vector2 & out)
    {
        out.X = Remap(in.X, inRangeMin.X, inRangeMax.X, outRangeMin.X, outRangeMax.X);
        out.Y = Remap(in.Y, inRangeMin.Y, inRangeMax.Y, outRangeMin.Y, outRangeMax.Y);
    }

    inline Vector2 Max(const Vector2 & v1, const Vector2 & v2)
    {
        Vector2 out;
        Max(v1, v2, out);
        return out;
    }

    inline void Max(const Vector2 & v1, const Vector2 & v2, Vector2 & out)
    {
        out.X = Max(v1.X, v2.X);
        out.Y = Max(v1.Y, v2.Y);
    }

    inline Vector2 Min(const Vector2 & v1, const Vector2 & v2)
    {
        Vector2 out;
        Min(v1, v2, out);
        return out;
    }

    inline void Min(const Vector2 & v1, const Vector2 & v2, Vector2 & out)
    {
        out.X = Min(v1.X, v2.X);
        out.Y = Min(v1.Y, v2.Y);
    }

    inline Vector2 Ceiling(const Vector2 & v)
    {
        Vector2 out;
        Ceiling(v, out);
        return out;
    }

    inline void Ceiling(const Vector2 & v, Vector2 & out)
    {
        out.X = Ceiling(v.X);
        out.Y = Ceiling(v.Y);
    }

    inline Vector2 Floor(const Vector2 & v)
    {
        Vector2 out;
        Floor(v, out);
        return out;
    }

    inline void Floor(const Vector2 & v, Vector2 & out)
    {
        out.X = Floor(v.X);
        out.Y = Floor(v.Y);
    }

    inline Vector2 Round(const Vector2 & v)
    {
        Vector2 out;
        Round(v, out);
        return out;
    }

    inline void Round(const Vector2 & v, Vector2 & out)
    {
        out.X = Round(v.X);
        out.Y = Round(v.Y);
    }

    inline float Length(const Vector2 & v)
    {
        return Sqrt(LengthSquared(v));
    }

    inline float LengthSquared(const Vector2 & v)
    {
        return ((v.X * v.X) + (v.Y * v.Y));
    }

    inline float Distance(const Vector2 & lhs, const Vector2 & rhs)
    {
        return Length(lhs - rhs);
    }

    inline float DistanceSquared(const Vector2 & lhs, const Vector2 & rhs)
    {
        return LengthSquared(lhs - rhs);
    }

    inline Vector2 Normalize(const Vector2 & v)
    {
        Vector2 out;
        Normalize(v, out);
        return out;
    }

    inline void Normalize(const Vector2 & v, Vector2 & out)
    {
        float lengthSquared = LengthSquared(v);
        DebugAssert(false == NearlyZero(lengthSquared), "Trying to normalize a zero vector!");
        Multiply(v, InvSqrt(lengthSquared), out);
    }

    inline Vector2 Negate(const Vector2 & v)
    {
        Vector2 out;
        Negate(v, out);
        return out;
    }

    inline void Negate(const Vector2 & v, Vector2 & out)
    {
        out.X = -v.X;
        out.Y = -v.Y;
    }

    inline float Dot(const Vector2 & lhs, const Vector2 & rhs)
    {
        return ((lhs.X * rhs.X) + (lhs.Y * rhs.Y));
    }

    inline float Cross(const Vector2 & lhs, const Vector2 & rhs)
    {
        // Also known as 2D Perpendicular Product
        return ((lhs.X * rhs.Y) - (lhs.Y * rhs.X));
    }

    inline Vector2 Lerp(const Vector2 & v1, const Vector2 & v2, float weight)
    {
        Vector2 out;
        Lerp(v1, v2, weight, out);
        return out;
    }

    inline void Lerp(const Vector2 & v1, const Vector2 & v2, float weight, Vector2 & out)
    {
        out.X = Lerp(v1.X, v2.X, weight);
        out.Y = Lerp(v1.Y, v2.Y, weight);
    }

    inline Vector2 Hermite(const Vector2 & v1, const Vector2 & t1, const Vector2 & v2, const Vector2 & t2, float weight)
    {
        Vector2 out;
        Hermite(v1, t1, v2, t2, weight, out);
        return out;
    }

    inline void Hermite(const Vector2 & v1, const Vector2 & t1, const Vector2 & v2, const Vector2 & t2, float weight, Vector2 & out)
    {
        out.X = Hermite(v1.X, t1.X, v2.X, t2.X, weight);
        out.Y = Hermite(v1.Y, t1.Y, v2.Y, t2.Y, weight);
    }

    inline Vector2 SmoothStep(const Vector2 & v1, const Vector2 & v2, float weight)
    {
        Vector2 out;
        SmoothStep(v1, v2, weight, out);
        return out;
    }

    inline void SmoothStep(const Vector2 & v1, const Vector2 & v2, float weight, Vector2 & out)
    {
        out.X = SmoothStep(v1.X, v2.X, weight);
        out.Y = SmoothStep(v1.Y, v2.Y, weight);
    }

    inline void Swap(Vector2 & v1, Vector2 & v2)
    {
        Swap(v1.X, v2.X);
        Swap(v1.Y, v2.Y);
    }

} //namespace Math
} //namespace Phx

#endif //_PHX_MATH_VECTOR2_INL_
