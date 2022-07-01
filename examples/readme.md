
# CKwargs Example Projects

The examples show using named-parameters (i.e. keywords) in both keyword and function-based keyword forms.

They also show two different types of methodologies: 

## Packed Parameters

This is the general format, where you can use canonical keywords, such as

```C++
MyFunction(parm1,parm1,keyword1=value1,keyword2=value2) 
```

and so -forth.  Or, with function-based keywords: 

```C++
MyFunction(parm1,parm2,keyword1(value1),keyword(value2))
```

or 

```C++
MyFunction(parm1,parm2,keyword()) for keywords that have default parameters (useful with booleans)
```

### Object-Based Parameters

A second form uses a single object that contains a linked-list back to all keywords, and is formed as an object stream.

This type of keyword has some advantages including better intellisense lookup, no template code and more &ndash; see comments at bottom of text.

These are used exactly the same way as the packed parameters, with a () surrounding the keyword portion: 

for example,

```C++
MyFunction(parm1,parm1,( keyword1=value1,keyword2=value2) );
```

and so -forth.  In the case of function-based keywords:

```C++
MyFunction(parm1,parm2,( keyword1(value1),keyword(value2) ));
```

note that the function-based keywords can use <<, +, or | without the enclosing (), i.e.

```C++
MyFunction(parm1,parm2, keyword1(value1) << keyword(value2));
MyFunction(parm1,parm2, keyword1(value1) + keyword(value2));
MyFunction(parm1,parm2, keyword1(value1) | keyword(value2));
```

any of which work fine. 

# Packed-Parameter Examples

files: `simple_packed_functions.cpp` and `simple_packed_keywords.cpp`

These two examples show using canonical style keywords using a packed-parameter format.   
These have the advantage of using true keyword style keywords, and use a packed-parameter template.

These examples show a good form in creating an interface for the template, which then calls the actual
function that is a private member.

Examples:

```C++
MyFunction(parm1,parm2,AddBorder=true, Range = { 1,10 }, ExtraText="Hello World");
```
	
or
	
```C++
MyFunction(parm1,parm2,AddBorder(),Range(1,10),ExtraText("Hello World"));
```

# Object-Based Examples

files: `simple_streamed_functions.cpp` and `simple_streamed_keywords.cpp`

These examples show using a streamed-object format, which is exactly the same as the packed-parameter format 
except that the keyword part of the function call must be enclosed in "()", or in the case of function-based
keywords, can be separated by "<<", "+", and "|" rather than a "," without the enclosing "()".

#### The Streamed Object format has a number of advantages:

* There is no template code
* The function can be called directly without being in the interface
   * (i.e. the prototype only need exist, where in the packed-parameter format, some template code must exist in the interface)

* Intellisense will show all forms of the keyword functions and which parameters they take.
   * With the packed-parameter format, the intellisense will only show the function name, and the programmer must know or assume the types that will be accepted.

