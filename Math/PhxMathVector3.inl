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

#ifndef _PHX_MATH_VECTOR3_INL_
#define _PHX_MATH_VECTOR3_INL_

namespace Phx {
namespace Math {

    inline Vector3::Vector3(float f)
        : X(f), Y(f), Z(f)
    { }

    inline Vector3::Vector3(float x, float y, float z)
        : X(x), Y(y), Z(z)
    { }

    inline Vector3::Vector3(const Vector2 & src, float z)
        : X(src.X), Y(src.Y), Z(z)
    { }

    inline Vector3::Vector3(const Vector3 & src)
    { 
        Set(src);
    }

    inline Vector3 & Vector3::operator=(const Vector3 & rhs)
    {
        Set(rhs);
        return *this;
    }

    inline float & Vector3::operator[](unsigned int idx)
    {
        DebugAssert(idx < 3, "Invalid index (%u) into a vector 3!", idx);
        return ToArray()[idx];
    }

    inline const float & Vector3::operator[](unsigned int idx) const
    {
        DebugAssert(idx < 3, "Invalid index (%u) into a vector 3!", idx);
        return ToArray()[idx];
    }

    inline Vector3 & Vector3::operator+=(const Vector3 & rhs)
    {
        Math::Add(*this, rhs, *this);
        return *this;
    }

    inline Vector3 & Vector3::operator+=(float rhs)
    {
        Math::Add(*this, rhs, *this);
        return *this;
    }

    inline Vector3 & Vector3::operator-=(const Vector3 & rhs)
    {
        Math::Subtract(*this, rhs, *this);
        return *this;
    }

    inline Vector3 & Vector3::operator-=(float rhs)
    {
        Math::Subtract(*this, rhs, *this);
        return *this;
    }

    inline Vector3 & Vector3::operator*=(const Vector3 & rhs)
    {
        Math::Multiply(*this, rhs, *this);
        return *this;
    }

    inline Vector3 & Vector3::operator*=(float rhs)
    {
        Math::Multiply(*this, rhs, *this);
        return *this;
    }

    inline Vector3 & Vector3::operator/=(const Vector3 & rhs)
    {
        Math::Divide(*this, rhs, *this);
        return *this;
    }

    inline Vector3 & Vector3::operator/=(float rhs)
    {
        Math::Divide(*this, rhs, *this);
        return *this;
    }

    inline void Vector3::Transform(const Matrix4x4 & m)
    {
        Math::Transform(*this, m, *this);
    }

    inline void Vector3::Transform(const Quaternion & q)
    {
        Math::Transform(*this, q, *this);
    }

    inline void Vector3::Clamp(const Vector3 & min, const Vector3 & max)
    {
        Math::Clamp(*this, min, max, *this);
    }

    inline void Vector3::Clamp01()
    {
        Math::Clamp01(*this, *this);
    }

    inline Vector3 Clamp01(const Vector3 & v)
    {
        Vector3 out;
        Clamp01(v, out);
        return out;
    }

    inline void Clamp01(const Vector3 & v, Vector3 & out)
    {
        out.X = Clamp01(v.X);
        out.Y = Clamp01(v.Y);
        out.Z = Clamp01(v.Z);
    }

    inline Vector3 Remap(const Vector3 & in, const Vector3 & inRangeMin, const Vector3 & inRangeMax, const Vector3 & outRangeMin, const Vector3 & outRangeMax)
    {
        Vector3 out;
        Remap(in, inRangeMin, inRangeMax, outRangeMin, outRangeMax, out);
        return out;
    }

    inline void Remap(const Vector3 & in, const Vector3 & inRangeMin, const Vector3 & inRangeMax, const Vector3 & outRangeMin, const Vector3 & outRangeMax, Vector3 & out)
    {
        out.X = Remap(in.X, inRangeMin.X, inRangeMax.X, outRangeMin.X, outRangeMax.X);
        out.Y = Remap(in.Y, inRangeMin.Y, inRangeMax.Y, outRangeMin.Y, outRangeMax.Y);
        out.Z = Remap(in.Z, inRangeMin.Z, inRangeMax.Z, outRangeMin.Z, outRangeMax.Z);
    }

    inline Vector3 Max(const Vector3 & v1, const Vector3 & v2)
    {
        Vector3 out;
        Max(v1, v2, out);
        return out;
    }

