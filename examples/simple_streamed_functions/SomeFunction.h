#pragma once

#include <stdio.h>
#include "ckwargs.h"

// Prototype for example function using CKWargs.
// 
// Note that ckw defaults to an empty ckw() so that the calling function
// does not need to specify keywords()
//
void SomeFunction(const char * sTitle, const ckwargs::ckw & kwx = ckwargs::ckw());

