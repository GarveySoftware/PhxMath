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

#ifndef _PHX_MATH_MATRIX4X4_INL_
#define _PHX_MATH_MATRIX4X4_INL_

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// = Some matrix math is transposed vs the references, this is due to pre vs post multiplicaiton.
// - Quaternions use post multiplication q1 * q2 is q2 rotated by q1.
// = Matrices use pre multiplication m1 * m2 is m1 transformed by m2.
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

namespace Phx {
namespace Math {

    inline Matrix4x4 Matrix4x4::CreateIdentity()
    {
        Matrix4x4 out;
        CreateIdentity(out);
        return out;
    }

    inline void Matrix4x4::CreateIdentity(Matrix4x4 & out)
    {
        out.Copy(Matrix4x4::Identity);
    }

    inline Matrix4x4 Matrix4x4::CreateView(const Vector3 & position, const Vector3 & target, const Vector3 & up)
    {
        Matrix4x4 out;
        CreateView(position, target, up, out);
        return out;
    }

    inline void Matrix4x4::CreateView(const Vector3 & position, const Vector3 & target, const Vector3 & up, Matrix4x4 & out)
    {
        // The View matrix translates from World space to View (also called Camera or Eye) space.
        // We do this by building the inverse of the "Camera to World" matrix.
        //
        // The implementation below is a simplifed version of this matrix multiplication:
        //
        // [ 1,      0,      0,     0 ] * [ xAxis.X, yAxis.X, zAxis.X,  0 ]
        // [ 0,      1,      0,     0 ]   [ xAxis.Y, yAxis.Y, zAxis.Y,  0 ]
        // [ 0,      0,      1,     0 ]   [ xAxis.Z, yAxix.Z, zAxis.Z,  0 ]
        // [-pos.X, -pos.Y, -pos.Z, 1 ]   [ 0,       0,       0,        1 ]
        //
        // Where x, y, zAxis are the basis vectors for the camera space, and pos is the translation of the camera.
        //
        // Ref: http://stackoverflow.com/questions/349050/calculating-a-lookat-matrix
        //      http://msdn.microsoft.com/en-us/library/windows/desktop/bb281711(v=vs.85).aspx
        //
        // Note: This is a right handed view matrix.

        Vector3 xAxis;
        Vector3 yAxis;
        Vector3 zAxis;

        DebugAssert(false == NearlyEqual(position, target), "Cannot create a look at matrix with position == target");

        Math::Subtract(position, target, zAxis);
        zAxis.Normalize();

        Math::Cross(up, zAxis, xAxis);
        xAxis.Normalize();

        Math::Cross(zAxis, xAxis, yAxis);
        yAxis.Normalize();

        out.Copy( xAxis.X,               yAxis.X,               zAxis.X,              0.0f,
                  xAxis.Y,               yAxis.Y,               zAxis.Y,              0.0f,
                  xAxis.Z,               yAxis.Z,               zAxis.Z,              0.0f,
                 -Dot(xAxis, position), -Dot(yAxis, position), -Dot(zAxis, position), 1.0f);
    }

    inline Matrix4x4 Matrix4x4::CreateOrthographic(float left, float right, float bottom, float top, float nearDistance, float farDistance)
    {
        Matrix4x4 out;
        Matrix4x4::CreateOrthographic(left, right, bottom, top, nearDistance, farDistance, out);
        return out;
    }

    inline void Matrix4x4::CreateOrthographic(float left, float right, float bottom, float top, float nearDistance, float farDistance, Matrix4x4 & out)
    {
        // windows.h strikes again! they #define near and far in minwindef.h :(

        // We are building a projection matrix, which defines the clipping planes.
        // For an orthographic projection, these planes form a box with the min (left, bottom, nearDistance) and the max at (right, top, far) in View space.
        // The box is mapped (translated and scaled) to min (-1,-1, 0) and max (1, 1, 1) to go from View space to Projection space.
        // Projection space is also know as the canonical view volume, the canonical clipping volume, or NDC (normalized device coordinate) space.
        //
        // [ 2/(r-l),     0,           0,       0 ]
        // [ 0,           2/(t-b)      0,       0 ]
        // [ 0,           0,           1/(n-f), 0 ]
        // [ (l+r)/(l-r), (t+b)/(b-t), n/(n-f), 1 ]
        //
        // Ref: http://msdn.microsoft.com/en-us/library/windows/desktop/bb205348(v=vs.85).aspx
        //
        // Note: The cannonical view volume differs between directX and openGL (ogl uses z -1 to 1), we use the directX way.
        //       This is a right handed orthographic projection matrix.

        DebugAssert(false == NearlyEqual(left, right) && false == NearlyEqual(bottom, top) && nearDistance >= 0.0f && farDistance > nearDistance
          , "Invalid left/right, bottom/top, or near/far when creating an orthographic projection. left: (%f), right: (%f), bottom: (%f), top: (%f), near: (%f), far: (%f)"
          , left, right, bottom, top, nearDistance, farDistance);

        const float invNFDelta = 1.0f / (nearDistance - farDistance);

        out.M11 = 2.0f / (right - left);
        out.M12 = 0.0f;
        out.M13 = 0.0f;
        out.M14 = 0.0f;

        out.M21 = 0.0f;
        out.M22 = 2.0f / (top - bottom);
        out.M23 = 0.0f;
        out.M24 = 0.0f;

        out.M31 = 0.0f;
        out.M32 = 0.0f;
        out.M33 = invNFDelta;
        out.M34 = 0.0f;

        out.M41 = (left + right) / (left - right);
        out.M42 = (top + bottom) / (bottom - top);
        out.M43 = nearDistance * invNFDelta;
        out.M44 = 1.0f;
    }

    inline Matrix4x4 Matrix4x4::CreateOrthographic(float width, float height, float nearDistance, float farDistance)
    {
        Matrix4x4 out;
        CreateOrthographic(width, height, nearDistance, farDistance, out);
        return out;
    }

    inline void Matrix4x4::CreateOrthographic(float width, float height, float nearDistance, float farDistance, Matrix4x4 & out)
    {
        // windows.h strikes again! they #define near and far in minwindef.h :(

        // This is a special case of the orthographic projection matrix above, assuming left=-w/2, right=w/2, bottom=-h/2, top=h/2
        //
        // [ 2/w, 0,   0,       0 ]
        // [ 0,   2/h, 0,       0 ]
        // [ 0,   0,   1/(n-f), 0 ]
        // [ 0,   0,   n/(n-f), 1 ]
        //
        // Ref: http://msdn.microsoft.com/en-us/library/windows/desktop/bb205348(v=vs.85).aspx
        //      http://msdn.microsoft.com/en-us/library/windows/desktop/bb205349(v=vs.85).aspx
        //
        // Note: The cannonical view volume differs between directX and openGL (ogl uses z -1 to 1), we use the directX way.
        //       This is a right handed orthographic projection matrix.

        DebugAssert(false == NearlyZero(width) && false == NearlyZero(height) && nearDistance >= 0.0f && farDistance > nearDistance
          , "Invalid width/height, or near/far when creating an orthographic projection. width: (%f), height: (%f), near: (%f), far: (%f)"
          , width, height, nearDistance, farDistance);

        const float invNFDelta = 1.0f / (nearDistance - farDistance);

        out.M11 = 2.0f / width;
        out.M12 = 0.0f;
        out.M13 = 0.0f;
        out.M14 = 0.0f;

        out.M21 = 0.0f;
        out.M22 = 2.0f / height;
        out.M23 = 0.0f;
        out.M24 = 0.0f;

        out.M31 = 0.0f;
        out.M32 = 0.0f;
        out.M33 = invNFDelta;
        out.M34 = 0.0f;

        out.M41 = 0.0f;
        out.M42 = 0.0f;
        out.M43 = nearDistance * invNFDelta;
        out.M44 = 1.0f;
    }

