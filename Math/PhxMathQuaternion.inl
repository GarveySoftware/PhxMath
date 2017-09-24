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

#ifndef _PHX_MATH_QUATERNION_INL_
#define _PHX_MATH_QUATERNION_INL_

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// = Some matrix math is transposed vs the references, this is due to pre vs post multiplicaiton.
// - Quaternions use post multiplication q1 * q2 = q2 rotated by q1.
// = Matrices use pre multiplication m1 * m2 = m1 transformed by m2.
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

namespace Phx {
namespace Math {

    inline Quaternion Quaternion::CreateIdentity()
    {
        Quaternion out;
        CreateIdentity(out);
        return out;
    }

    inline void Quaternion::CreateIdentity(Quaternion & out)
    {
        out.Copy(Quaternion::Identity);
    }

    inline Quaternion Quaternion::CreateOrientation(const Vector3 & forward, const Vector3 & up)
    {
        Quaternion out;
        CreateOrientation(forward, up, out);
        return out;
    }

    inline void Quaternion::CreateOrientation(const Vector3 & forward, const Vector3 & up, Quaternion & out)
    {
        Matrix4x4 m;
        Matrix4x4::CreateOrientation(forward, up, m);
        CreateFromMatrix(m, out);
    }

    inline Quaternion Quaternion::CreateFromMatrix(const Matrix4x4 & m)
    {
        Quaternion out;
        CreateFromMatrix(m, out);
        return out;
    }

    inline void Quaternion::CreateFromMatrix(const Matrix4x4 & m, Quaternion & out)
    {
        // Converts a rotation matrix to a Quaternion.
        // Treats the input matrix as if it is a 3x3 (pure rotation).
        // Any translation and projection components will be lost.
        //
        // Ref: http://www.cs.ucr.edu/~vbz/resources/quatut.pdf
        //      http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/

        float s;
        
        const float trace = m.M11 + m.M22 + m.M33;
        if (trace >= 0.0f)
        {
            s = Sqrt(trace + 1.0f);
            out.W = s * 0.5f;
            s = 0.5f / s;
            out.X = (m.M23 - m.M32) * s;
            out.Y = (m.M31 - m.M13) * s;
            out.Z = (m.M12 - m.M21) * s;
        }
        else if (m.M11 > m.M22 && m.M11 > m.M33)
        {
            s = Sqrt(m.M11 - m.M22 - m.M33 + 1.0f);
            out.X = s * 0.5f;
            s = 0.5f / s;
            out.Y = (m.M12 + m.M21) * s;
            out.Z = (m.M13 + m.M31) * s;       
            out.W = (m.M23 - m.M32) * s;       
        }
        else if (m.M22 > m.M33)
        {
            s = Sqrt(m.M22 - m.M11 - m.M33 + 1.0f);
            out.Y = s * 0.5f;
            s = 0.5f / s;
            out.X = (m.M12 + m.M21) * s;
            out.Z = (m.M23 + m.M32) * s;
            out.W = (m.M31 - m.M13) * s;
        }
        else
        {
            s = Sqrt(m.M33 - m.M11 - m.M22 + 1.0f);
            out.Z = s * 0.5f;
            s = 0.5f / s;
            out.X = (m.M13 + m.M31) * s;
            out.Y = (m.M23 + m.M32) * s;
            out.W = (m.M12 - m.M21) * s;
        }
    }

    inline Quaternion Quaternion::CreateFromAxisAngle(const Vector3 & axis, float radians)
    {
        Quaternion out;
        CreateFromAxisAngle(axis, radians, out);
        return out;
    }

    inline void Quaternion::CreateFromAxisAngle(const Vector3 & axis, float radians, Quaternion & out)
    {
        DebugAssert(IsNormalized(axis), "Axis must be normalized to create a quaternion.");

        float s, c;
        SinCos(radians * 0.5f, &s, &c);
        out.Copy(axis.X * s, axis.Y * s, axis.Z * s, c);
    }

    inline Quaternion Quaternion::CreateRotationX(float radians)   
    {
        Quaternion out;
        CreateRotationX(radians, out);
        return out;
    }

    inline void Quaternion::CreateRotationX(float radians, Quaternion & out)
    {
        float s, c;
        SinCos(radians * 0.5f, &s, &c);
        out.Copy(s, 0.0f, 0.0f, c);
    }

