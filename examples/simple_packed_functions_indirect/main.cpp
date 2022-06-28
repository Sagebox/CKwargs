
// ----------------------------------------------------------------
// CKwargs -- Sagebox C++ Named Parameter and Named Functions Class 
// ----------------------------------------------------------------
//
// Copyright (c) 2022 Rob Nelson, All Rights Reserved. Released under MIT License.  rob@sagebox.org
// 
// ------------------------------------
// simple_packed_functions_indirect.cpp
// ------------------------------------
//
// This file shows a quick example of using CKwargs with packed-parameters to provide a more canonical keyword style,
// in a function-based keyword format vs. keyword assigment, i.e. AddBorder(), Range(1,10), etc.
//
// This version shows calling the function indirectly, so the only exposed, inline templated code processes
// the keywords and calls the main function.  See SomeFunction.h and SomeFunction.cpp
//
// see: simple_packed_keywords_indirect.cpp for a canonical keyword approach, i.e. AddBorder = true, Range = {1,10 }, etc.
//
// also see: simple_packed_functions.cpp showing using the template function code calling the function directly.

#include <stdio.h>
#include "my_keywords.h"
#include "SomeFunction.h"

// ------------
// Main Program
// ------------
//
// Shows using packed-parameter keywords as functions, both using scoped keywords, i.e. kf::AddBorder(),
// as well as plain, unscoped keywords, i.e. AddBorder() by itself.
//
// note: The kf namespace is a user-defined namespace or class for each keyword set.
//
int main()
{
    std::array<int,2> szRange = {40,100};   // Sample incoming Range variable
 
    MyClass obj;    // Sample class object

    // Use a more flexible function format, where function calls are used (the function names are the keywords themselves),
    // and more parameters can be used for keywords (such as Range(min,max), etc.

    obj.SomeFunction("Keyword Functions",kf::Range(100,200), kf::Text("Sample Text 1"), kf::AddBorder(), kf::BorderSize(123)); 
 
    // Basically the same as the first one, but without the kw:: namespace prefix (which puts all of the keywords in the local namespace)
    // and can be useful for multiple calls using the same keywords. 
 
    // Put kf namespace keywords into our function namespace

    using namespace kf;     // For multiple or longer namespaces, namespace kf = <namespace> can be used, 
    
    obj.SomeFunction("Keyword Functions (unscoped)",Range(1,10), Text("Sample Text 2"), AddBorder()); 

    // Call SomeFunction() without any keywords

    obj.SomeFunction("Keyword Functions (no keywords)"); 
}