    inline void Max(const Vector3 & v1, const Vector3 & v2, Vector3 & out)
    {
        out.X = Max(v1.X, v2.X);
        out.Y = Max(v1.Y, v2.Y);
        out.Z = Max(v1.Z, v2.Z);
    }

    inline Vector3 Min(const Vector3 & v1, const Vector3 & v2)
    {
        Vector3 out;
        Min(v1, v2, out);
        return out;
    }

    inline void Min(const Vector3 & v1, const Vector3 & v2, Vector3 & out)
    {
        out.X = Min(v1.X, v2.X);
        out.Y = Min(v1.Y, v2.Y);
        out.Z = Min(v1.Z, v2.Z);
    }

    inline Vector3 Ceiling(const Vector3 & v)
    {
        Vector3 out;
        Ceiling(v, out);
        return out;
    }

    inline void Ceiling(const Vector3 & v, Vector3 & out)
    {
        out.X = Ceiling(v.X);
        out.Y = Ceiling(v.Y);
        out.Z = Ceiling(v.Z);
    }

    inline Vector3 Floor(const Vector3 & v)
    {
        Vector3 out;
        Floor(v, out);
        return out;
    }

    inline void Floor(const Vector3 & v, Vector3 & out)
    {
        out.X = Floor(v.X);
        out.Y = Floor(v.Y);
        out.Z = Floor(v.Z);
    }

    inline Vector3 Round(const Vector3 & v)
    {
        Vector3 out;
        Round(v, out);
        return out;
    }

    inline void Round(const Vector3 & v, Vector3 & out)
    {
        out.X = Round(v.X);
        out.Y = Round(v.Y);
        out.Z = Round(v.Z);
    }

    inline float Vector3::Length() const
    {
        return Math::Length(*this);
    }

    inline float Vector3::LengthSquared() const
    {
        return Math::LengthSquared(*this);
    }

    inline void Vector3::Normalize()
    {
        Math::Normalize(*this, *this);
    }

    inline void Vector3::Negate()
    {
        Math::Negate(*this, *this);
    }

    inline void Vector3::Set(const Vector3 & src)
    {
        memcpy(this, &src, sizeof(Vector3));
    }

    inline void Vector3::Set(const float * pSrc)
    {
        memcpy(ToArray(), pSrc, sizeof(Vector3));
    }

    inline void Vector3::Set(float x, float y, float z)
    {
        this->X = x;
        this->Y = y;
        this->Z = z;
    }

    inline void Vector3::Set(float f)
    {
        this->X = f;
        this->Y = f;
        this->Z = f;
    }

    inline const float * Vector3::ToArray() const
    {
        return &(this->X);
    }

    inline float * Vector3::ToArray()
    {
        return &(this->X);
    }

    inline bool operator==(const Vector3 & lhs, const Vector3 & rhs)
    {
        return ExactlyEqual(lhs, rhs);
    }

    inline bool operator!=(const Vector3 & lhs, const Vector3 & rhs)
    {
        return (false == ExactlyEqual(lhs, rhs));
    }

    inline bool operator>(const Vector3 & lhs, const Vector3 & rhs)
    {
        return AllGreater(lhs, rhs);
    }

    inline bool operator>=(const Vector3 & lhs, const Vector3 & rhs)
    {
        return AllGreaterEqual(lhs, rhs);
    }

    inline bool operator<(const Vector3 & lhs, const Vector3 & rhs)
    {
        return AllLess(lhs, rhs);
    }

    inline bool operator<=(const Vector3 & lhs, const Vector3 & rhs)
    {
        return AllLessEqual(lhs, rhs);
    }

    inline Vector3 operator+(const Vector3 & lhs, const Vector3 & rhs)
    {
        Vector3 out;
        Add(lhs, rhs, out);
        return out;
    }

    inline Vector3 operator+(const Vector3 & lhs, float rhs)
    {
        Vector3 out;
        Add(lhs, rhs, out);
        return out;
    }

    inline Vector3 operator-(const Vector3 & lhs, const Vector3 & rhs)
    {
        Vector3 out;
        Subtract(lhs, rhs, out);
        return out;
    }

    inline Vector3 operator-(const Vector3 & lhs, float rhs)
    {
        Vector3 out;
        Subtract(lhs, rhs, out);
        return out;
    }