    inline Quaternion Quaternion::CreateRotationY(float radians)
    {
        Quaternion out;
        CreateRotationY(radians, out);
        return out;
    }

    inline void Quaternion::CreateRotationY(float radians, Quaternion & out)
    {
        float s, c;
        SinCos(radians * 0.5f, &s, &c);
        out.Copy(0.0f, s, 0.0f, c);
    }

    inline Quaternion Quaternion::CreateRotationZ(float radians)
    {
        Quaternion out;
        CreateRotationZ(radians, out);
        return out;
    }

    inline void Quaternion::CreateRotationZ(float radians, Quaternion & out)
    {
        float s, c;
        SinCos(radians * 0.5f, &s, &c);
        out.Copy(0.0f, 0.0f, s, c);
    }

    inline Quaternion Quaternion::CreateFromYawPitchRoll(float yaw, float pitch, float roll)
    {
        Quaternion out;
        CreateFromYawPitchRoll(yaw, pitch, roll, out);
        return out;
    }

    inline void Quaternion::CreateFromYawPitchRoll(float yaw, float pitch, float roll, Quaternion & out)
    {
        // This will create a YXZ rotation quaternion.
        // Yaw is applied first, then rotated by pitch, then rotated by roll.
        // Yaw, pitch, and roll are expected to be angles in radians.
        //
        // Unrolled and simplified form of this:
        // CreateRotaitonZ(roll) * (CreateRotationX(pitch) * CreateRotationY(yaw))

        float sY, cY;
        SinCos(yaw * 0.5f, &sY, &cY);

        float sX, cX;
        SinCos(pitch * 0.5f, &sX, &cX);

        float sZ, cZ;
        SinCos(roll * 0.5f, &sZ, &cZ);

        out.X = (cZ * sX * cY) - (sZ * cX * sY);
        out.Y = (sZ * sX * cY) + (cZ * cX * sY);
        out.Z = (cZ * sX * sY) + (sZ * cX * cY);
        out.W = (cZ * cX * cY) - (sZ * sX * sY);
    }

    inline Quaternion::Quaternion(float x, float y, float z, float w)
        : X(x), Y(y), Z(z), W(w)
    { }

    inline Quaternion::Quaternion(const Quaternion & src)
    {
        Copy(src);
    }

    inline Quaternion & Quaternion::operator=(const Quaternion & rhs)
    {
        Copy(rhs);
        return *this;
    }

    inline float & Quaternion::operator[](unsigned int idx)
    {
        DebugAssert(idx < 4, "Invalid index (%u) into a quaternion!", idx);
        return ToArray()[idx];
    }

    inline const float & Quaternion::operator[](unsigned int idx) const
    {
        DebugAssert(idx < 4, "Invalid index (%u) into a quaternion!", idx);
        return ToArray()[idx];
    }

    inline Quaternion & Quaternion::operator+=(const Quaternion & rhs)
    {
        Math::Add(*this, rhs, *this);
        return *this;
    }

    inline Quaternion & Quaternion::operator-=(const Quaternion & rhs)
    {
        Math::Subtract(*this, rhs, *this);
        return *this;
    }

    inline Quaternion & Quaternion::operator*=(float rhs)
    {
        Math::Multiply(*this, rhs, *this);
        return *this;
    }

    inline Quaternion & Quaternion::operator/=(float rhs)
    {
        Math::Divide(*this, rhs, *this);
        return *this;
    }

    inline void Quaternion::Transform(const Matrix4x4 & m)
    {
        Math::Transform(*this, m, *this);
    }

    inline float Quaternion::Length() const
    {
        return Math::Length(*this);
    }

    inline float Quaternion::LengthSquared() const
    {
        return Math::LengthSquared(*this);
    }

    inline Vector3 Quaternion::EulerAngles() const
    {
        return Math::EulerAngles(*this);
    }

    inline void Quaternion::Normalize()
    {
        Math::Normalize(*this, *this);
    }

    inline void Quaternion::Inverse()
    {
        Math::Inverse(*this, *this);
    }

    inline void Quaternion::Negate()
    {
        Math::Negate(*this, *this);
    }

    inline void Quaternion::Copy(const Quaternion & src)
    {
        memcpy(this, &src, sizeof(Quaternion));
    }

    inline void Quaternion::Copy(float x, float y, float z, float w)
    {
        this->X = x;
        this->Y = y;
        this->Z = z;
        this->W = w;
    }

    inline float * Quaternion::ToArray()
    {
        return &(this->X);
    }

