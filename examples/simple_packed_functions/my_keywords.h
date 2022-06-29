#pragma once

#include "ckwargs.h"


// ---------------------------------------------------------------------------------------------
// Keywords (canonical) class for program usage using packed-parameter style keyword definitions
// ---------------------------------------------------------------------------------------------
// 
// When kw:: is entered, the intellisense will show all available keywords and will also show any comments 
//
// For this example, only the last two functions are commented. 
// 

// Helper Macros

#define _kw_op_eq ckwargs::ckw operator = 
#define _kw_return(_x) return ckwargs::ckw(ckwargs::Keywords::_x, [&](ckwargs::ckw & kwx)
#define _kw_reteasy(_x,_value) { return ckwargs::ckw(ckwargs::Keywords::_x, [&](ckwargs::ckw & kwx) { kwx.keyValues._x = _value;   }); }

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
//    3. More legible and uniform interface.  The functions below have the names of the keyword functions in a nice line to the left, and
//       are easily readable.  The keyworded format makes them a little harder to read, as they names are at the end of the structure definition.
//       This isn't an issue for the end-user, though, just when implementing the code for the keyword functions.
//
// Example without Helper Macros:
//
//  ckwargs::ckw BorderSize(int iSize)  
//          { return ckwargs::ckw(Keywords::BorderSize, [&](ckwargs::ckw & kwx) { kwx.keyValues.BorderSize = iSize;   }); } 
//
//
namespace kf        // Can be namespace or class/struct.  See notes in ckwargs.h 
{
// public:      // Add for class usage, but not needed for struct

    // Sets a Range of iMin to iMax values.
    // integer, or array<int,2> values may be used. 
    // 
    // This example shows using 2 forms for the Range keyword, which delivers one type to the function using the keyword.
    //
    static ckwargs::ckw Range(std::array<int,2> szRange)  { _kw_reteasy(Range,szRange); }

    // Use the longer form for this entry since we have a ','.  in two places, and #defines don't like that.

    static ckwargs::ckw Range(int iMin,int iMax)          { _kw_return(Range)      { kwx.keyValues.Range = std::array<int,2>{ iMin, iMax}; }); }

    // Text keyword is used to send additional text to the function, i.e. function(..parms...,Text("This is some additional text"); 
    // 
    // This example sets "<nullptr>" to the string, so we know it as input as a keyword.  Otherwise, the null can just be sent
    //
    static ckwargs::ckw Text(const char * sText)      { _kw_reteasy(Text      , sText ? sText : "<nullptr>"); }
    static ckwargs::ckw BorderSize(int iSize)         { _kw_reteasy(BorderSize, iSize); }
    static ckwargs::ckw AddBorder(bool bValue = true) { _kw_reteasy(AddBorder , bValue); }

}
