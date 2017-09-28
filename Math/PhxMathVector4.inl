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

#ifndef _PHX_MATH_VECTOR4_INL_
#define _PHX_MATH_VECTOR4_INL_

namespace Phx {
namespace Math {

    inline Vector4::Vector4(float f)
        : X(f), Y(f), Z(f), W(f)
    { }

    inline Vector4::Vector4(float x, float y, float z, float w)
        : X(x), Y(y), Z(z), W(w)
    { }

    inline Vector4::Vector4(const Vector2 &src, float z, float w)
        : X(src.X), Y(src.Y), Z(z), W(w)
    { }

    inline Vector4::Vector4(const Vector3 &src, float w)
        : X(src.X), Y(src.Y), Z(src.Z), W(w)
    { }

    inline Vector4::Vector4(const Vector4 &src)
    { 
        Copy(src);
    }

    inline Vector4& Vector4::operator=(const Vector4 &rhs)
    {
        Copy(rhs);
        return *this;
    }

    inline float& Vector4::operator[](unsigned int idx)
    {
        DebugAssert(idx < 4, "Invalid index (%u) into a vector 4!", idx);
        return ToArray()[idx];
    }

    inline const float& Vector4::operator[](unsigned int idx) const
    {
        DebugAssert(idx < 4, "Invalid index (%u) into a vector 4!", idx);
        return ToArray()[idx];
    }

    inline Vector4& Vector4::operator+=(const Vector4 &rhs)
    {
        Math::Add(*this, rhs, *this);
        return *this;
    }

    inline Vector4& Vector4::operator+=(float rhs)
    {
        Math::Add(*this, rhs, *this);
        return *this;
    }

    inline Vector4& Vector4::operator-=(const Vector4 &rhs)
    {
        Math::Subtract(*this, rhs, *this);
        return *this;
    }

    inline Vector4& Vector4::operator-=(float rhs)
    {
        Math::Subtract(*this, rhs, *this);
        return *this;
    }

    inline Vector4& Vector4::operator*=(const Vector4 &rhs)
    {
        Math::Multiply(*this, rhs, *this);
        return *this;
    }

    inline Vector4& Vector4::operator*=(float rhs)
    {
        Math::Multiply(*this, rhs, *this);
        return *this;
    }

    inline Vector4& Vector4::operator/=(const Vector4 &rhs)
    {
        Math::Divide(*this, rhs, *this);
        return *this;
    }

    inline Vector4& Vector4::operator/=(float rhs)
    {
        Math::Divide(*this, rhs, *this);
        return *this;
    }

    inline void Vector4::Transform(const Matrix4x4 &m)
    {
        Math::Transform(*this, m, *this);
    }

    inline void Vector4::Clamp(const Vector4 &min, const Vector4 &max)
    {
        Math::Clamp(*this, min, max, *this);
    }

    inline void Vector4::Clamp01()
    {
        Math::Clamp01(*this, *this);
    }

    inline float Vector4::Length() const
    {
        return Math::Length(*this);
    }

    inline float Vector4::LengthSquared() const
    {
        return Math::LengthSquared(*this);
    }

    inline void Vector4::Normalize()
    {
        Math::Normalize(*this, *this);
    }

    inline void Vector4::Negate()
    {
        Math::Negate(*this, *this);
    }

    inline void Vector4::Copy(const Vector4 &src)
    {
        memcpy(this, &src, sizeof(Vector4));
    }

    inline void Vector4::Copy(const float *pSrc)
    {
        memcpy(ToArray(), &pSrc, sizeof(Vector4));
    }

    inline void Vector4::Copy(float x, float y, float z, float w)
    {
        this->X = x;
        this->Y = y;
        this->Z = z;
        this->W = w;
    }

    inline void Vector4::Copy(float f)
    {
        this->X = f;
        this->Y = f;
        this->Z = f;
        this->W = f;
    }

    inline const float* Vector4::ToArray() const
    {
        return &(this->X);
    }

    inline float* Vector4::ToArray()
    {
        return &(this->X);
    }

    inline bool operator==(const Vector4 &lhs, const Vector4 &rhs)
    {
        return ExactlyEqual(lhs, rhs);
    }

    inline bool operator!=(const Vector4 &lhs, const Vector4 &rhs)
    {
        return (false == ExactlyEqual(lhs, rhs));
    }

