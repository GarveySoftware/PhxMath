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

#ifndef _PHX_MATH_RECTANGLE_INL_
#define _PHX_MATH_RECTANGLE_INL_

namespace Phx {
namespace Math {

    inline Rect::Rect(float x, float y, float width, float height)
        : X(x)
        , Y(y)
        , Width(width)
        , Height(height)
    { }

    inline Rect::Rect(const Vector2 & position, const Vector2 & size)
        : X(position.X)
        , Y(position.Y)
        , Width(size.X)
        , Height(size.Y)
    { }

    inline Rect::Rect(const Rect & src)
    {
        Copy(src);
    }

    inline Rect & Rect::operator=(const Rect & rhs)
    {
        Copy(rhs);
        return *this;
    }

    inline float Rect::GetLeft() const
    {
        return this->X;
    }

    inline float Rect::GetRight() const
    {
        return this->X + this->Width;
    }

    inline float Rect::GetTop() const
    {
        return this->Y + this->Height;
    }

    inline float Rect::GetBottom() const
    {
        return this->Y;
    }

    inline Vector2 & Rect::GetPosition()
    {
        return *reinterpret_cast<Vector2 *>(&(this->X));
    }

    inline const Vector2 & Rect::GetPosition() const
    {
        return *reinterpret_cast<const Vector2 *>(&(this->X));
    }

    inline Vector2 & Rect::GetSize()
    {
        return *reinterpret_cast<Vector2 *>(&(this->Width));
    }

    inline const Vector2 & Rect::GetSize() const
    {
        return *reinterpret_cast<const Vector2 *>(&(this->Width));
    }

    inline Vector2 Rect::GetCenter() const
    {
        return Vector2(this->X + (this->Width * 0.5f), this->Y + (this->Height * 0.5f));
    }

    inline bool Rect::IsEmpty() const
    {
        return Math::IsEmpty(*this);
    }

    inline bool Rect::Contains(float x, float y) const
    {
        return Math::Contains(*this, x, y);
    }

    inline bool Rect::Contains(const Vector2 & p) const
    {
        return Math::Contains(*this, p.X, p.Y);
    }

    inline bool Rect::Contains(const Rect & r) const
    {
        return Math::Contains(*this, r);
    }

    inline bool Rect::Intersects(const Rect & r) const
    {
        Math::Intersects(*this, r);
    }

    inline void Rect::Offset(float x, float y)
    {
        Math::Offset(*this, x, y, *this);
    }

    inline void Rect::Offset(const Vector2 & p)
    {
        Math::Offset(*this, p.X, p.Y, *this);
    }

    inline void Rect::Inflate(float horizontalValue, float verticalValue)
    {
        Math::Inflate(*this, horizontalValue, verticalValue, *this);
    }

    inline void Rect::Inflate(const Vector2 & value)
    {
        Math::Inflate(*this, value.X, value.Y, *this);
    }

    inline Rect Rect::Intersect(const Rect & r) const
    {
        Rect out;
        Math::Intersect(*this, r, out);
        return out;
    }

    inline void Rect::Intersect(const Rect & r, Rect & out) const
    {
        Math::Intersect(*this, r, out);
    }

    inline Rect Rect::Union(const Rect & r) const
    {
        Rect out;
        Math::Union(*this, r, out);
        return out;
    }

    inline void Rect::Union(const Rect & r, Rect & out) const
    {
        Math::Union(*this, r, out);
    }
    
    inline void Rect::Copy(float x, float y, float width, float height)
    {
        this->X = x;
        this->Y = y;
        this->Width = width;
        this->Height = height;
    }

    inline void Rect::Copy(const Vector2 & position, const Vector2 & size)
    {
        this->X = position.X;
        this->Y = position.Y;
        this->Width = size.X;
        this->Height = size.Y;
    }

    inline void Rect::Copy(const Rect & src)
    {
        memcpy(this, &src, sizeof(Rect));
    }

    inline bool operator==(const Rect & lhs, const Rect & rhs)
    {
        return ExactlyEqual(lhs, rhs);
    }

    inline bool operator!=(const Rect & lhs, const Rect & rhs)
    {
        return (false == ExactlyEqual(lhs, rhs));
    }

    inline bool ExactlyEqual(const Rect & lhs, const Rect & rhs)
    {
        return ExactlyEqual(lhs.X, rhs.X) &&
               ExactlyEqual(lhs.Y, rhs.Y) &&
               ExactlyEqual(lhs.Width, rhs.Width) &&
               ExactlyEqual(lhs.Height, rhs.Height);
    }

    inline bool ExactlyZero(const Rect & v)
    {
        return ExactlyEqual(v, Rect::Empty);
    }

