#pragma once


// ******************************** Example my_keywords.h file **********************************************************
//
// --------------------------
// Keyword-Style Example File
// --------------------------
// 
// This file shows setting up keyword-style keywords (i.e. AddBorder=true, Range = { 1, 10}, BorderSize=5, etc.)
// 
// See the file my_keyfuncs.h for setting up function-based keywords (i.e. AddBorder, Range(1,10), BorderSize(5)); 
// 
// my_keyfuncs.h and my_keywords.h are generally not meant to be used together -- the idea is to choose which format you
// want for your keywords and use one of these files as a starting template.
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
// ***********************************************************************************************************************

#include "ckwargs.h"

// -------------------------------------------------------------
// Keywords (canonical) namespace/class/struct for program usage
// -------------------------------------------------------------
// 
// When kw:: is entered, the intellisense will show all available keywords and will also show any comments 
//
// For this example, only the last two functions are commented, i.e. kw::Text will show intellisense information
// about the keyword.
// 
//


// Declare namespace for our keywords
// 
// 'kw' is an arbitrarily-named namespace, class, or struct you can set here or include in a class. 
// 
// the 'namespace kw' below can be a struct or a class, and is used as a namespace below
// to use examples where the keyword is unscoped, i.e. 'BorderSize=123' vs. 'kw::BorderSize=123', which
// is not currently possible in C++ with a class or struct.
//
// To use 'namespace kw' as a class or struct, i.e. 'struct kw', change
// 'extern struct' statements to 'static struct' -- a class definition will also require 'public:' as the first declaration.


namespace kw  // rename to whatever fits your program.  Or bring it in as a class/struct into a class.
{

    // Sets a Range of iMin to iMax values.
    //
    // This example shows using 1 form for the Range keyword, but could be expanded to other forms, though
    // probably not too useful in the keyword form -- See the kf class below to show the Range() option 
    // used with more than one value (i.e. min, max)
    //
    extern struct __Range        { ckwargs::ckw operator =(std::array<int,2> szRange); } Range;
    extern struct __BorderSize   { ckwargs::ckw operator =(int iSize);                 } BorderSize;

    // Text keyword is used to send additional text to the function, i.e. function(..parms...,Text("This is some additional text"); 
    // 
    // This example sets "<nullptr>" to the string, so we know it as input as a keyword.  Otherwise, the null can just be sent
    //
    extern struct __Text        { ckwargs::ckw operator =(const char * sText)  ; } Text ;
    extern struct __AddBorder   { ckwargs::ckw operator =(bool bValue)         ; } AddBorder;

};