    inline const float * Quaternion::ToArray() const
    {
        return &(this->X);
    }

    inline bool operator==(const Quaternion & lhs, const Quaternion & rhs)
    {
        return ExactlyEqual(lhs, rhs);
    }

    inline bool operator!=(const Quaternion & lhs, const Quaternion & rhs)
    {
        return (false == ExactlyEqual(lhs, rhs));
    }

    inline bool operator>(const Quaternion & lhs, const Quaternion & rhs)
    {
        return AllGreater(lhs, rhs);
    }

    inline bool operator>=(const Quaternion & lhs, const Quaternion & rhs)
    {
        return AllGreaterEqual(lhs, rhs);
    }

    inline bool operator<(const Quaternion & lhs, const Quaternion & rhs)
    {
        return AllLess(lhs, rhs);
    }

    inline bool operator<=(const Quaternion & lhs, const Quaternion & rhs)
    {
        return AllLessEqual(lhs, rhs);
    }

    inline Quaternion operator+(const Quaternion & lhs, const Quaternion & rhs)
    {
        Quaternion out;
        Add(lhs, rhs, out);
        return out;
    }

    inline Quaternion operator-(const Quaternion & lhs, const Quaternion & rhs)
    {
        Quaternion out;
        Subtract(lhs, rhs, out);
        return out;
    }

    inline Quaternion operator-(const Quaternion & q)
    {
        Quaternion out;
        Negate(q, out);
        return out;
    }

    inline Quaternion operator*(const Quaternion & lhs, const Quaternion & rhs)
    {
        Quaternion out;
        Multiply(lhs, rhs, out);
        return out;
    }

    inline Quaternion operator*(const Quaternion & lhs, float rhs)
    {
        Quaternion out;
        Multiply(lhs, rhs, out);
        return out;
    }

    inline bool ExactlyEqual(const Quaternion & lhs, const Quaternion & rhs)
    {
        return (ExactlyEqual(lhs.X, rhs.X) &&
                ExactlyEqual(lhs.Y, rhs.Y) &&
                ExactlyEqual(lhs.Z, rhs.Z) &&
                ExactlyEqual(lhs.W, rhs.W));
    }

    inline bool ExactlyZero(const Quaternion & q)
    {
        return ExactlyEqual(q, Quaternion::Zero);
    }

    inline bool NearlyEqual(const Quaternion & lhs, const Quaternion & rhs)
    {
        return NearlyZero(lhs - rhs);
    }

    inline bool NearlyZero(const Quaternion & q)
    {
        return (NearlyZero(q.X) &&
                NearlyZero(q.Y) &&
                NearlyZero(q.Z) &&
                NearlyZero(q.W));
    }

    inline bool AllLess(const Quaternion & lhs, const Quaternion & rhs)
    {
        return ((lhs.X < rhs.X) && (lhs.Y < rhs.Y) && (lhs.Z < rhs.Z) && (lhs.W < rhs.W));
    }

    inline bool AllLessEqual(const Quaternion & lhs, const Quaternion & rhs)
    {
        return ((lhs.X <= rhs.X) && (lhs.Y <= rhs.Y) && (lhs.Z <= rhs.Z) && (lhs.W <= rhs.W));
    }

    inline bool AllGreater(const Quaternion & lhs, const Quaternion & rhs)
    {
        return ((lhs.X > rhs.X) && (lhs.Y > rhs.Y) && (lhs.Z > rhs.Z) && (lhs.W > rhs.W));
    }

    inline bool AllGreaterEqual(const Quaternion & lhs, const Quaternion & rhs)
    {
        return ((lhs.X >= rhs.X) && (lhs.Y >= rhs.Y) && (lhs.Z >= rhs.Z) && (lhs.W >= rhs.W));
    }

    inline bool IsNormalized(const Quaternion & q)
    {
        return NearlyEqual(LengthSquared(q), 1.0f);
    }

    inline Quaternion Add(const Quaternion & lhs, const Quaternion & rhs)
    {
        Quaternion out;
        Add(lhs, rhs, out);
        return out;
    }

    inline void Add(const Quaternion & lhs, const Quaternion & rhs, Quaternion & out)
    {
        out.X = lhs.X + rhs.X;
        out.Y = lhs.Y + rhs.Y;
        out.Z = lhs.Z + rhs.Z;
        out.W = lhs.W + rhs.W;
    }