    inline Vector3 operator-(const Vector3 & v)
    {
        Vector3 out;
        Negate(v, out);
        return out;
    }

    inline Vector3 operator*(const Vector3 & lhs, const Vector3 & rhs)
    {
        Vector3 out;
        Multiply(lhs, rhs, out);
        return out;
    }

    inline Vector3 operator*(const Vector3 & lhs, float rhs)
    {
        Vector3 out;
        Multiply(lhs, rhs, out);
        return out;
    }

    inline Vector3 operator/(const Vector3 & lhs, const Vector3 & rhs)
    {
        Vector3 out;
        Divide(lhs, rhs, out);
        return out;
    }

    inline Vector3 operator/(const Vector3 & lhs, float rhs)
    {
        Vector3 out;
        Divide(lhs, rhs, out);
        return out;
    }

    inline bool ExactlyEqual(const Vector3 & lhs, const Vector3 & rhs)
    {
        return (ExactlyEqual(lhs.X, rhs.X) &&
                ExactlyEqual(lhs.Y, rhs.Y) &&
                ExactlyEqual(lhs.Z, rhs.Z));
    }

    inline bool ExactlyZero(const Vector3 & v)
    {
        return ExactlyEqual(v, Vector3::Zero);
    }

    inline bool NearlyEqual(const Vector3 & lhs, const Vector3 & rhs)
    {
        return NearlyZero(lhs - rhs);
    }

    inline bool NearlyZero(const Vector3 & v)
    {
        return (NearlyZero(v.X) &&
                NearlyZero(v.Y) &&
                NearlyZero(v.Z));
    }

    inline bool AllLess(const Vector3 & lhs, const Vector3 & rhs)
    {
        return ((lhs.X < rhs.X) && (lhs.Y < rhs.Y) && (lhs.Z < rhs.Z));
    }

    inline bool AllLessEqual(const Vector3 & lhs, const Vector3 & rhs)
    {
        return ((lhs.X <= rhs.X) && (lhs.Y <= rhs.Y) && (lhs.Z <= rhs.Z));
    }

    inline bool AllGreater(const Vector3 & lhs, const Vector3 & rhs)
    {
        return ((lhs.X > rhs.X) && (lhs.Y > rhs.Y) && (lhs.Z > rhs.Z));
    }

    inline bool AllGreaterEqual(const Vector3 & lhs, const Vector3 & rhs)
    {
        return ((lhs.X >= rhs.X) && (lhs.Y >= rhs.Y) && (lhs.Z >= rhs.Z));
    }

    inline bool IsNormalized(const Vector3 & v)
    {
        return NearlyEqual(LengthSquared(v), 1.0f);
    }

    inline Vector3 Add(const Vector3 & lhs, const Vector3 & rhs)
    {
        Vector3 out;
        Add(lhs, rhs, out);
        return out;
    }

    inline Vector3 Add(const Vector3 & lhs, float rhs)
    {
        Vector3 out;
        Add(lhs, rhs, out);
        return out;
    }

    inline void Add(const Vector3 & lhs, const Vector3 & rhs, Vector3 & out)
    {
        out.X = lhs.X + rhs.X;
        out.Y = lhs.Y + rhs.Y;
        out.Z = lhs.Z + rhs.Z;
    }

    inline void Add(const Vector3 & lhs, float rhs, Vector3 & out)
    {
        out.X = lhs.X + rhs;
        out.Y = lhs.Y + rhs;
        out.Z = lhs.Z + rhs;
    }

    inline Vector3 Subtract(const Vector3 & lhs, const Vector3 & rhs)
    {
        Vector3 out;
        Subtract(lhs, rhs, out);
        return out;
    }

    inline Vector3 Subtract(const Vector3 & lhs, float rhs)
    {
        Vector3 out;
        Subtract(lhs, rhs, out);
        return out;
    }

    inline void Subtract(const Vector3 & lhs, const Vector3 & rhs, Vector3 & out)
    {
        out.X = lhs.X - rhs.X;
        out.Y = lhs.Y - rhs.Y;
        out.Z = lhs.Z - rhs.Z;
    }

