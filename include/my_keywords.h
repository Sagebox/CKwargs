#pragma once

#include "keyclass.h"

// ******************************** Example my_keywords.h file *************************************
//
// Important note:  This file contains two namespaces (or classes),
// 
//      kw: declaring assigned-keyword style keywords, i.e. keyword=value
//      kf: declaring function-based keyword style keyword i.e. keyword(value) or keyword() 
//          in the case of booleans with a default value
// 
// --> Only one namespace is required, depending on your choice of what keyword you want to use
//     (both can be used if support for both styles is supported).
// 
//     As an example file, both are included, but usually one would be chosen.
// 
// The keyword declaration examples 1:1 with the keyword examples in keyclass.h
// 
// For your own keywords, replace the example kewords in keyclass.h and 
// replace the keyword code below with code that represents the keywords declared in keyclass.h
// 
// Also delete whichever namespsace you are not using.
// 
// namespace names are arbitrary --> kw and kf were chosen as short naems.
// "my_keywords.h" is also arbitrary --> This is not included by any CKwargs code, so it can be named anything
//                                       such as ClassNameKeys.h, etc.  
// 
// -------------------------------
// namespace vs. class (or struct)
// -------------------------------
// 
// note: keep in mind that namespaces can also be declared as classes, which can be easier because:
// 
//   1. as a namespace, inlined functions declared as static are duplicated for all
//      source files that include "my_keywords.h"
//   2. This can be prevented by moving the code from inline to a separate
//      C++ file, but does require the work to do so
// 
//   --> A recommendation is to just use static functions in the namespacee or class at first,
//       and then decide whether the project is large enough to support the extra work.
// 
// --> Namespaces vs. classes for the kw and kf namespaces below are only useful if you want to unscope keywords, to use
//     keywords like 'BorderSize=50' vs. 'kw::BorderSize=50' by specifying "using namespace kw" in the function or at the top of the file.
//  
// --> struct can also be used instead of a class, and doesn't require 'public' after the class definition.
// 
// *************************************************************************************************


// --- Beginning of File ---


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


namespace kw    // Can be namespace or class/struct.  See notes in keyclass.h
{
// public:      // Add for class usage, but not needed for struct

    // Sets a Range of iMin to iMax values.
    //
    // This example shows using 1 form for the Range keyword, but could be expanded to other forms, though
    // probably not too useful in the keyword form -- See the kf class below to show the Range() option 
    // used with more than one value (i.e. min, max)
    //
    static struct { _kw_op_eq(std::array<int,2> szRange)  { _kw_return(Range)      { kwx.keyValues.Range      = szRange; }); } }  Range        ;
    static struct { _kw_op_eq(int iSize)                  { _kw_return(BorderSize) { kwx.keyValues.BorderSize = iSize;   }); } }  BorderSize   ;

    // Text keyword is used to send additional text to the function, i.e. function(..parms...,Text("This is some additional text"); 
    // 
    // This example sets "<nullptr>" to the string, so we know it as input as a keyword.  Otherwise, the null can just be sent
    //
    static struct { _kw_op_eq(const char * sText)    _kw_reteasy(Text,sText)          }  Text ;
    static struct { _kw_op_eq(bool bValue)           _kw_reteasy(AddBorder,bValue )   }  AddBorder;

}


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

namespace kf        // Can be namespace or class/struct.  See notes in keyclass.h 
{
// public:      // Add for class usage, but not needed for struct

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
