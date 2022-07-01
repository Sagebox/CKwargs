#pragma once

#define _ckwargs_inc_check_items
#include "my_keyfuncs.h"

using namespace ckwargs;        // Use are namespace locally so if we change it we only have to do it here.

// ------------------------------------------------------------------------------------
// Function-Based Keywords (i.e. keyword functions) namespace/class/struct Example Code
// ------------------------------------------------------------------------------------
//
// This file contains code for setting up function-based keywords using the example keywords in keydefs.h.

// Helper Macros.  See examples below. The second Range example shows filling in the keyword value
//                 without using any macros, showing the original form.

#define SetKeyVal(_x,_value) { return ckw(Keywords::_x, [&](ckw & kwx) { kwx.keyValues._x = _value;   }); }
#define SetKeyDirect(_x) { return ckw(Keywords::_x, [&](ckw & kwx) { kwx.keyValues._x = value;   }); }
#define defOptEq(x) ckw __##x        :: operator

// --------------------------------------------------
// Named Parameter Functions (i.e. Keyword Functions)
// --------------------------------------------------
// 
// These are much more flexible and useful than the keyword form, but don't have the canonical keyword (i.e. Text="HelloWorld" look, vs.
// Text("Hello World").
//
// The main advantages are:
// 
//    1. Different forms can be used with variable parameters, such as Range(min,max) or Range(SIZE), where
//       the keyworded form allows multiple forms, though not quite as easily. The keyworded form, by definition, cannot use
//       multiple values.
//
//    2. Intellisense.  The Intellisense shows the documentation and all overloaded forms.  The keyworded version will show the
//       documentation for the structure, but won't show the function form or overloads.
// 
//       With the canonical keyword format, the intellisense also shows the structure definitions. For example '__AddBorder' is also listed with
//       'AddBorder'
//
//       With they function-based keywords, only the keywords are shown in the intellisense listing. 
// 
//    3. More legible and uniform interface.  The functions below have the names of the keyword functions in a nice line to the left, and
//       are easily readable.  The keyworded format makes them a little harder to read, as they names are at the end of the structure definition.
//       This isn't an issue for the end-user, though, just when implementing the code for the keyword functions.
//
// Example without Helper Macros:
//
//  ckw BorderSize(int iSize)  
//          { return ckw(Keywords::BorderSize, [&](ckw & kwx) { kwx.keyValues.BorderSize = iSize;   }); } 
//
//
namespace kf        // Can be namespace or class/struct.  See notes in ckwargs.h 
{
    ckw Range(std::array<int,2> value)  SetKeyDirect(Range)

    // because of the ',' in the values, we can't use the macros:

    ckw Range(int iMin,int iMax)   { return ckw(Keywords::Range, [&](auto & kwx) { kwx.keyValues.Range = std::array<int,2>{ iMin, iMax}; }); }

    // Here, we can't use SetKeyDirect() because of the ternery, but can use SetKeyVal

    ckw Text(const char * value)      SetKeyVal(Text , value ? value : "<nullptr>"); 

    ckw BorderSize(int value)         SetKeyDirect(BorderSize); 
    ckw AddBorder(bool value)         SetKeyDirect(AddBorder) ; 

}

// class/struct-based Example
//
// ckw kf::BorderSize(int value)         SetKeyDirect(BorderSize); 