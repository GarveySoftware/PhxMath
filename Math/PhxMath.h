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

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// - Math formulas and descriptions in "Essential Mathematics from Games and Interactive 
// = Applications, A Programmers Guide" by J. Verth and L. Bishop were used as reference 
// - for many of the formulas used in this library.
// =
// - The Geometric Toools Engine and many of the papers at: http://www.geometrictools.com/
// = by David Eberly were also used as reference.
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#ifndef _PHX_MATH_H_
#define _PHX_MATH_H_

// C Standard Libary Includes
#include <string.h>
#include <math.h>
#include <float.h>

#ifndef DebugAssert
// Add a definition to this for your own use
# define DebugAssert(condition, format, ...)
#endif

#ifndef PHX_RESTRICT_PTR
# define PHX_RESTRICT_PTR __restrict
#endif

// Mangage the dependencies between the math classes by explicity
// ordering their declarations before their inlined implementations.

// Forward Declarations
namespace Phx {
namespace Math {

    class Matrix4x4;
    class Quaternion;
    class Rect;
    class Vector2;
    class Vector3;
    class Vector4;

} //namespace Math
} //namespace Phx

// Class Declarations
#include "PhxMathFloat.h"
#include "PhxMathMatrix4x4.h"
#include "PhxMathQuaternion.h"
#include "PhxMathRectangle.h"
#include "PhxMathVector2.h"
#include "PhxMathVector3.h"
#include "PhxMathVector4.h"

// Inline Implementations
#include "PhxMathFloat.inl"
#include "PhxMathMatrix4x4.inl"
#include "PhxMathQuaternion.inl"
#include "PhxMathRectangle.inl"
#include "PhxMathVector2.inl"
#include "PhxMathVector3.inl"
#include "PhxMathVector4.inl"

// Typedef for basic matrix (4x3, 3x3, 2x2 may be implemented in the future)
namespace Phx {
namespace Math {

typedef Matrix4x4 Matrix;

} //namespace Math
} //namespace Phx

#endif //_PHX_MATH_H_