    inline Quaternion Subtract(const Quaternion & lhs, const Quaternion & rhs)
    {
        Quaternion out;
        Subtract(lhs, rhs, out);
        return out;
    }

    inline void Subtract(const Quaternion & lhs, const Quaternion & rhs, Quaternion & out)
    {
        out.X = lhs.X - rhs.X;
        out.Y = lhs.Y - rhs.Y;
        out.Z = lhs.Z - rhs.Z;
        out.W = lhs.W - rhs.W;
    }

    inline Quaternion Multiply(const Quaternion & lhs, const Quaternion & rhs)
    {
        Quaternion out;
        Multiply(lhs, rhs, out);
        return out;
    }

    inline Quaternion Multiply(const Quaternion & lhs, float rhs)
    {
        Quaternion out;
        Multiply(lhs, rhs, out);
        return out;
    }

    inline void Multiply(const Quaternion & lhs, const Quaternion & rhs, Quaternion & out)
    {
        // The quaternion concatenation is defined as:
        // lhs * rhs = (rhs.W * lhs.W - Dot(rhs.XYZ, lhs.XYZ), rhs.W * lhs.XYZ + lhs.W * rhs.XYZ + Cross(lhs.XYZ, rhs.XYZ))
        //
        // Post multiplication: lhs * rhs = rhs rotated by lhs.
        // The result should be normalized (assuming input is normalized), but floating point error will accumulate.
        //
        // The implementation below is an unrolled version of the equation above.
        //
        // Ref: http://www.cs.ucr.edu/~vbz/resources/quatut.pdf
        //      Top of page 7.

        const float x = (rhs.W * lhs.X) + (lhs.W * rhs.X) + (lhs.Y * rhs.Z) - (lhs.Z * rhs.Y);
        const float y = (rhs.W * lhs.Y) + (lhs.W * rhs.Y) + (lhs.Z * rhs.X) - (lhs.X * rhs.Z);
        const float z = (rhs.W * lhs.Z) + (lhs.W * rhs.Z) + (lhs.X * rhs.Y) - (lhs.Y * rhs.X);
        const float w = (rhs.W * lhs.W) - (lhs.X * rhs.X) - (lhs.Y * rhs.Y) - (lhs.Z * rhs.Z);

        out.Copy(x, y, z, w);
    }

    inline void Multiply(const Quaternion & lhs, float rhs, Quaternion & out)
    {
        out.X = lhs.X * rhs;
        out.Y = lhs.Y * rhs;
        out.Z = lhs.Z * rhs;
        out.W = lhs.W * rhs;
    }

    inline Quaternion Divide(const Quaternion & lhs, float rhs)
    {
        Quaternion out;
        Divide(lhs, rhs, out);
        return out;
    }

    inline void Divide(const Quaternion & lhs, float rhs, Quaternion & out)
    {
        DebugAssert(false == NearlyZero(rhs), "Divide by zero!");
        const float inv = 1.0f / rhs;
        out.X = lhs.X * inv;
        out.Y = lhs.Y * inv;
        out.Z = lhs.Z * inv;
        out.W = lhs.W * inv;
    }

    inline Quaternion Transform(const Quaternion & q, const Matrix4x4 & m)
    {
        Quaternion out;
        Transform(q, m, out);
        return out;
    }

    inline void Transform(const Quaternion & q, const Matrix4x4 & m, Quaternion & out)
    {
        // Rotates q by m
        Quaternion lhs;
        Quaternion::CreateFromMatrix(m, lhs);
        Multiply(lhs, q, out);
    }

    inline float Length(const Quaternion & q)
    {
        return Sqrt(LengthSquared(q));
    }

    inline float LengthSquared(const Quaternion & q)
    {
        return ((q.X * q.X) + (q.Y * q.Y) + (q.Z * q.Z) + (q.W * q.W));
    }