    inline Matrix4x4 Matrix4x4::CreatePerspective(float fieldOfView, float aspectRatio, float nearDistance, float farDistance)
    {
        Matrix4x4 out;
        CreatePerspective(fieldOfView, aspectRatio, nearDistance, farDistance, out);
        return out;
    }

    inline void Matrix4x4::CreatePerspective(float fieldOfView, float aspectRatio, float nearDistance, float farDistance, Matrix4x4 & out)
    {
        // We are building a projection matrix, which defines the clipping planes.
        // For a perspective projection, these planes form a frustrum (pyramid with the top clipped off).
        // This frustrum is then mapped (non-linearly) to a box with min (-1,-1, 0) and max (1, 1, 1) to go from View space to Projection space.
        // Projection space is also know as the canonical view volume, the canonical clipping volume, or NDC (normalized device coordinate) space.
        //
        // [ xScale, 0,       0,         0 ]
        // [ 0,      yScale,  0,         0 ]
        // [ 0,      0,       f/(n-f),  -1 ]
        // [ 0,      0,       n*f/(n-f), 0 ]
        //
        // Where:
        //   yScale = cot(fovY/2)
        //   xScale = yScale/aspectRatio
        //
        // Ref: http://msdn.microsoft.com/en-us/library/bb205351(v=vs.85).aspx
        //      http://www.songho.ca/opengl/gl_projectionmatrix.html
        //      (uses openGL's matrix notation so conversion is necessary, but it explains the concept)
        //
        // Note: The cannonical view volume differs between directX and openGL (ogl uses z -1 to 1), we use the directX way.
        //       We are using a Y-based FOV.
        //       This is a right handed perspective projection matrix.

        DebugAssert(fieldOfView > 0.0f && fieldOfView < Trig::Pi,
            "Invalid fov when creating a perspective projection. fov: (%f)", fieldOfView);

        DebugAssert(nearDistance >= 0.0f && farDistance > nearDistance,
            "Invalid near/far distance when creating a perspective projection. near: (%f), far: (%f)", nearDistance, farDistance);

        const float yScale = 1.0f / Tan(fieldOfView * 0.5f);
        const float xScale = yScale / aspectRatio;

        const float invNFDelta = 1.0f / (nearDistance - farDistance);

        out.M11 = xScale;
        out.M12 = 0.0f;
        out.M13 = 0.0f;
        out.M14 = 0.0f;

        out.M21 = 0.0f;
        out.M22 = yScale;
        out.M23 = 0.0f;
        out.M24 = 0.0f;

        out.M31 = 0.0f;
        out.M32 = 0.0f;
        out.M33 = farDistance * invNFDelta;
        out.M34 = -1.0f;

        out.M41 = 0.0f;
        out.M42 = 0.0f;
        out.M43 = nearDistance * farDistance * invNFDelta;
        out.M44 = 0.0f;
    }

    inline Matrix4x4 Matrix4x4::CreateFromQuaternion(const Quaternion & q)
    {
        Matrix4x4 out;
        CreateFromQuaternion(q, out);
        return out;
    }

    inline void Matrix4x4::CreateFromQuaternion(const Quaternion & q, Matrix4x4 & out)
    {
        // Creates a rotation matrix from a quaternion using the following conversion:
        //
        // [ 1 - 2yy - 2zz, 2xy + 2wz,     2xz - 2wy,     0 ]
        // [ 2xy - 2wz,     1 - 2xx - 2zz, 2yz + 2wx,     0 ]
        // [ 2xz + 2wy,     2yz - 2wx,     1 - 2xx - 2yy, 0 ]
        // [ 0,             0,             0,             1 ]
        //
        // Ref: http://www.cs.ucr.edu/~vbz/resources/quatut.pdf

        DebugAssert(IsNormalized(q), "Quaternion must be normalized to create a matrix.");

        const float s = 2.0f;

        const float x = s * q.X;
        const float y = s * q.Y;
        const float z = s * q.Z;

        const float xx = x * q.X;
        const float yy = y * q.Y;
        const float zz = z * q.Z;

        const float wx = x * q.W;
        const float wy = y * q.W;
        const float wz = z * q.W;

        const float xy = x * q.Y;
        const float xz = x * q.Z;
        const float yz = y * q.Z;

        out.M11 = 1.0f - yy - zz;
        out.M12 = xy + wz;
        out.M13 = xz - wy;
        out.M14 = 0.0f;

        out.M21 = xy - wz;
        out.M22 = 1.0f - xx - zz;
        out.M23 = yz + wx;
        out.M24 = 0.0f;

        out.M31 = xz + wy;
        out.M32 = yz - wx;
        out.M33 = 1.0f - xx - yy;
        out.M34 = 0.0f;

        out.M41 = 0.0f;
        out.M42 = 0.0f;
        out.M43 = 0.0f;
        out.M44 = 1.0f;
    }

    inline Matrix4x4 Matrix4x4::CreateFromAxisAngle(const Vector3 & axis, float radians)
    {
        Matrix4x4 out;
        CreateFromAxisAngle(axis, radians, out);
        return out;
    }

    inline void Matrix4x4::CreateFromAxisAngle(const Vector3 & axis, float radians, Matrix4x4 & out)
    {
        // This will create a matrix that roates about the given axis.
        // Positive rotation is counter-clockwise (right handed), when viewed along the axis looking towards the origin.
        //
        // [ txx + c,  txy + sz, txz - sy, 0 ]
        // [ txy - sz, tyy + c,  tyz + sx, 0 ]
        // [ txz + sy, tyz - sx, tzz + c,  0 ]
        // [ 0,        0,        0,        1 ]
        //
        // Where c = cos(theta), s = sin(theta), t = 1 - cos(theta)
        //
        // Ref: http://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToMatrix/

        DebugAssert(IsNormalized(axis), "Invalid param: axis vector needs to be normalized.");

        float s, c;
        SinCos(radians, &s, &c);

        const float t = 1.0f - c;

        const float xy = axis.X * axis.Y;
        const float xz = axis.X * axis.Z;
        const float yz = axis.Y * axis.Z;

        out.M11 = t * axis.X * axis.X + c;
        out.M12 = t * xy + s * axis.Z;
        out.M13 = t * xz - s * axis.Y;
        out.M14 = 0.0f;

        out.M21 = t * xy - s * axis.Z;
        out.M22 = t * axis.Y * axis.Y + c;
        out.M23 = t * yz + s * axis.X;
        out.M24 = 0.0f;

        out.M31 = t * xz + s * axis.Y;
        out.M32 = t * yz - s * axis.X;
        out.M33 = t * axis.Z * axis.Z + c;
        out.M34 = 0.0f;

        out.M41 = 0.0f;
        out.M42 = 0.0f;
        out.M43 = 0.0f;
        out.M44 = 1.0f;
    }

