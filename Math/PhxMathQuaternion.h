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

#ifndef _PHX_MATH_QUATERNION_H_
#define _PHX_MATH_QUATERNION_H_

namespace Phx {
namespace Math {

    class Quaternion
    {
    public:
        float X;
        float Y;
        float Z;
        float W;

    public:
        static const Quaternion Zero;
        static const Quaternion Identity;

    public:
        static inline Quaternion CreateIdentity();
        static inline void CreateIdentity(Quaternion & out);

        static inline Quaternion CreateOrientation(const Vector3 & forward, const Vector3 & up);
        static inline void CreateOrientation(const Vector3 & forward, const Vector3 & up, Quaternion & out);

        static inline Quaternion CreateFromMatrix(const Matrix4x4 & m);
        static inline void CreateFromMatrix(const Matrix4x4 & m, Quaternion & out);

        static inline Quaternion CreateFromAxisAngle(const Vector3 & axis, float radians);
        static inline void CreateFromAxisAngle(const Vector3 & axis, float radians, Quaternion & out);

        static inline Quaternion CreateRotationX(float radians);
        static inline void CreateRotationX(float radians, Quaternion & out);

        static inline Quaternion CreateRotationY(float radians);
        static inline void CreateRotationY(float radians, Quaternion & out);

        static inline Quaternion CreateRotationZ(float radians);
        static inline void CreateRotationZ(float radians, Quaternion & out);

        static inline Quaternion CreateFromYawPitchRoll(float yaw, float pitch, float roll);
        static inline void CreateFromYawPitchRoll(float yaw, float pitch, float roll, Quaternion & out);

    public:
        inline Quaternion()
        { 
            // Do nothing in the default ctor.
            // So we don't have to pay for arrays or quaternions initialized as an out parameter.
        }
        inline explicit Quaternion(float x, float y, float z, float w);
        inline Quaternion(const Quaternion & src);

        inline ~Quaternion() { }

        inline Quaternion & operator=(const Quaternion & rhs);

        inline float & operator[](unsigned int idx);
        inline const float & operator[](unsigned int idx) const;

        inline Quaternion & operator+=(const Quaternion & rhs);
        inline Quaternion & operator-=(const Quaternion & rhs);

        inline Quaternion & operator*=(float rhs);
        inline Quaternion & operator/=(float rhs);

        inline void Transform(const Matrix4x4 & m);

        inline float Length() const;
        inline float LengthSquared() const;

        inline Vector3 EulerAngles() const;

        inline void Normalize();

        inline void Inverse();
        inline void Negate();

        inline void Set(const Quaternion & src);
        inline void Set(float x, float y, float z, float w);

        inline float * ToArray();
        inline const float * ToArray() const;
    };

    inline bool operator==(const Quaternion & lhs, const Quaternion & rhs);
    inline bool operator!=(const Quaternion & lhs, const Quaternion & rhs);
    inline bool operator>(const Quaternion & lhs, const Quaternion & rhs);
    inline bool operator>=(const Quaternion & lhs, const Quaternion & rhs);
    inline bool operator<(const Quaternion & lhs, const Quaternion & rhs);
    inline bool operator<=(const Quaternion & lhs, const Quaternion & rhs);

    inline Quaternion operator+(const Quaternion & lhs, const Quaternion & rhs);

    inline Quaternion operator-(const Quaternion & lhs, const Quaternion & rhs);
    inline Quaternion operator-(const Quaternion & q);

    inline Quaternion operator*(const Quaternion & lhs, const Quaternion & rhs);
    inline Quaternion operator*(const Quaternion & lhs, float rhs);

    inline bool ExactlyEqual(const Quaternion & lhs, const Quaternion & rhs);
    inline bool ExactlyZero(const Quaternion & q);

    inline bool NearlyEqual(const Quaternion & lhs, const Quaternion & rhs);
    inline bool NearlyZero(const Quaternion & q);

    inline bool AllLess(const Quaternion & lhs, const Quaternion & rhs);
    inline bool AllLessEqual(const Quaternion & lhs, const Quaternion & rhs);

    inline bool AllGreater(const Quaternion & lhs, const Quaternion & rhs);
    inline bool AllGreaterEqual(const Quaternion & lhs, const Quaternion & rhs);

    inline bool IsNormalized(const Quaternion & q);

    inline Quaternion Add(const Quaternion & lhs, const Quaternion & rhs);
    inline void Add(const Quaternion & lhs, const Quaternion & rhs, Quaternion & out);

    inline Quaternion Subtract(const Quaternion & lhs, const Quaternion & rhs);
    inline void Subtract(const Quaternion & lhs, const Quaternion & rhs, Quaternion & out);

    inline Quaternion Multiply(const Quaternion & lhs, const Quaternion & rhs);
    inline Quaternion Multiply(const Quaternion & lhs, float rhs);
    inline void Multiply(const Quaternion & lhs, const Quaternion & rhs, Quaternion & out);
    inline void Multiply(const Quaternion & lhs, float rhs, Quaternion & out);

    inline Quaternion Divide(const Quaternion & lhs, float rhs);
    inline void Divide(const Quaternion & lhs, float rhs, Quaternion & out);

    inline Quaternion Transform(const Quaternion & q, const Matrix4x4 & m);
    inline void Transform(const Quaternion & q, const Matrix4x4 & m, Quaternion & out);

    inline float Length(const Quaternion & q);
    inline float LengthSquared(const Quaternion & q);

    inline Vector3 EulerAngles(const Quaternion & q);

    inline Quaternion Normalize(const Quaternion & q);
    inline void Normalize(const Quaternion & q, Quaternion & out);

    inline Quaternion Inverse(const Quaternion & q);
    inline void Inverse(const Quaternion & q, Quaternion & out);

    inline Quaternion Negate(const Quaternion & q);
    inline void Negate(const Quaternion & q, Quaternion & out);

    inline float Dot(const Quaternion & lhs, const Quaternion & rhs);

    inline Quaternion Lerp(const Quaternion & q1, const Quaternion & q2, float weight);
    inline void Lerp(const Quaternion & q1, const Quaternion & q2, float weight, Quaternion & out);

    inline Quaternion Nlerp(const Quaternion & q1, const Quaternion & q2, float weight);
    inline void Nlerp(const Quaternion & q1, const Quaternion & q2, float weight, Quaternion & out);

    inline Quaternion Slerp(const Quaternion & q1, const Quaternion & q2, float weight);
    inline void Slerp(const Quaternion & q1, const Quaternion & q2, float weight, Quaternion & out);

} //namespace Math
} //namespace Phx

#endif //_PHX_MATH_QUATERNION_H_
