
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
// This file shows a quick example of using CKwargs with packed-parameters to provide a more canonical keyword style,
// in a function-based keyword format vs. keyword assigment, i.e. AddBorder(), Range(1,10), etc.
// 
// see: simple_packed_keywords.cpp for a canonical, assigned keyword approach, i.e. AddBorder=true, Range = { 1,10 }, etc.
//
// --> Note: This file contains both the function being called with the keyword as well as the call itself (in main)
//           This is to show the pure form of the function.  
// 
// also see: simple_packed_functions_indirect.cpp shows a simpler, more normative use where the 
//           Function and template-based Interface are separated.

#include <stdio.h>
#include "my_keywords.h"

using namespace ckwargs;

// Example function called indirectly with parameter-packed version allowing more canonical-like keywords

template <class... Args>
void SomeFunction(const char * sTitle, const Args&... kwArgs)
{
    auto keys = pkw::FillKeyValues(kwArgs...);

    printf("\nIncomingText: %s\n\n",sTitle);

    // Get the keyword values.  All calls (except iBorderSize) return either the value or a prototype if the keyword
    // wasn't specified.  iBorderSize returns a std::optional since no default is specified.

    auto Range          = ckw::Get(keys.Range,{0,0}); 
    auto sText          = ckw::Get(keys.Text,(const char *) nullptr);   // (const char *)  due to typless nullptr
    auto iBorderSize    = ckw::Get(keys.BorderSize);                    // This comes back as a std::optional since there is no default

    bool bAddBorder     = ckw::Get(keys.AddBorder,false); 

    // Print out values, some of which are keyword values and some defaults where keywords were
    // not used.  
    //
    // In the case of BorderSize, the optional is looked at to determine of the keyword was used.

    printf("Range      = (%d,%d)\n",Range[0],Range[1]); 
    printf("Text       = %s\n",sText);
    printf("AddBorder  = %s\n",bAddBorder ? "True" : "False");

    if (iBorderSize) printf("BorderSize = %d\n",*iBorderSize);
    else printf("Border Size was not used as a keyword.\n"); 
}

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
   std::array<int,2> szRange = {40,100};
    
    // Use a more flexible function-baed keyword format, where function calls are used (the function names are the keywords themselves),
    // and more parameters can be used for keywords (such as Range(min,max), etc.

    SomeFunction("Keyword Functions",kf::Range(100,200), kf::Text("Sample Text 1"), kf::AddBorder(), kf::BorderSize(123)); 
 
    // Basically the same as the first one, but without the kf:: namespace prefix (which puts all of the keywords in the local namespace)
    // and can be useful for multiple calls using the same keywords. 
 
    // Put kf namespace keywords into our function namespace

    using namespace kf;     // For multiple or longer namespaces, namespace kf = <namespace> can be used, 
    
    SomeFunction("Keyword Functions (unscoped)",Range(1,10), Text("Sample Text 2"), AddBorder()); 

    // Call the function with no keywords.

    SomeFunction("Keyword Functions (no keywords)");
}