    inline bool operator>(const Vector4 &lhs, const Vector4 &rhs)
    {
        return AllGreater(lhs, rhs);
    }

    inline bool operator>=(const Vector4 &lhs, const Vector4 &rhs)
    {
        return AllGreaterEqual(lhs, rhs);
    }

    inline bool operator<(const Vector4 &lhs, const Vector4 &rhs)
    {
        return AllLess(lhs, rhs);
    }

    inline bool operator<=(const Vector4 &lhs, const Vector4 &rhs)
    {
        return AllLessEqual(lhs, rhs);
    }

    inline Vector4 operator+(const Vector4 &lhs, const Vector4 &rhs)
    {
        Vector4 out;
        Add(lhs, rhs, out);
        return out;
    }

    inline Vector4 operator+(const Vector4 &lhs, float rhs)
    {
        Vector4 out;
        Add(lhs, rhs, out);
        return out;
    }

    inline Vector4 operator-(const Vector4 &lhs, const Vector4 &rhs)
    {
        Vector4 out;
        Subtract(lhs, rhs, out);
        return out;
    }

    inline Vector4 operator-(const Vector4 &lhs, float rhs)
    {
        Vector4 out;
        Subtract(lhs, rhs, out);
        return out;
    }

    inline Vector4 operator-(const Vector4 &v)
    {
        Vector4 out;
        Negate(v, out);
        return out;
    }

    inline Vector4 operator*(const Vector4 &lhs, const Vector4 &rhs)
    {
        Vector4 out;
        Multiply(lhs, rhs, out);
        return out;
    }

    inline Vector4 operator*(const Vector4 &lhs, float rhs)
    {
        Vector4 out;
        Multiply(lhs, rhs, out);
        return out;
    }

    inline Vector4 operator/(const Vector4 &lhs, const Vector4 &rhs)
    {
        Vector4 out;
        Divide(lhs, rhs, out);
        return out;
    }

    inline Vector4 operator/(const Vector4 &lhs, float rhs)
    {
        Vector4 out;
        Divide(lhs, rhs, out);
        return out;
    }

    inline bool ExactlyEqual(const Vector4 &lhs, const Vector4 &rhs)
    {
        return (ExactlyEqual(lhs.X, rhs.X) &&
                ExactlyEqual(lhs.Y, rhs.Y) &&
                ExactlyEqual(lhs.Z, rhs.Z) &&
                ExactlyEqual(lhs.W, rhs.W));
    }

    inline bool ExactlyZero(const Vector4 &v)
    {
        return ExactlyEqual(v, Vector4::Zero);
    }

    inline bool NearlyEqual(const Vector4 &lhs, const Vector4 &rhs)
    {
        return NearlyZero(lhs - rhs);
    }

    inline bool NearlyZero(const Vector4 &v)
    {
        return (NearlyZero(v.X) &&
                NearlyZero(v.Y) &&
                NearlyZero(v.Z) &&
                NearlyZero(v.W));
    }

    inline bool AllLess(const Vector4 &lhs, const Vector4 &rhs)
    {
        return ((lhs.X < rhs.X) && (lhs.Y < rhs.Y) && (lhs.Z < rhs.Z) && (lhs.W < rhs.W));
    }

    inline bool AllLessEqual(const Vector4 &lhs, const Vector4 &rhs)
    {
        return ((lhs.X <= rhs.X) && (lhs.Y <= rhs.Y) && (lhs.Z <= rhs.Z) && (lhs.W <= rhs.W));
    }

    inline bool AllGreater(const Vector4 &lhs, const Vector4 &rhs)
    {
        return ((lhs.X > rhs.X) && (lhs.Y > rhs.Y) && (lhs.Z > rhs.Z) && (lhs.W > rhs.W));
    }

    inline bool AllGreaterEqual(const Vector4 &lhs, const Vector4 &rhs)
    {
        return ((lhs.X >= rhs.X) && (lhs.Y >= rhs.Y) && (lhs.Z >= rhs.Z) && (lhs.W >= rhs.W));
    }

    inline bool IsNormalized(const Vector4 &v)
    {
        return NearlyEqual(LengthSquared(v), 1.0f);
    }

    inline Vector4 Add(const Vector4 &lhs, const Vector4 &rhs)
    {
        Vector4 out;
        Add(lhs, rhs, out);
        return out;
    }