    inline Matrix4x4 Matrix4x4::CreateRotationX(float radians)
    {
        Matrix4x4 out;
        CreateRotationX(radians, out);
        return out;
    }

    inline void Matrix4x4::CreateRotationX(float radians, Matrix4x4 & out)
    {
        // This will create a matrix that rotates about the X axis (also known as Pitch, or Attitude).
        // Positive rotation is counter-clockwise (right handed), when viewed along the positive X axis looking toward the origin.

        float sinTheta, cosTheta;
        SinCos(radians, &sinTheta, &cosTheta);

        out.Copy(1.0f,  0.0f,     0.0f,     0.0f,
                 0.0f,  cosTheta, sinTheta, 0.0f,
                 0.0f, -sinTheta, cosTheta, 0.0f,
                 0.0f,  0.0f,     0.0f,     1.0f);
    }

    inline Matrix4x4 Matrix4x4::CreateRotationY(float radians)
    {
        Matrix4x4 out;
        CreateRotationY(radians, out);
        return out;
    }

    inline void Matrix4x4::CreateRotationY(float radians, Matrix4x4 & out)
    {
        // This will create a matrix that rotates about the Y axis (also known as Yaw, or Heading).
        // Positive rotation is counter-clockwise (right handed), when viewed along the positive Y axis looking toward the origin.

        float sinTheta, cosTheta;
        SinCos(radians, &sinTheta, &cosTheta);

        out.Copy(cosTheta, 0.0f, -sinTheta, 0.0f,
                 0.0f,     1.0f,  0.0f,     0.0f,
                 sinTheta, 0.0f,  cosTheta, 0.0f,
                 0.0f,     0.0f,  0.0f,     1.0f);
    }

    inline Matrix4x4 Matrix4x4::CreateRotationZ(float radians)
    {
        Matrix4x4 out;
        CreateRotationZ(radians, out);
        return out;
    }

    inline void Matrix4x4::CreateRotationZ(float radians, Matrix4x4 & out)
    {
        // This will create a matrix that rotates about the Z axis (also known as Roll, or Bank).
        // Positive rotation is counter-clockwise (right handed), when viewed along the positive Z axis looking toward the origin.

        float sinTheta, cosTheta;
        SinCos(radians, &sinTheta, &cosTheta);

        out.Copy( cosTheta, sinTheta, 0.0f, 0.0f,
                 -sinTheta, cosTheta, 0.0f, 0.0f,
                  0.0f,     0.0f,     1.0f, 0.0f,
                  0.0f,     0.0f,     0.0f, 1.0f);
    }

    inline Matrix4x4 Matrix4x4::CreateFromYawPitchRoll(float yaw, float pitch, float roll)
    {
        Matrix4x4 out;
        CreateFromYawPitchRoll(yaw, pitch, roll, out);
        return out;
    }

    inline void Matrix4x4::CreateFromYawPitchRoll(float yaw, float pitch, float roll, Matrix4x4 & out)
    { 
        // This will create a YXZ rotation matrix.
        // Yaw is applied first, then rotated by pitch, then rotated by roll.
        // Equivalent to CreateRotationY(yaw) * CreateRotationX(pitch) * CreateRotaitonZ(roll)
        // Yaw, pitch, and roll are expected to be angles in radians.
        //
        // [ cY * cZ - sY * sX * sZ, cY * sZ + sY * sX * cZ, -sY * cX, 0 ]
        // [ cX * -sZ,               cX * cZ,                 sX,    , 0 ]
        // [ sY * cZ + cY * sX * sZ, sY * sZ - cY * sX * cZ,  cY * cX, 0 ]
        // [ 0                       0,                       0,       1 ]
        //
        // Note: Watch out for gimbal lock when pitch is +/- 90 degrees.
        //       http://www.altdevblogaday.com/2013/03/15/what-is-gimbal-lock-and-why-do-we-still-have-to-worry-about-it/

        float sinY, cosY;
        SinCos(yaw, &sinY, &cosY);

        float sinX, cosX;
        SinCos(pitch, &sinX, &cosX);

        float sinZ, cosZ;
        SinCos(roll, &sinZ, &cosZ);

        out.M11 = cosY * cosZ - sinY * sinX * sinZ;
        out.M12 = cosY * sinZ + sinY * sinX * cosZ;
        out.M13 = -sinY * cosX;
        out.M14 = 0.0f;

        out.M21 = cosX * -sinZ;
        out.M22 = cosX * cosZ;
        out.M23 = sinX;
        out.M24 = 0.0f;

        out.M31 = sinY * cosZ + cosY * sinX * sinZ;
        out.M32 = sinY * sinZ - cosY * sinX * cosZ;
        out.M33 = cosY * cosX;
        out.M34 = 0.0f;

        out.M41 = 0.0f;
        out.M42 = 0.0f;
        out.M43 = 0.0f;
        out.M44 = 1.0f;
    }

    inline Matrix4x4 Matrix4x4::CreateOrientation(const Vector3 & forward, const Vector3 & up)
    {
        Matrix4x4 out;
        CreateWorld(Vector3::Zero, forward, up, out);
        return out;
    }

    inline void Matrix4x4::CreateOrientation(const Vector3 & forward, const Vector3 & up, Matrix4x4 & out)
    {
        CreateWorld(Vector3::Zero, forward, up, out);
    }

    inline Matrix4x4 Matrix4x4::CreateScale(const Vector3 & scale)
    {
        Matrix4x4 out;
        CreateScale(scale.X, scale.Y, scale.Z, out);
        return out;
    }

    inline void Matrix4x4::CreateScale(const Vector3 & scale, Matrix4x4 & out)
    {
        CreateScale(scale.X, scale.Y, scale.Z, out);
    }

    inline Matrix4x4 Matrix4x4::CreateScale(float scale)
    {
        Matrix4x4 out;
        CreateScale(scale, scale, scale, out);
        return out;
    }

    inline void Matrix4x4::CreateScale(float scale, Matrix4x4 & out)
    {
        CreateScale(scale, scale, scale, out);
    }

    inline Matrix4x4 Matrix4x4::CreateScale(float xScale, float yScale, float zScale)
    {
        Matrix4x4 out;
        CreateScale(xScale, yScale, zScale, out);
        return out;
    }

    inline void Matrix4x4::CreateScale(float xScale, float yScale, float zScale, Matrix4x4 & out)
    {
        out.Copy(xScale, 0.0f,   0.0f,   0.0f,
                 0.0f,   yScale, 0.0f,   0.0f,
                 0.0f,   0.0f,   zScale, 0.0f,
                 0.0f,   0.0f,   0.0f,   1.0f);
    }

    inline Matrix4x4 Matrix4x4::CreateTranslation(const Vector3 & position)
    {
        Matrix4x4 out;
        CreateTranslation(position.X, position.Y, position.Z, out);
        return out;
    }

    inline void Matrix4x4::CreateTranslation(const Vector3 & position, Matrix4x4 & out)
    {
        CreateTranslation(position.X, position.Y, position.Z, out);
    }

    inline Matrix4x4 Matrix4x4::CreateTranslation(float xPosition, float yPosition, float zPosition)
    {
        Matrix4x4 out;
        CreateTranslation(xPosition, yPosition, zPosition, out);
        return out;
    }

