
// ----------------------------------------------------------------
// CKwargs -- Sagebox C++ Named Parameter and Named Functions Class 
// ----------------------------------------------------------------
//
// Copyright (c) 2022 Rob Nelson, All Rights Reserved. Released under MIT License.  rob@sagebox.org
// 
// -----------------------------------
// simple_packed_keywords_indirect.cpp
// -----------------------------------
//
// This file shows a quick example of using CKwargs using packed-paramaters to provide a more canonical keyword approach,
// such as AddBorder = true, Range = { 1,10 }, etc.
//
// This version shows calling the function indirectly, so the only exposed, inline templated code processes
// the keywords and calls the main function.  See SomeFunction.h and SomeFunction.cpp
//
// see: simple_packed_functions_indirect.cpp for a function-based keyword approach, i.e. AddBorder(), Range(1,10), etc.
//
// also see: simple_packed_keywords.cpp showing using the template function code in the calling the 
//           function directly.

#include <stdio.h>
#include "my_keywords.h"
#include "SomeFunction.h"

// ------------
// Main Program
// ------------
//
// Shows using packed-parameter keywords, both using scoped keywords, i.e. 'kf::AddBorder = true',
// as well as plain, unscoped keywords, i.e. 'AddBorder = true' by itself.
//
// note: The kw namespace is a user-defined namespace or class for each keyword set.
//
int main()
{
    std::array<int,2> szRange = {40,100};   // Sample incoming Range variable
 
    MyClass obj;    // Sample class object

    // Use a canonical keyword style, with scope keywords

    obj.SomeFunction("Keywords",kw::Range={100,200}, kw::Text="Sample Text 1", kw::AddBorder=true, kw::BorderSize=123); 
 
    // Basically the same as the first one, but without the kw:: namespace prefix (which puts all of the keywords in the local namespace)
    // and can be useful for multiple calls using the same keywords. 
 
    // Put kf namespace keywords into our function namespace

    using namespace kw;     // For multiple or longer namespaces, namespace kw = <namespace> can be used, 
    
    obj.SomeFunction("Keywords (unscoped)",Range={100,200}, Text="Sample Text 2", AddBorder=true, BorderSize=123); 

    // Call SomeFunction() with no keywords

    obj.SomeFunction("Keywords (blank)"); 
}