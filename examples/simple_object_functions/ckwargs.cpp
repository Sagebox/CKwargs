
// ----------------------------------------------------------------
// CKwargs -- Sagebox C++ Named Parameter and Named Functions Class 
// ----------------------------------------------------------------
//
// Copyright (c) 2022 Rob Nelson, All Rights Reserved. Released under MIT License.  rob@sagebox.org
//
// --------------------------------
// ckwargs.cpp -- main CKwargs code
// --------------------------------
//
// This code base is very small, cosisting of 20-25 lines, but is very extensible and can be used in many ways. 
// Much of the formation of the class is the data structures and inlined functions in ckwargs.h
// 
// The basic idea behind the code is how it handles compiling the keywords, either through the packed-parameter
// format or streamed format.  Either way, the process is the same
// 
// The elements are compiled as they are streamed together -- in the packed-parameter format, the function
// FillKeyValues(Args&... args) creates a ckw object that has streamed the keywords together.
// 
// When the individual ckw objects are streamed together, they are not copied -- since they are 
// all safely on the stack, each ckw object contains the keyword data for only one value.   
// 
// A linked-list is created to chain them together so when FillKeyValues() (in ckw class)
// is called, a keyword pointer list can be created to define keyword pointers for keywords
// that were used -- this is created on the stack of the caller.
// 
// -------------------------------
// Speed and Memory Considerations
// -------------------------------
// 
// This process was created for use with Sagebox C++ code, where it is important to use as little memory as 
// possible, and even more important to use as little time as possible.  
// 
// Also in consideraton is not constantly copying memory.
// 
// This methodology is written around the idea that the entire keyword process is fast, uses little memory,
// and can be used in more-or-less real-time situations.
// 
// Therefore, the STL usage is limited in favor of faster, less memory-intensive code, with no
// memory allocatioins -- the STL can add a lot of code per-element, copy lots of memory, and will
// allocate memory a the drop of a hat.
// 
// 
// See my_keywords.h for code that is generated for the keywords (and is not part of the CKwargs class)
//

#define _ckwargs_inc_check_items        // Expose CheckItems macro for just this file

#include "ckwargs.h"
#include <cstring>

#ifdef _MSC_VER 

// Turn off some MSVC warnings that, while generally useful, also cause inefficient code
// for routines that are focused towards not wasting processor time. 
//
// Specifically, warnings about uninitialized values that are purposely left uninitialized, both locally on the stack
// and in class definitions

#pragma warning( push )
#pragma strict_gs_check(off)

#endif

namespace ckwargs      // namespace name is arbitrary
{
    // Constructor for packed-parameter start point to create and compile ckw keywords
    //
    ckw::ckw()
    {
        package.key     = (Keywords) -1;    // Not really needed, should probably be removed.
        package.pData   = nullptr;
    }

    // Constructor called by keyword functions in my_keywords.h (or whichever keyword function file)
    //
    ckw::ckw(Keywords key,std::function<void(ckw &)> const & fFunc)
    {
        package.key     = key;
        package.pData   = this;

        if (fFunc) fFunc(*this);
    }
  
    // Link the incoming ckw object to the current one, but con't copy it.
    //
    ckw & ckw::operator << (const ckw & Opt)
    {
        if (pLast) pLast->pNext = &Opt;
        else pNext = &Opt;
        pLast = const_cast<ckw *>(&Opt);

        return *this;
    }

    // Move constructor should only be used when assigning a keyword.
    // afaik -- this is never called and is probably not needed.
    //          however, for various debug environments, or perhaps different compilers,
    //          it might.
    //
    //          note: because it has never been called in testing, it was not been thoroughly tested.
    //
    ckw::ckw(ckw && p2) noexcept 
    {
        // Should probably throw an error here until it is thoroughly tested
        // in multiple environments, so removing it is up to the user.

        memcpy(this,&p2,sizeof(ckw));           // This should probably be changed to specific items
        if(package.pData) package.pData = this; // transfer the memory location, but only if it exists
    }
       
    // FillKeyValues() -- Go through compiled, ckw class linked list
    // and save pointer to values of used keywords (otherwise pointers are nullptr)
    //
    // note: This is the ckw class version.  The ckwargs version for packed parameters
    //       (that then calls this version) is in ckwargs.h
    //
    const KeyValuesPtr ckw::FillKeyValues() const
    {
        if (!this) return KeyValuesPtr{};

    #define CheckItem(_x) case Keywords::_x : kValues._x = &keyClass->keyValues._x;      break;
  
        KeyValuesPtr kValues{};     // Initialize all pointers to nullptr

        const ckw * pckw = this;    // Start at the top (by definition, we call with the top-level
                                    // ckw class object)

        // Go through the linked list and save any pointers we find.

        while (pckw)
        {
            auto key = pckw->package.key;
            auto keyClass = pckw->package.pData;

            if (keyClass)
                switch(key) 
                {
                    _ckwargs_CheckItems; // Check user-defined keywords as defined in ckwargs.h
                }
            pckw = pckw->pNext;
        }
        return kValues;
    }

} // namespace ckwargs

#ifdef _MSC_VER 
#pragma warning( pop )
#endif