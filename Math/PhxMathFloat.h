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

#ifndef _PHX_MATH_FLOAT_H_
#define _PHX_MATH_FLOAT_H_

#define PHX_FLT_TOLERANCE 0.000001f

namespace Phx {
namespace Math {

    inline bool ExactlyEqual(float lhs, float rhs);
    inline bool ExactlyZero(float f);

    inline bool NearlyEqual(float lhs, float rhs);
    inline bool NearlyZero(float f);

    inline float Abs(float f);
    
    inline float Clamp(float f, float min, float max);
    inline float Clamp01(float f);

    inline float Sin(float radians);
    inline float Cos(float radians);
    inline float Tan(float radians);

    inline void SinCos(float radians, float * PHX_RESTRICT_PTR pOutSin, float * PHX_RESTRICT_PTR pOutCos);
    
    inline float ASin(float f);
    inline float ACos(float f);
    inline float ATan(float f);
    inline float ATan2(float y, float x);

    inline float Lerp(float f1, float f2, float weight);
    inline float Hermite(float f1, float t1, float f2, float t2, float weight);
    inline float SmoothStep(float f1, float f2, float weight);

    inline float Sign(float f);

    inline float Sqrt(float f);
    inline float InvSqrt(float f);

    inline float Max(float f1, float f2);
    inline float Min(float f1, float f2);

    inline float Ceiling(float f);
    inline float Floor(float f);
    inline float Round(float f);

    inline float ToRadians(float degrees);
    inline float ToDegrees(float radians);

    inline float WrapRadians(float radians);
    inline float WrapDegrees(float degrees);

    inline float Remap(float in, float inRangeMin, float inRangeMax, float outRangeMin, float outRangeMax);

    namespace Float
    {
        extern const float Max;
        extern const float Min;
        extern const float Epsilon;
        extern const float Tolerance;
    }

    namespace Trig
    {
        extern const float Pi;
        extern const float PiOverTwo;
        extern const float PiOverFour;
        extern const float TwoPi;
        extern const float DegreesToRadians;
        extern const float RadiansToDegrees;
    }

} //namespace Math
} //namespace Phx

#endif //_PHX_MATH_FLOAT_H_
