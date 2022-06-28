
// ----------------------------------------------------------------
// CKwargs -- Sagebox C++ Named Parameter and Named Functions Class 
// ----------------------------------------------------------------
//
// Copyright (c) 2022 Rob Nelson, All Rights Reserved. Released under MIT License.  rob@sagebox.org
//
// -------------- 
// TestStreamed()
// --------------
//
// Uses the CKwargs class to call the main function (i.e. typical function that would use named-parameters or named-functions).
//
// This uses the streaming-format that combines the keyword elements before the call to the MainFunction(). 
//
// This allows a call directly to the MainFunction, which only needs to have a 'const ckw &' at the end of the function in its declaration,
// and -- as opposed to the packed-parameter format -- does not need any inlined code or templatized code.
//
// The drawback is that the keywords must be streamed together.  They can be used just as keywords, but
// must be enclosed in ().
//
// Keywords must use the ',' format, where the named-functions can use <<, +, and | without the need for the enclosing ()
//
// See examples in the code below.
//
// See the documentation on named-parameters vs. named-parameter-functions (i.e. Range = {1,10} vs. Range(1,0), etc.)
//

#include "my_keywords.h"

// External Main Function we want to call -- usually the function definition would be in the header and class interface.

void MainFunction(const char * sTitle, const ckw & kwx);

void TestStreamed()
{
    std::array<int,2> szRange = {40,100};   // A Sample range.  For the named-parameter (i.e. keyword) format, we need
                                            // to express the range as one object.  In the named-function format, we can 
                                            // use various methods, including multiple parameters.
 
    // Use keyword format -- ',' must be used enclosed by () to stream together elements

    MainFunction("Keywords",( kw::Range = szRange, kw::Text = "Sample Text 1", kw::AddBorder = true)); 
    
    // Use a more flexible function format, using "<<" and also "|" (they are exactly the same)
    // These do not require the extra () surrounging the keywords

    MainFunction("Functions (using <<)",kf::Range(100,200) << kf::Text("Sample Text 2") << kf::AddBorder() << kf::BorderSize(123));
    MainFunction("Functions (using |)" ,kf::Range(100,200) | kf::Text("Sample Text 2") | kf::AddBorder() | kf::BorderSize(123));

    // Call without using the kw:: prefix -- the same as the first one, but without the kw:: namespace prefix
    // and can be useful for multiple calls using the same keywords. 

    // Put kw namespace keywords into our function namespace

    using namespace kw;     // Put kw namespace keywords into our function namespace

    // Use a keyword version with ',' -- named functions can be used here, too with "<<", "|" , etc.
 
    MainFunction("Keywords (with no namespace prefix)",( Range = {1,10}, Text = "Sample Text 3", BorderSize = 567)); 
}
