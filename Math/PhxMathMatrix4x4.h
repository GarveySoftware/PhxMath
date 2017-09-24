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

#ifndef _PHX_MATH_MATRIX4X4_H_
#define _PHX_MATH_MATRIX4X4_H_

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Row Major Matrix                        
// Row Vectors                             
// Pre-multiplication                      
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Right Handed Coordinate System          
//                                         
//     (forward) -z   +y (up)              
// (into screen)   \   |                   
//                  \  |                   
//                   \ |                   
//                    \|                   
//    (left) -x - - - -|- - - - +x (right) 
//                     |\                  
//                     | \                 
//                     |  \                
//                     |   \  (out of screen) 
//             (down) -y   +z (backward)   
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

namespace Phx {
namespace Math {

    class Matrix4x4
    {
    public:
        float M11;
        float M12;
        float M13;
        float M14;
        float M21;
        float M22;
        float M23;
        float M24;
        float M31;
        float M32;
        float M33;
        float M34;
        float M41;
        float M42;
        float M43;
        float M44;

    public:
        static const Matrix4x4 Zero;
        static const Matrix4x4 Identity;

    public:
        static inline Matrix4x4 CreateIdentity();
        static inline void CreateIdentity(Matrix4x4 & out);

        static inline Matrix4x4 CreateView(const Vector3 & position, const Vector3 & target, const Vector3 & up);
        static inline void CreateView(const Vector3 & position, const Vector3 & target, const Vector3 & up, Matrix4x4 & out);

        static inline Matrix4x4 CreateOrthographic(float left, float right, float bottom, float top, float nearDistance, float farDistance);
        static inline void CreateOrthographic(float left, float right, float bottom, float top, float nearDistance, float farDistance, Matrix4x4 & out);
        static inline Matrix4x4 CreateOrthographic(float width, float height, float nearDistance, float farDistance);
        static inline void CreateOrthographic(float width, float height, float nearDistance, float farDistance, Matrix4x4 & out);

        static inline Matrix4x4 CreatePerspective(float fieldOfView, float aspectRatio, float nearDistance, float farDistance);
        static inline void CreatePerspective(float fieldOfView, float aspectRatio, float nearDistance, float farDistance, Matrix4x4 & out);

        static inline Matrix4x4 CreateFromQuaternion(const Quaternion & q);
        static inline void CreateFromQuaternion(const Quaternion & q, Matrix4x4 & out);

        static inline Matrix4x4 CreateFromAxisAngle(const Vector3 & axis, float radians);
        static inline void CreateFromAxisAngle(const Vector3 & axis, float radians, Matrix4x4 & out);

        static inline Matrix4x4 CreateRotationX(float radians);
        static inline void CreateRotationX(float radians, Matrix4x4 & out);

        static inline Matrix4x4 CreateRotationY(float radians);
        static inline void CreateRotationY(float radians, Matrix4x4 & out);

        static inline Matrix4x4 CreateRotationZ(float radians);
        static inline void CreateRotationZ(float radians, Matrix4x4 & out);

        static inline Matrix4x4 CreateFromYawPitchRoll(float yaw, float pitch, float roll);
        static inline void CreateFromYawPitchRoll(float yaw, float pitch, float roll, Matrix4x4 & out);

        static inline Matrix4x4 CreateOrientation(const Vector3 & forward, const Vector3 & up);
        static inline void CreateOrientation(const Vector3 & forward, const Vector3 & up, Matrix4x4 & out);

        static inline Matrix4x4 CreateScale(const Vector3 & scale);
        static inline void CreateScale(const Vector3 & scale, Matrix4x4 & out);
        static inline Matrix4x4 CreateScale(float scale);
        static inline void CreateScale(float scale, Matrix4x4 & out);
        static inline Matrix4x4 CreateScale(float xScale, float yScale, float zScale);
        static inline void CreateScale(float xScale, float yScale, float zScale, Matrix4x4 & out);

        static inline Matrix4x4 CreateTranslation(const Vector3 & position);
        static inline void CreateTranslation(const Vector3 & position, Matrix4x4 & out);
        static inline Matrix4x4 CreateTranslation(float xPosition, float yPosition, float zPosition);
        static inline void CreateTranslation(float xPosition, float yPosition, float zPosition, Matrix4x4 & out);

        static inline Matrix4x4 CreateWorld(const Vector3 & position, const Vector3 & forward, const Vector3 & up);
        static inline void CreateWorld(const Vector3 & position, const Vector3 & forward, const Vector3 & up, Matrix4x4 & out);

        static inline Matrix4x4 CreateSRT(const Vector3 & translation, const Quaternion & rotation, const Vector3 & scale);
        static inline void CreateSRT(const Vector3 & translation, const Quaternion & rotation, const Vector3 & scale, Matrix4x4 & out);

    public:
        inline Matrix4x4()
        { 
            // Do nothing in the default ctor.
            // So we don't have to pay for arrays or matrices initialized as an out parameter.
        }
        
        inline explicit Matrix4x4(const Vector4 & row1,
                                  const Vector4 & row2,
                                  const Vector4 & row3,
                                  const Vector4 & row4);

        inline explicit Matrix4x4(float m11, float m12, float m13, float m14,
                                  float m21, float m22, float m23, float m24,
                                  float m31, float m32, float m33, float m34,
                                  float m41, float m42, float m43, float m44);

        inline Matrix4x4(const Matrix4x4 & src);