    inline void Matrix4x4::CreateTranslation(float xPosition, float yPosition, float zPosition, Matrix4x4 & out)
    {
        out.Copy(1.0f,      0.0f,      0.0f,      0.0f,
                 0.0f,      1.0f,      0.0f,      0.0f,
                 0.0f,      0.0f,      1.0f,      0.0f,
                 xPosition, yPosition, zPosition, 1.0f);
    }

    inline Matrix4x4 Matrix4x4::CreateWorld(const Vector3 & position, const Vector3 & forward, const Vector3 & up)
    {
        Matrix4x4 out;
        CreateWorld(position, forward, up, out);
        return out;
    }

    inline void Matrix4x4::CreateWorld(const Vector3 & position, const Vector3 & forward, const Vector3 & up, Matrix4x4 & out)
    {
        // The World matrix transforms from Object (also called Local) space to World space.
        // We do this by building the basis vectors starting with forward and up.
        // In case that up and forward are not orthogonal, we preserve the direction of the forward vector.
        //
        // [ xAxis.X, xAxis.Y, xAxis.Z,  0 ]
        // [ yAxis.X, yAxis.Y, yAxis.Z,  0 ]
        // [ zAxis.X, zAxix.Y, zAxis.Z,  0 ]
        // [ pos.X,   pos.Y,   pos.Z,    1 ]
        //
        // Where x, y, zAxis are the basis vectors for the object space, and pos is the translation of the object.

        Vector3 xAxis;
        Vector3 yAxis;
        Vector3 zAxis;

        DebugAssert(false == NearlyZero(forward), "Cannot create a world matrix with a zero forward vector.");
        DebugAssert(false == NearlyZero(up), "Cannot create a world matrix with a zero up vector.");

        Math::Normalize(forward, zAxis);
        zAxis.Negate(); // Right handed (forward is -z)

        Math::Cross(up, zAxis, xAxis);
        xAxis.Normalize();

        Math::Cross(zAxis, xAxis, yAxis);
        yAxis.Normalize();

        out.Copy(xAxis.X,    xAxis.Y,    xAxis.Z,    0.0f,
                 yAxis.X,    yAxis.Y,    yAxis.Z,    0.0f,
                 zAxis.X,    zAxis.Y,    zAxis.Z,    0.0f,
                 position.X, position.Y, position.Z, 1.0f);
    }

    inline Matrix4x4 Matrix4x4::CreateSRT(const Vector3 & translation, const Quaternion & rotation, const Vector3 & scale)
    {
        Matrix4x4 out;
        CreateSRT(translation, rotation, scale, out);
        return out;
    }

    inline void Matrix4x4::CreateSRT(const Vector3 & translation, const Quaternion & rotation, const Vector3 & scale, Matrix4x4 & out)
    {
        // Creates a matrix equivalent to CreateScale(scale) * CreateRotation(rotation) * CreateTranslation(translation)

        // Scale
        CreateScale(scale, out);

        // Rotation
        Math::Transform(out, rotation, out);

        // Translation
        out.M41 = translation.X;
        out.M42 = translation.Y;
        out.M43 = translation.Z;
    }

    inline Matrix4x4::Matrix4x4(const Vector4 & row1,
                                const Vector4 & row2,
                                const Vector4 & row3,
                                const Vector4 & row4)
        : M11(row1.X), M12(row1.Y), M13(row1.Z), M14(row1.W),
          M21(row2.X), M22(row2.Y), M23(row2.Z), M24(row2.W),
          M31(row3.X), M32(row3.Y), M33(row3.Z), M34(row3.W),
          M41(row4.X), M42(row4.Y), M43(row4.Z), M44(row4.W)
    { }

    inline Matrix4x4::Matrix4x4(float m11, float m12, float m13, float m14,
                                float m21, float m22, float m23, float m24,
                                float m31, float m32, float m33, float m34,
                                float m41, float m42, float m43, float m44)
        : M11(m11), M12(m12), M13(m13), M14(m14),
          M21(m21), M22(m22), M23(m23), M24(m24),
          M31(m31), M32(m32), M33(m33), M34(m34),
          M41(m41), M42(m42), M43(m43), M44(m44)
    { }

    inline Matrix4x4::Matrix4x4(const Matrix4x4 & src)
    {
        Copy(src);
    }

    inline Matrix4x4 & Matrix4x4::operator=(const Matrix4x4 & rhs)
    {
        Copy(rhs);
        return *this;
    }

    inline float & Matrix4x4::operator[](unsigned int idx)
    {
        DebugAssert(idx < 16, "Invalid index (%u) into a matrix 4x4!", idx);
        return ToArray()[idx];
    }

    inline const float & Matrix4x4::operator[](unsigned int idx) const
    {
        DebugAssert(idx < 16, "Invalid index (%u) into a matrix 4x4!", idx);
        return ToArray()[idx];
    }

    inline Matrix4x4 & Matrix4x4::operator+=(const Matrix4x4 & rhs)
    {
        Math::Add(*this, rhs, *this);
        return *this;
    }

    inline Matrix4x4 & Matrix4x4::operator+=(float rhs)
    {
        Math::Add(*this, rhs, *this);
        return *this;
    }

    inline Matrix4x4 & Matrix4x4::operator-=(const Matrix4x4 & rhs)
    {
        Math::Subtract(*this, rhs, *this);
        return *this;
    }

    inline Matrix4x4 & Matrix4x4::operator-=(float rhs)
    {
        Math::Subtract(*this, rhs, *this);
        return *this;
    }

    inline Matrix4x4 & Matrix4x4::operator*=(const Matrix4x4 & rhs)
    {
        Math::Multiply(*this, rhs, *this);
        return *this;
    }

    inline Matrix4x4 & Matrix4x4::operator*=(float rhs)
    {
        Math::Multiply(*this, rhs, *this);
        return *this;
    }

    inline void Matrix4x4::Transform(const Quaternion & q)
    {
        Math::Transform(*this, q, *this);
    }

    inline float Matrix4x4::Determinant() const
    {
        return Math::Determinant(*this);
    }

    inline Vector3 Matrix4x4::EulerAngles() const
    {
        return Math::EulerAngles(*this);
    }

    inline void Matrix4x4::Inverse()
    {
        Math::Inverse(*this, *this);
    }

    inline void Matrix4x4::Negate()
    {
        Math::Negate(*this, *this);
    }

    inline void Matrix4x4::Orthonormalize()
    {
        return Math::Orthonormalize(*this, *this);
    }

    inline void Matrix4x4::Transpose()
    {
        Math::Transpose(*this, *this);
    }

    inline bool Matrix4x4::Decompose(Vector3 & outScale, Quaternion & outOrientation, Vector3 & outTranslation) const
    {
        return Math::Decompose(*this, outScale, outOrientation, outTranslation);
    }

    inline Vector3 Matrix4x4::GetForward() const
    {
        return Vector3(-this->M31, -this->M32, -this->M33);
    }

    inline Vector3 Matrix4x4::GetBackward() const
    {
        return Vector3(this->M31, this->M32, this->M33);
    }

    inline Vector3 Matrix4x4::GetLeft() const
    {
        return Vector3(-this->M11, -this->M12, -this->M13);
    }

