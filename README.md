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







