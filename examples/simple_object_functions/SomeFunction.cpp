
#include "SomeFunction.h"
#include <cstdio>

using namespace ckwargs;

// MainFunction function using keywords.
// 
// As input is the ckw class object "kwx". 
// 
// The first line called kwx.FillKeyValues() link together keyword objects (and does
// not move or create memory), returning a structure with pointers to the keywords used
// (or nullptr for keywords not used).
//
// These values may be accessed directly or through the ckw::Get() functions used in the code.

void SomeFunction(const char * sTitle, const ckw & kwx)
{
    auto keys = kwx.FillKeyValues();        // Link together all 

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
