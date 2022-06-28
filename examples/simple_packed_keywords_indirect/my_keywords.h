#pragma once

#include "keyclass.h"

// --------------------------------------------
// Keywords (canonical) class for program usage
// --------------------------------------------
// 
// Only the keywords are displayed.  When kw:: is entered, the intellisense will show all available keywords and will also
// show any comments 
//
// For the example, only the last two functions are commented. 
    
using namespace keyclass;   // Placing this inside kw causes MSVS intellisense to list keyclass members, rather than just
                            // pure keyword members.



namespace kw    // Can be namespace or class.  See notes in keyclass.h
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