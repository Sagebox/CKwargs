#pragma once

#include "keyclass.h"

// --------------------------------------------
// Keywords (canonical) class for program usage
// --------------------------------------------
// 
// Only the keywords are displayed.  When kw:: is entered, the intellisense will show all available keywords and will also
// show any comments 
//
// For the example, only the last two functions are commented. 
    
using namespace keyclass;   // Placing this inside kw causes MSVS intellisense to list keyclass members, rather than just
                            // pure keyword members.


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

namespace kf        // Can be namespace or class.  See notes in keyclass.h 
{
    // Sets a Range of iMin to iMax values.
    // integer, or array<int,2> values may be used. 
    // 
    // This example shows using 2 forms for the Range keyword, which delivers one type to the function using the keyword.
    //
    static ckw Range(int iMin,int iMax)           { return ckw(Keywords::Range, [&](ckw & kwx) { kwx.keyValues.Range = std::array<int,2>{ iMin, iMax}; }); }
    static ckw Range(std::array<int,2> szRange)   { return ckw(Keywords::Range, [&](ckw & kwx) { kwx.keyValues.Range = szRange;       }); }

    // Text keyword is used to send additional text to the function, i.e. function(..parms...,Text("This is some additional text"); 
    // 
    // This example sets "<nullptr>" to the string, so we know it as input as a keyword.  Otherwise, the null can just be sent
    //
    static ckw Text(const char * sText)      { return ckw(Keywords::Text      ,  [&](ckw & kwx) { kwx.keyValues.Text = sText ? sText : "<nullptr>";  }); }
    static ckw BorderSize(int iSize)         { return ckw(Keywords::BorderSize,  [&](ckw & kwx) { kwx.keyValues.BorderSize = iSize;                  }); }
    static ckw AddBorder(bool bValue = true) { return ckw(Keywords::AddBorder ,  [&](ckw & kwx) { kwx.keyValues.AddBorder  = bValue;                 }); }

    // Another form for AddBorder() is to just have no values, such as:
    //
    // const ckw AddBorder() { return ckw(Keywords::AddBorder,  [&](ckw & kwx) { kwx.keyValues.AddBorder  = true;                 }); }
    //
    // Where it is only used when it is wanted as a positive, true value, and otherwise is left undefined with a false as a default (or whatever
    // the program desides is the default)
    //
    // Either way, we can just use AddBorder() with a function, rather than a keyword-style 'AddBorder = true'

}
