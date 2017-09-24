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

#ifndef _PHX_MATH_RECTANGLE_H_
#define _PHX_MATH_RECTANGLE_H_

namespace Phx {
namespace Math {

    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // Simple 2D Rectangle                                                  
    // Origin at the bottom left (x, y)                                     
    // x + is right, y + is up                                              
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // I wanted to name this class Rectangle.. but windows.h strikes again! 
    // They declare a function named Rectangle in wingdi.h :(               
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    class Rect
    {
    public:
        float X;
        float Y;
        float Width;
        float Height;

    public:
        static const Rect Empty;

    public:
        inline Rect()
        { 
            // Do nothing in the default ctor.
            // So we don't have to pay for arrays or rectangles initialized as an out parameter.
        }
        inline Rect(float x, float y, float width, float height);
        inline Rect(const Vector2 & position, const Vector2 & size);
        inline Rect(const Rect & src);

        inline ~Rect() { }

        inline Rect & operator=(const Rect & rhs);

        inline float GetLeft() const;
        inline float GetRight() const;
        inline float GetTop() const;
        inline float GetBottom() const;

        inline Vector2 & GetPosition();
        inline const Vector2 & GetPosition() const;

        inline Vector2 & GetSize();
        inline const Vector2 & GetSize() const;

        inline Vector2 GetCenter() const;

        inline bool IsEmpty() const;

        inline bool Contains(float x, float y) const;
        inline bool Contains(const Vector2 & p) const;
        inline bool Contains(const Rect & r) const;

        inline bool Intersects(const Rect & r) const;

        inline void Offset(float x, float y);
        inline void Offset(const Vector2 & p);

        inline void Inflate(float horizontalValue, float verticalValue);
        inline void Inflate(const Vector2 & value);

        inline Rect Intersect(const Rect & r) const;
        inline void Intersect(const Rect & r, Rect & out) const;

        inline Rect Union(const Rect & r) const;
        inline void Union(const Rect & r, Rect & out) const;

        inline void Copy(float x, float y, float width, float height);
        inline void Copy(const Vector2 & position, const Vector2 & size);
        inline void Copy(const Rect & src);
    };

    inline bool operator==(const Rect & lhs, const Rect & rhs);
    inline bool operator!=(const Rect & lhs, const Rect & rhs);

    inline bool ExactlyEqual(const Rect & lhs, const Rect & rhs);
    inline bool ExactlyZero(const Rect & v);

    inline bool NearlyEqual(const Rect & lhs, const Rect & rhs);
    inline bool NearlyZero(const Rect & v);

    inline bool IsEmpty(const Rect & r);

    inline bool Contains(const Rect & r, float x, float y);
    inline bool Contains(const Rect & r, const Vector2 & p);
    inline bool Contains(const Rect & r1, const Rect & r2);

    inline bool Intersects(const Rect & r1, const Rect & r2);

    inline Rect Offset(const Rect & r, float x, float y);
    inline Rect Offset(const Rect & r, const Vector2 & p);
    inline void Offset(const Rect & r, float x, float y, Rect & out);
    inline void Offset(const Rect & r, const Vector2 & p, Rect & out);

    inline Rect Inflate(const Rect & r, float horizontalValue, float verticalValue);
    inline Rect Inflate(const Rect & r, const Vector2 & value);
    inline void Inflate(const Rect & r, float horizontalValue, float verticalValue, Rect & out);
    inline void Inflate(const Rect & r, const Vector2 & value, Rect & out);

    inline Rect Intersect(const Rect & r1, const Rect & r2);
    inline void Intersect(const Rect & r1, const Rect & r2, Rect & out);

    inline Rect Union(const Rect & r1, const Rect & r2);
    inline void Union(const Rect & r1, const Rect & r2, Rect & out);

} //namespace Math
} //namespace Phx

#endif _PHX_MATH_RECTANGLE_H_