        inline ~Matrix4x4() { }

        inline Matrix4x4 & operator=(const Matrix4x4 & rhs);

        inline float & operator[](unsigned int idx);
        inline const float & operator[](unsigned int idx) const;

        inline Matrix4x4 & operator+=(const Matrix4x4 & rhs);
        inline Matrix4x4 & operator+=(float rhs);

        inline Matrix4x4 & operator-=(const Matrix4x4 & rhs);
        inline Matrix4x4 & operator-=(float rhs);

        inline Matrix4x4 & operator*=(const Matrix4x4 & rhs);
        inline Matrix4x4 & operator*=(float rhs);

        inline void Transform(const Quaternion & q);

        inline float Determinant() const;
        inline Vector3 EulerAngles() const;

        inline void Inverse();
        inline void Negate();
        inline void Orthonormalize();
        inline void Transpose();

        inline bool Decompose(Vector3 & outScale, Quaternion & outOrientation, Vector3 & outTranslation) const;

        inline Vector3 GetForward() const;
        inline Vector3 GetBackward() const;
        inline Vector3 GetLeft() const;
        inline Vector3 GetRight() const;
        inline Vector3 GetUp() const;
        inline Vector3 GetDown() const;
        inline Vector3 GetTranslation() const;

        inline void Copy(const Matrix4x4 & src);
        inline void Copy(const float * pSrc);
        inline void Copy(float m11, float m12, float m13, float m14,
                         float m21, float m22, float m23, float m24,
                         float m31, float m32, float m33, float m34,
                         float m41, float m42, float m43, float m44);
        inline void Copy(float f);

        inline Vector4 & Row(unsigned int idx);
        inline const Vector4 & Row(unsigned int idx) const;

        inline float * ToArray();
        inline const float * ToArray() const;
    };

    inline bool operator==(const Matrix4x4 & lhs, const Matrix4x4 & rhs);
    inline bool operator!=(const Matrix4x4 & lhs, const Matrix4x4 & rhs);

    inline Matrix4x4 operator+(const Matrix4x4 & lhs, const Matrix4x4 & rhs);
    inline Matrix4x4 operator+(const Matrix4x4 & lhs, float rhs);

    inline Matrix4x4 operator-(const Matrix4x4 & lhs, const Matrix4x4 & rhs);
    inline Matrix4x4 operator-(const Matrix4x4 & lhs, float rhs);
    inline Matrix4x4 operator-(const Matrix4x4 & m);

    inline Matrix4x4 operator*(const Matrix4x4 & lhs, const Matrix4x4 & rhs);
    inline Matrix4x4 operator*(const Matrix4x4 & lhs, float rhs);

    inline bool ExactlyEqual(const Matrix4x4 & lhs, const Matrix4x4 & rhs);
    inline bool ExactlyZero(const Matrix4x4 & m);

    inline bool NearlyEqual(const Matrix4x4 & lhs, const Matrix4x4 & rhs);
    inline bool NearlyZero(const Matrix4x4 & m);

    inline Matrix4x4 Add(const Matrix4x4 & lhs, const Matrix4x4 & rhs);
    inline Matrix4x4 Add(const Matrix4x4 & lhs, float rhs);
    inline void Add(const Matrix4x4 & lhs, const Matrix4x4 & rhs, Matrix4x4 & out);
    inline void Add(const Matrix4x4 & lhs, float rhs, Matrix4x4 & out);

    inline Matrix4x4 Subtract(const Matrix4x4 & lhs, const Matrix4x4 & rhs);
    inline Matrix4x4 Subtract(const Matrix4x4 & lhs, float rhs);
    inline void Subtract(const Matrix4x4 & lhs, const Matrix4x4 & rhs, Matrix4x4 & out);
    inline void Subtract(const Matrix4x4 & lhs, float rhs, Matrix4x4 & out);

    inline Matrix4x4 Multiply(const Matrix4x4 & lhs, const Matrix4x4 & rhs);
    inline Matrix4x4 Multiply(const Matrix4x4 & lhs, float rhs);
    inline void Multiply(const Matrix4x4 & lhs, const Matrix4x4 & rhs, Matrix4x4 & out);
    inline void Multiply(const Matrix4x4 & lhs, float rhs, Matrix4x4 & out);

    inline Matrix4x4 Transform(const Matrix4x4 & m, const Quaternion & q);
    inline void Transform(const Matrix4x4 & m, const Quaternion & q, Matrix4x4 & out);

    inline float Determinant(const Matrix4x4 & m);

    inline Vector3 EulerAngles(const Matrix4x4 & m);

    inline Matrix4x4 Inverse(const Matrix4x4 & m);
    inline void Inverse(const Matrix4x4 & m, Matrix4x4 & out);

    inline Matrix4x4 Negate(const Matrix4x4 & m);
    inline void Negate(const Matrix4x4 & m, Matrix4x4 & out);

    inline Matrix4x4 Orthonormalize(const Matrix4x4 & m);
    inline void Orthonormalize(const Matrix4x4 & m, Matrix4x4 & out);

    inline Matrix4x4 Transpose(const Matrix4x4 & m);
    inline void Transpose(const Matrix4x4 & m, Matrix4x4 & out);

    inline bool Decompose(const Matrix4x4 & m, Vector3 & outScale, Quaternion & outOrientation, Vector3 & outTranslation);

} //namespace Math
} //namespace Phx

#endif //_PHX_MATH_MATRIX4X4_H_
