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

#include "PhxMath.h"

namespace Phx {
namespace Math {

    namespace Float
    {
        const float Max       ( FLT_MAX );
        const float Min       ( FLT_MIN );
        const float Epsilon   ( FLT_EPSILON );
        const float Tolerance ( PHX_FLT_TOLERANCE );
    }

    namespace Trig
    {
        const float Pi               ( 3.14159265f );
        const float PiOverTwo        ( 1.57079633f );
        const float PiOverFour       ( 0.78539816f );
        const float TwoPi            ( 6.28318531f );
        const float DegreesToRadians ( 0.01745329f );
        const float RadiansToDegrees ( 57.2957795f );
    }

} //namespace Math
} //namespace Phx
