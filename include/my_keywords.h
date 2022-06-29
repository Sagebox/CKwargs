#pragma once

#include "ckwargs.h"

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
// The keyword declaration examples 1:1 with the keyword examples in ckwargs.h
// 
// For your own keywords, replace the example kewords in ckwargs.h and 
// replace the keyword code below with code that represents the keywords declared in ckwargs.h
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

// Adding a keyword in this form without helper macros:
// 
//   struct {
//               const ckwargs::ckw operator = (int iSize) 
//                      { return ckwargs::ckw(Keywords::BorderSize, [&](ckwargs::ckw & kwx) { kwx.keyValues.BorderSize = iSize;   }); } 
//          }  BorderSize   ;
// 
// Where the std::function routine sets the value of the key in the constructor.
// 
// With the helper #define macros below, we can simplify the process:
// 
// Example macro with _kw_return #define: 
// 
//      struct { _kw_op_eq(int iSize)            { _kw_return(BorderSize) { kwx.keyValues.BorderSize = iSize;   }); } }  BorderSize   ;
// 
//      --> This allows setting of the key value, which may not be straightforward of require more than one statement to process.
// 
// Example macro with _kw_reteasy #define: 
// 
//      struct { _kw_op_eq(int iSize  )          { _kw_reteasy(BorderSize,iSize )   }  BorderSize;
//
//      --> This is the easy method when an incoming value can be directly assigned to the key, so no code is required.
//          
 
// -----------------------------------------------------------------------------------------------------
// Adding a keyword with multiple types can be done simply by expressing a new overload in the structure
// -----------------------------------------------------------------------------------------------------
//
// Example using form2: Range() which can accept a SIZE or a POINT can be done with -->
//
//    struct { _kw_op_eq(SIZE szRange  )      { _kw_return(Range) { kwx.keyValues.Range = szRange;              }); }
//             _kw_op_eq(POINT pRange  )      { _kw_return(Range) { kwx.keyValues.Range = {pRange.x,pRange.y};  }); }
//    } Range;
//

namespace kw    // Can be namespace or class.  See notes in ckwargs.h
{

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
