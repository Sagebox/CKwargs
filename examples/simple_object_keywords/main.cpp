
// ----------------------------------------------------------------
// CKwargs -- Sagebox C++ Named Parameter and Named Functions Class 
// ----------------------------------------------------------------
//
// Copyright (c) 2022 Rob Nelson, All Rights Reserved. Released under MIT License.  rob@sagebox.org
// 
// --------------------------
// simple_object_keywords.cpp
// --------------------------
//
// Shows using keywords in a object-based format that does not use a template.
// 
// --> The only difference between canonical keyword format is using () to encapsulate the 
//     keywords, i.e. MyFunction(parm1,parm2,(keyword1 = value1, keyword2 = value2)).
// 
//     Streamed-object format allows calling to the function via the interface alone, without requiring a
//     template or packed-parameter interface.  For large scale programs, this can be easier to implement.
//
// 
// This file shows a quick example of using CKwargs to provide keywords such as AddBorder = true, Range = { 1,10 }, etc.
// 
// see: simple_object_functions.cpp for function-based keyword approach, i.e. AddBorder=true, Range = { 1,10 }, etc.
//

#include "SomeFunction.h"
#include "my_keywords.h"

// ------------
// Main Program
// ------------
// 
// Two forms are used, using scoped keywords, i.e. kw::AddBorder = true, as well as plain, 
// unscoped keywords, i.e. AddBorder = true by itself.
//
// note: The kw namespace is a user-defined namespace or class for each keyword set.
//
int main()
{
    std::array<int,2> szRange = {40,100};    // Range() is used with two different forms below (array & (int,int))
 
    // Use various keywords to set values in SomeFunction(). 
    // 
    // Note the () at the beginning and end of the keywords assignments. 

    SomeFunction("Keywords",( kw::Range={100,200}, kw::Text="Sample Text 1", kw::AddBorder=true, kw::BorderSize=123 )); 
 
    // Put kw namespace keywords into our function namespace so we can use the keywords without a scope
    // (only works when kw is a namespace vs. class or struct)

    using namespace kw;     // For multiple or longer namespaces, namespace kw = <namespace> can be used, 
    
    SomeFunction("Keywords (unscoped)",( Range={100,200}, Text="Sample Text 2", AddBorder=true, BorderSize=123 )); 

    // Make an Empty call to demonstrate using no keywords

    SomeFunction("No Keywords (blank)"); 

}