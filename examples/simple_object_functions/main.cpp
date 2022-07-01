
// ----------------------------------------------------------------
// CKwargs -- Sagebox C++ Named Parameter and Named Functions Class 
// ----------------------------------------------------------------
//
// Copyright (c) 2022 Rob Nelson, All Rights Reserved. Released under MIT License.  rob@sagebox.org
// 
// -----------------------------
// simple_object_functions.cpp
// -----------------------------
//
// Shows using function-based keywords (as opposed to keywords) in a object format that does not use a template, but 
// a compiled, streamed object for the keywords.
// 
// --> The only difference between a canonical keyword format and this method is using () to encapsulate the 
//     entire keyword list, i.e. MyFunction(parm1,parm2,( keyfunc1(value1), keyfunc2(value2) )).
// 
//     Also, this form may be used, without any surrounding () to use the keywords more directly:
// 
//          MyFunction(parm1,parm2,keyfunc1(value1) << keyfunc2(value2)).
//          MyFunction(parm1,parm2,keyfunc1(value1) + keyfunc2(value2)).
//          MyFunction(parm1,parm2,keyfunc1(value1) | keyfunc2(value2)).
// 
//     Any form above works, and the surrounding () are only needed when the ',' is used as the mai
//     form of keyword separation (i.e. operator). 
// 
//     This Object format allows calling to the function via the interface alone, without requiring a
//     template or packed-parameter interface.  For large scale programs, this can be easier to implement.
//
// 
// This file shows a quick example of function-based keywords (i.e. named-parameter functions) via CKwargs
// using a streamed ojbect format to provide keywords such as AddBorder(), Range( 1,10 ), etc.
// 
// see: simple_object_keywords.cpp for a more canonical, assigned keyword approach, i.e. AddBorder=true, Range = { 1, 10 }, etc.
//

#include "SomeFunction.h"
#include "my_keyfuncs.h"

// ------------
// Main Program
// ------------
// 
// Two forms are used, using scoped keywords, i.e. kf::AddBorder(), as well as plain, 
// unscoped keywords, i.e. AddBorder() by itself.
//
// note: The kf namespace is an arbitrarily user-defined namespace or class for each keyword set.
//
int main()
{
    std::array<int,2> szRange = {40,100};    // Range() is used with two different forms below (array & (int,int))
 
    // Use various keywords to set values in SomeFunction(), using function-based keywords
    // 
    // Note the () at the beginning and end of the keywords assignments. 

    SomeFunction("Keyword Functions",( kf::Range(100,200), kf::Text("Sample Text 1"), kf::AddBorder(), kf::BorderSize(123) )); 
 
    // Put kf namespace keywords into our function namespace so we can use the keywords without a scope
    // (only works when kf is a namespace vs. class or struct)

    using namespace kf;     // For multiple or longer namespaces, namespace kf = <namespace> can be used, 
    
    SomeFunction("Keyword Functions (unscoped)",( Range(100,200), Text("Sample Text 2"), AddBorder(), BorderSize(123) )); 

    // Make an Empty call to demonstrate using no keywords

    SomeFunction("No Keywords (blanke)"); 

}