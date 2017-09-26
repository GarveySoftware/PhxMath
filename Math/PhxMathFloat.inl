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

#ifndef _PHX_MATH_FLOAT_INL_
#define _PHX_MATH_FLOAT_INL_

namespace Phx {
namespace Math {

    inline bool ExactlyEqual(float lhs, float rhs)
    {
        return (lhs == rhs);
    }

    inline bool ExactlyZero(float f)
    {
        return (f == 0.0f);
    }

    inline bool NearlyEqual(float lhs, float rhs)
    {
        return NearlyZero(lhs - rhs);
    }

    inline bool NearlyZero(float f)
    {
        return ((f * f) < Float::Tolerance);
    }

    inline float Abs(float f)
    {
        return fabsf(f);
    }

    inline float Clamp(float f, float min, float max)
    {
        DebugAssert(min <= max, "min greater than max (%d > %d)", min, max);
        return (f < min ? min : (f > max ? max : f));
    }

    inline float Clamp01(float f)
    {
        return (f < 0.0f ? 0.0f : (f > 1.0f ? 1.0f : f));
    }

    inline float Sin(float radians)
    {
        return sinf(radians);
    }

    inline float Cos(float radians)
    {
        return cosf(radians);
    }

    inline void SinCos(float radians, float * PHX_RESTRICT_PTR pOutSin, float * PHX_RESTRICT_PTR pOutCos)
    {
        *pOutSin = sinf(radians);
        *pOutCos = cosf(radians);
    }

    inline float Tan(float radians)
    {
        return tanf(radians);
    }

    inline float ASin(float f)
    {
        if (f < 1.0f)
        {
            if (f > -1.0f)
            {
                return asinf(f);
            }
            else
            {
                return Trig::Pi;
            }
        }
        else
        {
            return 0.0f;
        }
    }

    inline float ACos(float f)
    {
        if (f < 1.0f)
        {
            if (f > -1.0f)
            {
                return acosf(f);
            }
            else
            {
                return -Trig::PiOverTwo;
            }
        }
        else
        {
            return Trig::PiOverTwo;
        }
    }
    
    inline float ATan(float f)
    {
        return atanf(f);
    }

    inline float ATan2(float y, float x)
    {
        if (y == 0.0f && x == 0.0f)
        {
            DebugAssert(false, "Atan2(0,0) is undefined!");
            return 0.0f;
        }
        return atan2f(y, x);
    }

    inline float Lerp(float f1, float f2, float t)
    {
        return f1 + ((f2 - f1) * t);
    }

    inline float Hermite(float f1, float t1, float f2, float t2, float weight)
    {
        // factored form of pseudo code found here:
        // http://cubic.org/docs/hermite.htm

        const float s = weight;
        const float sSquared = weight * weight;
        const float sCubed = sSquared * weight;

        return (sCubed * ((2.0f * f1) - (2.0f * f2) + t1 + t2)) +
               (sSquared * ((-3.0f * f1) + (3.0f * f2) - (2.0f * t1) - t2)) +
               (s * t1) +
               f1;
    }

    inline float SmoothStep(float f1, float f2, float weight)
    {
        // equivalent to Hermite(f1, 0.0f, f2, 0.0f, Clamp01(weight));

        const float s = Clamp01(weight);
        const float sSquared = s * s;
        const float sCubed = sSquared * s;

        return (sCubed * ((2.0f * f1) - (2.0f * f2))) +
               (sSquared * ((-3.0f * f1) + (3.0f * f2))) +
               f1;
    }

    inline float Sign(float f)
    {
        return (f < 0.0f ? -1.0f : 1.0f);
    }

    inline float Sqrt(float f)
    {
        DebugAssert(f >= 0.0f, "Trying to take the square root of a negative number!");
        return sqrtf(f);
    }

    inline float InvSqrt(float f)
    {
        // TODO: perhaps implement something like this
        // http://stackoverflow.com/questions/17789928/fast-inverse-square-root-algorithm-in-modern-c

        DebugAssert(f > 0.0f, "Division by zero or trying to take the square root of a negative number!");
        return (1.0f / sqrtf(f));
    }

    inline float Max(float f1, float f2)
    {
        return (f1 > f2 ? f1 : f2);
    }

    inline float Max(float f1, float f2, float f3)
    {
        float out = f1;
        if (f2 > out) { out = f2; }
        if (f3 > out) { out = f3; }
        return out;
    }

    inline float Max(float f1, float f2, float f3, float f4)
    {
        float out = f1;
        if (f2 > out) { out = f2; }
        if (f3 > out) { out = f3; }
        if (f4 > out) { out = f4; }
        return out;
    }

    inline float Min(float f1, float f2)
    {
        return (f1 < f2 ? f1 : f2);
    }

    inline float Min(float f1, float f2, float f3)
    {
        float out = f1;
        if (f2 < out) { out = f2; }
        if (f3 < out) { out = f3; }
        return out;
    }

    inline float Min(float f1, float f2, float f3, float f4)
    {
        float out = f1;
        if (f2 < out) { out = f2; }
        if (f3 < out) { out = f3; }
        if (f4 < out) { out = f4; }
        return out;
    }

    inline float Ceiling(float f)
    {
        return ceilf(f);
    }

    inline float Floor(float f)
    {
        return floorf(f);
    }

    inline float Round(float f)
    {
        return ((f > 0.0) ? floorf(f + 0.5f) : ceilf(f - 0.5f));
    }

    inline float ToRadians(float degrees)
    {
        return (degrees * Trig::DegreesToRadians);
    }

    inline float ToDegrees(float radians)
    {
        return (radians * Trig::RadiansToDegrees);
    }

    inline float WrapRadians(float radians)
    {
        // TODO: more roboust implemntation, this will fail with angles > or < FourPi
        // Look into floor algorithm here: http://stackoverflow.com/questions/11980292/how-to-wrap-around-a-range
        if (radians > Trig::TwoPi)
        {
            return radians - Trig::TwoPi;
        }
        else if (radians < 0.0f)
        {
            return radians + Trig::TwoPi;
        }
        return radians;
    }

    inline float WrapDegrees(float degrees)
    {
        // TODO: more roboust implemntation, this will fail with angles > or < 720.0f
        // Look into floor algorithm here: http://stackoverflow.com/questions/11980292/how-to-wrap-around-a-range
        if (degrees > 360.0f)
        {
            return degrees - 360.0f;
        }
        else if (degrees < 0.0f)
        {
            return degrees + 360.0f;
        }
        return degrees;
    }

    inline float Remap(float in, float inRangeMin, float inRangeMax, float outRangeMin, float outRangeMax)
    {
        if (in <= inRangeMin) { return outRangeMin; }
        if (in >= inRangeMax) { return outRangeMax; }

        return outRangeMin + ((in - inRangeMin) / (inRangeMax - inRangeMin)) * (outRangeMax - outRangeMin);
    }

    inline void Swap(float & f1, float & f2)
    {
        float temp = f1;
        f1 = f2;
        f2 = temp;
    }

} //namespace Math
} //namespace Phx

#endif //_PHX_MATH_FLOAT_INL_