    inline Vector3 EulerAngles(const Quaternion & q)
    {
        // To convert a quaternion to euler angles we convert it to a rotaiton matrix and then convert the matrix to euler angles.
        // Doing the full conversion would waste time so we only do the parts necessary below.
        //
        // Rotation matrix conversion of a normalized quaternion.
        //
        // [ 1 - 2yy - 2zz, 2xy + 2wz,     2xz - 2wy,     0 ]
        // [ 2xy - 2wz,     1 - 2xx - 2zz, 2yz + 2wx,     0 ]
        // [ 2xz + 2wy,     2yz - 2wx,     1 - 2xx - 2yy, 0 ]
        // [ 0,             0,             0,             1 ]
        //
        // YawPitchRoll (YXZ) Rotation Matrix
        //
        // [ cY * cZ - sY * sX * sZ, cY * sZ + sY * sX * cZ, -sY * cX, 0 ]
        // [ cX * -sZ,               cX * cZ,                 sX,    , 0 ]
        // [ sY * cZ + cY * sX * sZ, sY * sZ - cY * sX * cZ,  cY * cX, 0 ]
        // [ 0                       0,                       0,       1 ]
        //
        // Ref: http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToEuler/index.htm
        //      Also see Matrix4x4::EulerAngles() for more information.

        DebugAssert(IsNormalized(q), "Quaternion must be normalized to convert to euler angles.");

        const float s = 2.0f;

        const float x = s * q.X;
        const float y = s * q.Y;
        const float z = s * q.Z;

        const float M23 = y * q.Z + x * q.W;

        if (NearlyEqual(M23, 1.0f))
        {
            // sin(x) = 1.0, cos(x) = 0.0
            // M11 = cos(z + y), M12 = sin(z + y)
            // z + y = atan2(M12, M11), not a unique solution
            const float M12 = x * q.Y + z * q.W;
            const float M11 = 1.0f - y * q.Y - z * q.Z;
            return Vector3(Trig::PiOverTwo, ATan2(M12, M11), 0.0f);
        }
        else if (NearlyEqual(M23, -1.0f))
        {
            // sin(x) = -1.0, cos(x) = 0.0
            // M11 = cos(z - y), M12 = sin(z - y)
            // z - y = atan2(M12, M11), not a unique solution
            const float M12 = x * q.Y + z * q.W;
            const float M11 = 1.0f - y * q.Y - z * q.Z;
            return Vector3(-Trig::PiOverTwo, -ATan2(M12, M11), 0.0f);
        }
        else
        {
            // M23 = sin(x), -M13/M33 = tan(y), -M12/M22 = tan(z)
            const float xx = x * q.X;
            const float M13 = x * q.Z - y * q.W;
            const float M33 = 1.0f - xx - y * q.Y;
            const float M21 = x * q.Y - z * q.W;
            const float M22 = 1.0f - xx - z * q.Z;
            return Vector3(ASin(M23), ATan2(-M13, M33), ATan2(-M21, M22));
        }
    }

    inline Quaternion Normalize(const Quaternion & q)
    {
        Quaternion out;
        Normalize(q, out);
        return out;
    }

    inline void Normalize(const Quaternion & q, Quaternion & out)
    {
        float lengthSquared = LengthSquared(q);
        DebugAssert(false == NearlyZero(lengthSquared), "Trying to normalize a zero quaternion!");
        Multiply(q, InvSqrt(lengthSquared), out);
    }

    inline Quaternion Inverse(const Quaternion & q)
    {
        Quaternion out;
        Inverse(q, out);
        return out;
    }

    inline void Inverse(const Quaternion & q, Quaternion & out)
    {
        DebugAssert(IsNormalized(q), "Quaternaion must be normalized to invert.");
        out.X = -q.X;
        out.Y = -q.Y;
        out.Z = -q.Z;
        out.W =  q.W;
    }

    inline Quaternion Negate(const Quaternion & q)
    {
        Quaternion out;
        Negate(q, out);
        return out;
    }

    inline void Negate(const Quaternion & q, Quaternion & out)
    {
        out.X = -q.X;
        out.Y = -q.Y;
        out.Z = -q.Z;
        out.W = -q.W;
    }

    inline float Dot(const Quaternion & lhs, const Quaternion & rhs)
    {
        return ((lhs.X * rhs.X) + (lhs.Y * rhs.Y) + (lhs.Z * rhs.Z) + (lhs.W * rhs.W));
    }

    inline Quaternion Lerp(const Quaternion & q1, const Quaternion & q2, float weight)
    {
        Quaternion out;
        Lerp(q1, q2, weight, out);
        return out;
    }

    inline void Lerp(const Quaternion & q1, const Quaternion & q2, float weight, Quaternion & out)
    {
        // Linearly iterpolates two quaternions, can produce acceptable results for very accute angles (< 30 degrees).
        // The rate of rotation will not be constant: it starts slow, speeds up in the middle, and slows again at the end.
        //
        // It should not be used to interpolate between quaternions that are 180 degrees apart or are negations of eachother (will pass through [0,0,0,0]).

        out.X = Lerp(q1.X, q2.X, weight);
        out.Y = Lerp(q1.Y, q2.Y, weight);
        out.Z = Lerp(q1.Z, q2.Z, weight);
        out.W = Lerp(q1.W, q2.W, weight);

        Normalize(out, out);
    }