    inline void Subtract(const Vector3 & lhs, float rhs, Vector3 & out)
    {
        out.X = lhs.X - rhs;
        out.Y = lhs.Y - rhs;
        out.Z = lhs.Z - rhs;
    }

    inline Vector3 Multiply(const Vector3 & lhs, const Vector3 & rhs)
    {
        Vector3 out;
        Multiply(lhs, rhs, out);
        return out;
    }

    inline Vector3 Multiply(const Vector3 & lhs, float rhs)
    {
        Vector3 out;
        Multiply(lhs, rhs, out);
        return out;
    }

    inline void Multiply(const Vector3 & lhs, const Vector3 & rhs, Vector3 & out)
    {
        out.X = lhs.X * rhs.X;
        out.Y = lhs.Y * rhs.Y;
        out.Z = lhs.Z * rhs.Z;
    }

    inline void Multiply(const Vector3 & lhs, float rhs, Vector3 & out)
    {
        out.X = lhs.X * rhs;
        out.Y = lhs.Y * rhs;
        out.Z = lhs.Z * rhs;
    }

    inline Vector3 Transform(const Vector3 & v, const Matrix4x4 & m)
    {
        Vector3 out;
        Transform(v, m, out);
        return out;
    }

    inline Vector3 Transform(const Vector3 & v, const Quaternion & q)
    {
        Vector3 out;
        Transform(v, q, out);
        return out;
    }

    inline void Transform(const Vector3 & v, const Matrix4x4 & m, Vector3 & out)
    {
        const float x = v.X * m.M11 + v.Y * m.M21 + v.Z * m.M31 + m.M41;
        const float y = v.X * m.M12 + v.Y * m.M22 + v.Z * m.M32 + m.M42;
        const float z = v.X * m.M13 + v.Y * m.M23 + v.Z * m.M33 + m.M43;
        out.Set(x, y, z);
    }

    inline void Transform(const Vector3 & v, const Quaternion & q, Vector3 & out)
    {
        // The formula for rotating a vector by a unit quaternion is:
        // result = q * v * Inverse(q)
        //
        // If you treat v as a quaternion with a 0 W component, expand, and simplify you can get: 
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

        const float cX = 2.0f * ((q.Y * v.Z) - (q.Z * v.Y));
        const float cY = 2.0f * ((q.Z * v.X) - (q.X * v.Z));
        const float cZ = 2.0f * ((q.X * v.Y) - (q.Y * v.X));

        const float x = v.X + q.W * cX + (q.Y * cZ) - (q.Z * cY);
        const float y = v.Y + q.W * cY + (q.Z * cX) - (q.X * cZ);
        const float z = v.Z + q.W * cZ + (q.X * cY) - (q.Y * cX);

        out.Set(x, y, z);
    }

    inline Vector3 Divide(const Vector3 & lhs, const Vector3 & rhs)
    {
        Vector3 out;
        Divide(lhs, rhs, out);
        return out;
    }
    
    inline Vector3 Divide(const Vector3 & lhs, float rhs)
    {
        Vector3 out;
        Divide(lhs, rhs, out);
        return out;
    }

    inline void Divide(const Vector3 & lhs, const Vector3 & rhs, Vector3 & out)
    {
        DebugAssert(false == NearlyZero(rhs.X), "Divide by zero!");
        DebugAssert(false == NearlyZero(rhs.Y), "Divide by zero!");
        DebugAssert(false == NearlyZero(rhs.Z), "Divide by zero!");
        out.X = lhs.X / rhs.X;
        out.Y = lhs.Y / rhs.Y;
        out.Z = lhs.Z / rhs.Z;
    }

    inline void Divide(const Vector3 & lhs, float rhs, Vector3 & out)
    {
        DebugAssert(false == NearlyZero(rhs), "Divide by zero!");
        const float inv = 1.0f / rhs;
        out.X = lhs.X * inv;
        out.Y = lhs.Y * inv;
        out.Z = lhs.Z * inv;
    }

    inline Vector3 Clamp(const Vector3 & v, const Vector3 & min, const Vector3 & max)
    {
        Vector3 out;
        Clamp(v, min, max, out);
        return out;
    }

    inline void Clamp(const Vector3 & v, const Vector3 & min, const Vector3 & max, Vector3 & out)
    {
        out.X = Clamp(v.X, min.X, max.X);
        out.Y = Clamp(v.Y, min.Y, max.Y);
        out.Z = Clamp(v.Z, min.Z, max.Z);
    }

