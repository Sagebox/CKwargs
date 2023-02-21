#define _ckwargs_inc_check_items
#include "my_keywords.h"

using namespace ckwargs;

// --------------------------------------------------------
// Keywords (canonical) namespace/class/struct Example Code
// --------------------------------------------------------
//
// This file contains code for setting up function-based keywords using the example keywords in keydefs.h.

// Helper Macros.  See examples below. The second Range example shows filling in the keyword value
//                 without using any macros, showing the original form.


#define SetKeyVal(_x,_value) { return ckw(Keywords::_x, [&](ckw & kwx) { kwx.keyValues._x = _value;   }); }
#define SetKeyDirect(_x) { return ckw(Keywords::_x, [&](ckw & kwx) { kwx.keyValues._x = value;   }); }

// Note: for a class/struct version prefix 'ckw' in defOptEq with namespace::, i.e. in this example: 'kw::ckw'

#define defOptEq(x) ckw __##x        :: operator

// --------------------------------------------------
// Named Parameter Functions (i.e. Keyword Functions)
// --------------------------------------------------
//
// Function-Based Keywords offer a lot of flexibility over canonical keywords.
// See my_keyfuncs.cpp for more information


namespace kw    // Can be namespace or class.  See notes in ckwargs.h/
{


    __Range        Range            ;       // defined as kw::__Range when kw is a struct or class.
    __BorderSize   BorderSize       ;
    __Text         Text             ;
    __AddBorder    AddBorder        ;

    // Assignments to key classes. 

    defOptEq(Range       ) = (std::array<int,2> value)  SetKeyDirect(Range);
    defOptEq(BorderSize  ) = (int value)                SetKeyDirect(BorderSize);
    defOptEq(Text        ) = (const char * value)       SetKeyDirect(Text);
    defOptEq(AddBorder   ) = (bool value)               SetKeyDirect(AddBorder);
}
