# CKwargs
C++ True Named-Parameter Keywords and Name-Parameter Functions

### (In-Progress Version)

```C++
DrawBox(x,y,size,Color=RgbColor(255,0,0), Angle=75, Opacity=50);
```
CKwargs is a light, efficient class to enable using canonical keywords (aka named-parameters) in C++, such as with the above example. 

## Table of Contents
- [Keywords are Necessary in Today's Projects]()
- [DrawBox(int ix,int y,int size) example]()
  - [Keywords to the Rescue]()
- [A Note About Scoped Variables]()
- [Mutiple Types with the Same Keyword]()
- [Using CKwargs from the Called Function]()
  - [Packed-Parameter Usage (default usage)]()
   -[Object-Based version Usage]()
- [C++17 (std::optional)]()
- [Direct Access vs. Get() functions]()
 
## Other Items
- [Function-Based Keywords (aka C++ named-parameter functions)]()
- [Intallation]()
- [License]()
- [Support]()


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
     auto cColor = ckw::Get(keys.color)          // With no default, returns std::optional with value or nullopt.
     
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
     auto cColor = ckw::Get(keys.color)          // With no default, returns std::optional with value or nullopt
}
```

## C++17 (std::optional)

If your compiler does not support C++17 for C++11 and C++14 compatibility.

## Direct Access vs. Get() functions

ckw::Get() is an inline shortcut function and not required -- you can turn off the optional support and refer to the 
value directly, such as:

```C++
auto bBorder = keys.Border() ? *keys.Border : false;
```

which is the equivalent of the original line:

```C++
auto bBorder = ckw::Get(keys.Border,false);  // Return keyword if used or false as default
```

Get() also has a form that will return a std::optional() when no defsault is given and C++17 support is turned on.