    inline Vector4 Add(const Vector4 &lhs, float rhs)
    {
        Vector4 out;
        Add(lhs, rhs, out);
        return out;
    }

    inline void Add(const Vector4 &lhs, const Vector4 &rhs, Vector4 &out)
    {
        out.X = lhs.X + rhs.X;
        out.Y = lhs.Y + rhs.Y;
        out.Z = lhs.Z + rhs.Z;
        out.W = lhs.W + rhs.W;
    }

    inline void Add(const Vector4 &lhs, float rhs, Vector4 &out)
    {
        out.X = lhs.X + rhs;
        out.Y = lhs.Y + rhs;
        out.Z = lhs.Z + rhs;
        out.W = lhs.W + rhs;
    }

    inline Vector4 Subtract(const Vector4 &lhs, const Vector4 &rhs)
    {
        Vector4 out;
        Subtract(lhs, rhs, out);
        return out;
    }

    inline Vector4 Subtract(const Vector4 &lhs, float rhs)
    {
        Vector4 out;
        Subtract(lhs, rhs, out);
        return out;
    }

    inline void Subtract(const Vector4 &lhs, const Vector4 &rhs, Vector4 &out)
    {
        out.X = lhs.X - rhs.X;
        out.Y = lhs.Y - rhs.Y;
        out.Z = lhs.Z - rhs.Z;
        out.W = lhs.W - rhs.W;
    }

    inline void Subtract(const Vector4 &lhs, float rhs, Vector4 &out)
    {
        out.X = lhs.X - rhs;
        out.Y = lhs.Y - rhs;
        out.Z = lhs.Z - rhs;
        out.W = lhs.W - rhs;
    }

    inline Vector4 Multiply(const Vector4 &lhs, const Vector4 &rhs)
    {
        Vector4 out;
        Multiply(lhs, rhs, out);
        return out;
    }

    inline Vector4 Multiply(const Vector4 &lhs, float rhs)
    {
        Vector4 out;
        Multiply(lhs, rhs, out);
        return out;
    }

    inline void Multiply(const Vector4 &lhs, const Vector4 &rhs, Vector4 &out)
    {
        out.X = lhs.X * rhs.X;
        out.Y = lhs.Y * rhs.Y;
        out.Z = lhs.Z * rhs.Z;
        out.W = lhs.W * rhs.W;
    }

    inline void Multiply(const Vector4 &lhs, float rhs, Vector4 &out)
    {
        out.X = lhs.X * rhs;
        out.Y = lhs.Y * rhs;
        out.Z = lhs.Z * rhs;
        out.W = lhs.W * rhs;
    }

    inline Vector4 Transform(const Vector4 &v, const Matrix4x4 &m)
    {
        Vector4 out;
        Transform(v, m, out);
        return out;
    }

    inline void Transform(const Vector4 &v, const Matrix4x4 &m, Vector4 &out)
    {
        const float x = v.X * m.M11 + v.Y * m.M21 + v.Z * m.M31 + v.W * m.M41;
        const float y = v.X * m.M12 + v.Y * m.M22 + v.Z * m.M32 + v.W * m.M42;
        const float z = v.X * m.M13 + v.Y * m.M23 + v.Z * m.M33 + v.W * m.M43;
        const float w = v.X * m.M14 + v.Y * m.M24 + v.Z * m.M34 + v.W * m.M44;
        out.Copy(x, y, z, w);
    }

    inline Vector4 Divide(const Vector4 &lhs, const Vector4 &rhs)
    {
        Vector4 out;
        Divide(lhs, rhs, out);
        return out;
    }
    
    inline Vector4 Divide(const Vector4 &lhs, float rhs)
    {
        Vector4 out;
        Divide(lhs, rhs, out);
        return out;
    }

    inline void Divide(const Vector4 &lhs, const Vector4 &rhs, Vector4 &out)
    {
        DebugAssert(false == NearlyZero(rhs.X), "Divide by zero!");
        DebugAssert(false == NearlyZero(rhs.Y), "Divide by zero!");
        DebugAssert(false == NearlyZero(rhs.Z), "Divide by zero!");
        DebugAssert(false == NearlyZero(rhs.W), "Divide by zero!");
        out.X = lhs.X / rhs.X;
        out.Y = lhs.Y / rhs.Y;
        out.Z = lhs.Z / rhs.Z;
        out.W = lhs.W / rhs.W;
    }

