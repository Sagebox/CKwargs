
// ----------------------------------------------------------------
// CKwargs -- Sagebox C++ Named Parameter and Named Functions Class 
// ----------------------------------------------------------------
//
// Copyright (c) 2022 Rob Nelson, All Rights Reserved. Released under MIT License.  rob@sagebox.org
// 
// ---------------------------
// simple_packed_keywords.cpp
// ---------------------------
//
// This file shows a quick example of using CKwargs with packed-parameters to provide a more canonical keyword style,
// such as AddBorder(), Range(1,10), etc.
// 
// see: simple_packed_functions.cpp for a function-based keyword approach, i.e. AddBorder(), Range(1,10), etc.
//
// --> Note: This file contains both the function being called with the keyword as well as the call itself (in main)
//           This is to show the pure form of the function.  
// 
// also see: simple_packed_keywords_indirect.cpp shows a simpler, more normative use where the 
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
// Shows using packed-parameter keywords, both using scoped keywords, i.e. kf::AddBorder = true,
// as well as plain, unscoped keywords, i.e. AddBorder = true by itself.
//
// note: The kw namespace is a user-defined namespace or class for each keyword set.
//
int main()
{
    std::array<int,2> szRange = {40,100};   // Sample incoming Range variable

    // Use a canonical keyword style, with scoped keywords

    SomeFunction("Keywords",kw::Range={100,200}, kw::Text="Sample Text 1", kw::AddBorder=true, kw::BorderSize=123); 
 
    // Basically the same as the first one, but without the kw:: namespace prefix (which puts all of the keywords in the local namespace)
    // and can be useful for multiple calls using the same keywords. 
 
    // Put kf namespace keywords into our function namespace

    using namespace kw;     // For multiple or longer namespaces, namespace kw = <namespace> can be used, 
    
    SomeFunction("Keywords (unscoped)",Range={100,200}, Text="Sample Text 2", AddBorder=true, BorderSize=123); 

    // Call SomeFunction() with no keywords.

    SomeFunction("No Keywords (blank)");
}