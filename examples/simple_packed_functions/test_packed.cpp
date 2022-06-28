
// ----------------------------------------------------------------
// CKwargs -- Sagebox C++ Named Parameter and Named Functions Class 
// ----------------------------------------------------------------
//
// Copyright (c) 2022 Rob Nelson, All Rights Reserved. Released under MIT License.  rob@sagebox.org
//
// ------------ 
// TestPacked()
// ------------
//
// Uses the CKwargs class to call the main function (i.e. typical function that would use named-parameters or named-functions).
//
// This uses the packed-format that allow more a more canonical form of named-parameters (i.e. keywords) and named-parameter functions
// 
// ------------------------------------------
// MainFunction() and MainFunction_Indirect()
// ------------------------------------------
//
// Since a packed parameter template is used, the first function called must be a templated funciton in the form of MainFunction() below, and the code
// must appear in the interface, i.e. as an inline set of code in the interface.
// 
// In this example, the Main Function is renamed tpo MainFunction_Indirect() and the MainFunction is now the template function.
//
// This template function then calls ckw::FillKeyValues() with the packed parameters (kwArgs), which compiles
// the keyword pointer struct, which it then sends to MainFunction_Indirect()
//
// The main function can just accept the kwArgs argument, but must be inlined as code. 
// 
// ----------------------------------------
// Using Canonical Keywords (and functions)
// ----------------------------------------
//
// Even though it is either two-step process, or an exposed & inlined function in the interface,
// it is nice to be able to used canonical-style keywords and keyword functions, as they
// act and appear as regular code.
//
// For large-scale programs that may not want to have a lot of indirection or exposed code, 
// the streaming-based version may be a good option, where the keywords are identical and only 
// need to be wrapped in a () (i.e. MFunction(1234, ( Range={1,10}, AddBorder=true )), and otherwise
// work exactly the same.


#include "my_keywords.h"

void MainFunction_Indirect(const char * sTitle, const KeyValuesPtr & keys);

// Main function proxy, which then calls the 'real' function as MainFunction_Indirect()
//
// This function is here because it is only referred to here.  However, as a general function,
// this would need to appear in the .h file interface as-as, which is why it called the main function
// indirectly, so the main function does not need to be coded in the .h file interface.
//
template <class... Args>
void MainFunction(const char * sTitle, const Args&... kwArgs)
{
    // Call the actual function we mean to call

    MainFunction_Indirect(sTitle,ckw::FillKeyValues(kwArgs...));  // canonically expressed as std::forward<Args>(kwArgs)...
}


void TestPacked()
{
    std::array<int,2> szRange = {40,100};
 
    // Use keyword format -- ',', which look and act as canonical keywords

    MainFunction("Keywords (packed)",kw::Range = szRange, kw::Text = "Sample Text 1", kw::AddBorder = true); 

    // Use a more flexible function format, where function calls are used (the function names are the keywords themselves),
    // and more parameters can be used for keywords (such as Range(min,max), etc.


    MainFunction("Functions (packed)",kf::Range(100,200), kf::Text("Sample Text 2"), kf::AddBorder(), kf::BorderSize(123)); 
 
    // Basically the same as the first one, but without the kw:: namespace prefix (which puts all of the keywords in the local namespace)
    // and can be useful for multiple calls using the same keywords. 
 
    // Put kw namespace keywords into our function namespace

    using namespace kw;     // For multiple or longer namespaces, namespace kw = <namespace> can be used, 
    
    MainFunction("Keywords (with no namespace prefix)",Range = {1,10}, Text = "Sample Text 3", BorderSize = 567); 
}