    inline void Divide(const Vector4 &lhs, float rhs, Vector4 &out)
    {
        DebugAssert(false == NearlyZero(rhs), "Divide by zero!");
        const float inv = 1.0f / rhs;
        out.X = lhs.X * inv;
        out.Y = lhs.Y * inv;
        out.Z = lhs.Z * inv;
        out.W = lhs.W * inv;
    }

    inline Vector4 Clamp(const Vector4 &v, const Vector4 &min, const Vector4 &max)
    {
        Vector4 out;
        Clamp(v, min, max, out);
        return out;
    }

    inline void Clamp(const Vector4 &v, const Vector4 &min, const Vector4 &max, Vector4 &out)
    {
        out.X = Clamp(v.X, min.X, max.X);
        out.Y = Clamp(v.Y, min.Y, max.Y);
        out.Z = Clamp(v.Z, min.Z, max.Z);
        out.W = Clamp(v.W, min.W, max.W);
    }

    inline Vector4 Clamp01(const Vector4 &v)
    {
        Vector4 out;
        Clamp01(v, out);
        return out;
    }

    inline void Clamp01(const Vector4 &v, Vector4 &out)
    {
        out.X = Clamp01(v.X);
        out.Y = Clamp01(v.Y);
        out.Z = Clamp01(v.Z);
        out.W = Clamp01(v.W);
    }

    inline Vector4 Remap(const Vector4 &in, const Vector4 &inRangeMin, const Vector4 &inRangeMax, const Vector4 &outRangeMin, const Vector4 &outRangeMax)
    {
        Vector4 out;
        Remap(in, inRangeMin, inRangeMax, outRangeMin, outRangeMax, out);
        return out;
    }

    inline void Remap(const Vector4 &in, const Vector4 &inRangeMin, const Vector4 &inRangeMax, const Vector4 &outRangeMin, const Vector4 &outRangeMax, Vector4 &out)
    {
        out.X = Remap(in.X, inRangeMin.X, inRangeMax.X, outRangeMin.X, outRangeMax.X);
        out.Y = Remap(in.Y, inRangeMin.Y, inRangeMax.Y, outRangeMin.Y, outRangeMax.Y);
        out.Z = Remap(in.Z, inRangeMin.Z, inRangeMax.Z, outRangeMin.Z, outRangeMax.Z);
        out.W = Remap(in.W, inRangeMin.W, inRangeMax.W, outRangeMin.W, outRangeMax.W);
    }

    inline Vector4 Max(const Vector4 &v1, const Vector4 &v2)
    {
        Vector4 out;
        Max(v1, v2, out);
        return out;
    }

    inline void Max(const Vector4 &v1, const Vector4 &v2, Vector4 &out)
    {
        out.X = Max(v1.X, v2.X);
        out.Y = Max(v1.Y, v2.Y);
        out.Z = Max(v1.Z, v2.Z);
        out.W = Max(v1.W, v2.W);
    }

    inline Vector4 Min(const Vector4 &v1, const Vector4 &v2)
    {
        Vector4 out;
        Min(v1, v2, out);
        return out;
    }

    inline void Min(const Vector4 &v1, const Vector4 &v2, Vector4 &out)
    {
        out.X = Min(v1.X, v2.X);
        out.Y = Min(v1.Y, v2.Y);
        out.Z = Min(v1.Z, v2.Z);
        out.W = Min(v1.W, v2.W);
    }

    inline Vector4 Ceiling(const Vector4 &v)
    {
        Vector4 out;
        Ceiling(v, out);
        return out;
    }

    inline void Ceiling(const Vector4 &v, Vector4 &out)
    {
        out.X = Ceiling(v.X);
        out.Y = Ceiling(v.Y);
        out.Z = Ceiling(v.Z);
        out.W = Ceiling(v.W);
    }

    inline Vector4 Floor(const Vector4 &v)
    {
        Vector4 out;
        Floor(v, out);
        return out;
    }

    inline void Floor(const Vector4 &v, Vector4 &out)
    {
        out.X = Floor(v.X);
        out.Y = Floor(v.Y);
        out.Z = Floor(v.Z);
        out.W = Floor(v.W);
    }