    inline Vector3 Matrix4x4::GetRight() const
    {
        return Vector3(this->M11, this->M12, this->M13);
    }

    inline Vector3 Matrix4x4::GetUp() const
    {
        return Vector3(this->M21, this->M22, this->M23);
    }

    inline Vector3 Matrix4x4::GetDown() const
    {
        return Vector3(-this->M21, -this->M22, -this->M23);
    }

    inline Vector3 Matrix4x4::GetTranslation() const
    {
        return Vector3(this->M41, this->M42, this->M43);
    }

    inline void Matrix4x4::Copy(const Matrix4x4 & src)
    {
        memcpy(this, &src, sizeof(Matrix4x4));
    }

    inline void Matrix4x4::Copy(const float *pSrc)
    {
        memcpy(ToArray(), pSrc, sizeof(Matrix4x4));
    }

    inline void Matrix4x4::Copy(float m11, float m12, float m13, float m14,
                                float m21, float m22, float m23, float m24,
                                float m31, float m32, float m33, float m34,
                                float m41, float m42, float m43, float m44)
    {
        this->M11 = m11;
        this->M12 = m12;
        this->M13 = m13;
        this->M14 = m14;
        this->M21 = m21;
        this->M22 = m22;
        this->M23 = m23;
        this->M24 = m24;
        this->M31 = m31;
        this->M32 = m32;
        this->M33 = m33;
        this->M34 = m34;
        this->M41 = m41;
        this->M42 = m42;
        this->M43 = m43;
        this->M44 = m44;
    }

    inline void Matrix4x4::Copy(float f)
    {
        this->M11 = f;
        this->M12 = f;
        this->M13 = f;
        this->M14 = f;
        this->M21 = f;
        this->M22 = f;
        this->M23 = f;
        this->M24 = f;
        this->M31 = f;
        this->M32 = f;
        this->M33 = f;
        this->M34 = f;
        this->M41 = f;
        this->M42 = f;
        this->M43 = f;
        this->M44 = f;
    }

    inline Vector4 & Matrix4x4::Row(unsigned int idx)
    {
        DebugAssert(idx < 4, "Invalid row index (%u) into a matrix 4x4!", idx);
        return *reinterpret_cast<Vector4 *>(this->ToArray() + (idx * 4));
    }

    inline const Vector4 & Matrix4x4::Row(unsigned int idx) const
    {
        DebugAssert(idx < 4, "Invalid row index (%u) into a matrix 4x4!", idx);
        return *reinterpret_cast<const Vector4 *>(this->ToArray() + (idx * 4));
    }

    inline float* Matrix4x4::ToArray()
    {
        return &(this->M11);
    }

    inline const float* Matrix4x4::ToArray() const
    {
        return &(this->M11);
    }

    inline bool operator==(const Matrix4x4 & lhs, const Matrix4x4 & rhs)
    {
        return ExactlyEqual(lhs, rhs);
    }

    inline bool operator!=(const Matrix4x4 & lhs, const Matrix4x4 & rhs)
    {
        return (false == ExactlyEqual(lhs, rhs));
    }

    inline Matrix4x4 operator+(const Matrix4x4 & lhs, const Matrix4x4 & rhs)
    {
        Matrix4x4 out;
        Add(lhs, rhs, out);
        return out;
    }

    inline Matrix4x4 operator+(const Matrix4x4 & lhs, float rhs)
    {
        Matrix4x4 out;
        Add(lhs, rhs, out);
        return out;
    }

    inline Matrix4x4 operator-(const Matrix4x4 & lhs, const Matrix4x4 & rhs)
    {
        Matrix4x4 out;
        Subtract(lhs, rhs, out);
        return out;
    }

    inline Matrix4x4 operator-(const Matrix4x4 & lhs, float rhs)
    {
        Matrix4x4 out;
        Subtract(lhs, rhs, out);
        return out;
    }

    inline Matrix4x4 operator-(const Matrix4x4 & m)
    {
        Matrix4x4 out;
        Negate(m, out);
        return out;
    }

    inline Matrix4x4 operator*(const Matrix4x4 & lhs, const Matrix4x4 & rhs)
    {
        Matrix4x4 out;
        Multiply(lhs, rhs, out);
        return out;
    }

    inline Matrix4x4 operator*(const Matrix4x4 & lhs, float rhs)
    {
        Matrix4x4 out;
        Multiply(lhs, rhs, out);
        return out;
    }

    inline bool ExactlyEqual(const Matrix4x4 & lhs, const Matrix4x4 & rhs)
    {
        return (ExactlyEqual(lhs.M11, rhs.M11) &&
                ExactlyEqual(lhs.M12, rhs.M12) &&
                ExactlyEqual(lhs.M13, rhs.M13) &&
                ExactlyEqual(lhs.M14, rhs.M14) &&
                ExactlyEqual(lhs.M21, rhs.M21) &&
                ExactlyEqual(lhs.M22, rhs.M22) &&
                ExactlyEqual(lhs.M23, rhs.M23) &&
                ExactlyEqual(lhs.M24, rhs.M24) &&
                ExactlyEqual(lhs.M31, rhs.M31) &&
                ExactlyEqual(lhs.M32, rhs.M32) &&
                ExactlyEqual(lhs.M33, rhs.M33) &&
                ExactlyEqual(lhs.M34, rhs.M34) &&
                ExactlyEqual(lhs.M41, rhs.M41) &&
                ExactlyEqual(lhs.M42, rhs.M42) &&
                ExactlyEqual(lhs.M43, rhs.M43) &&
                ExactlyEqual(lhs.M44, rhs.M44));
    }

    inline bool ExactlyZero(const Matrix4x4 & m)
    {
        return ExactlyEqual(m, Matrix4x4::Zero);
    }

    inline bool NearlyEqual(const Matrix4x4 & lhs, const Matrix4x4 & rhs)
    {
        return NearlyZero(lhs - rhs);
    }

    inline bool NearlyZero(const Matrix4x4 & m)
    {
        return (NearlyZero(m.M11) &&
                NearlyZero(m.M12) &&
                NearlyZero(m.M13) &&
                NearlyZero(m.M14) &&
                NearlyZero(m.M21) &&
                NearlyZero(m.M22) &&
                NearlyZero(m.M23) &&
                NearlyZero(m.M24) &&
                NearlyZero(m.M31) &&
                NearlyZero(m.M32) &&
                NearlyZero(m.M33) &&
                NearlyZero(m.M34) &&
                NearlyZero(m.M41) &&
                NearlyZero(m.M42) &&
                NearlyZero(m.M43) &&
                NearlyZero(m.M44));
    }

    inline Matrix4x4 Add(const Matrix4x4 & lhs, const Matrix4x4 & rhs)
    {
        Matrix4x4 out;
        Add(lhs, rhs, out);
        return out;
    }

    inline Matrix4x4 Add(const Matrix4x4 & lhs, float rhs)
    {
        Matrix4x4 out;
        Add(lhs, rhs, out);
        return out;
    }

