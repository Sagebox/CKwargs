
// ----------------------------------------------------------------
// CKwargs -- Sagebox C++ Named Parameter and Named Functions Class 
// ----------------------------------------------------------------
//
// Copyright (c) 2022 Rob Nelson, All Rights Reserved. Released under MIT License.  rob@sagebox.org
// 
// 
// -----------------
// MainFunction file
// -----------------
//  
//      The function below MainFunction (and MainFunction_Indirect) are an example of the target function called using 
//      named-parameters (keyword) or name-functions (keyfuncs)
//
//      MainFunction() and MainFunction_Indirect() are identical except for the prototype and 
//      code in MainFunction() that retreives the keyword. 
// 
//      MainFunction_Indirect() differs only in that FillKeyWords() are called in the Parameter-Packed Template
//      function that must exist as inlined code in the interface and cannot exist only in the code base.
// 
// -------------------
// C++ and C++14 Usage
// -------------------
// 
// This example uses std::optional.  If keyword_cpp17_support is not set in keyclass.h, this is omitted.
// 
// -----
// Notes
// -----
// 
// Once the function is called FillKeyValues() is called which returns a structure of pointers
// that either contain the address of the keyword value or nullptr if the keyword was not specified.
// 
// Use ckw::Get() shortcuts to retrieve values as std::optional the value_or_default depending on whether the keyword
// was used.
// 
// Otherwise, the values in the structure turned by FillKeyValues() can be retreived directly, which are 
// pointers by default, containing nullptr for keywords that were not specified, or pointers to the keyword value.
// 
//
// 
// --> MainFunction()
//
//      The function MainFunction() is the main function when using streamed-parameters, since these can be used to call 
//      the function directly.
//
//      MainFunction() example calls:
//      
//           MainFunction("This is a Test",( Range={1,10}, AddBorder=True, BorderSize=10, Text="This is some text" ));
//      
//               --> The above form is the ',' based form that is between () so that we can stream together the ckw objects
//      
//           MainFunction("This is a Test", ( Range(1,10), AddBorder(), BorderSize(10), Text("This is some text" ));
//           MainFunction("This is a Test", Range(1,10) << AddBorder() << BorderSize(10) << Text("This is some text" ));
//           MainFunction("This is a Test", Range(1,10) + AddBorder() + BorderSize(10) + Text("This is some text" ));
//           MainFunction("This is a Test", Range(1,10) | AddBorder() | BorderSize(10) | Text("This is some text" ));
//      
//               --> The above forms can be used in the named-function style -- only the ',' format needs the enclosing ()
//      
// --> MainFunction_Indirect():
//
//       The function MainFunction_Indirect() is the main function when using packed parameters, which allow the canonical 
//       form of keywords, which can be nicer to use and look at.
//
//       However, these can only call the main function indirectly, as the MainFunction() call must be a template call in the format
//
//           template <class... Args>
//           void MainFunction(const char * sTitle, const Args&... kwArgs)
//
//       which then calls the MainFunction_Indirect() after calling FillKeyValues() to process the keywords and remove the 
//       packed parameter template.
//
//       MainFunction_Indirect() example calls:
//
//           MainFunction("This is a Test",Range={1,10}, AddBorder=True, BorderSize=10, Text="This is some text");
//
//               --> This is the same as the above example, but without the enclosing (), allowing a canonical
//                   named-parameter or keyword style.
//
//           MainFunction("This is a Test",Range(1,10), AddBorder(), BorderSize(10), Text("This is some text");
//   
//               --> Named-Function version, which can be more flexible.
//                
// ----------------------------------------------------------------------
// The Biggest Advantage of Using the Streaming-Style of Named-Parameters
// ----------------------------------------------------------------------
//
// While using packed-parameters allows canonical style keywords and key-functions, the interface to the function
// must exist as inlined code in the class header, requiring exposed interface code as well as splitting the main function
// into two parts.
//
// For large scale programs, this can be a little hard to deal with.
//
// The streaming-style allows direct calls to the function as well as privatizing all code, with only the
// need for the regular function prototype that includes a 'const & ckw' at the end.

