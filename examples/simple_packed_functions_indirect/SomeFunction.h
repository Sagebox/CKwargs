
// ----------------------------------------------------------------
// CKwargs -- Sagebox C++ Named Parameter and Named Functions Class 
// ----------------------------------------------------------------
//
// Copyright (c) 2022 Rob Nelson, All Rights Reserved. Released under MIT License.  rob@sagebox.org

// --> SomeFunction.h - Sample function using CKwargs keywords
//
//     This is an example of a function using CKwargs paramater-pack keywords where the
//     function interface -- which is using a parameter-pack template -- is abstracted from 
//     the main function, so that only the compilation/translation of the keyword object needs 
//     to be compiled in the interface, allowing the code for the main function to remain in the .cpp file.

#pragma once

#include "keyclass.h"
class MyClass
{
    // The main function we intend to call.  It is abstraced away from the keyword arguments, and
    // is given the resultant keyword information as input
    //
    void SomeFunction(const char * sTitle,const keyclass::KeyValuesPtr & keys);

public:

    // The template interface code for the function.
    //
    // It assembles the keyword values by calling pkw::FillKeyValues(), which
    // links together all keyword objects on the stack.
    //
    // This is then transferred to the main function, which is a private
    // class member and its code does not need to be in the interface.
    //
    template <class... Args>
    void SomeFunction(const char * sTitle, const Args&... kwArgs)
    {
        SomeFunction(sTitle,keyclass::pkw::FillKeyValues(kwArgs...));
    }

};

