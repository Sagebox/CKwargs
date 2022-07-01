#pragma once

// ---------------------------
// Example keyword definitions
// ---------------------------

// Fill in the macros below for keyword name and keyword type.
// This sample file has 4 entries as examples.

// --> Using Multiple Keywords Sets in the Same Program
// 
//     Some #defines are used, which are necessarily included in the keyword interface, which means
//     they become global macros, hence the "_ckwargs_" prefix to make them unique. 
//
//     For programs that want to use multiple keyword sets, 
//     the first 4 #defines will need to be unique, such as basing the prefix on the namespace for each keyword set.
//
//     Another option is to remove the #defines (nothing else exposed but the first 4 #defines below)
//     and add each keyword name for each of the 4 sections where they are used.
// 
//     The using statements and CheckItem macros are not exposed pubilicy and don't need to be changed for 
//     other keywords sets.
//

// For a program to use functions using cwargs, it only needs to include the single my_keywords.h/my_keyfuncs.h, depending on the
// form being used.  The file included will set up all keywords for the program. 

namespace ckwargs
{

// define the keyword names used.  These are not the keywords used by the user (these come from my_keywordsh and/or my_keyfuncs.h).
// The keys below are used by the functions using the keywords as symblic names such as key.Range, key.Text, etc.

#define _ckwargs_key1 Range                  // Example Range keyword or function, i.e. Range = {5,10} or Range(5,10)
#define _ckwargs_key2 Text                   // i.e. Text = "Hello World" or Text("Hello World")
#define _ckwargs_key3 BorderSize             // i.e. BorderSize = 10, or BorderSize(10)
#define _ckwargs_key4 AddBorder              // i.e. AddBorder = true, AddBorder = false, or AddBorder() or AddBorder(true) or AddBorder(false)


// Set the type for each keyword. Note that for this example, <array> is included in ckwargs.h to define array for use here.

using  _ckwargs_type1 = std::array<int,2>    ;   // i.e. std::array<int,2> Range, etc.
using  _ckwargs_type2 = const char *         ;   // i.e. const char * Text
using  _ckwargs_type3 = int                  ;   // i.e. int BoderSize
using  _ckwargs_type4 = bool                 ;   // i.e. bool AddBorder

    
// These sections don't need to be changed for keywords, but need to have the same number of entries as keywords defined above. 

    enum class Keywords 
    {   
        _ckwargs_key1, 
        _ckwargs_key2, 
        _ckwargs_key3, 
        _ckwargs_key4, 
    };

#ifdef _ckwargs_inc_check_items // Limit exposure to _kw_CheckItems macro so we can re-use it with multiple ckwargs modules
                                // (i.e. this #define never needs to be changed for multiple ckwargs uses in the same module)

    #define _ckwargs_CheckItems     CheckItem(_ckwargs_key1    );    \
                                    CheckItem(_ckwargs_key2    );    \
                                    CheckItem(_ckwargs_key3    );    \
                                    CheckItem(_ckwargs_key4    );

#endif
    // -----------------
    // Key Value storage
    // -----------------
    //  
    // This is currently set as a union.  It can be a struct to allow container items with constructors/destructors/etc., but
    // is not recommended.  It's recommended to use references as the input for the keywords for class objects. 
    
    union KeyValues     // Optionally a struct for more flexibility (and headaches)
    {
        _ckwargs_type1         _ckwargs_key1 ;
        _ckwargs_type2         _ckwargs_key2 ;    
        _ckwargs_type3         _ckwargs_key3 ;
        _ckwargs_type4         _ckwargs_key4 ;
    };

    // ------------
    // KeyValuesPtr
    // ------------
    // 
    // Used when calling KillKeyValues() and not part of the keyword class (i.e. it's put on the stack of the function using
    // the keywords)
    //  
    // This is the exact format as KeyValues, but as pointers.  
    //
     // See the Get() functions for shortcuts on retrieving values.
    //
    struct KeyValuesPtr
    {
        _ckwargs_type1  * _ckwargs_key1 ;
        _ckwargs_type2  * _ckwargs_key2 ;
        _ckwargs_type3  * _ckwargs_key3 ;
        _ckwargs_type4  * _ckwargs_key4 ;
    };
} // namespace ckwargs