    inline bool NearlyEqual(const Rect & lhs, const Rect & rhs)
    {
        return NearlyEqual(lhs.X, rhs.X) &&
               NearlyEqual(lhs.Y, rhs.Y) &&
               NearlyEqual(lhs.Width, rhs.Width) &&
               NearlyEqual(lhs.Height, rhs.Height);
    }

    inline bool NearlyZero(const Rect & v)
    {
        return NearlyZero(v.X) &&
               NearlyZero(v.Y) &&
               NearlyZero(v.Width) &&
               NearlyZero(v.Height);
    }

    inline bool IsEmpty(const Rect & r)
    {
        return ExactlyZero(r);
    }

    inline bool Contains(const Rect & r, float x, float y)
    {
        // Counts points right on the edges as being contained.
        return (x >= r.X) &&
               (x <= (r.X + r.Width)) &&
               (y >= r.Y) &&
               (y <= (r.Y + r.Height));
    }

    inline bool Contains(const Rect & r, const Vector2 & p)
    {
        return Contains(r, p.X, p.Y);
    }

    inline bool Contains(const Rect & r1, const Rect & r2)
    {
        return (r1.X <= r2.X) &&
               ((r1.X + r1.Width) >= (r2.X + r2.Width)) &&
               (r1.Y <= r2.Y) &&
               ((r1.Y + r1.Height) >= (r2.Y + r2.Height));
    }

    inline bool Intersects(const Rect & r1, const Rect & r2)
    {
        // Test for non-intersection and negate the result.
        // Does not count rectangles that are touching as an intersecion.
        return (false == ((r1.X > (r2.X + r2.Width)) ||
                          ((r1.X + r1.Width) < r2.X) || 
                          (r1.Y > (r2.Y + r2.Height)) ||
                          ((r1.Y + r1.Height) < r2.Y)));
    }

    inline Rect Offset(const Rect & r, float x, float y)
    {
        Rect out;
        Offset(r, x, y, out);
        return out;
    }

    inline Rect Offset(const Rect & r, const Vector2 & p)
    {
        Rect out;
        Offset(r, p.X, p.Y, out);
        return out;
    }

    inline void Offset(const Rect & r, float x, float y, Rect & out)
    {
        out.X = r.X + x;
        out.Y = r.Y + y;
        out.Width = r.Width;
        out.Height = r.Height;
    }

    inline void Offset(const Rect & r, const Vector2 & p, Rect & out)
    {
        Offset(r, p.X, p.Y, out);
    }

    inline Rect Inflate(const Rect & r, float horizontalValue, float verticalValue)
    {
        Rect out;
        Inflate(r, horizontalValue, verticalValue, out);
        return out;
    }

    inline Rect Inflate(const Rect & r, const Vector2 & value)
    {
        Rect out;
        Inflate(r, value.X, value.Y, out);
        return out;
    }

    inline void Inflate(const Rect & r, float horizontalValue, float verticalValue, Rect & out)
    {
        out.X = r.X - horizontalValue;
        out.Y = r.Y - verticalValue;
        out.Width = r.Width + horizontalValue * 2.0f;
        out.Height = r.Height + verticalValue * 2.0f;
    }

    inline void Inflate(const Rect & r, const Vector2 & value, Rect & out)
    {
        Inflate(r, value.X, value.Y, out);
    }

    inline Rect Intersect(const Rect & r1, const Rect & r2)
    {
        Rect out;
        Intersect(r1, r2, out);
        return out;
    }

    inline void Intersect(const Rect & r1, const Rect & r2, Rect & out)
    {
        if (Intersects(r1, r2))
        {
            float left = Max(r1.X, r2.X);
            float right = Min(r1.X + r1.Width, r2.X + r2.Width);
            float top = Min(r1.Y + r1.Height, r2.Y + r2.Height);
            float bottom = Max(r1.Y, r2.Y);

            out.X = left;
            out.Y = bottom;
            out.Width = right - left;
            out.Height = top - bottom;
        }
        else
        {
            out.Copy(Rect::Empty);
        }
    }

    inline Rect Union(const Rect & r1, const Rect & r2)
    {
        Rect out;
        Union(r1, r2, out);
        return out;
    }

    inline void Union(const Rect & r1, const Rect & r2, Rect & out)
    {
        float left = Min(r1.X, r2.X);
        float right = Max(r1.X + r1.Width, r2.X + r2.Width);
        float top = Max(r1.Y + r1.Height, r2.Y + r2.Height);
        float bottom = Min(r1.Y, r2.Y);

        out.X = left;
        out.Y = bottom;
        out.Width = right - left;
        out.Height = top - bottom;
    }

} //namespace Math
} //namespace Phx

#endif //_PHX_MATH_RECTANGLE_INL_