    inline Quaternion Nlerp(const Quaternion & q1, const Quaternion & q2, float weight)
    {
        Quaternion out;
        Nlerp(q1, q2, weight, out);
        return out;
    }

    inline void Nlerp(const Quaternion & q1, const Quaternion & q2, float weight, Quaternion & out)
    {
        // Nlerp is cheaper than slerp, and produces acceptable results for accute angles (< 90 degrees).
        // If left alone the rate of rotation would not be constant: it would start slow, speed up in the middle, and slow again at the end.
        // To compensate for this, t is altered and the result gives a close approximate to slerp (overall error of 2.07 x 10-3).
        //
        // k = 0.5069269f * (1.0 - 0.7878088f * cosTheta)^2
        // t' = 2kt^3 - 3kt^2 + (1+k)t
        //
        // It should not be used to interpolate between quaternions that are 180 degrees apart, aligned, or negations of eachother (will pass through [0,0,0,0]).
        //
        // Ref: http://number-none.com/product/Hacking%20Quaternions/
        //      http://number-none.com/product/Understanding%20Slerp,%20Then%20Not%20Using%20It/

        DebugAssert(IsNormalized(q1), "Quaternaion must be normalized to nlerp.");
        DebugAssert(IsNormalized(q2), "Quaternaion must be normalized to nlerp.");

        const float cosTheta = Dot(q1, q2);
        
        DebugAssert(false == NearlyEqual(Abs(cosTheta), 1.0f), 
            "Using nlerp on quaternions that are 180 degrees apart, aligned, or negations of eachother.");

        const float f = 1.0f - (0.7878088f * cosTheta);
        const float k = 0.5069269f * f * f;
        const float t = weight;
        const float tt = t * t;
        const float ttt = tt * t;
        const float tPrime = (2.0f * k * ttt) - (3.0f * k * tt) + ((1.0f + k) * t);

        out.X = Lerp(q1.X, q2.X, tPrime);
        out.Y = Lerp(q1.Y, q2.Y, tPrime);
        out.Z = Lerp(q1.Z, q2.Z, tPrime);
        out.W = Lerp(q1.W, q2.W, tPrime);

        Normalize(out, out);
    }

    inline Quaternion Slerp(const Quaternion & q1, const Quaternion & q2, float weight)
    {
        Quaternion out;
        Slerp(q1, q2, weight, out);
        return out;
    }

    inline void Slerp(const Quaternion & q1, const Quaternion & q2, float weight, Quaternion & out)
    {
        // Interpolates 2 orientations along the arc that connects them.
        // The result should be a unit quaternion, but floating point error will accumulate.
        //
        // Take a look at Nlerp before using this if speed is important.
        //
        // This should not be used to interpolate between quaternions that are 180 degrees apart, aligned, negations of eachother.
        //
        // Ref: http://www.geometrictools.com/Documentation/Quaternions.pdf

        DebugAssert(IsNormalized(q1), "Quaternaion must be normalized to slerp.");
        DebugAssert(IsNormalized(q2), "Quaternaion must be normalized to slerp.");

        const float cosTheta = Dot(q1, q2);

        DebugAssert(false == NearlyEqual(Abs(cosTheta), 1.0f), 
            "Using slerp on quaternions that are 180 degrees apart, aligned, or negations of eachother.");

        const float theta = ACos(cosTheta);
        if (NearlyZero(theta))
        {
            // theta is too close to 0 for slerp
            out.Copy(q1);
            return;
        }
        
        const float invSinTheta = 1.0f / Sin(theta);
        
        const float tAngle = weight * theta;
        const float t1 = Sin(theta - tAngle) * invSinTheta;
        const float t2 = Sin(tAngle) * invSinTheta;

        out.X = t1 * q1.X + t2 * q2.X;
        out.Y = t1 * q1.Y + t2 * q2.Y;
        out.Z = t1 * q1.Z + t2 * q2.Z;
        out.W = t1 * q1.W + t2 * q2.W;
    }

} //namespace Math
} //namespace Phx

#endif //_PHX_MATH_QUATERNION_INL_
