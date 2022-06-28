# CKwargs
C++ True Named-Parameter Keywords and Named-Parameter Functions

### (In-Progress Version)

```C++
DrawBox(x,y,size,Color=RgbColor(255,0,0), Angle=75, Opacity=50);
```
CKwargs is a light, efficient class to enable using canonical keywords (aka named-parameters) in C++, such as with the above example. 

## Table of Contents
- [Keywords are Necessary in Today's Projects](#keywords-are-necessary-in-todays-projects)
- [DrawBox(int ix,int y,int size) example](#drawboxint-ixint-yint-size-example)
  - [Keywords to the Rescue](#keywords-to-the-rescue)
- [A Note About Scoped Variables](#a-note-about-scoped-keywords)
- [Mutiple Types with the Same Keyword](#mutiple-types-with-the-same-keyword)
- [Using CKwargs from the Called Function](#using-ckwargs-from-the-called-function)
  - [Packed-Parameter Usage (default usage)](#packed-parameter-usage-default-usage)
   -[Object-Based version Usage](#object-based-version-usage)
- [C++17 (std::optional)](#c17-stdoptional)
- [Direct Access vs. Get() functions](#direct-access-vs-get-functions)
 
## Other Items
- [Function-Based Keywords (aka C++ named-parameter functions)](#function-based-keywords-aka-c-named-parameter-functions)
- [Packed-Parameters vs. Stream-Object Keyword formats](#packed-parameters-vs-stream-object-keyword-formats)
  - [Packed-Parameters](#packed-parameters)
  - [Stream-Object Format](#stream-object-format)
- [Intallation and Implementation](#installation-and-implementation)
- [License](#license)
- [Support](#support)


## Keywords are Necessary in Today's Projects

Keywords in programming and using functions in C++ are becoming much more important and necessary.  Sadly, C++ has still to adopt a named-parameter/keyword format, 
and there doesn't appear to be one on the horizon.

## DrawBox(int ix,int y,int size) example

Lets say we want to draw a square, but want to have a lot of power behind it, but don't want to put a large number of options in the protoype, or, worse,
have to create a "DrawBox" object and make a number of calls end then "show" the Box.  We want to affect the box options and attributes on the call, so it can perform
these tasks before it created the box, completely obviating the need to return an object of anything at all

While the Box has its defaults, we may want to change a number of those, and add other things such as:

  Color, Border, BorderSize, DrawStyle, Skew, Angle, BorderColor, Opacity, and so-on, 
  
  while keeping the prototype as simple as 
  
  DrawBox(int x,int y, int size)
  
  only adding
  
  ```C++
  DrawBox(int x,int y,int size,const Args&... kwArgs)
  ```
  
  of
  ```C++
  DrawBox(int x,int y,int size,const ckw & keywords)
  ```
  
  depending on whether you use the Packed-Parameter or Streamed-Object format of CKwargs.
  
  
## Keywords to the Rescue

With CKwargs, we can do the following, 

```C++
DrawBox(x,y,size,Color="red", Angle=75, Opacity=50)
```

choosing any keywords and placing them in any order, all without any of the keyword in the function prototype.

## A Note about Scoped Keywords

Note that the keywords are unscoped.  The default behavior for CKwarhgs is scope, such as:

```C++
DrawBox(x,y,size,kw::Color="red", kw::Angle=75, kw::Opacity=50)
```

Where kw is an arbitrarily-defined (i.e. you set it, not CKwargs) namespace, class, or struct to encapsulate they keywords in a localize scope.

It is easy to remove the scope by simply stating 'using namespace kw', , either locally in the function or at the top of the
source file.

This document uses mostly unscoped examples for clarity of demonstration.

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

The packed-paremeter usage allows a true, canonical keyword style, and looks like this from the function's side, using DrawBox() as an example:

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

## C++17 (std::optional)

If your compiler does not support C++17 for C++11 and C++14 compatibility.

## Direct Access vs. Get() functions

ckw::Get() is an inline shortcut function and not required -- you can turn off the optional support and refer to the 
value directly, such as:

```C++
auto bBorder = keys.Border ? *keys.Border : false;
```

which is the equivalent of the original line:

```C++
auto bBorder = ckw::Get(keys.Border,false);  // Return keyword if used or false as default
```

Get() also has a form that will return a std::optional() when no defsault is given and C++17 support is turned on.

# Function-Based Keywords (aka C++ named-parameter functions)

-- To be completed --

# Packed-Parameters vs. Stream-Object Keyword formats

-- To be completed --

## Packed-Parameters

-- To be completed --

## Stream-Object Format

-- To be completed --

# Installation and Implementation

Installation is just the two files: `keyclass.cpp` and `keyclass.h`

The file `my_keywords.h` is an example file and is created by the program using CKwargs.

## Implementation

- Copy `keyclass.cpp` and `keyclass.h` into your project directory
- Edit `keyclass.h` to remove or change the example keywords (Range, AddBorder, etc.), placing your own keywords in the file
  - Also set the types for each keyword
- use `my_keywords.h` to create your own keyword code to parse the keywords, using either the canonical keyword method (in the kw namespace) or the function-based keyword format (in the kf namespace)
  - only one namespace is typically used, depending on the style you choose, although both styles can be used simultaneously
  - namespaces can also be classes or structs.  As a namespace, you can unscope the keywords for cleaner usage (i.e. AddBorder=true vs. kw::AddBorder=true)
    - This is the only advantage to using a namespace vs. a class or struct.
    - Note that the examples have static in front of the functions.  This will cause duplicated code when multiple source files bring in the `my_keywords.h` file.
      - Move the code to a separate C++ file to avoid duplicate code
      - The code itself is small, so it is not required when mulitple files use `my_keywords.h`, and it can be easier to let the duplicated code exist during the design phase and/or until a refactoring step to avoid extra work until the design is solidified.
  - the namespace are arbitrary names and can be named anything you liked, and can also be put into any scope you wish, such as within a class (as classes or structs vs. namespaces)

As many keywords sets as desired may be used with different namespace/classes as shown in my_keywords.h, allowing different modules to use different and unique keywords without overlap.

# License

CKwargs is part of the Sagebox suite of open-source code.

CKWargs is distributed under the MIT License, with the title and copyright notice as:

`CKwargs -- Sagebox C++ Named Parameter Keywords and Functions`<br />
`Copyright (c) 2022 Rob Nelson.  All Rights Reserved.`

# Support

-- To be completed --
