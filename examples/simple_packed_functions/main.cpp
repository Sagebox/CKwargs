
// ----------------------------------------------------------------
// CKwargs -- Sagebox C++ Named Parameter and Named Functions Class 
// ----------------------------------------------------------------
//
// Copyright (c) 2022 Rob Nelson, All Rights Reserved. Released under MIT License.  rob@sagebox.org
// 
// ---------------------------
// simple_packed_functions.cpp
// ---------------------------
//
// This file shows a quick example of using CKwargs with packed-parameters in a function-based keyword format 
// vs. a more canonical keyword assigment, i.e. AddBorder(), Range(1,10), etc.
//
// This version shows calling the function indirectly, so the only exposed, inline templated code processes
// the keywords and calls the main function.  See SomeFunction.h and SomeFunction.cpp
//
// see: simple_packed_keywords.cpp for a more canonical assignment-based keyword configuration (i.e. AddBorder=true, etc.)
// see: simple_streamed_functions.cpp for an object-based approach that can be simpler to use.
//
#include <stdio.h>
#include "my_keyfuncs.h"
#include "SomeFunction.h"

// ------------
// Main Program
// ------------
//
// Shows using packed-parameter keywords as functions, using scoped keywords, i.e. kf::AddBorder(),
// as well as plain, unscoped keywords, i.e. AddBorder() by itself.
//
// note: The kf namespace is an arbitrarily user-defined namespace or class for each keyword set.
//
int main()
{
    std::array<int,2> szRange = {40,100};    // Range() is used with two different forms below (array & (int,int))
 
    MyClass obj;    // Sample class object
        
    // Use a more flexible function format, where function calls are used (the function names are the keywords themselves),
    // and more parameters can be used for keywords (such as Range(min,max), etc.

    // intellisys shows "void SomeFunction(const char * sTitle,const Args & ...args)" when "obj.SomeFunction(" is typed.

    obj.SomeFunction("Keyword Functions",kf::Range(100,200), kf::Text("Sample Text 1"), kf::AddBorder(), kf::BorderSize(123)); 
 
    // Put kf namespace keywords into our function namespace so we can use the keywords without a scope
    // (only works when kf is a namespace vs. class or struct)

    using namespace kf;     // For multiple or longer namespaces, namespace kf = <namespace> can be used, 
    
    obj.SomeFunction("Keyword Functions (unscoped)",Range(1,10), Text("Sample Text 2"), AddBorder()); 

    // Call SomeFunction() without any keywords

    obj.SomeFunction("Keyword Functions (no keywords)"); 
}