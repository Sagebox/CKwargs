# CKwargs
C++ Named-Parameter Keywords and Named-Parameter Functions

### (In-Progress Version)

CKwargs is a light, efficient class to enable using canonical keywords (aka named-parameters) in C++, such as with this example:

## Canonical Keywords (keyword=value)

```C++
DrawBox(x,y,size,Color="Red", Angle=75, Opacity=50, Skew={10,-10});
```
CKwargs works with canonical keywords, such as `Angle=75` as shown above, but also supports function-based keywords.

### Function-Based Keywords

Function-based keywords are another way of expressing keywords, which can be more flexible and more powerful.  They can use more than one parameter, are easier to see with the intellisense, as well as some other additives.



### Example using Function-Based Keywords (aka named-parameter functions)


```C++
DrawBox(x,y,size,Color("Red") ,Angle(75), Opacity(50), Skew(10,-10));
```


Even though the canonical keyword form (i.e. `Range=123` vs. `Range(123)`) can be more compelling, this is the form used in [Sagebox C++ GUI tools](https://github.com/Sagebox/Sagebox), because it is more flexible and easier to work with for larger projects.

See the section below, entitled [Function-Based Keywords (aka C++ named-parameter functions)](#function-based-keywords-aka-c-named-parameter-functions) for more information and examples.


## Table of Contents
- [Keywords are Necessary in Today's Projects](#keywords-are-necessary-in-todays-projects)
- [DrawBox(int ix,int y,int size) example](#drawboxint-ixint-yint-size-example)
  - [Keywords to the Rescue](#keywords-to-the-rescue)
- [A Note About Scoped Keywords vs. Unscoped Keywords](#a-note-about-scoped-keywords-vs-unscoped-keywords)
- [Mutiple Types with the Same Keyword](#mutiple-types-with-the-same-keyword)
- [Using CKwargs from the Called Function](#using-ckwargs-from-the-called-function)
  - [Packed-Parameter Usage (default usage)](#packed-parameter-usage-default-usage)
   -[Object-Based version Usage](#object-based-version-usage)
- [Direct Access vs. Get() functions](#direct-access-vs-get-functions)
 
## Other Items
- [Function-Based Keywords (aka C++ named-parameter functions)](#function-based-keywords-aka-c-named-parameter-functions)
- [Packed-Parameters vs. Stream-Object Keyword formats](#packed-parameters-vs-stream-object-keyword-formats)
  - [Packed-Parameters](#packed-parameters)
  - [Object-Based](#object-based)
- [Requirements and Compiler Support](#requirements-and-compiler-support)
  - [A Note About Cpmpiler Warnings](#a-note-about-compiler-warnings)
- [C++ 11 and C++ 14 Support](#c-11-and-c-14-support)
- [Intallation and Implementation](#installation-and-implementation)
- [MIT License](#mit-license)
- [Support](#support)


## Keywords are Necessary in Today's Projects

Keywords in general programming and function usage in C++ are becoming much more important and necessary.  Sadly, C++ has still to adopt a named-parameter/keyword format, 
and there doesn't appear to be one on the horizon.

## DrawBox(int ix,int y,int size) example

Lets say we want to draw a square.  We want to have a lot of power behind it, but don't want to put a large number of options in the protoype, or, worse,
have to create a "DrawBox" object and make a number of calls end then "show" the Box.  We want to affect the box options and attributes on the call, so it can perform
these tasks before it creates the box, completely obviating the need to return an object or anything at all.

While the Box has its defaults, we may want to change a number of those, and add other things such as:

  - Color, Border, BorderSize, DrawStyle, Skew, Angle, BorderColor, Opacity, and so-on, 
  
  while keeping the prototype as simple as 
  
  ```C++
  DrawBox(int x,int y, int size)
  ```
  
  only adding
  
  ```C++
  DrawBox(int x,int y,int size,const Args&... kwArgs)
  ```
  
  or
  ```C++
  DrawBox(int x,int y,int size,const ckw & keywords)
  ```
  
  depending on whether you use the Packed-Parameter or Object format of CKwargs.
  
  
## Keywords to the Rescue

With CKwargs, we can do the following, 

```C++
DrawBox(x,y,size,Color="red", Angle=75, Opacity=50)
```

choosing any keywords and placing them in any order, all without the keywords in the function prototype.

## A Note About Scoped Keywords vs. Unscoped Keywords

Note that the keywords in these examples are unscoped.  The default behavior for C++ is to scope keywords, such as:

```C++
DrawBox(x,y,size,kw::Color="red", kw::Angle=75, kw::Opacity=50)
```

Where `kw` is an arbitrarily-defined (i.e. you set it, not CKwargs) namespace, class, or struct to encapsulate the keywords in a localized scope.

It is easy to remove the scope by simply stating `using namespace kw`, either locally in the function or at the top of the
source file.

This document and much of the source-code documentation uses mostly unscoped examples for clarity of demonstration.

## Mutiple Types with the Same Keyword

The keywords can accept multiple types.  For example, the above color can be in the form of an Rgb Color, too:

```C++
DrawBox(x,y,size,Color=RgbColor(255,0,0), Angle=75, Opacity=50);
DrawBox(x,y,size,Color="red", Angle=75, Opacity=50);
DrawBox(x,y,size,Color=MyColor, Angle=75, Opacity=50);
```

are all acceptable, even though different types are used.

## Using CKwargs from the Called Function

From the function side of things, it is easy to use CKwargs.  There are two ways to use CKwargs, as a packed-paremeter or object.

### Packed-Parameter Usage (default usage)

The packed-parameter usage allows a true, canonical keyword style, and looks like this from the function's side, using DrawBox() as an example:

```C++
template<class... Args>
void DrawBox(int x,int y,int size,const Args&... args)
{
     auto keys = pkw::FillKeywords(); // Get a list of keyword pointers
     
     auto bBorder = ckw::Get(keys.Border,false); // Return keyword if used or false as default
     auto cColor = ckw::Get(keys.color)          // With no default, returns std::optional 
                                                 // with value or nullopt.
}
```

**_With this format, the interface is usually split into two components, where the keys are passed to the main function,
and the packed-parameter list is parsed in the interface, since this part of the code must be in the .h-file interface vs.
the source code (unless the call and function are in the same source body.)_**


## Object-Based version Usage

With an object-based version, things are simpler as the interface does not require a template:



```C++
void DrawBox(int x,int y,int size,const & ckw kwx)
{
     auto keys = kwx.FillKeywords(); // Get a list of keyword pointers

    // This is the only coding difference between the packed-parameter and passed object styles.
    // After the above statement, the code is exactly the same as the packed-parameter version
     
     auto bBorder = ckw::Get(keys.Border,false); // Return keyword if used or false as default
     auto cColor = ckw::Get(keys.color)          // With no default, returns std::optional 
                                                 // with value or nullopt
}
```

## Direct Access vs. Get() functions

`ckw::Get()` is an inline shortcut function and not required -- you can refer to the value directly, such as:

```C++
auto bBorder = keys.Border ? *keys.Border : false;
```

which is the equivalent of the original line:

```C++
auto bBorder = ckw::Get(keys.Border,false);  // Return keyword if used or false as default
```

Get() also has a form that will return a std::optional() when no default is given and C++17 support is turned on.

# Canonical Assigned Keywords vs. Function-Based Keywords (aka C++ named-parameter functions)


We are used to keywords being in the form of `keyword=assignment`, such as `AddBorder=true`. 

Function-Based keywords, such as `AddBorder()` or `AddBorder(true)` are the equivalent and can be more flexible and useful.

## Sagebox Example

With Sagebox (where CKwargs comes from), the canonical `keyword=assignment` format turned out to be limiting becuase Sagebox works to be self-evident and self-documenting, which can be an issue with assignment-based keywords.

It was also important with Sagebox to be able to use multiple parameters and multiple types to keep things easy and readable.  For example, a keyword like `Range` can use multiple forms such as `(int min,int max)`, or just `(int min)`, but also a `POINT`, or even a `std::array<int,2>`

With keywords, we can assign them as `Range = MyPoint` or `Range = { 1, 10 }`.   But there are a few issues here that function-based keywords eliminate:

- Keeping it simpler.  In the above example, we can use Range(MyPoint), Range(1,10), Range(5)' very simply.  As keywords grow and use more parameters, this makes using keywords a little easier.
- Doesn't require explicit true/false & can have default.  `AddBorder(true)` can become simply `AddBorder()` with a default set for true.  Any default may be used, which will tell the function the keyword is intended even if a value is not used.  With the assignment-based keywords (i.e. 'AddBorder=true') shortcut defaults can't be used.
- Intellisense Documentation.   With the assignment format, i.e. `Range = { 1,10 }`, entering the base namespace `Range =` will list all keyword members of the space, but won't list the protoypes - it will, though show any source-level documentation above the Range prototype
  - With function-based keywords, entering `Range(` will show all prototypes of the Range keyword, and once the intellisense understand what you are entering, it will
also show documentation on different forms. 
- Can get rid of the outer () in Object-Based Usage.  When using an object-based set of keywords (see [Packed-Parameters vs. Object (Class-Based) Keyword functions]() for more information), the other streaming overloads can be used other than the `,`, such as `AddBorder() << Range(1,10)`, removing the outer `()` required with the ',' usage (i.e. (AddBorder(), Range(1,10)).  
  - '+' and '|' can also be used, such as `AddBorder() + Range(1,10)`
    - I personally prefer the '|' format, so we go from 
    
    `MyFunction(123,(AddBorder(), Range(1,10)))` 
    
    to 
    
    `MyFunction(123,AddBorder() | Range(1,10))`
  
    While not the biggest deal, it can be nice to get rid of the outer `()` for clarity.



# Packed-Parameters vs. Object (Class-Based) Keyword functions

## Packed Parameters

Packed-Paremeter usage allows more true-style keyword usage, such as `MyFunction(123,AddBorder=true,Range={1,10})` which looks great and is nice and clean. 

It requires a function that is defined as a template, which will typically call the intended function after it resolves the keywords from the packed parameter.

i.e. 

```C++
template<class... Args>
void DrawBox(int x,int y,int size,const Args&... args)
{
   DrawBox(x,y,size,pkw::FillKeywords());
}
```

All-in-all, pretty simple, though it does mean separating the code, and the above needs to be in the interface (i.e. the .h file) so the compiler
can contruct the template as it compiled.

Basically, while nice to use, the templatized format can become a little abstract compared to using an object-based keyword format.


## Object-Based Keywords

With an object, we can simply define the function as 

```C++
void DrawBox(int x,int y,int size,const ckwargs::ckw & kwx)
{
    // << main function here >>
}
```

which is the function itself (i.e. the second function the packed-parameter-style called).

The downside is that the keywords must have a `()` surrounding the keyword stream, such as 

```C++
DrawBox(x,y,size,( AddBorder=true, Range = {1,10} ));
```

or when using the function-based keyword format, one of the following forms that do not require the outer `()`:

```C++
DrawBox(x,y,size,AddBorder() << Range(1,10));
DrawBox(x,y,size,AddBorder() + Range(1,10));
DrawBox(x,y,size,AddBorder() | Range(1,10));
```

any of which is acceptable.

### The main advantages of an object-based approach:

- The function can be called directly.  This makes it easier to program for larger scale projects.  Since the function template does not need to be in the interface, the function does not need to split into two parts, making it easier to write.
- Easier for intellisense.  Intellisense will always show the prototype, i.e. `void DrawBox(int x,int y,int size,const ckwargs::ckw & kwx)` where the intellisense will start showing the template format, which an be less clean in appearance.


## Requirements and Compiler Support

The only requirement is C++11 and above.

On the initial release, MSVC was used as the compiler and it has not been tested on GCC.

All code is standard C++11 or C++17 code (which can be turned off with a switch) and should compilder under GCC.
As people use the project, I am happy make sure it works fine on GCC and other comppilers, of if anyone wants to send me
an altered version with that support, I can update the repository.

### A Note About Compiler Warnings

In the code, there are MSC_VER ifdefs to remove SDL and struct C++ form options.  This is because MSVC (with /SDL on, which is usually a good
idea, at least in development) complains about uninitialized variables and other things.  This is purposely design into CKwargs to keep memory usage low and
processing faster, to allow keyword usage in real-time functions. 

These warnings are shut off, and the equivalent #pragmas may need to be added for other compilers. 


## C++ 11 and C++ 14 Support

CKwargs supports any C++ version from C++ 11 and forward.

However, some CKwarg functions make use of std::optional.

If your compiler does not support C++17, you can turn off `keyword_cpp17_support` in `keyclass.h` for C++11 and C++14 compatibility.


# Installation and Implementation

Installation is just the two files: `keyclass.cpp` and `keyclass.h`

The file `my_keywords.h` is an example file and is created by the program using CKwargs.

## Implementation

- Copy `ckwargs.cpp`,`ckwargs.h`, and `my_keydefs.h` into your project directory
- Edit `my_keydefs.h` to remove or change the example keywords (Range, AddBorder, etc.), placing your own keywords in the file
  - Also set the types for each keyword
  - `my_keydefs.h` contains 4 sample keywords.  See comments within on how to personalize it for your project.
- Creating Keywords in Code
  - For canonical keyword style (i.e. `AddBorder=true`): copy and edit `my_keywords.h` and `my_keywords.cpp` into the project.
  - For function-based keywords (i.e. `AddBorder()` or `AddBorder(true)`): copy and edit `my_keyfuncs.h` and `my_keyfunc.cpp`
  - Change the sample keyword namespaces (either `kw` or `kf`) to whatever desired (or just keep them the same name, `kw` is recommended)
    - These are declared as namespaces in the .h file, but can be a class or a struct 
    - The namespace is used to show in the examples unscoped keyword usage.  That's about the only advantage to using a namespace vs. a class or struct.
 
# MIT License

CKwargs is part of the Sagebox suite of open-source code.

CKWargs is distributed under the MIT License, with the title and copyright notice as:

`CKwargs -- Sagebox C++ Named Parameter Keywords and Functions`<br />
`Copyright (c) 2022 Rob Nelson.  All Rights Reserved.`

# Support

-- To be completed --
