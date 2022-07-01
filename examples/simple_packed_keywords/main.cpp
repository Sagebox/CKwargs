
// ----------------------------------------------------------------
// CKwargs -- Sagebox C++ Named Parameter and Named Functions Class 
// ----------------------------------------------------------------
//
// Copyright (c) 2022 Rob Nelson, All Rights Reserved. Released under MIT License.  rob@sagebox.org
// 
// --------------------------
// simple_packed_keywords.cpp
// --------------------------
//
// This file shows a quick example of using CKwargs using packed-paramaters to provide a more canonical keyword approach,
// such as AddBorder = true, Range = { 1,10 }, etc.
//
// This version shows calling the function indirectly, so the only exposed, inline templated code processes
// the keywords and calls the main function.  See SomeFunction.h and SomeFunction.cpp
//
// see: simple_packed_functions.cpp for a function-based keyword approach, i.e. AddBorder(), Range(1,10), etc.
//
// also see: simple_packed_keywords.cpp showing using an object-based approach and the calling the function directly.

#include <stdio.h>
#include "my_keywords.h"
#include "SomeFunction.h"

// ------------
// Main Program
// ------------
//
// Shows using packed-parameter keywords, both using scoped keywords, i.e. 'kw::AddBorder = true',
// as well as plain, unscoped keywords, i.e. 'AddBorder = true' by itself.
//
// note: The kw namespace is a arbitrarily user-defined namespace or class for each keyword set.
//
int main()
{
    std::array<int,2> szRange = {40,100};   // Sample incoming Range variable
 
    MyClass obj;    // Sample class object

    // Use a canonical keyword style, with scope keywords

    obj.SomeFunction("Keywords",kw::Range={100,200}, kw::Text="Sample Text 1", kw::AddBorder=true, kw::BorderSize=123); 
 
    // Put kw namespace keywords into our function namespace so we can use the keywords without a scope
    // (only works when kw is a namespace vs. class or struct)

    using namespace kw;     // For multiple or longer namespaces, namespace kw = <namespace> can be used, 
    
    obj.SomeFunction("Keywords (unscoped)",Range={100,200}, Text="Sample Text 2", AddBorder=true, BorderSize=123); 

    // Call SomeFunction() with no keywords

    obj.SomeFunction("Keywords (blank)"); 
}