    inline Vector4 Round(const Vector4 &v)
    {
        Vector4 out;
        Round(v, out);
        return out;
    }

    inline void Round(const Vector4 &v, Vector4 &out)
    {
        out.X = Round(v.X);
        out.Y = Round(v.Y);
        out.Z = Round(v.Z);
        out.W = Round(v.W);
    }

    inline float Length(const Vector4 &v)
    {
        return Sqrt(LengthSquared(v));
    }

    inline float LengthSquared(const Vector4 &v)
    {
        return ((v.X * v.X) + (v.Y * v.Y) + (v.Z * v.Z) + (v.W * v.W));
    }

    inline float Distance(const Vector4 &lhs, const Vector4 &rhs)
    {
        return Length(lhs - rhs);
    }

    inline float DistanceSquared(const Vector4 &lhs, const Vector4 &rhs)
    {
        return LengthSquared(lhs - rhs);
    }

    inline Vector4 Normalize(const Vector4 &v)
    {
        Vector4 out;
        Normalize(v, out);
        return out;
    }

    inline void Normalize(const Vector4 &v, Vector4 &out)
    {
        float lengthSquared = LengthSquared(v);
        DebugAssert(false == NearlyZero(lengthSquared), "Trying to normalize a zero vector!");
        Multiply(v, InvSqrt(lengthSquared), out);
    }

    inline Vector4 Negate(const Vector4 &v)
    {
        Vector4 out;
        Negate(v, out);
        return out;
    }

    inline void Negate(const Vector4 &v, Vector4 &out)
    {
        out.X = -v.X;
        out.Y = -v.Y;
        out.Z = -v.Z;
        out.W = -v.W;
    }

    inline float Dot(const Vector4 &lhs, const Vector4 &rhs)
    {
        return ((lhs.X * rhs.X) + (lhs.Y * rhs.Y) + (lhs.Z * rhs.Z) + (lhs.W * rhs.W));
    }

    inline Vector4 Lerp(const Vector4 &v1, const Vector4 &v2, float weight)
    {
        Vector4 out;
        Lerp(v1, v2, weight, out);
        return out;
    }

    inline void Lerp(const Vector4 &v1, const Vector4 &v2, float weight, Vector4 &out)
    {
        out.X = Lerp(v1.X, v2.X, weight);
        out.Y = Lerp(v1.Y, v2.Y, weight);
        out.Z = Lerp(v1.Z, v2.Z, weight);
        out.W = Lerp(v1.W, v2.W, weight);
    }

    inline Vector4 Hermite(const Vector4 &v1, const Vector4 &t1, const Vector4 &v2, const Vector4 &t2, float weight)
    {
        Vector4 out;
        Hermite(v1, t1, v2, t2, weight, out);
        return out;
    }

    inline void Hermite(const Vector4 &v1, const Vector4 &t1, const Vector4 &v2, const Vector4 &t2, float weight, Vector4 &out)
    {
        out.X = Hermite(v1.X, t1.X, v2.X, t2.X, weight);
        out.Y = Hermite(v1.Y, t1.Y, v2.Y, t2.Y, weight);
        out.Z = Hermite(v1.Z, t1.Z, v2.Z, t2.Z, weight);
        out.W = Hermite(v1.W, t1.W, v2.W, t2.W, weight);
    }

    inline Vector4 SmoothStep(const Vector4 &v1, const Vector4 &v2, float weight)
    {
        Vector4 out;
        SmoothStep(v1, v2, weight, out);
        return out;
    }

    inline void SmoothStep(const Vector4 &v1, const Vector4 &v2, float weight, Vector4 &out)
    {
        out.X = SmoothStep(v1.X, v2.X, weight);
        out.Y = SmoothStep(v1.Y, v2.Y, weight);
        out.Z = SmoothStep(v1.Z, v2.Z, weight);
        out.W = SmoothStep(v1.W, v2.W, weight);
    }

    inline void Swap(Vector4 & v1, Vector4 & v2)
    {
        Swap(v1.X, v2.X);
        Swap(v1.Y, v2.Y);
        Swap(v1.Z, v2.Z);
        Swap(v1.W, v2.W);
    }

} //namespace Math
} //namespace Phx

#endif //_PHX_MATH_VECTOR4_INL_