    inline void Add(const Matrix4x4 & lhs, const Matrix4x4 & rhs, Matrix4x4 & out)
    {
        out.M11 = lhs.M11 + rhs.M11;
        out.M12 = lhs.M12 + rhs.M12;
        out.M13 = lhs.M13 + rhs.M13;
        out.M14 = lhs.M14 + rhs.M14;
        out.M21 = lhs.M21 + rhs.M21;
        out.M22 = lhs.M22 + rhs.M22;
        out.M23 = lhs.M23 + rhs.M23;
        out.M24 = lhs.M24 + rhs.M24;
        out.M31 = lhs.M31 + rhs.M31;
        out.M32 = lhs.M32 + rhs.M32;
        out.M33 = lhs.M33 + rhs.M33;
        out.M34 = lhs.M34 + rhs.M34;
        out.M41 = lhs.M41 + rhs.M41;
        out.M42 = lhs.M42 + rhs.M42;
        out.M43 = lhs.M43 + rhs.M43;
        out.M44 = lhs.M44 + rhs.M44;
    }

    inline void Add(const Matrix4x4 & lhs, float rhs, Matrix4x4 & out)
    {
        out.M11 = lhs.M11 + rhs;
        out.M12 = lhs.M12 + rhs;
        out.M13 = lhs.M13 + rhs;
        out.M14 = lhs.M14 + rhs;
        out.M21 = lhs.M21 + rhs;
        out.M22 = lhs.M22 + rhs;
        out.M23 = lhs.M23 + rhs;
        out.M24 = lhs.M24 + rhs;
        out.M31 = lhs.M31 + rhs;
        out.M32 = lhs.M32 + rhs;
        out.M33 = lhs.M33 + rhs;
        out.M34 = lhs.M34 + rhs;
        out.M41 = lhs.M41 + rhs;
        out.M42 = lhs.M42 + rhs;
        out.M43 = lhs.M43 + rhs;
        out.M44 = lhs.M44 + rhs;
    }

    inline Matrix4x4 Subtract(const Matrix4x4 & lhs, const Matrix4x4 & rhs)
    {
        Matrix4x4 out;
        Subtract(lhs, rhs, out);
        return out;
    }

    inline Matrix4x4 Subtract(const Matrix4x4 & lhs, float rhs)
    {
        Matrix4x4 out;
        Subtract(lhs, rhs, out);
        return out;
    }

    inline void Subtract(const Matrix4x4 & lhs, const Matrix4x4 & rhs, Matrix4x4 & out)
    {
        out.M11 = lhs.M11 - rhs.M11;
        out.M12 = lhs.M12 - rhs.M12;
        out.M13 = lhs.M13 - rhs.M13;
        out.M14 = lhs.M14 - rhs.M14;
        out.M21 = lhs.M21 - rhs.M21;
        out.M22 = lhs.M22 - rhs.M22;
        out.M23 = lhs.M23 - rhs.M23;
        out.M24 = lhs.M24 - rhs.M24;
        out.M31 = lhs.M31 - rhs.M31;
        out.M32 = lhs.M32 - rhs.M32;
        out.M33 = lhs.M33 - rhs.M33;
        out.M34 = lhs.M34 - rhs.M34;
        out.M41 = lhs.M41 - rhs.M41;
        out.M42 = lhs.M42 - rhs.M42;
        out.M43 = lhs.M43 - rhs.M43;
        out.M44 = lhs.M44 - rhs.M44;
    }

    inline void Subtract(const Matrix4x4 & lhs, float rhs, Matrix4x4 & out)
    {
        out.M11 = lhs.M11 - rhs;
        out.M12 = lhs.M12 - rhs;
        out.M13 = lhs.M13 - rhs;
        out.M14 = lhs.M14 - rhs;
        out.M21 = lhs.M21 - rhs;
        out.M22 = lhs.M22 - rhs;
        out.M23 = lhs.M23 - rhs;
        out.M24 = lhs.M24 - rhs;
        out.M31 = lhs.M31 - rhs;
        out.M32 = lhs.M32 - rhs;
        out.M33 = lhs.M33 - rhs;
        out.M34 = lhs.M34 - rhs;
        out.M41 = lhs.M41 - rhs;
        out.M42 = lhs.M42 - rhs;
        out.M43 = lhs.M43 - rhs;
        out.M44 = lhs.M44 - rhs;
    }

    inline Matrix4x4 Multiply(const Matrix4x4 & lhs, const Matrix4x4 & rhs)
    {
        Matrix4x4 out;
        Multiply(lhs, rhs, out);
        return out;
    }

    inline Matrix4x4 Multiply(const Matrix4x4 & lhs, float rhs)
    {
        Matrix4x4 out;
        Multiply(lhs, rhs, out);
        return out;
    }

    inline void Multiply(const Matrix4x4 & lhs, const Matrix4x4 & rhs, Matrix4x4 & out)
    {
        // Pre multiplication: lhs * rhs = lhs transformed by rhs.

        const float m11 = lhs.M11 * rhs.M11 + lhs.M12 * rhs.M21 + lhs.M13 * rhs.M31 + lhs.M14 * rhs.M41;
        const float m12 = lhs.M11 * rhs.M12 + lhs.M12 * rhs.M22 + lhs.M13 * rhs.M32 + lhs.M14 * rhs.M42;
        const float m13 = lhs.M11 * rhs.M13 + lhs.M12 * rhs.M23 + lhs.M13 * rhs.M33 + lhs.M14 * rhs.M43;
        const float m14 = lhs.M11 * rhs.M14 + lhs.M12 * rhs.M24 + lhs.M13 * rhs.M34 + lhs.M14 * rhs.M44;

        const float m21 = lhs.M21 * rhs.M11 + lhs.M22 * rhs.M21 + lhs.M23 * rhs.M31 + lhs.M24 * rhs.M41;
        const float m22 = lhs.M21 * rhs.M12 + lhs.M22 * rhs.M22 + lhs.M23 * rhs.M32 + lhs.M24 * rhs.M42;
        const float m23 = lhs.M21 * rhs.M13 + lhs.M22 * rhs.M23 + lhs.M23 * rhs.M33 + lhs.M24 * rhs.M43;
        const float m24 = lhs.M21 * rhs.M14 + lhs.M22 * rhs.M24 + lhs.M23 * rhs.M34 + lhs.M24 * rhs.M44;

        const float m31 = lhs.M31 * rhs.M11 + lhs.M32 * rhs.M21 + lhs.M33 * rhs.M31 + lhs.M34 * rhs.M41;
        const float m32 = lhs.M31 * rhs.M12 + lhs.M32 * rhs.M22 + lhs.M33 * rhs.M32 + lhs.M34 * rhs.M42;
        const float m33 = lhs.M31 * rhs.M13 + lhs.M32 * rhs.M23 + lhs.M33 * rhs.M33 + lhs.M34 * rhs.M43;
        const float m34 = lhs.M31 * rhs.M14 + lhs.M32 * rhs.M24 + lhs.M33 * rhs.M34 + lhs.M34 * rhs.M44;

        const float m41 = lhs.M41 * rhs.M11 + lhs.M42 * rhs.M21 + lhs.M43 * rhs.M31 + lhs.M44 * rhs.M41;
        const float m42 = lhs.M41 * rhs.M12 + lhs.M42 * rhs.M22 + lhs.M43 * rhs.M32 + lhs.M44 * rhs.M42;
        const float m43 = lhs.M41 * rhs.M13 + lhs.M42 * rhs.M23 + lhs.M43 * rhs.M33 + lhs.M44 * rhs.M43;
        const float m44 = lhs.M41 * rhs.M14 + lhs.M42 * rhs.M24 + lhs.M43 * rhs.M34 + lhs.M44 * rhs.M44;

        out.Copy(m11, m12, m13, m14,
                 m21, m22, m23, m24,
                 m31, m32, m33, m34,
                 m41, m42, m43, m44);
    }