// Include the keyclass -- note that the namespace for the keywords is not included here. It is not necessary, and 
//                         when namespaces are used (instead of classes) can generate extra code if the code is in the interface.

#include "keyclass.h"

using namespace keyclass;

// MainFunction called directly with streaming-format of CKwargs
//
// MainFunction() could just call MainFunction_Indirect() after the first line of code.
// This isn't done here to show the difference between the two styles, and since 
// one style would be in use, MainFunction_Indirect() wouldn't otherwise exist.
//
void MainFunction(const char * sTitle, const ckw & kwx)
{
    auto keys = kwx.FillKeyValues();

    printf("\n%.*s\n", 25+(int) strlen(sTitle), "------------------------------------------------------------------------------");
    printf("Keyword Named Parameters %s\n",sTitle);
    printf("%.*s\n\n", 25+(int) strlen(sTitle), "------------------------------------------------------------------------------");

    // Get the keyword values.  All calls (except iBorderSize) return either the value or a prototype if the keyword
    // wasn't specified.  iBorderSize returns a std::optional since no default is specified.

    auto Range          = ckw::Get(keys.Range,{0,0}); 
    auto sText          = ckw::Get(keys.Text,(const char *) nullptr);   // (const char *)  due to typless nullptr
#ifdef keyword_cpp17_support
    auto iBorderSize    = ckw::Get(keys.BorderSize);                    // This comes back as a std::optional since there is no default
#endif
    bool bAddBorder     = ckw::Get(keys.AddBorder,false); 

    // Print out values, some of which are keyword values and some defaults where keywords were
    // not used.  
    //
    // In the case of BorderSize, the optional is looked at to determine of the keyword was used.

    printf("Range      = (%d,%d)\n",Range[0],Range[1]); 
    printf("Text       = %s\n",sText);
    printf("AddBorder  = %s\n",bAddBorder ? "True" : "False");

#ifdef keyword_cpp17_support
    if (iBorderSize) printf("BorderSize = %d\n",*iBorderSize);
    else printf("Border Size was not used as a keyword.\n"); 
#else
    printf("BorderSize not evaluated since keyword_cpp17_support was not specified in keyclass.h\n");
#endif
}

// MainFunction called indirectly with parameter packed version allowing canonical-like keywords (see test-packed.cpp)
//
void MainFunction_Indirect(const char * sTitle, const KeyValuesPtr & keys)
{
    printf("\n%.*s\n", 25+(int) strlen(sTitle), "------------------------------------------------------------------------------");
    printf("Keyword Named Parameters %s\n",sTitle);
    printf("%.*s\n\n", 25+(int) strlen(sTitle), "------------------------------------------------------------------------------");

    // Get the keyword values.  All calls (except iBorderSize) return either the value or a prototype if the keyword
    // wasn't specified.  iBorderSize returns a std::optional since no default is specified.

    auto Range          = ckw::Get(keys.Range,{0,0}); 
    auto sText          = ckw::Get(keys.Text,(const char *) nullptr);   // (const char *)  due to typless nullptr
#ifdef keyword_cpp17_support
    auto iBorderSize    = ckw::Get(keys.BorderSize);                    // This comes back as a std::optional since there is no default
#endif
    bool bAddBorder     = ckw::Get(keys.AddBorder,false); 

    // Print out values, some of which are keyword values and some defaults where keywords were
    // not used.  
    //
    // In the case of BorderSize, the optional is looked at to determine of the keyword was used.

    printf("Range      = (%d,%d)\n",Range[0],Range[1]); 
    printf("Text       = %s\n",sText);
    printf("AddBorder  = %s\n",bAddBorder ? "True" : "False");

#ifdef keyword_cpp17_support
    if (iBorderSize) printf("BorderSize = %d\n",*iBorderSize);
    else printf("Border Size was not used as a keyword.\n"); 
#else
    printf("BorderSize not evaluated since keyword_cpp17_support was not specified in keyclass.h\n");
#endif
}

