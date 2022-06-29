#pragma once

#include "ckwargs.h"

// ---------------------------------------------------------------------------------------------
// Keywords (canonical) class for program usage using packed-parameter style keyword definitions
// ---------------------------------------------------------------------------------------------
// 
// When kw:: is entered, the intellisense will show all available keywords and will also show any comments 
//
// For this example, only the last two functions are commented. 
// 

// Helper Macros

#define _kw_op_eq ckwargs::ckw operator = 
#define _kw_return(_x) return ckwargs::ckw(ckwargs::Keywords::_x, [&](ckwargs::ckw & kwx)
#define _kw_reteasy(_x,_value) { return ckwargs::ckw(ckwargs::Keywords::_x, [&](ckwargs::ckw & kwx) { kwx.keyValues._x = _value;   }); }


// Adding a keyword in this form without helper macros:
// 
//   struct {
//               const ckwargs::ckw operator = (int iSize) 
//                      { return ckwargs::ckw(Keywords::BorderSize, [&](ckwargs::ckw & kwx) { kwx.keyValues.BorderSize = iSize;   }); } 
//          }  BorderSize   ;
// 
// Where the std::function routine sets the value of the key in the constructor.
// 
// With the helper #define macros below, we can simplify the process:
// 
// Example macro with _kw_return #define: 
// 
//      struct { _kw_op_eq(int iSize)            { _kw_return(BorderSize) { kwx.keyValues.BorderSize = iSize;   }); } }  BorderSize   ;
// 
//      --> This allows setting of the key value, which may not be straightforward of require more than one statement to process.
// 
// Example macro with _kw_reteasy #define: 
// 
//      struct { _kw_op_eq(int iSize  )          { _kw_reteasy(BorderSize,iSize )   }  BorderSize;
//
//      --> This is the easy method when an incoming value can be directly assigned to the key, so no code is required.
//          
 
// -----------------------------------------------------------------------------------------------------
// Adding a keyword with multiple types can be done simply by expressing a new overload in the structure
// -----------------------------------------------------------------------------------------------------
//
// Example using form2: Range() which can accept a SIZE or a POINT can be done with -->
//
//    struct { _kw_op_eq(SIZE szRange  )      { _kw_return(Range) { kwx.keyValues.Range = szRange;              }); }
//             _kw_op_eq(POINT pRange  )      { _kw_return(Range) { kwx.keyValues.Range = {pRange.x,pRange.y};  }); }
//    } Range;
//

namespace kw    // Can be namespace or class.  See notes in ckwargs.h
{

    // Sets a Range of iMin to iMax values.
    //
    // This example shows using 1 form for the Range keyword, but could be expanded to other forms, though
    // probably not too useful in the keyword form -- See the kf class below to show the Range() option 
    // used with more than one value (i.e. min, max)
    //
    static struct { _kw_op_eq(std::array<int,2> szRange)  { _kw_return(Range)      { kwx.keyValues.Range      = szRange; }); } }  Range        ;
    static struct { _kw_op_eq(int iSize)                  { _kw_return(BorderSize) { kwx.keyValues.BorderSize = iSize;   }); } }  BorderSize   ;

    // Text keyword is used to send additional text to the function, i.e. function(..parms...,Text("This is some additional text"); 
    // 
    // This example sets "<nullptr>" to the string, so we know it as input as a keyword.  Otherwise, the null can just be sent
    //
    static struct { _kw_op_eq(const char * sText)    _kw_reteasy(Text,sText)          }  Text ;
    static struct { _kw_op_eq(bool bValue)           _kw_reteasy(AddBorder,bValue )   }  AddBorder;

}