    inline void Multiply(const Matrix4x4 & lhs, float rhs, Matrix4x4 & out)
    {
        out.M11 = lhs.M11 * rhs;
        out.M12 = lhs.M12 * rhs;
        out.M13 = lhs.M13 * rhs;
        out.M14 = lhs.M14 * rhs;
        out.M21 = lhs.M21 * rhs;
        out.M22 = lhs.M22 * rhs;
        out.M23 = lhs.M23 * rhs;
        out.M24 = lhs.M24 * rhs;
        out.M31 = lhs.M31 * rhs;
        out.M32 = lhs.M32 * rhs;
        out.M33 = lhs.M33 * rhs;
        out.M34 = lhs.M34 * rhs;
        out.M41 = lhs.M41 * rhs;
        out.M42 = lhs.M42 * rhs;
        out.M43 = lhs.M43 * rhs;
        out.M44 = lhs.M44 * rhs;
    }

    inline Matrix4x4 Transform(const Matrix4x4 & m, const Quaternion & q)
    {
        Matrix4x4 out;
        Transform(m, q, out);
        return out;
    }

    inline void Transform(const Matrix4x4 & m, const Quaternion & q, Matrix4x4 & out)
    {
        // Rotates m by q
        Matrix4x4 rhs;
        Matrix4x4::CreateFromQuaternion(q, rhs);
        Multiply(m, rhs, out);
    }

    inline float Determinant(const Matrix4x4 & m)
    {
        // 4x4 Matrix Laplace expansion.
        // Reduced run time complexity of the mathmatical formula by reusing stored results.
        //
        // Ref: http://www.mathsisfun.com/algebra/matrix-determinant.html
        //      http://www.geometrictools.com/Documentation/LaplaceExpansionTheorem.pdf

        // 2x2 Determinants
        const float a = (m.M33 * m.M44) - (m.M34 * m.M43);
        const float b = (m.M32 * m.M44) - (m.M34 * m.M42);
        const float c = (m.M32 * m.M43) - (m.M33 * m.M42);
        const float d = (m.M31 * m.M44) - (m.M34 * m.M41);
        const float e = (m.M31 * m.M43) - (m.M33 * m.M41);
        const float f = (m.M31 * m.M42) - (m.M32 * m.M41);

        // 3x3 Determinants
        return (m.M11 * ((m.M22 * a) - (m.M23 * b) + (m.M24 * c)))
             - (m.M12 * ((m.M21 * a) - (m.M23 * d) + (m.M24 * e)))
             + (m.M13 * ((m.M21 * b) - (m.M22 * d) + (m.M24 * f)))
             - (m.M14 * ((m.M21 * c) - (m.M22 * e) + (m.M23 * f)));
    }

    inline Vector3 EulerAngles(const Matrix4x4 & m)
    {
        // Decomposes YawPitchRoll (YXZ) Rotation Matrix into euler angles.
        //
        // [ cY * cZ - sY * sX * sZ, cY * sZ + sY * sX * cZ, -sY * cX, 0 ]
        // [ cX * -sZ,               cX * cZ,                 sX,    , 0 ]
        // [ sY * cZ + cY * sX * sZ, sY * sZ - cY * sX * cZ,  cY * cX, 0 ]
        // [ 0                       0,                       0,       1 ]
        //
        // Ref: http://www.geometrictools.com/Documentation/EulerAngles.pdf
        //      http://www.sosmath.com/trig/Trig5/trig5/trig5.html (for sum-difference trig identities)

        if (NearlyEqual(m.M23, 1.0f))
        {
            // sin(x) = 1.0, cos(x) = 0.0
            // M11 = cos(z + y), M12 = sin(z + y)
            // z + y = atan2(M12, M11), not a unique solution
            return Vector3(Trig::PiOverTwo, ATan2(m.M12, m.M11), 0.0f);
        }
        else if (NearlyEqual(m.M23, -1.0f))
        {
            // sin(x) = -1.0, cos(x) = 0.0
            // M11 = cos(z - y), M12 = sin(z - y)
            // z - y = atan2(M12, M11), not a unique solution
            return Vector3(-Trig::PiOverTwo, -ATan2(m.M12, m.M11), 0.0f);
        }
        else
        {
            // M23 = sin(x), -M13/M33 = tan(y), -M12/M22 = tan(z)
            return Vector3(ASin(m.M23), ATan2(-m.M13, m.M33), ATan2(-m.M21, m.M22));
        }
    }

    inline Matrix4x4 Inverse(const Matrix4x4 & m)
    {
        Matrix4x4 out;
        Inverse(m, out);
        return out;
    }

    inline void Inverse(const Matrix4x4 & m, Matrix4x4 & out)
    {
        // This finds the determinant of a 4x4 Matrix using an alternate form of the Laplace
        // Expansion Therom. Use the minors to build the adjugate matrix and divide by the
        // determinant to get the inverse.
        //
        // Ref: http://www.geometrictools.com/Documentation/LaplaceExpansionTheorem.pdf

        // 2x2 Determinants
        const float s0 = (m.M11 * m.M22) - (m.M12 * m.M21);
        const float s1 = (m.M11 * m.M23) - (m.M13 * m.M21);
        const float s2 = (m.M11 * m.M24) - (m.M14 * m.M21);
        const float s3 = (m.M12 * m.M23) - (m.M13 * m.M22);
        const float s4 = (m.M12 * m.M24) - (m.M14 * m.M22);
        const float s5 = (m.M13 * m.M24) - (m.M14 * m.M23);

        const float c0 = (m.M31 * m.M42) - (m.M32 * m.M41);
        const float c1 = (m.M31 * m.M43) - (m.M33 * m.M41);
        const float c2 = (m.M31 * m.M44) - (m.M34 * m.M41);
        const float c3 = (m.M32 * m.M43) - (m.M33 * m.M42);
        const float c4 = (m.M32 * m.M44) - (m.M34 * m.M42);
        const float c5 = (m.M33 * m.M44) - (m.M34 * m.M43);

        // 4x4 Determinant
        const float det = (s0 * c5) - (s1 * c4) + (s2 * c3) + (s3 * c2) - (s4 *c1) + (s5 * c0);

        if (NearlyZero(det))
        {
            // Not possible to invert
            DebugAssert(false, "Trying to invert a matrix that has no inverse (0 determinant).");
            out.Copy(Matrix4x4::Zero);
            return;
        }

        // Adjugate(m) / Det
        const float invDet = 1.0f / det;

        const float m11 = (+(m.M22 * c5) - (m.M23 * c4) + (m.M24 * c3)) * invDet;
        const float m12 = (-(m.M12 * c5) + (m.M13 * c4) - (m.M14 * c3)) * invDet;
        const float m13 = (+(m.M42 * s5) - (m.M43 * s4) + (m.M44 * s3)) * invDet;
        const float m14 = (-(m.M32 * s5) + (m.M33 * s4) - (m.M34 * s3)) * invDet;

        const float m21 = (-(m.M21 * c5) + (m.M23 * c2) - (m.M24 * c1)) * invDet;
        const float m22 = (+(m.M11 * c5) - (m.M13 * c2) + (m.M14 * c1)) * invDet;
        const float m23 = (-(m.M41 * s5) + (m.M43 * s2) - (m.M44 * s1)) * invDet;
        const float m24 = (+(m.M31 * s5) - (m.M33 * s2) + (m.M34 * s1)) * invDet;

        const float m31 = (+(m.M21 * c4) - (m.M22 * c2) + (m.M24 * c0)) * invDet;
        const float m32 = (-(m.M11 * c4) + (m.M12 * c2) - (m.M14 * c0)) * invDet;
        const float m33 = (+(m.M41 * s4) - (m.M42 * s2) + (m.M44 * s0)) * invDet;
        const float m34 = (-(m.M31 * s4) + (m.M32 * s2) - (m.M34 * s0)) * invDet;

        const float m41 = (-(m.M21 * c3) + (m.M22 * c1) - (m.M23 * c0)) * invDet;
        const float m42 = (+(m.M11 * c3) - (m.M12 * c1) + (m.M13 * c0)) * invDet;
        const float m43 = (-(m.M41 * s3) + (m.M42 * s1) - (m.M43 * s0)) * invDet;
        const float m44 = (+(m.M31 * s3) - (m.M32 * s1) + (m.M33 * s0)) * invDet;

        out.Copy(m11, m12, m13, m14,
                 m21, m22, m23, m24,
                 m31, m32, m33, m34,
                 m41, m42, m43, m44);
    }