    inline float Length(const Vector3 & v)
    {
        return Sqrt(LengthSquared(v));
    }

    inline float LengthSquared(const Vector3 & v)
    {
        return ((v.X * v.X) + (v.Y * v.Y) + (v.Z * v.Z));
    }

    inline float Distance(const Vector3 & lhs, const Vector3 & rhs)
    {
        return Length(lhs - rhs);
    }

    inline float DistanceSquared(const Vector3 & lhs, const Vector3 & rhs)
    {
        return LengthSquared(lhs - rhs);
    }

    inline Vector3 Normalize(const Vector3 & v)
    {
        Vector3 out;
        Normalize(v, out);
        return out;
    }

    inline void Normalize(const Vector3 & v, Vector3 & out)
    {
        float lengthSquared = LengthSquared(v);
        DebugAssert(false == NearlyZero(lengthSquared), "Trying to normalize a zero vector!");
        Multiply(v, InvSqrt(lengthSquared), out);
    }

    inline Vector3 Negate(const Vector3 & v)
    {
        Vector3 out;
        Negate(v, out);
        return out;
    }

    inline void Negate(const Vector3 & v, Vector3 & out)
    {
        out.X = -v.X;
        out.Y = -v.Y;
        out.Z = -v.Z;
    }

    inline float Dot(const Vector3 & lhs, const Vector3 & rhs)
    {
        return ((lhs.X * rhs.X) + (lhs.Y * rhs.Y) + (lhs.Z * rhs.Z));
    }

    inline Vector3 Cross(const Vector3 & lhs, const Vector3 & rhs)
    {
        Vector3 out;
        Cross(lhs, rhs, out);
        return out;
    }

    inline void Cross(const Vector3 & lhs, const Vector3 & rhs, Vector3 & out)
    {
        const float x = (lhs.Y * rhs.Z) - (lhs.Z * rhs.Y);
        const float y = (lhs.Z * rhs.X) - (lhs.X * rhs.Z);
        const float z = (lhs.X * rhs.Y) - (lhs.Y * rhs.X);
        out.Set(x, y, z);
    }

    inline Vector3 Lerp(const Vector3 & v1, const Vector3 & v2, float weight)
    {
        Vector3 out;
        Lerp(v1, v2, weight, out);
        return out;
    }

    inline void Lerp(const Vector3 & v1, const Vector3 & v2, float weight, Vector3 & out)
    {
        out.X = Lerp(v1.X, v2.X, weight);
        out.Y = Lerp(v1.Y, v2.Y, weight);
        out.Z = Lerp(v1.Z, v2.Z, weight);
    }

    inline Vector3 Hermite(const Vector3 & v1, const Vector3 & t1, const Vector3 & v2, const Vector3 & t2, float weight)
    {
        Vector3 out;
        Hermite(v1, t1, v2, t2, weight, out);
        return out;
    }

    inline void Hermite(const Vector3 & v1, const Vector3 & t1, const Vector3 & v2, const Vector3 & t2, float weight, Vector3 & out)
    {
        out.X = Hermite(v1.X, t1.X, v2.X, t2.X, weight);
        out.Y = Hermite(v1.Y, t1.Y, v2.Y, t2.Y, weight);
        out.Z = Hermite(v1.Z, t1.Z, v2.Z, t2.Z, weight);
    }

    inline Vector3 SmoothStep(const Vector3 & v1, const Vector3 & v2, float weight)
    {
        Vector3 out;
        SmoothStep(v1, v2, weight, out);
        return out;
    }

    inline void SmoothStep(const Vector3 & v1, const Vector3 & v2, float weight, Vector3 & out)
    {
        out.X = SmoothStep(v1.X, v2.X, weight);
        out.Y = SmoothStep(v1.Y, v2.Y, weight);
        out.Z = SmoothStep(v1.Z, v2.Z, weight);
    }

    inline void Swap(Vector3 & v1, Vector3 & v2)
    {
        Swap(v1.X, v2.X);
        Swap(v1.Y, v2.Y);
        Swap(v1.Z, v2.Z);
    }

} //namespace Math
} //namespace Phx

#endif //_PHX_MATH_VECTOR3_INL_