    inline Matrix4x4 Negate(const Matrix4x4 & m)
    {
        Matrix4x4 out;
        Negate(m, out);
        return out;
    }

    inline void Negate(const Matrix4x4 & m, Matrix4x4 & out)
    {
        out.M11 = -m.M11;
        out.M12 = -m.M12;
        out.M13 = -m.M13;
        out.M14 = -m.M14;
        out.M21 = -m.M21;
        out.M22 = -m.M22;
        out.M23 = -m.M23;
        out.M24 = -m.M24;
        out.M31 = -m.M31;
        out.M32 = -m.M32;
        out.M33 = -m.M33;
        out.M34 = -m.M34;
        out.M41 = -m.M41;
        out.M42 = -m.M42;
        out.M43 = -m.M43;
        out.M44 = -m.M44;
    }

    inline Matrix4x4 Orthonormalize(const Matrix4x4 & m)
    {
        Matrix4x4 out;
        Orthonormalize(m, out);
        return out;
    }

    inline void Orthonormalize(const Matrix4x4 & m, Matrix4x4 & out)
    {
        // Uses a modified Gram–Schmidt method to orthonormalize the matrix.
        // Treats the input matrix like a 3x3, does not preserve translation if there is any.
        //
        // Note: rows 0, 1, and 2 should be non-zero length otherwise this will fail.
        //
        // Ref: http://fgiesen.wordpress.com/2013/06/02/modified-gram-schmidt-orthogonalization/
        //      http://www.geometrictools.com/Documentation/OrthonormalSets.pdf

        Vector3 basis1(m.M11, m.M12, m.M13);
        Vector3 basis2(m.M21, m.M22, m.M23);
        Vector3 basis3(m.M31, m.M32, m.M33);

        DebugAssert(false == NearlyZero(basis1.Length()), "Trying to orthonormalize a matrix with a zero basis vector.");
        DebugAssert(false == NearlyZero(basis2.Length()), "Trying to orthonormalize a matrix with a zero basis vector.");
        DebugAssert(false == NearlyZero(basis3.Length()), "Trying to orthonormalize a matrix with a zero basis vector.");

        // First basis:
        // Simply normalize it.
        basis1.Normalize();

        // Second basis:
        // Subtract the parts not orthogonal to the new basis1 (basis2 projected onto basis1) then normalize.
        basis2 -= basis1 * Dot(basis2, basis1);
        basis2.Normalize();

        // Third basis:
        // Subtract the parts not orthogonal to the new basis2 (basis3 projected onto basis2) then normalize.
        // Don't do the cross product to compute basis3, it is slightly slower this way but preserves the handedness of the input matrix.
        basis3 -= basis2 * Dot(basis3, basis2);
        basis3.Normalize();

        // Done, now rebuild the orthonormal matrix.
        out.Copy(basis1.X, basis1.Y, basis1.Z, 0.0f,
                 basis2.X, basis2.Y, basis2.Z, 0.0f,
                 basis3.X, basis3.Y, basis3.Z, 0.0f,
                 0.0f,     0.0f,     0.0f,     1.0f);
    }

    inline Matrix4x4 Transpose(const Matrix4x4 & m)
    {
        Matrix4x4 out;
        Transpose(m, out);
        return out;
    }

    inline void Transpose(const Matrix4x4 & m, Matrix4x4 & out)
    {
        out.M11 = m.M11;

        float swap = m.M12;
        out.M12 = m.M21;
        out.M21 = swap;

        swap = m.M13;
        out.M13 = m.M31;
        out.M31 = swap;

        swap = m.M14;
        out.M14 = m.M41;
        out.M41 = swap;

        out.M22 = m.M22;

        swap = m.M32;
        out.M32 = m.M23;
        out.M23 = swap;

        swap = m.M42;
        out.M42 = m.M24;
        out.M24 = swap;

        out.M33 = m.M33;

        swap = m.M43;
        out.M43 = m.M34;
        out.M34 = swap;

        out.M44 = m.M44;
    }

    inline bool Decompose(const Matrix4x4 & m, Vector3 & outScale, Quaternion & outOrientation, Vector3 & outTranslation)
    {
        // This isn't the most robust implementation of matrix decomposition (more roboust methods are prohibitively expensive).
        // It will fail sometimes if m was created by a series of Scale Rotation Translation concatenations (object hierarchies: SRT2 * SRT1 * SRT0).

        outTranslation.Copy(m.M41, m.M42, m.M43);

        float x = m.M11 * m.M11 + m.M12 * m.M12 + m.M13 * m.M13;
        float y = m.M21 * m.M21 + m.M22 * m.M22 + m.M23 * m.M23;
        float z = m.M31 * m.M31 + m.M32 * m.M32 + m.M33 * m.M33;

        if (NearlyZero(x) || NearlyZero(y) || NearlyZero(z))
        {
            outScale.Copy(Vector3::One);
            outOrientation.Copy(Quaternion::Identity);
            return false;
        }
        
        outScale.Copy(Sqrt(x), Sqrt(y), Sqrt(z));

        const float invX = 1.0f / outScale.X;
        const float invY = 1.0f / outScale.Y;
        const float invZ = 1.0f / outScale.Z;

        Matrix4x4 r
        ( 
            m.M11 * invX, m.M12 * invX, m.M13 * invX, 0.0f,
            m.M21 * invY, m.M22 * invY, m.M23 * invY, 0.0f,
            m.M31 * invZ, m.M32 * invZ, m.M33 * invZ, 0.0f,
            0.0f,          0.0f,         0.0f,        1.0f
        );

        Quaternion::CreateFromMatrix(r, outOrientation);

        return true;
    }

} //namespace Math
} //namespace Phx

#endif //_PHX_MATH_MATRIX4X4_INL_
